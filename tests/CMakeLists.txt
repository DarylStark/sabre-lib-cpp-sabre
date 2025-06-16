file(GLOB SOURCES test_*.cpp)
add_executable(sabre_tests ${SOURCES})

target_link_libraries(sabre_tests PRIVATE sabre gtest gtest_main)

target_compile_options(sabre_tests PRIVATE --coverage)
target_link_options(sabre_tests PRIVATE --coverage)

target_include_directories(
    sabre_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

include(GoogleTest)
gtest_discover_tests(sabre_tests)
