cmake_minimum_required (VERSION 2.8)
project (TerrainTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Terrain)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Terrain/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Terrain)

target_link_libraries(${PROJECT_NAME}
    Terrain 
)

