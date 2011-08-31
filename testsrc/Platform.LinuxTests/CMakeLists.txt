cmake_minimum_required (VERSION 2.8)
project (PlatformLinuxTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Platform.Linux)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Platform.Linux/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Platform.Linux)

target_link_libraries(${PROJECT_NAME}
    Platform.Linux 
)

