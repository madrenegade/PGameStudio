cmake_minimum_required (VERSION 2.8)
project (memprof)

include("../../../common.cmake")

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../../..")
set(ADDITIONAL_CMAKE_MODULE_DIR "${ROOT_DIR}/cmake")
set(BIN_DIR "${ROOT_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${BIN_DIR}/${OUTPUT_SUB_DIRECTORY}")

set(CMAKE_LIBRARY_PATH
    "${LIBRARY_OUTPUT_PATH}")

file (STRINGS "BuildNumber.txt" BUILD_NUMBER)

add_definitions("-DBUILD_NUMBER=${BUILD_NUMBER}")


file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*")

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME}
    gcov
)
