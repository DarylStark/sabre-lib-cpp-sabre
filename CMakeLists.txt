cmake_minimum_required(VERSION 3.14)
project(cpp-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling coverage flags")
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

# Application source
add_subdirectory(src)

# Tests
add_subdirectory(tests)