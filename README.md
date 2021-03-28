# Cpp-Library

## Featured utilities
Argparse:
* parser for command-line options, arguments and sub-commands
* this is an analog of python package `argparse`
* see `argparse.md` for details

Chemistry:
* template classes to hold molecules

Linear algebra:
* vector operation for pointer and std::vector
* overloaded operators for std::vector

Mathematics:
* combinatorics

Utility:
* some general basic routines
* function not ready exception
* file manipulations
* string manipulations
* template struct triple
* template class matrix

## Installation
1. `mkdir build lib`
2. `cd build`
3. `cmake ..`
4. `cmake --build .`
5. `mv lib* ../lib`
6. add `include` and `lib` to your path

## Usage
`#include <CppLibrary/CppLibrary.hpp>`
