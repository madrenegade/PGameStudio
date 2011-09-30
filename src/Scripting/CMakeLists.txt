cmake_minimum_required (VERSION 2.8)
project (Scripting)

include("../../common.cmake")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_PATH})

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} Utilities Core)
include_directories("${SRC_DIR}/Utilities")
include_directories("${SRC_DIR}/StackTrace")
include_directories("${SRC_DIR}/Core")

target_link_libraries(${PROJECT_NAME}
    ${LUA_LIBRARIES}
    Utilities
    Core
)
