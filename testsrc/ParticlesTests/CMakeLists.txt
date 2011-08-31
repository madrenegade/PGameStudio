cmake_minimum_required (VERSION 2.8)
project (ParticlesTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Particles)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Particles/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Particles)

target_link_libraries(${PROJECT_NAME}
    PGameStudio.Particles 
)

