cmake_minimum_required (VERSION 2.8)
project (Demo)

include("../../common.cmake")
include_directories(${SRC_DIR}/Core)
include_directories(${SRC_DIR}/Game)

FILE(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/*")

find_package(Boost REQUIRED serialization thread)
find_package(UNWIND REQUIRED)

add_executable(${PROJECT_NAME} ${Project_Sources})

add_dependencies(${PROJECT_NAME} Game Platform.Linux)

target_link_libraries(${PROJECT_NAME}
    Game
    pthread
    unwind
    ${UNWIND_LIBRARIES}
    ${Boost_LIBRARIES}
)