#!/usr/bin/env python3

# Copyright 2020 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# pylint: disable=line-too-long
"""Runs unit tests on device and displays the results.

This script assumes you have a ~/.servodrc config file with a line that
corresponds to the board being tested.

See https://chromium.googlesource.com/chromiumos/third_party/hdctools/+/HEAD/docs/servo.md#servodrc

In addition to running this script locally, you can also run it from a remote
machine against a board connected to a local machine. For example:

Start servod and JLink locally:

(local chroot) $ sudo servod --board dragonclaw
(local chroot) $ JLinkRemoteServerCLExe -select USB

Forward the FPMCU console on a TCP port:

(local chroot) $ socat $(dut-control raw_fpmcu_console_uart_pty | cut -d: -f2) \
                 tcp4-listen:10000,fork

Forward all the ports to the remote machine:

(local outside) $ ssh -R 9999:localhost:9999 <remote> -N
(local outside) $ ssh -R 10000:localhost:10000 <remote> -N
(local outside) $ ssh -R 19020:localhost:19020 <remote> -N

Run the script on the remote machine:

(remote chroot) ./test/run_device_tests.py --remote 127.0.0.1 \
                --jlink_port 19020 --console_port 10000
"""
# pylint: enable=line-too-long

import argparse
import concurrent
import io
import logging
import os
import re
import socket
import subprocess
import sys
import time
from concurrent.futures.thread import ThreadPoolExecutor
from enum import Enum
from pathlib import Path
from typing import Optional, BinaryIO, List

# pylint: disable=import-error
import colorama  # type: ignore[import]
from contextlib2 import ExitStack
import fmap
# pylint: enable=import-error

EC_DIR = Path(os.path.dirname(os.path.realpath(__file__))).parent
JTRACE_FLASH_SCRIPT = os.path.join(EC_DIR, 'util/flash_jlink.py')
SERVO_MICRO_FLASH_SCRIPT = os.path.join(EC_DIR, 'util/flash_ec')

ALL_TESTS_PASSED_REGEX = re.compile(r'Pass!\r\n')
ALL_TESTS_FAILED_REGEX = re.compile(r'Fail! \(\d+ tests\)\r\n')

SINGLE_CHECK_PASSED_REGEX = re.compile(r'Pass: .*')
SINGLE_CHECK_FAILED_REGEX = re.compile(r'.*failed:.*')

ASSERTION_FAILURE_REGEX = re.compile(r'ASSERTION FAILURE.*')

DATA_ACCESS_VIOLATION_8020000_REGEX = re.compile(
    r'Data access violation, mfar = 8020000\r\n')
DATA_ACCESS_VIOLATION_8040000_REGEX = re.compile(
    r'Data access violation, mfar = 8040000\r\n')
DATA_ACCESS_VIOLATION_80C0000_REGEX = re.compile(
    r'Data access violation, mfar = 80c0000\r\n')
DATA_ACCESS_VIOLATION_80E0000_REGEX = re.compile(
    r'Data access violation, mfar = 80e0000\r\n')
DATA_ACCESS_VIOLATION_20000000_REGEX = re.compile(
    r'Data access violation, mfar = 20000000\r\n')
DATA_ACCESS_VIOLATION_24000000_REGEX = re.compile(
    r'Data access violation, mfar = 24000000\r\n')

BLOONCHIPPER = 'bloonchipper'
DARTMONKEY = 'dartmonkey'

JTRACE = 'jtrace'
SERVO_MICRO = 'servo_micro'

GCC = 'gcc'
CLANG = 'clang'

TEST_ASSETS_BUCKET = 'gs://chromiumos-test-assets-public/fpmcu/RO'
DARTMONKEY_IMAGE_PATH = os.path.join(
    TEST_ASSETS_BUCKET, 'dartmonkey_v2.0.2887-311310808.bin')
NOCTURNE_FP_IMAGE_PATH = os.path.join(
    TEST_ASSETS_BUCKET, 'nocturne_fp_v2.2.64-58cf5974e.bin')
NAMI_FP_IMAGE_PATH = os.path.join(
    TEST_ASSETS_BUCKET, 'nami_fp_v2.2.144-7a08e07eb.bin')
BLOONCHIPPER_V4277_IMAGE_PATH = os.path.join(
    TEST_ASSETS_BUCKET, 'bloonchipper_v2.0.4277-9f652bb3.bin')
