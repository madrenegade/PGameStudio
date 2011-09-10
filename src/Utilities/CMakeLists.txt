cmake_minimum_required (VERSION 2.8)
project (Utilities)

include("../../common.cmake")
include_directories(${SRC_DIR}/MemoryProfiler/memprof)
include_directories(${SRC_DIR}/StackTrace)

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Allocators/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Exceptions/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Tracking/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Pages/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Properties/*")

find_package(GLOG REQUIRED)
find_package(TBB REQUIRED)
find_package(Boost REQUIRED system program_options)

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} memprof)

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${Boost_LIBRARIES}
    memprof
)