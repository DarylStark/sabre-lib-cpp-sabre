file(GLOB SOURCES sabre/**/*.cpp sabre/*.cpp)
add_library(sabre SHARED ${SOURCES})

target_compile_options(sabre PRIVATE --coverage)
target_link_options(sabre PRIVATE --coverage)

target_include_directories(
    sabre
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