BLOONCHIPPER_V5938_IMAGE_PATH = os.path.join(
    TEST_ASSETS_BUCKET, 'bloonchipper_v2.0.5938-197506c1.bin')


class ImageType(Enum):
    """EC Image type to use for the test."""
    RO = 1
    RW = 2


class BoardConfig:
    """Board-specific configuration."""

    def __init__(self, name, servo_uart_name, servo_power_enable,
                 rollback_region0_regex, rollback_region1_regex, mpu_regex,
                 variants):
        self.name = name
        self.servo_uart_name = servo_uart_name
        self.servo_power_enable = servo_power_enable
        self.rollback_region0_regex = rollback_region0_regex
        self.rollback_region1_regex = rollback_region1_regex
        self.mpu_regex = mpu_regex
        self.variants = variants


class TestConfig:
    """Configuration for a given test."""

    def __init__(self, test_name, image_to_use=ImageType.RW,
                 finish_regexes=None, fail_regexes=None, toggle_power=False,
                 test_args=None, num_flash_attempts=2, timeout_secs=10,
                 enable_hw_write_protect=False, ro_image=None, build_board=None,
                 config_name=None):
        if test_args is None:
            test_args = []
        if finish_regexes is None:
            finish_regexes = [ALL_TESTS_PASSED_REGEX, ALL_TESTS_FAILED_REGEX]
        if fail_regexes is None:
            fail_regexes = [SINGLE_CHECK_FAILED_REGEX, ALL_TESTS_FAILED_REGEX,
                            ASSERTION_FAILURE_REGEX]
        if config_name is None:
            config_name = test_name

        self.test_name = test_name
        self.config_name = config_name
        self.image_to_use = image_to_use
        self.finish_regexes = finish_regexes
        self.fail_regexes = fail_regexes
        self.test_args = test_args
        self.toggle_power = toggle_power
        self.num_flash_attempts = num_flash_attempts
        self.timeout_secs = timeout_secs
        self.enable_hw_write_protect = enable_hw_write_protect
        self.logs = []
        self.passed = False
        self.num_fails = 0
        self.num_passes = 0
        self.ro_image = ro_image
        self.build_board = build_board


