cmake_minimum_required (VERSION 2.8)
project (Math)

include("../../common.cmake")

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/Math/*")

add_library(PGameStudio.Math SHARED ${Project_Sources})
