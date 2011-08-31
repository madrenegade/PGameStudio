cmake_minimum_required (VERSION 2.8)
project (GeometryTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Geometry)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Geometry/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Geometry)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Geometry 
)

