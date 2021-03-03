# FindCL
# -------
#
# Finds Cpp-Library (CL)
#
# This will define the following variables:
#
#   CL_FOUND        -- True if the system has CL
#   CL_INCLUDE_DIRS -- The include directories for CL
#   CL_LIBRARIES    -- Libraries to link against
#
# and the following imported targets:
#
#   CL

# Find CL root
# Assume we are in ${CLROOT}/share/cmake/CL/CLConfig.cmake
get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(CLROOT "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# include directory
set(CL_INCLUDE_DIRS ${CLROOT}/include)

# library
add_library(CL STATIC IMPORTED)
set(CL_LIBRARIES CL)

find_library(CL_LIBRARY CL PATHS "${CLROOT}/lib")
set_target_properties(CL PROPERTIES
    IMPORTED_LOCATION "${CL_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${CL_INCLUDE_DIRS}"
    CXX_STANDARD 14
)