cmake_minimum_required (VERSION 2.8)
project (Renderer.OpenGL)

include("../../common.cmake")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/Renderer/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME}
    Core
)
