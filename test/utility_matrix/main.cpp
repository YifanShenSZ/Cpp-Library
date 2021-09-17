#include <iostream>

#include <CppLibrary/utility.hpp>

int main() {
    CL::utility::matrix<double> M(2);

    for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++)
    M[i][j] = i + j;

    for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++)
    std::cout << M[i][j] - (i + j) << ' ';
    std::cout << '\n';
}