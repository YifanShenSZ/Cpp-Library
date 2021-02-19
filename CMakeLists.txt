cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Release)

include_directories(include)

add_library(CL STATIC
    source/utility.cpp
    source/string.cpp
    source/file.cpp
    source/math.cpp
)
