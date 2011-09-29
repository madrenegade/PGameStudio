cmake_minimum_required (VERSION 2.8)
project (Utilities)

include("../../common.cmake")

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/IO/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/IO/Backend/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/IO/Exceptions/*"
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Allocators/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Exceptions/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Tracking/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Memory/Pages/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Properties/*")

find_package(GLOG REQUIRED)
include_directories(${GLOG_INCLUDE_DIR})

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})

find_package(Boost REQUIRED system program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PhysFS REQUIRED)
include_directories(${PhysFS_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

add_dependencies(${PROJECT_NAME} memprof StackTrace)
include_directories(${SRC_DIR}/MemoryProfiler/memprof)
include_directories(${SRC_DIR}/StackTrace)

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${Boost_LIBRARIES}
    ${TBB_LIBRARIES}
    physfs
    memprof
    StackTrace
)