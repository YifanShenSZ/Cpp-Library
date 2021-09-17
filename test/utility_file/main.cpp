#include <iostream>

#include <CppLibrary/utility/file.hpp>

int main() {
    std::cout << CL::utility::NLines  ("whatever") << '\n'
              << CL::utility::NStrings("whatever") << '\n';

    std::cout << CL::utility::NLines  ("frequency.txt") - 48 << '\n'
              << CL::utility::NStrings("frequency.txt") - 48 << '\n';
}