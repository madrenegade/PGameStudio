cmake_minimum_required (VERSION 2.8)
project (ScriptingTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Scripting)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Scripting/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Scripting)

target_link_libraries(${PROJECT_NAME}
    Scripting
)

