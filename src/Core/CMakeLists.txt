cmake_minimum_required (VERSION 2.8)
project (Core)

include("../../common.cmake")
include_directories(${SRC_DIR}/StackTrace)
include_directories(${SRC_DIR}/Utilities)

file(GLOB Project_Sources 
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Events/*"
    "${PROJECT_SOURCE_DIR}/Graphics/*"
    "${PROJECT_SOURCE_DIR}/Platform/*"
    "${PROJECT_SOURCE_DIR}/Platform/Linux/*")

find_package(GLOG REQUIRED)
find_package(TBB REQUIRED)
find_package(Boost REQUIRED signals system)

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${TBB_LIBRARIES}
    ${Boost_LIBRARIES}
)
