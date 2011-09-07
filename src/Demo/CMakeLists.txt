cmake_minimum_required (VERSION 2.8)
project (Demo)

include("../../common.cmake")
include_directories(${SRC_DIR}/StackTrace)
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/Core)

FILE(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/*")

find_package(Boost REQUIRED serialization)
find_package(UNWIND REQUIRED)

add_executable(${PROJECT_NAME} ${Project_Sources})

add_dependencies(${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME}
    Core
    Utilities
    StackTrace
    pthread
    unwind
    ${UNWIND_LIBRARIES}
    ${Boost_LIBRARIES}
)