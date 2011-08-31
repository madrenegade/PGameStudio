cmake_minimum_required (VERSION 2.8)
project (ScriptingLuaTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Scripting.Lua)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Scripting.Lua/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Scripting.Lua)

target_link_libraries(${PROJECT_NAME}
	Scripting.Lua
)

