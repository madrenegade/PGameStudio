cmake_minimum_required (VERSION 2.8)
project (Game)

include("../../common.cmake")

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})