# All possible tests.
class AllTests:
    """All possible tests."""

    @staticmethod
    def get(board_config: BoardConfig) -> List[TestConfig]:
        public_tests = AllTests.get_public_tests(board_config)
        private_tests = AllTests.get_private_tests()

        return public_tests + private_tests

    @staticmethod
    def get_public_tests(board_config: BoardConfig) -> List[TestConfig]:
        tests = [
            TestConfig(test_name='aes'),
            TestConfig(test_name='cec'),
            TestConfig(test_name='cortexm_fpu'),
            TestConfig(test_name='crc'),
            TestConfig(test_name='flash_physical', image_to_use=ImageType.RO,
                       toggle_power=True),
            TestConfig(test_name='flash_write_protect',
                       image_to_use=ImageType.RO,
                       toggle_power=True, enable_hw_write_protect=True),
            TestConfig(test_name='fpsensor_hw'),
            TestConfig(config_name='fpsensor_spi_ro', test_name='fpsensor',
                       image_to_use=ImageType.RO, test_args=['spi']),
            TestConfig(config_name='fpsensor_spi_rw', test_name='fpsensor',
                       test_args=['spi']),
            TestConfig(config_name='fpsensor_uart_ro', test_name='fpsensor',
                       image_to_use=ImageType.RO, test_args=['uart']),
            TestConfig(config_name='fpsensor_uart_rw', test_name='fpsensor',
                       test_args=['uart']),
            TestConfig(config_name='mpu_ro', test_name='mpu',
                       image_to_use=ImageType.RO,
                       finish_regexes=[board_config.mpu_regex]),
            TestConfig(config_name='mpu_rw', test_name='mpu',
                       finish_regexes=[board_config.mpu_regex]),
            TestConfig(test_name='mutex'),
            TestConfig(test_name='pingpong'),
            TestConfig(test_name='printf'),
            TestConfig(test_name='queue'),
            TestConfig(config_name='rollback_region0', test_name='rollback',
                       finish_regexes=[board_config.rollback_region0_regex],
                       test_args=['region0']),
            TestConfig(config_name='rollback_region1', test_name='rollback',
                       finish_regexes=[board_config.rollback_region1_regex],
                       test_args=['region1']),
            TestConfig(test_name='rollback_entropy', image_to_use=ImageType.RO),
            TestConfig(test_name='rtc'),
            TestConfig(test_name='sha256'),
            TestConfig(test_name='sha256_unrolled'),
            TestConfig(test_name='static_if'),
            TestConfig(config_name='system_is_locked_wp_on',
                       test_name='system_is_locked', test_args=['wp_on'],
                       toggle_power=True, enable_hw_write_protect=True),
            TestConfig(config_name='system_is_locked_wp_off',
                       test_name='system_is_locked', test_args=['wp_off'],
                       toggle_power=True, enable_hw_write_protect=False),
            TestConfig(test_name='timer_dos'),
            TestConfig(test_name='utils', timeout_secs=20),
            TestConfig(test_name='utils_str'),
        ]

        if board_config.name == BLOONCHIPPER:
            tests.append(TestConfig(test_name='stm32f_rtc'))

        # Run panic data tests for all boards and RO versions.
        for variant_name, variant_info in board_config.variants.items():
            tests.append(
                TestConfig(config_name='panic_data_' + variant_name,
                           test_name='panic_data',
                           fail_regexes=[SINGLE_CHECK_FAILED_REGEX,
                                         ALL_TESTS_FAILED_REGEX],
                           ro_image=variant_info.get('ro_image_path'),
                           build_board=variant_info.get('build_board')))

        return tests

    @staticmethod
    def get_private_tests() -> List[TestConfig]:
        # Return all private tests, if the folder exists
        tests = []
        try:
            current_dir = os.path.dirname(__file__)
            private_dir = os.path.join(current_dir, os.pardir, 'private/test')
            have_private = os.path.isdir(private_dir)
            if not have_private:
                return []
            sys.path.append(private_dir)
            import private_tests  # pylint: disable=import-error
            for test_args in private_tests.tests:
                tests.append(TestConfig(**test_args))
        # Catch all exceptions to avoid disruptions in public repo
        except BaseException as e:
            logging.debug('Failed to get list of private tests: %s', str(e))
            logging.debug('Ignore error and continue.')
            return []
        return tests


BLOONCHIPPER_CONFIG = BoardConfig(
    name=BLOONCHIPPER,
    servo_uart_name='raw_fpmcu_console_uart_pty',
    servo_power_enable='fpmcu_pp3300',
    rollback_region0_regex=DATA_ACCESS_VIOLATION_8020000_REGEX,
    rollback_region1_regex=DATA_ACCESS_VIOLATION_8040000_REGEX,
    mpu_regex=DATA_ACCESS_VIOLATION_20000000_REGEX,
    variants={
        'bloonchipper_v2.0.4277': {
            'ro_image_path': BLOONCHIPPER_V4277_IMAGE_PATH
        },
        'bloonchipper_v2.0.5938': {
            'ro_image_path': BLOONCHIPPER_V5938_IMAGE_PATH
        }
    }
)

DARTMONKEY_CONFIG = BoardConfig(
    name=DARTMONKEY,
    servo_uart_name='raw_fpmcu_console_uart_pty',
    servo_power_enable='fpmcu_pp3300',
    rollback_region0_regex=DATA_ACCESS_VIOLATION_80C0000_REGEX,
    rollback_region1_regex=DATA_ACCESS_VIOLATION_80E0000_REGEX,
    mpu_regex=DATA_ACCESS_VIOLATION_24000000_REGEX,
    # For dartmonkey board, run panic data test also on nocturne_fp and
    # nami_fp boards with appropriate RO image.
    variants={
        'dartmonkey_v2.0.2887': {
            'ro_image_path': DARTMONKEY_IMAGE_PATH
        },
        'nocturne_fp_v2.2.64': {
            'ro_image_path': NOCTURNE_FP_IMAGE_PATH,
            'build_board': 'nocturne_fp'
        },
        'nami_fp_v2.2.144': {
            'ro_image_path': NAMI_FP_IMAGE_PATH,
            'build_board': 'nami_fp'
        }
    }
)

BOARD_CONFIGS = {
    'bloonchipper': BLOONCHIPPER_CONFIG,
    'dartmonkey': DARTMONKEY_CONFIG,
}


