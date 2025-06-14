file(GLOB SOURCES sabre/**/*.cpp sabre/*.cpp)
add_library(sabre ${SOURCES})

target_include_directories(
    sabre
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

