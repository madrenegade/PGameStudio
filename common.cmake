SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

if(APPLE)
	MESSAGE(FATAL_ERROR "APPLE is not supported")
elseif(WIN32)
	MESSAGE(FATAL_ERROR "WIN32 is not supported")
elseif(UNIX)
	add_definitions(-DLINUX)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_definitions(-DDEBUG)
	add_definitions(-DNDEBUG)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Profile")
	add_definitions(-DPROFILE)
	SET(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE} -g")
	SET(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} -g")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
        add_definitions(-DGCC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fPIC")
endif()

if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86")
    add_definitions(-DX86)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "i686")
    add_definitions(-DX86)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86_64")
    add_definitions(-DX86_64)
else()
    MESSAGE(FATAL_ERROR "Only x86, i686 and x86_64 platforms are supported (using ${CMAKE_HOST_SYSTEM_PROCESSOR})")
endif()

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../..")
set(BIN_DIR "${ROOT_DIR}/bin")
set(SRC_DIR "${ROOT_DIR}/src")
set(TESTSRC_DIR "${ROOT_DIR}/testsrc")

set(ADDITIONAL_CMAKE_MODULE_DIR "${ROOT_DIR}/cmake")
set(CMAKE_MODULE_PATH ${ADDITIONAL_CMAKE_MODULE_DIR} ${CMAKE_MODULE_PATH})
include_directories(${PROJECT_SOURCE_DIR})

# output subdirectory

set(OUTPUT_SUB_DIRECTORY "${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}")

set(LIBRARY_OUTPUT_PATH "${BIN_DIR}/${OUTPUT_SUB_DIRECTORY}")
set(EXECUTABLE_OUTPUT_PATH "${BIN_DIR}")
#set(PLUGIN_OUTPUT_PATH "${WORKSPACE_DIR}/runtime/plugins/")

set(CMAKE_LIBRARY_PATH
    "${LIBRARY_OUTPUT_PATH}")
