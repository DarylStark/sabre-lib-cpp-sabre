cmake_minimum_required(VERSION 3.14)
project(cpp-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

enable_testing()

# Application source
add_subdirectory(src)

# Tests
add_subdirectory(tests)
