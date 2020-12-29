# Cpp-Library

## Featured utilities
Argparse:
* Parser for command-line options, arguments and sub-commands
* This is an analog of python package `argparse`
* See `argparse.md` for details

Chemistry:
* Template for molecular geometry and mass

Utility:
* Some file and string operation

Mathematics:
* Combinatorics

Linear algebra:
* Linear algebra for pointer and std::vector

## Usage
Include headers
1. Add `include` to your include path
2. `#include <CppLibrary/CppLibrary.hpp>`

Compile with `CMake`
1. In your app main directory, create a symbolic link to here
2. `add_subdirectory(Cpp-Library)` in your `CMakeLists.txt`
