cmake_minimum_required (VERSION 2.8)
project (PhysicsBulletTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Physics.Bullet)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Physics.Bullet/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Physics.Bullet)

target_link_libraries(${PROJECT_NAME}
    Physics.Bullet 
)

