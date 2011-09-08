cmake_minimum_required (VERSION 2.8)
project (TestRunner)

include("../../common.cmake")
include_directories(${SRC_DIR}/StackTrace)
include_directories(${SRC_DIR}/Utilities)

file(GLOB Project_Sources "${PROJECT_SOURCE_DIR}/*")

find_package(GTEST REQUIRED)

add_executable(TestRunner ${Project_Sources})

add_dependencies(TestRunner MathTests UtilitiesTests)

target_link_libraries(TestRunner -fprofile-arcs -ftest-coverage --coverage
    ${GTEST_LIBRARIES}
    MathTests
    UtilitiesTests
    gcov
    pthread
)

