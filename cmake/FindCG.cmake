FIND_PATH(CG_INCLUDE_DIR Cg/cg.h)
FIND_LIBRARY(CG_LIBRARIES NAMES Cg CgGL)


IF (CG_LIBRARIES AND CG_INCLUDE_DIR)
   SET(CG_FOUND TRUE)
ENDIF ()

IF (CG_FOUND)
    IF (NOT CG_FIND_QUIETLY)
       MESSAGE(STATUS "Found CG: ${CG_LIBRARIES}")
    ENDIF()
ELSE (CG_FOUND)
    IF (CG_FIND_REQUIRED)
       MESSAGE(FATAL_ERROR "Could not find CG library: ${CG_LIBRARIES}, ${CG_INCLUDE_DIR}")
    ENDIF ()
ENDIF ()

MARK_AS_ADVANCED(CG_LIBRARIES CG_INCLUDE_DIR)
