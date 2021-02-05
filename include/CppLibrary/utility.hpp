// General basic routine

#ifndef CL_utility_hpp
#define CL_utility_hpp

#include <cctype>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include <algorithm>

#include <CppLibrary/utility/file.hpp>
#include <CppLibrary/utility/string.hpp>

namespace CL { namespace utility {

void show_time(std::ostream & stream);

void echo_command(const size_t & argc, const char** argv, std::ostream & stream);

// Sort an arbitrary array y according to the order defined by x (ascendingly)
template <typename T> void pairsort(std::vector<size_t> x, std::vector<T> y) {
    assert(("x and y must share a same size", x.size() == y.size()));
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
// User defined order
template <typename T, typename _Compare> void pairsort(std::vector<size_t> x, std::vector<T> y, _Compare __comp) {
    assert(("x and y must share a same size", x.size() == y.size()));
    std::vector<std::pair<size_t, T>> pairs(x.size());
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

// Wrap the ugly std::vector<std::vector<T>>
template <typename T> struct matrix {
    std::vector<std::vector<T>> rows;

    matrix() {}
    matrix(const size_t & N) {
        rows.resize(N);
        for (auto & row : rows) row.resize(N);
    }
    matrix(const size_t & M, const size_t & N) {
        rows.resize(M);
        for (auto & row : rows) row.resize(N);
    }
    ~matrix() {}

    size_t size(const size_t & dim) {
        assert(("Dimension must be 0 or 1", dim == 0 || dim == 1));
        if (dim == 0) return rows.size();
        else          return rows[0].size();
    }

    std::vector<T> & operator[](const size_t & index) {return rows[index];}
    const std::vector<T> & operator[](const size_t & index) const {return rows[index];}
};

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