def read_file_gsutil(path: str) -> bytes:
    """Get data from bucket, using gsutil tool"""
    cmd = ['gsutil', 'cat', path]

    logging.debug('Running command: "%s"', ' '.join(cmd))
    gsutil = subprocess.run(cmd, stdout=subprocess.PIPE)  # pylint: disable=subprocess-run-check
    gsutil.check_returncode()

    return gsutil.stdout


def find_section_offset_size(section: str, image: bytes) -> (int, int):
    """Get offset and size of the section in image"""
    areas = fmap.fmap_decode(image)['areas']
    area = next(area for area in areas if area['name'] == section)
    return area['offset'], area['size']


def read_section(src: bytes, section: str) -> bytes:
    """Read FMAP section content into byte array"""
    (src_start, src_size) = find_section_offset_size(section, src)
    src_end = src_start + src_size
    return src[src_start:src_end]


def write_section(data: bytes, image: bytearray, section: str):
    """Replace the specified section in image with the contents of data"""
    (section_start, section_size) = find_section_offset_size(section, image)

    if section_size < len(data):
        raise ValueError(section + ' section size is not enough to store data')

    section_end = section_start + section_size
    filling = bytes([0xff for _ in range(section_size - len(data))])

    image[section_start:section_end] = data + filling


def copy_section(src: bytes, dst: bytearray, section: str):
    """Copy section from src image to dst image"""
    (src_start, src_size) = find_section_offset_size(section, src)
    (dst_start, dst_size) = find_section_offset_size(section, dst)

    if dst_size < src_size:
        raise ValueError('Section ' + section + ' from source image has '
                         'greater size than the section in destination image')

    src_end = src_start + src_size
    dst_end = dst_start + dst_size
    filling = bytes([0xff for _ in range(dst_size - src_size)])

    dst[dst_start:dst_end] = src[src_start:src_end] + filling


def replace_ro(image: bytearray, ro: bytes):
    """Replace RO in image with provided one"""
    # Backup RO public key since its private part was used to sign RW.
    ro_pubkey = read_section(image, 'KEY_RO')

    # Copy RO part of the firmware to the image. Please note that RO public key
    # is copied too since EC_RO area includes KEY_RO area.
    copy_section(ro, image, 'EC_RO')

    # Restore RO public key.
    write_section(ro_pubkey, image, 'KEY_RO')


def get_console(board_config: BoardConfig) -> Optional[str]:
    """Get the name of the console for a given board."""
    cmd = [
        'dut-control',
        board_config.servo_uart_name,
    ]
    logging.debug('Running command: "%s"', ' '.join(cmd))

    with subprocess.Popen(cmd, stdout=subprocess.PIPE) as proc:
        for line in io.TextIOWrapper(proc.stdout):  # type: ignore[arg-type]
            logging.debug(line)
            pty = line.split(':')
            if len(pty) == 2 and pty[0] == board_config.servo_uart_name:
                return pty[1].strip()

    return None


def power(board_config: BoardConfig, on: bool) -> None:
    """Turn power to board on/off."""
    if on:
        state = 'pp3300'
    else:
        state = 'off'

    cmd = [
        'dut-control',
        board_config.servo_power_enable + ':' + state,
    ]
    logging.debug('Running command: "%s"', ' '.join(cmd))
    subprocess.run(cmd).check_returncode()  # pylint: disable=subprocess-run-check


def hw_write_protect(enable: bool) -> None:
    """Enable/disable hardware write protect."""
    if enable:
        state = 'force_on'
    else:
        state = 'force_off'

    cmd = [
        'dut-control',
        'fw_wp_state:' + state,
        ]
    logging.debug('Running command: "%s"', ' '.join(cmd))
    subprocess.run(cmd).check_returncode()  # pylint: disable=subprocess-run-check


def build(test_name: str, board_name: str, compiler: str) -> None:
    """Build specified test for specified board."""
    cmd = ['make']

    if compiler == CLANG:
        cmd = cmd + ['CC=arm-none-eabi-clang']

    cmd = cmd + [
        'BOARD=' + board_name,
        'test-' + test_name,
        '-j',
    ]

    logging.debug('Running command: "%s"', ' '.join(cmd))
    subprocess.run(cmd).check_returncode()  # pylint: disable=subprocess-run-check


