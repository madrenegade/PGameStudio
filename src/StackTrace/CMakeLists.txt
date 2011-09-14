cmake_minimum_required (VERSION 2.8)
project (StackTrace)

include("../../common.cmake")

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/*")

find_package(GLOG REQUIRED)
include_directories(${GLOG_INCLUDE_DIR})

find_package(Boost REQUIRED serialization)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${Boost_LIBRARIES}
)
