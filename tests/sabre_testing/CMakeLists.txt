file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp ./**/*.cpp)
add_library(sabre_testing STATIC ${SOURCES})

target_compile_options(sabre_testing PRIVATE --coverage)
target_link_options(sabre_testing PRIVATE --coverage)

target_link_libraries(sabre_testing PRIVATE sabre)

target_include_directories(
    sabre_testing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)

