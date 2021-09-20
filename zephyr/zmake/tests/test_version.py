# Copyright 2021 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import datetime
import subprocess
import unittest.mock as mock

import pytest

import zmake.project
import zmake.version as version


def _git_init(repo):
    """Create a new git repository."""
    repo.mkdir()
    subprocess.run(
        ["git", "-c", "init.defaultBranch=main", "-C", repo, "init"], check=True
    )


def _git_add(repo, path, contents="example!\n"):
    """Write contents and stage a file."""
    path.write_text(contents)
    subprocess.run(["git", "-C", repo, "add", path], check=True)


def _git_commit(repo, message="message!"):
    env = {
        "GIT_AUTHOR_NAME": "Alyssa P. Hacker",
        "GIT_AUTHOR_EMAIL": "aphacker@example.org",
        "GIT_AUTHOR_DATE": "Thu, 07 Apr 2005 22:13:13 +0200",
        "GIT_COMMITTER_NAME": "Ben Bitdiddle",
        "GIT_COMMITTER_EMAIL": "bitdiddle@example.org",
        "GIT_COMMITTER_DATE": "Tue, 30 Aug 2005 10:50:30 -0700",
    }
    subprocess.run(["git", "-C", repo, "commit", "-m", message], check=True, env=env)


def _setup_example_repos(tmp_path):
    """Setup temporary project, zephyr base, and module repos.

    Args:
        tmp_path: Directory to set up files in.

    Returns:
        A 3-tuple of project, zephyr_base, modules_dict.
    """
    project_path = tmp_path / "prj"
    project_path.mkdir()

    project = zmake.project.Project(
        project_path,
        config_dict={
            "board": "foo",
            "output-type": "raw",
            "supported-toolchains": ["coreboot-sdk"],
            "supported-zephyr-versions": ["v2.6"],
        },
    )
    # Has one commit.
    zephyr_base = tmp_path / "zephyr_base"
    _git_init(zephyr_base)
    _git_add(
        zephyr_base,
        zephyr_base / "VERSION",
        "VERSION_MAJOR=2\nVERSION_MINOR=6\nPATCHLEVEL=99\n",
    )
    _git_commit(zephyr_base, "Added version file")

    # Has one commit.
    mod1 = tmp_path / "mod1"
    _git_init(mod1)
    _git_add(mod1, mod1 / "file1")
    _git_commit(mod1)

    # Has two commits.
    mod2 = tmp_path / "ec"
    _git_init(mod2)
    _git_add(mod2, mod2 / "file2")
    _git_commit(mod2)
    _git_add(mod2, mod2 / "file3")
    _git_commit(mod2)

    return project, zephyr_base, {"mod1": mod1, "ec": mod2}


def test_version_string(tmp_path):
    project, zephyr_base, modules = _setup_example_repos(tmp_path)
    assert version.get_version_string(project, zephyr_base, modules) == (
        "prj_v2.6.4-ec:b5991f,os:377d26,mod1:02fd7a",
        "prj_v2.6-ec:b5991f,os:377d26",
    )


def test_version_string_static(tmp_path):
    project, zephyr_base, modules = _setup_example_repos(tmp_path)
    assert version.get_version_string(project, zephyr_base, modules, static=True) == (
        "prj_v2.6.0-STATIC",
        "prj_v2.6.0-STATIC",
    )


@pytest.fixture
def fake_user_hostname():
    with mock.patch("getpass.getuser", return_value="toukmond", autospec=True):
        with mock.patch("platform.node", return_value="pokey", autospec=True):
            yield


@pytest.fixture
def fake_date():
    fixed_date = datetime.datetime(2021, 6, 28, 3, 18, 53)
    with mock.patch("datetime.datetime") as mock_datetime:
        mock_datetime.now.return_value = fixed_date
        yield


