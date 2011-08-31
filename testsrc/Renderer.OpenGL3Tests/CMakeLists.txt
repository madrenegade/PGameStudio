cmake_minimum_required (VERSION 2.8)
project (RendererOpenGL3Tests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Renderer.OpenGL3)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Renderer.OpenGL3/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Renderer.OpenGL3)

target_link_libraries(${PROJECT_NAME}
    Renderer.OpenGL3
)

