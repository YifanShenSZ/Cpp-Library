// Vector operation for pointer and std::vector

#ifndef CL_linalg_hpp
#define CL_linalg_hpp

#include <cmath>
#include <vector>
#include <cassert>

// Add `shift` from each element
template <typename T> std::vector<T> operator+(const std::vector<T> & vector, const T & shift) {
    std::vector<T> result = vector;
    for (T & el : result) el += shift;
    return result;
}
template <typename T> void operator+=(std::vector<T> & vector, const T & shift) {
    for (T & el : vector) el += shift;
}
// Subtract `shift` from each element
template <typename T> std::vector<T> operator-(const std::vector<T> & vector, const T & shift) {
    std::vector<T> result = vector;
    for (T & el : result) el -= shift;
    return result;
}
template <typename T> void operator-=(std::vector<T> & vector, const T & shift) {
    for (T & el : vector) el -= shift;
}
// Scalar multiplication of a vector
template <typename T> std::vector<T> operator*(const T & coeff, const std::vector<T> & vector) {
    std::vector<T> result = vector;
    for (T & el : result) el *= coeff;
    return result;
}
template <typename T> void operator*=(std::vector<T> & vector, const T & coeff) {
    for (T & el : vector) el *= coeff;
}
// Scalar division of a vector
template <typename T> std::vector<T> operator/(const std::vector<T> & vector, const T & coeff) {
    std::vector<T> result = vector;
    for (T & el : result) el /= coeff;
    return result;
}
template <typename T> void operator/=(std::vector<T> & vector, const T & coeff) {
    for (T & el : vector) el /= coeff;
}

// Element-wise subtraction of 2 vectors
template <typename T> std::vector<T> operator-(const std::vector<T> & a, const std::vector<T> & b) {
    assert(("The 2 vectors must share a same size", a.size() == b.size()));
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] - b[i];
    return c;
}
// Element-wise multiplication of 2 vectors
template <typename T> std::vector<T> operator*(const std::vector<T> & a, const std::vector<T> & b) {
    assert(("The 2 vectors must share a same size", a.size() == b.size()));
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] * b[i];
    return c;
}

namespace CL { namespace linalg {

// 2-norm of a vector
template <typename T> double norm2(const T * x, const size_t & size) {
    double norm = x[0] * x[0];
    for (size_t i = 1; i < size; i++) norm += x[i] * x[i];
    return std::sqrt(norm);
}
template <typename T> double norm2(const std::vector<T> & x) {
    double norm = x[0] * x[0];
    for (size_t i = 1; i < x.size(); i++) norm += x[i] * x[i];
    return std::sqrt(norm);
}

// infinity-norm of a vector
template <typename T> double normInf(const T * x, const size_t & size) {
    double norm = std::abs(x[0]);
    for (size_t i = 1; i < size; i++) {
        double candidate = std::abs(x[i]);
        if (candidate > norm) norm = candidate;
    }
    return norm;
}
template <typename T> double normInf(const std::vector<T> & x) {
    double norm = std::abs(x[0]);
    for (size_t i = 1; i < x.size(); i++) {
        double candidate = std::abs(x[i]);
        if (candidate > norm) norm = candidate;
    }
    return norm;
}

} // namespace linalg
} // namespace CL

#endif