cmake_minimum_required(VERSION 3.14)
project(sabre LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(SABRE_BUILD_TESTS STREQUAL "ON")
    message(STATUS "Enabling testing")
    enable_testing()
    message(STATUS "Enabling coverage flags")
    add_compile_options(--coverage)
    add_link_options(--coverage)
    add_subdirectory(tests)
endif()

# Application source
add_subdirectory(src)
