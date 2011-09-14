cmake_minimum_required (VERSION 2.8)
project (Game)

include("../../common.cmake")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Core Utilities StackTrace)
include_directories(${SRC_DIR}/Core)
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/StackTrace)

target_link_libraries(${PROJECT_NAME}
    Core
    Utilities
    StackTrace
)
