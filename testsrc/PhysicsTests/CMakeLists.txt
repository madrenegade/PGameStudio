cmake_minimum_required (VERSION 2.8)
project (PhysicsTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Physics)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Physics/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Physics)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Physics 
)