def flash(image_path: str, board: str, flasher: str, remote_ip: str,
          remote_port: int) -> bool:
    """Flash specified test to specified board."""
    logging.info('Flashing test')

    cmd = []
    if flasher == JTRACE:
        cmd.append(JTRACE_FLASH_SCRIPT)
        if remote_ip:
            cmd.extend(['--remote', remote_ip + ':' + str(remote_port)])
    elif flasher == SERVO_MICRO:
        cmd.append(SERVO_MICRO_FLASH_SCRIPT)
    else:
        logging.error('Unknown flasher: "%s"', flasher)
        return False
    cmd.extend([
        '--board', board,
        '--image', image_path,
    ])
    logging.debug('Running command: "%s"', ' '.join(cmd))
    completed_process = subprocess.run(cmd)  # pylint: disable=subprocess-run-check
    return completed_process.returncode == 0


def patch_image(test: TestConfig, image_path: str):
    """Replace RO part of the firmware with provided one."""
    with open(image_path, 'rb+') as f:
        image = bytearray(f.read())
        ro = read_file_gsutil(test.ro_image)
        replace_ro(image, ro)
        f.seek(0)
        f.write(image)
        f.truncate()


def readline(executor: ThreadPoolExecutor, f: BinaryIO, timeout_secs: int) -> \
             Optional[bytes]:
    """Read a line with timeout."""
    a = executor.submit(f.readline)
    try:
        return a.result(timeout_secs)
    except concurrent.futures.TimeoutError:
        return None


def readlines_until_timeout(executor, f: BinaryIO, timeout_secs: int) -> \
                            List[bytes]:
    """Continuously read lines for timeout_secs."""
    lines: List[bytes] = []
    while True:
        line = readline(executor, f, timeout_secs)
        if not line:
            return lines
        lines.append(line)


def process_console_output_line(line: bytes, test: TestConfig):
    try:
        line_str = line.decode()

        if SINGLE_CHECK_PASSED_REGEX.match(line_str):
            test.num_passes += 1

        for regex in test.fail_regexes:
            if regex.match(line_str):
                test.num_fails += 1
                break

        return line_str
    except UnicodeDecodeError:
        # Sometimes we get non-unicode from the console (e.g., when the
        # board reboots.) Not much we can do in this case, so we'll just
        # ignore it.
        return None


def run_test(test: TestConfig, console: io.FileIO,
             executor: ThreadPoolExecutor) -> bool:
    """Run specified test."""
    start = time.time()

    # Wait for boot to finish
    time.sleep(1)
    console.write('\n'.encode())
    if test.image_to_use == ImageType.RO:
        console.write('reboot ro\n'.encode())
        time.sleep(1)

    test_cmd = 'runtest ' + ' '.join(test.test_args) + '\n'
    console.write(test_cmd.encode())

    while True:
        console.flush()
        line = readline(executor, console, 1)
        if not line:
            now = time.time()
            if now - start > test.timeout_secs:
                logging.debug('Test timed out')
                return False
            continue

        logging.debug(line)
        test.logs.append(line)
        # Look for test_print_result() output (success or failure)
        line_str = process_console_output_line(line, test)
        if line_str is None:
            # Sometimes we get non-unicode from the console (e.g., when the
            # board reboots.) Not much we can do in this case, so we'll just
            # ignore it.
            continue

        for r in test.finish_regexes:
            if r.match(line_str):
                # flush read the remaining
                lines = readlines_until_timeout(executor, console, 1)
                logging.debug(lines)
                test.logs.append(lines)

                for line in lines:
                    process_console_output_line(line, test)

                return test.num_fails == 0


def get_test_list(config: BoardConfig, test_args) -> List[TestConfig]:
    """Get a list of tests to run."""
    if test_args == 'all':
        return AllTests.get(config)

    test_list = []
    for t in test_args:
        logging.debug('test: %s', t)
        test_regex = re.compile(t)
        tests = [test for test in AllTests.get(config)
                 if test_regex.fullmatch(test.config_name)]
        if not tests:
            logging.error('Unable to find test config for "%s"', t)
            sys.exit(1)
        test_list += tests

    return test_list


