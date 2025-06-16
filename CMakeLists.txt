cmake_minimum_required(VERSION 3.14)
project(cpp-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

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
