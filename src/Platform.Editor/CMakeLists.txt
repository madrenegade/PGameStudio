cmake_minimum_required (VERSION 2.8)
project (Platform.Editor)

include("../../common.cmake")
include_directories(${SRC_DIR}/Core)
include_directories(${SRC_DIR}/Utilities)
include_directories(${SRC_DIR}/StackTrace)

file(GLOB Project_Sources 
	"${PROJECT_SOURCE_DIR}/Platform/*"
	"${PROJECT_SOURCE_DIR}/Platform/Editor/*")

add_library(${PROJECT_NAME} SHARED ${Project_Sources})

SET(QT_USE_QTOPENGL TRUE)

FIND_PACKAGE(Qt4 REQUIRED)
include_directories(${QT_INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} Core Utilities)

target_link_libraries(${PROJECT_NAME}
    Core
    Utilities
)
