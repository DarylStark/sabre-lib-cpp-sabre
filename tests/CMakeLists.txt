file(GLOB SOURCES test_*.cpp)
add_executable(sabre_tests ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(./sabre_testing)

target_link_libraries(sabre_tests PRIVATE sabre sabre_testing gtest gtest_main)

target_compile_options(sabre_tests PRIVATE --coverage)
target_link_options(sabre_tests PRIVATE --coverage)

target_include_directories(
    sabre_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

include(GoogleTest)
gtest_discover_tests(sabre_tests)
