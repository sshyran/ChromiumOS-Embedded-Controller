# Code Coverage

Provides an overview of how to use code coverage tools when running the unit
tests in the EC codebase.

[TOC]

## Availability

Code coverage is only available for host-based unit tests, as opposed to manual
tests that run on target hardware.

## Building for code coverage

To build host-based unit tests for code coverage, invoke `make` with the
`coverage` target, as follows:

`make coverage -j`

This target will compile and link the unit tests with `--coverage` flag (which
pulls in the `gcov` libraries), run the tests, and then process the profiling
data into a code coverage report using the `lcov` and `genhtml` tools.

The coverage report top-level page is `build/coverage/coverage_rpt/index.html`.

### Noise in the build output

When building for code coverage, you may see multiple warnings of the form
`geninfo: WARNING: no data found for
/mnt/host/source/src/platform/ec/core/host/cpu.h` and `genhtml: WARNING:
function data mismatch at
/mnt/host/source/src/platform/ec/common/math_util.c:134`

These warnings can be ignored. (FYI, the "function data mismatch" warnings
appear to be caused in part by using relative paths instead of absolute paths.)

## Zephyr ztest code coverage

To build the Zephyr unit tests for code coverage run:

`zmake test --host-tests-only --coverage`
`genhtml -q -o build/zephyr/coverage_rpt/ build/zephyr/all_tests.info`

The coverage report top-level page is
`build/zephyr/coverage_rpt/index.html`.

However you probably want to merge that with a single board's coverage report
also, so that you can include code that is not part of any test as well.

```
zmake build --coverage herobrine
zmake test --host-tests-only --coverage
genhtml -q -s --branch-coverage -o build/zephyr/coverage_rpt/ \
  build/zephyr/all_tests.info build/zephyr/herobrine/output/zephyr.info
```

The coverage report top-level page is
`build/zephyr/coverage_rpt/index.html`.

For coverage report for a single test you can run:
`zmake test --coverage <TESTNAME>`

Example:
`zmake test --coverage test-drivers`
`genhtml -q -o build/zephyr/test-drivers/output/coverage_rpt/ build/zephyr/test-drivers/output/zephyr.info`
