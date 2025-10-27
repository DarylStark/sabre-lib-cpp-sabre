file(GLOB_RECURSE SABRE_PILOT_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(sabre_pilot STATIC ${SABRE_PILOT_SOURCES})
list(FILTER SABRE_PILOT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

target_link_libraries(sabre_pilot PUBLIC sabre)

target_include_directories(
    sabre_pilot
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../sabre
)

# Temporary executable
# TODO: Remove
add_executable(sabre_pilot_exec main.cpp)
target_link_libraries(sabre_pilot_exec PRIVATE sabre_pilot)
target_include_directories(
    sabre_pilot_exec
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../sabre
)
