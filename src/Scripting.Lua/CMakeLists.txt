cmake_minimum_required (VERSION 2.8)
project (Scripting.Lua)

include("../../common.cmake")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/Scripting/*"
    "${PROJECT_SOURCE_DIR}/Scripting/Lua/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} Scripting Utilities)
include_directories(${SRC_DIR}/Scripting)
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/StackTrace)

target_link_libraries(${PROJECT_NAME}
    Scripting
    Utilities
    ${LUA_LIBRARIES}
)
