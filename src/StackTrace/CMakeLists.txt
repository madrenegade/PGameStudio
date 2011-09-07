cmake_minimum_required (VERSION 2.8)
project (StackTrace)

include("../../common.cmake")

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/*")

find_package(GLOG REQUIRED)
find_package(UNWIND REQUIRED)
find_package(Boost REQUIRED serialization)

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME}
    ${GLOG_LIBRARIES}
    ${UNWIND_LIBRARIES}
    ${Boost_LIBRARIES}
)
