cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Cpp-Library)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Release)

include_directories(include)

add_library(CL STATIC
    source/utility/exception.cpp
    source/utility/utility.cpp
    source/utility/string.cpp
    source/utility/file.cpp
    source/math.cpp
    source/chemistry.cpp
)
