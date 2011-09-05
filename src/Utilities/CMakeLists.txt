cmake_minimum_required (VERSION 2.8)
project (Utilities)

include("../../common.cmake")

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Allocators/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Exceptions/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Tracking/*")

find_package(GLOG REQUIRED)
find_package(TBB REQUIRED)

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
)