cmake_minimum_required (VERSION 2.8)
project (InputTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Input)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Input/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Input)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Input 
)

