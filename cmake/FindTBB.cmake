FIND_PATH(TBB_INCLUDE_DIR tbb/tbb.h)
FIND_LIBRARY(TBB_LIBRARIES NAMES tbb)


IF (TBB_LIBRARIES AND TBB_INCLUDE_DIR)
   SET(TBB_FOUND TRUE)
ENDIF ()

IF (TBB_FOUND)
    IF (NOT TBB_FIND_QUIETLY)
       MESSAGE(STATUS "Found TBB: ${TBB_LIBRARIES}")
    ENDIF()
ELSE (TBB_FOUND)
    IF (TBB_FIND_REQUIRED)
       MESSAGE(FATAL_ERROR "Could not find TBB library: ${TBB_LIBRARIES}, ${TBB_INCLUDE_DIR}")
    ENDIF ()
ENDIF ()

MARK_AS_ADVANCED(TBB_LIBRARIES TBB_INCLUDE_DIR)