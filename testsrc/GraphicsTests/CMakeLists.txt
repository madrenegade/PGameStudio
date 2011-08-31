cmake_minimum_required (VERSION 2.8)
project (GraphicsTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Graphics)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Graphics/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Graphics)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Graphics 
)

