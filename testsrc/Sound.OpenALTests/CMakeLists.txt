cmake_minimum_required (VERSION 2.8)
project (SoundOpenALTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Sound.OpenAL)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Sound.OpenAL/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Sound.OpenAL)

target_link_libraries(${PROJECT_NAME}
    Sound.OpenAL
)

