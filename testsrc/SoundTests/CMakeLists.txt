cmake_minimum_required (VERSION 2.8)
project (SoundTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Sound)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Sound/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Sound)

target_link_libraries(${PROJECT_NAME}
  	Sound
)