def parse_remote_arg(remote: str) -> str:
    if not remote:
        return ''

    try:
        ip = socket.gethostbyname(remote)
        return ip
    except socket.gaierror:
        logging.error('Failed to resolve host "%s".', remote)
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser()

    default_board = 'bloonchipper'
    parser.add_argument(
        '--board', '-b',
        help='Board (default: ' + default_board + ')',
        default=default_board)

    default_tests = 'all'
    parser.add_argument(
        '--tests', '-t',
        nargs='+',
        help='Tests (default: ' + default_tests + ')',
        default=default_tests)

    log_level_choices = ['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL']
    parser.add_argument(
        '--log_level', '-l',
        choices=log_level_choices,
        default='DEBUG'
    )

    flasher_choices = [SERVO_MICRO, JTRACE]
    parser.add_argument(
        '--flasher', '-f',
        choices=flasher_choices,
        default=JTRACE
    )

    compiler_options = [GCC, CLANG]
    parser.add_argument('--compiler', '-c',
                        choices=compiler_options,
                        default=GCC)

    # This might be expanded to serve as a "remote" for flash_ec also, so
    # we will leave it generic.
    parser.add_argument(
        '--remote', '-n',
        help='The remote host connected to one or both of: J-Link and Servo.',
    )

    parser.add_argument('--jlink_port', '-j',
                        type=int,
                        help='The port to use when connecting to JLink.')
    parser.add_argument('--console_port', '-p',
                        type=int,
                        help='The port connected to the FPMCU console.')

    args = parser.parse_args()
    logging.basicConfig(level=args.log_level)

    if args.jlink_port and not args.flasher == JTRACE:
        logging.error('jlink_port specified, but flasher is not set to J-Link.')
        sys.exit(1)

    if args.remote and not (args.jlink_port or args.console_port):
        logging.error('jlink_port or console_port must be specified when using '
                      'the remote option.')
        sys.exit(1)

    if (args.jlink_port or args.console_port) and not args.remote:
        logging.error('The remote option must be specified when using the '
                      'jlink_port or console_port options.')
        sys.exit(1)

    if args.board not in BOARD_CONFIGS:
        logging.error('Unable to find a config for board: "%s"', args.board)
        sys.exit(1)

    board_config = BOARD_CONFIGS[args.board]

    remote_ip = parse_remote_arg(args.remote)

    e = ThreadPoolExecutor(max_workers=1)

    test_list = get_test_list(board_config, args.tests)
    logging.debug(
        'Running tests: %s', [
            test.config_name for test in test_list])

    for test in test_list:
        build_board = args.board
        # If test provides this information, build image for board specified
        # by test.
        if test.build_board is not None:
            build_board = test.build_board

        # build test binary
        build(test.test_name, build_board, args.compiler)

        image_path = os.path.join(EC_DIR, 'build', build_board, test.test_name,
                                  test.test_name + '.bin')

        if test.ro_image is not None:
            try:
                patch_image(test, image_path)
            except Exception as exception:
                logging.warning('An exception occurred while patching '
                                'image: %s', exception)
                test.passed = False
                continue

        # flash test binary
        # TODO(b/158327221): First attempt to flash fails after
        #  flash_write_protect test is run; works after second attempt.
        flash_succeeded = False
        for i in range(0, test.num_flash_attempts):
            logging.debug('Flash attempt %d', i + 1)
            if flash(image_path, args.board, args.flasher, remote_ip,
                     args.jlink_port):
                flash_succeeded = True
                break
            time.sleep(1)

        if not flash_succeeded:
            logging.debug('Flashing failed after max attempts: %d',
                          test.num_flash_attempts)
            test.passed = False
            continue

        if test.toggle_power:
            power(board_config, on=False)
            time.sleep(1)
            power(board_config, on=True)

        hw_write_protect(test.enable_hw_write_protect)

        # run the test
        logging.info('Running test: "%s"', test.config_name)

        with ExitStack() as stack:
            if remote_ip and args.console_port:
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((remote_ip, args.console_port))
                console = stack.enter_context(
                    s.makefile(mode='rwb', buffering=0))
            else:
                console = stack.enter_context(
                    open(get_console(board_config), 'wb+', buffering=0))

            test.passed = run_test(test, console, executor=e)

    colorama.init()
    exit_code = 0
    for test in test_list:
        # print results
        print('Test "' + test.config_name + '": ', end='')
        if test.passed:
            print(colorama.Fore.GREEN + 'PASSED')
        else:
            print(colorama.Fore.RED + 'FAILED')
            exit_code = 1

        print(colorama.Style.RESET_ALL)

    e.shutdown(wait=False)
    sys.exit(exit_code)


if __name__ == '__main__':
    sys.exit(main())
