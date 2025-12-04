add_subdirectory(sabre)

if(SABRE_BUILD_PILOT STREQUAL "ON")
    add_subdirectory(pilot)
endif()