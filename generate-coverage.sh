#!/bin/bash

CURRENT_DIR=${PWD}
BUILD_DIR=${1:-build}
LCOV_FILE="${CURRENT_DIR}/coverage.info"
HTML_DIR="${CURRENT_DIR}/htmlcov"

cmake --build $BUILD_DIR || exit
cd $BUILD_DIR
ctest

# Capture coverage data
lcov --directory . --capture --output-file "$LCOV_FILE" || exit

# Optionally, remove coverage data for system and test files
lcov --remove "$LCOV_FILE" '/usr/*' '*/tests/*' '*/external/googletest/*' --output-file "$LCOV_FILE" || exit

# Generate HTML report
genhtml "$LCOV_FILE" --output-directory "$HTML_DIR" || exit
