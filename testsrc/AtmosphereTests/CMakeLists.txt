cmake_minimum_required (VERSION 2.8)
project (AtmosphereTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Atmosphere)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Atmosphere/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Atmosphere)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Atmosphere 
)

