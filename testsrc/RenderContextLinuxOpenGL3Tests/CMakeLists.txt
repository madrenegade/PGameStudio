cmake_minimum_required (VERSION 2.8)
project (RenderContextLinuxOpenGL3Tests)

include("../../common.cmake")
include_directories(${SRC_DIR}/RenderContextLinuxOpenGL3)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/RenderContextLinuxOpenGL3/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} RenderContextLinuxOpenGL3)

target_link_libraries(${PROJECT_NAME}
	RenderContextLinuxOpenGL3
)

