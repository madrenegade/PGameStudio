cmake_minimum_required (VERSION 2.8)
project (Renderer.OpenGL)

include("../../common.cmake")
include_directories(${SRC_DIR}/Math)
include_directories("${SRC_DIR}/Core")
include_directories("${SRC_DIR}/Utilities")
include_directories("${SRC_DIR}/StackTrace")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/Renderer/*")

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Core Utilities)

target_link_libraries(${PROJECT_NAME}
    ${IL_LIBRARIES}
    Math
    Core
    Utilities
    GL
    GLU
    GLEW
    Cg
    CgGL
)
