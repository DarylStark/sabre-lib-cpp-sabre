#!/bin/bash

CURRENT_DIR=${PWD}
BUILD_DIR=${1:-build}
HTML_DIR="${CURRENT_DIR}/htmlcov"
COVERAGE_XML="${CURRENT_DIR}/coverage.xml"
COVERAGE_HTML_INDEX="${HTML_DIR}/index.html"

cmake --build $BUILD_DIR || exit
cd $BUILD_DIR
ctest

# Ensure the HTML output directory exists
mkdir -p "$HTML_DIR"

# Generate HTML and XML coverage reports using gcovr
gcovr \
    --root ${CURRENT_DIR} \
    --exclude-directories 'tests' \
    --exclude '.*googletest.*' \
    --html="${COVERAGE_HTML_INDEX}" --html-details -o "$COVERAGE_HTML_INDEX" \
    --xml -o "$COVERAGE_XML" \
    --print-summary