HEADER_VERSION_STR = (
    "hayato_v2.6.73670-ec:5bd1aa,os:ade7b4,cmsis:c3bd20,hal_stm32:f8ff8d"
)
SHORT_HEADER_VERSION_STR = "hayato_v2.6-ec:5bd1aa,os:ade7b4"
EXPECTED_HEADER = (
    "/* This file is automatically generated by zmake */\n"
    '#define VERSION "hayato_v2.6.73670-ec:5bd1aa,os:ade7b4,cmsis:c3bd20,'
    'hal_stm32:f8ff8d"\n'
    '#define CROS_EC_VERSION32 "hayato_v2.6-ec:5bd1aa,os:ade7b4"\n'
    '#define BUILDER "toukmond@pokey"\n'
    '#define DATE "2021-06-28 03:18:53"\n'
    '#define CROS_FWID_MISSING_STR "CROS_FWID_MISSING"\n'
    "#define CROS_FWID32 CROS_FWID_MISSING_STR\n"
)
HEADER_VERSION_STR2 = (
    "herobrine_npcx9_v2.6.73695-ec:7b0169,os:862339,cmsis:c3bd20,hal_stm32:f8ff8d"
)
SHORT_HEADER_VERSION_STR2 = "herobrine_npcx9_v2.6-ec:7b0169"
EXPECTED_HEADER2 = (
    "/* This file is automatically generated by zmake */\n"
    '#define VERSION "herobrine_npcx9_v2.6.73695-ec:7b0169,os:862339,'
    'cmsis:c3bd20,hal_stm32:f8ff8d"\n'
    '#define CROS_EC_VERSION32 "herobrine_npcx9_v2.6-ec:7b0169"\n'
    '#define BUILDER "toukmond@pokey"\n'
    '#define DATE "2021-06-28 03:18:53"\n'
    '#define CROS_FWID_MISSING_STR "CROS_FWID_MISSING"\n'
    "#define CROS_FWID32 CROS_FWID_MISSING_STR\n"
)
HEADER_VERSION_STR_STATIC = "trogdor_v2.6.0-STATIC"
SHORT_HEADER_VERSION_STR_STATIC = "trogdor_v2.6.0-STATIC"
EXPECTED_HEADER_STATIC = (
    "/* This file is automatically generated by zmake */\n"
    '#define VERSION "trogdor_v2.6.0-STATIC"\n'
    '#define CROS_EC_VERSION32 "trogdor_v2.6.0-STATIC"\n'
    '#define BUILDER "reproducible@build"\n'
    '#define DATE "STATIC_VERSION_DATE"\n'
    '#define CROS_FWID_MISSING_STR "CROS_FWID_MISSING"\n'
    "#define CROS_FWID32 CROS_FWID_MISSING_STR\n"
)


@pytest.mark.parametrize(
    "version_str,short_version_str,expected_header,static",
    [
        (HEADER_VERSION_STR, SHORT_HEADER_VERSION_STR, EXPECTED_HEADER, False),
        (HEADER_VERSION_STR2, SHORT_HEADER_VERSION_STR2, EXPECTED_HEADER2, False),
        (
            HEADER_VERSION_STR_STATIC,
            SHORT_HEADER_VERSION_STR_STATIC,
            EXPECTED_HEADER_STATIC,
            True,
        ),
    ],
)
def test_header_gen(
    fake_user_hostname,
    fake_date,
    tmp_path,
    version_str,
    short_version_str,
    expected_header,
    static,
):
    # Test the simple case (static=False, no existing header).
    output_file = tmp_path / "ec_version.h"
    version.write_version_header(version_str, short_version_str, output_file, static)
    assert output_file.read_text() == expected_header


def test_header_gen_exists_not_changed(fake_user_hostname, fake_date, tmp_path):
    # Test we don't overwrite if no changes needed.
    output_file = tmp_path / "ec_version.h"

    # First time, write and record mtime.
    version.write_version_header(
        HEADER_VERSION_STR, SHORT_HEADER_VERSION_STR, output_file
    )
    expected_mtime = output_file.stat().st_mtime

    # Do another write (contents should be unchanged).
    version.write_version_header(
        HEADER_VERSION_STR, SHORT_HEADER_VERSION_STR, output_file
    )

    # Assert we didn't write again.
    assert output_file.stat().st_mtime == expected_mtime


def test_header_gen_exists_needs_changes(fake_user_hostname, fake_date, tmp_path):
    # Test we overwrite when it exists already and changes are needed.
    output_file = tmp_path / "ec_version.h"

    # First time, write and save contents.
    version.write_version_header(
        HEADER_VERSION_STR, SHORT_HEADER_VERSION_STR, output_file
    )
    original_contents = output_file.read_text()

    # Do another write (contents should be changed).
    version.write_version_header(
        HEADER_VERSION_STR_STATIC,
        SHORT_HEADER_VERSION_STR_STATIC,
        output_file,
        static=True,
    )

    # Assert we overwrote.
    assert output_file.read_text() != original_contents
