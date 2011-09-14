cmake_minimum_required (VERSION 2.8)
project (Core)

include("../../common.cmake")

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Events/*"
    "${PROJECT_SOURCE_DIR}/Graphics/*"
    "${PROJECT_SOURCE_DIR}/Platform/*"
    "${PROJECT_SOURCE_DIR}/Platform/Linux/*"
    "${PROJECT_SOURCE_DIR}/Platform/Windows/*")

find_package(GLOG REQUIRED)
include_directories(${GLOG_INCLUDE_DIR})

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})

find_package(Boost REQUIRED signals system)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} Utilities StackTrace)
include_directories(${SRC_DIR}/StackTrace)
include_directories(${SRC_DIR}/Utilities)

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${TBB_LIBRARIES}
    ${Boost_LIBRARIES}
    StackTrace
    Utilities
)
