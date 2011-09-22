cmake_minimum_required (VERSION 2.8)
project (MathTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Math)
include_directories(${SRC_DIR}/Utilities)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Math/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Math Utilities)

target_link_libraries(${PROJECT_NAME}
    Math  
    Utilities
)

