cmake_minimum_required (VERSION 2.8)
project (memprof)

include("../../../common.cmake")

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../../..")
set(SRC_DIR "${ROOT_DIR}/src")
set(ADDITIONAL_CMAKE_MODULE_DIR "${ROOT_DIR}/cmake")
set(CMAKE_MODULE_PATH ${ADDITIONAL_CMAKE_MODULE_DIR} ${CMAKE_MODULE_PATH})
set(BIN_DIR "${ROOT_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${BIN_DIR}/${OUTPUT_SUB_DIRECTORY}")

set(CMAKE_LIBRARY_PATH
    "${LIBRARY_OUTPUT_PATH}")

file (STRINGS "BuildNumber.txt" BUILD_NUMBER)
MATH(EXPR BUILD_NUMBER "${BUILD_NUMBER} + 1")
MESSAGE("BUILD: ${BUILD_NUMBER}")
file(WRITE "BuildNumber.txt" ${BUILD_NUMBER})

add_definitions("-DBUILD_NUMBER=${BUILD_NUMBER}")

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/tcp/*")

find_package(GLOG REQUIRED)
include_directories(${GLOG_INCLUDE_PATH})

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

add_dependencies(${PROJECT_NAME} StackTrace)
include_directories(${SRC_DIR}/StackTrace)

target_link_libraries(${PROJECT_NAME}
    StackTrace
    ${GLOG_LIBRARIES}
)
