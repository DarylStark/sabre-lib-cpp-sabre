file(GLOB SOURCES CONFIGURE_DEPENDS sabre_test_app/*.cpp)
add_library(sabre_test_app STATIC ${SOURCES})

target_compile_options(sabre_test_app PRIVATE --coverage)
target_link_options(sabre_test_app PRIVATE --coverage)

target_link_libraries(sabre_test_app PRIVATE sabre)

target_include_directories(
    sabre_test_app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sabre
)
