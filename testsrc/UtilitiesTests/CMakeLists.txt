cmake_minimum_required (VERSION 2.8)
project (UtilitiesTests)

include("../../common.cmake")
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/StackTrace)
 
file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/Utilities/*"
    "${PROJECT_SOURCE_DIR}/Utilities/Memory/*")

find_package(GPROFILER REQUIRED)

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Utilities StackTrace)

target_link_libraries(${PROJECT_NAME}
    ${GPROFILER_LIBRARIES}
    ${TBB_LIBRARIES}
    Utilities
    StackTrace
)

