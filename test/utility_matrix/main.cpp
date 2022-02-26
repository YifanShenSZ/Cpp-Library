#include <iostream>

#include <CppLibrary/utility.hpp>

int main() {
    CL::utility::matrix<double> a(2);
    a[0][0] = 1.0; a[0][1] = 2.0;
    a[1][0] = 3.0; a[1][1] = 4.0;

    CL::utility::matrix<double> b = (a - 1.0) * 3.0;
    CL::utility::matrix<double> c = a * b;

    CL::utility::matrix<double> b_answer(2);
    b_answer[0][0] = 0.0; b_answer[0][1] = 3.0;
    b_answer[1][0] = 6.0; b_answer[1][1] = 9.0;
    b = b - b_answer;
    for (auto & row : b) for (double & el : row) std::cerr << el << ' ';
    std::cerr << '\n';

    CL::utility::matrix<double> c_answer(2);
    c_answer[0][0] =  0.0; c_answer[0][1] =  6.0;
    c_answer[1][0] = 18.0; c_answer[1][1] = 36.0;
    c -= c_answer;
    for (auto & row : c) for (double & el : row) std::cerr << el << ' ';
    std::cerr << '\n';
}