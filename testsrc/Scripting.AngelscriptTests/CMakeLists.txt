cmake_minimum_required (VERSION 2.8)
project (ScriptingAngelscriptTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Scripting.Angelscript)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Scripting.Angelscript/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Scripting.Angelscript)

target_link_libraries(${PROJECT_NAME}
    Scripting.Angelscript
)

