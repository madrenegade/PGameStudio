cmake_minimum_required (VERSION 2.8)
project (GameTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Game)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Game/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Game)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Game
)

