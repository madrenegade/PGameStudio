cmake_minimum_required (VERSION 2.8)
project (Platform.Linux)

include("../../common.cmake")
include_directories(${SRC_DIR}/Core)
include_directories(${SRC_DIR}/Renderer.OpenGL)
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/StackTrace)

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/Platform/*"
	"${PROJECT_SOURCE_DIR}/Platform/Linux/*")

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Core Utilities Renderer.OpenGL)

target_link_libraries(${PROJECT_NAME}
    Core
    Utilities
    Renderer.OpenGL
    ${X11_LIBRARIES}
    GL
    ${OpenGL_LIBRARIES}
)
