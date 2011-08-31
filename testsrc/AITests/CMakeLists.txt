cmake_minimum_required (VERSION 2.8)
project (AITests)

include("../../common.cmake")
include_directories(${SRC_DIR}/AI)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/AI/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} AI)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.AI 
)

