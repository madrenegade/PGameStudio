cmake_minimum_required (VERSION 2.8)
project (Demo)

include("../../common.cmake")

FILE(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/*")

add_executable(${PROJECT_NAME} ${Project_Sources})
