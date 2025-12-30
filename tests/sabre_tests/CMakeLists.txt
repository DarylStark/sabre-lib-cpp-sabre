file(GLOB SOURCES CONFIGURE_DEPENDS test_*.cpp)
add_executable(sabre_tests ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(sabre_tests PRIVATE sabre sabre_test_mocks gtest gtest_main)

target_compile_options(sabre_tests PRIVATE --coverage)
target_link_options(sabre_tests PRIVATE --coverage)

target_include_directories(
    sabre_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sabre
        ${CMAKE_CURRENT_SOURCE_DIR}/../sabre_test_mocks
)

include(GoogleTest)
gtest_discover_tests(sabre_tests)
