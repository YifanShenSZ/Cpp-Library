#include <iostream>

#include <CppLibrary/linalg.hpp>

int main() {
    std::vector<double> a = {1.0, 2.0, 3.0};
    std::vector<double> b = 3.0 * (a - 1.0);
    std::vector<double> c = a * b;

    std::vector<double> b_answer = {0.0, 3.0, 6.0};
    b = b - b_answer;
    for (double & el : b) std::cerr << el << ' ';
    std::cerr << '\n';

    std::vector<double> c_answer = {0.0, 6.0, 18.0};
    c = c - c_answer;
     for (double & el : c) std::cerr << el << ' ';
    std::cerr << '\n';
}