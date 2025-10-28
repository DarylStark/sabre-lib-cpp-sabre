# ImGui
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

file(
    GLOB IMGUI_SOURCES CONFIGURE_DEPENDS
        ${imgui_SOURCE_DIR}/*.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(
    imgui
    PRIVATE
        ${imgui_SOURCE_DIR}
)

# Pilot Library
file(GLOB_RECURSE SABRE_PILOT_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(sabre_pilot STATIC ${SABRE_PILOT_SOURCES})
list(FILTER SABRE_PILOT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

target_link_libraries(sabre_pilot PRIVATE imgui sabre glfw OpenGL)

target_include_directories(
    sabre_pilot
    PRIVATE
        ${imgui_SOURCE_DIR}
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
