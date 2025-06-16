file(GLOB SOURCES *.cpp ./**/*.cpp)
add_library(sabre_testing SHARED ${SOURCES})

target_compile_options(sabre_testing PRIVATE --coverage)
target_link_options(sabre_testing PRIVATE --coverage)

target_include_directories(
    sabre_testing
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)

