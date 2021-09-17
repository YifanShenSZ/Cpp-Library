// General basic routine

#ifndef CL_utility_hpp
#define CL_utility_hpp

#include <cctype>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include <CppLibrary/utility/exception.hpp>
#include <CppLibrary/utility/file.hpp>
#include <CppLibrary/utility/string.hpp>
#include <CppLibrary/utility/triple.hpp>
#include <CppLibrary/utility/matrix.hpp>
#include <CppLibrary/utility/heap.hpp>
#include <CppLibrary/utility/UnionFind.hpp>

namespace CL { namespace utility {

void show_time(std::ostream & stream);

void echo_command(const size_t & argc, const char ** argv, std::ostream & stream);

// Sort x then use the same order to sort y (ascendingly)
template <typename T> void pairsort(std::vector<size_t> x, std::vector<T> y) {
    if (x.size() != y.size()) throw std::invalid_argument(
    "x and y must share a same size");
    std::vector<std::pair<size_t, T>> pairs(x.size());
    for (size_t i = 0; i < x.size(); i++) {
        pairs[i].first  = x[i];
        pairs[i].second = y[i];
    }
    std::sort(pairs.begin(), pairs.end());
    for (size_t i = 0; i < x.size(); i++) {
        x[i] = pairs[i].first ;
        y[i] = pairs[i].second;
    }
}
// User defined comparison
template <typename Tx, typename Ty, typename _Compare> void pairsort(std::vector<Tx> x, std::vector<Ty> y, _Compare __comp) {
    if (x.size() != y.size()) throw std::invalid_argument(
    "x and y must share a same size");
    std::vector<std::pair<Tx, Ty>> pairs(x.size());
    for (size_t i = 0; i < x.size(); i++) {
        pairs[i].first  = x[i];
        pairs[i].second = y[i];
    }
    std::sort(pairs.begin(), pairs.end(), __comp);
    for (size_t i = 0; i < x.size(); i++) {
        x[i] = pairs[i].first ;
        y[i] = pairs[i].second;
    }
}

// Allocate (deallocate) continuous memory for an n-dimensional array A(N1, N2, ..., Nn)
// Matrix
template <typename T> void CreateArray(T ** & A, const size_t & N1, const size_t & N2) {
    if (nullptr != A) std::cout << "CreateArray warning: pointer != nullptr, the matrix may has been allocated\n";
    if (N1 == 0) throw std::invalid_argument("CreateArray error: 1st dimensionality = 0");
    if (N2 == 0) throw std::invalid_argument("CreateArray error: 2nd dimensionality = 0");
    try {
        A = new T * [N1];
        A[0] = new T[N1*N2];
        for (size_t i = 1; i < N1; i++) A[i] = A[i-1] + N2;
    }
    catch (std::bad_alloc & error) {
        throw error;
    }
}
template <typename T> void DeleteArray(T ** & A) {
    if (nullptr == A) {
        std::cout << "DeleteArray warning: pointer == nullptr, the matrix has been deallocated\n";
    }
    else {
        delete [] A[0];
        delete [] A;
        A = nullptr;
    }
}
// 3rd-order tensor
template <typename T> void CreateArray(T *** & A, const size_t & N1, const size_t & N2, const size_t & N3) {
    if (nullptr != A) std::cout << "CreateArray warning: pointer != nullptr, the 3rd-order tensor may has been allocated\n";
    if (N1 == 0) throw std::invalid_argument("CreateArray error: 1st dimensionality = 0");
    if (N2 == 0) throw std::invalid_argument("CreateArray error: 2nd dimensionality = 0");
    if (N3 == 0) throw std::invalid_argument("CreateArray error: 3rd dimensionality = 0");
    try {
        size_t i, j;
        A = new T ** [N1];
        for (i = 0; i < N1; i++) A[i] = new T * [N2];
        A[0][0] = new T[N1*N2*N3];
        for (j = 1; j < N2; j++) A[0][j] = A[0][j-1] + N3;
        for (i = 1; i < N1; i++) {
            A[i][0] = A[i-1][N2-1] + N3;
            for (j = 1; j < N2; j++) A[i][j] = A[i][j-1] + N3;
        }
    }
    catch (std::bad_alloc & e) {
        throw e;
    }
}
template <typename T> void DeleteArray(T *** & A, const size_t & N1) {
    if (nullptr == A) {
        std::cout << "DeleteArray warning: pointer == nullptr, the 3rd-order tensor has been deallocated\n";
    }
    else {
        delete [] A[0][0];
        for (size_t i = 0; i < N1; i++) delete [] A[i];
        delete [] A;
        A = nullptr;
    }
}

} // namespace utility
} // namespace CL

#endif