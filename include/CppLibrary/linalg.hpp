// Vector operation for pointer, std::valarray, std::vector

#ifndef CL_linalg_hpp
#define CL_linalg_hpp

#include <cmath>
#include <vector>
#include <stdexcept>

// vector + broadcast scalar
template <typename T> std::vector<T> operator+(const std::vector<T> & vector, const T & scalar) {
    std::vector<T> result = vector;
    for (T & el : result) el += scalar;
    return result;
}
template <typename T> void operator+=(std::vector<T> & vector, const T & scalar) {
    for (T & el : vector) el += scalar;
}
// vector - broadcast scalar
template <typename T> std::vector<T> operator-(const std::vector<T> & vector, const T & scalar) {
    std::vector<T> result = vector;
    for (T & el : result) el -= scalar;
    return result;
}
template <typename T> void operator-=(std::vector<T> & vector, const T & scalar) {
    for (T & el : vector) el -= scalar;
}
// vector * broadcast scalar
template <typename T> std::vector<T> operator*(const std::vector<T> & vector, const T & scalar) {
    std::vector<T> result = vector;
    for (T & el : result) el *= scalar;
    return result;
}
template <typename T> void operator*=(std::vector<T> & vector, const T & scalar) {
    for (T & el : vector) el *= scalar;
}
// vector / broadcast scalar
template <typename T> std::vector<T> operator/(const std::vector<T> & vector, const T & scalar) {
    std::vector<T> result = vector;
    for (T & el : result) el /= scalar;
    return result;
}
template <typename T> void operator/=(std::vector<T> & vector, const T & scalar) {
    for (T & el : vector) el /= scalar;
}

// a + b
template <typename T> std::vector<T> operator+(const std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator+: The 2 vectors must share a same size");
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] + b[i];
    return c;
}
template <typename T> void operator+=(std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator+=: The 2 vectors must share a same size");
    for (size_t i = 0; i < a.size(); i++) a[i] += b[i];
}
// a - b
template <typename T> std::vector<T> operator-(const std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator-: The 2 vectors must share a same size");
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] - b[i];
    return c;
}
template <typename T> void operator-=(std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator-=: The 2 vectors must share a same size");
    for (size_t i = 0; i < a.size(); i++) a[i] -= b[i];
}
// a * b
template <typename T> std::vector<T> operator*(const std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator*: The 2 vectors must share a same size");
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] * b[i];
    return c;
}
template <typename T> void operator*=(std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator*=: The 2 vectors must share a same size");
    for (size_t i = 0; i < a.size(); i++) a[i] *= b[i];
}
// a / b
template <typename T> std::vector<T> operator/(const std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator/: The 2 vectors must share a same size");
    std::vector<T> c = a;
    for (size_t i = 0; i < a.size(); i++) c[i] = a[i] / b[i];
    return c;
}
template <typename T> void operator/=(std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() != b.size()) throw std::invalid_argument(
    "std::vector::operator/=: The 2 vectors must share a same size");
    for (size_t i = 0; i < a.size(); i++) a[i] /= b[i];
}

template <typename T> bool operator<(const std::vector<T> & a, const std::vector<T> & b) {
    if (a.size() < b.size()) return true;
    else if (a.size() > b.size()) return false;
    else for (size_t i = 0; i < a.size(); i++)
    if (a[i] < b[i]) return true;
    else if (a[i] > b[i]) return false;
    return false;
}

namespace CL { namespace linalg {

// 2-norm of a vector
template <typename T> double norm2(const T * x, const size_t & size) {
    double norm = x[0] * x[0];
    for (size_t i = 1; i < size; i++) norm += x[i] * x[i];
    return std::sqrt(norm);
}
template <typename T> double norm2(const std::valarray<T> & x) {
    double norm = x[0] * x[0];
    for (size_t i = 1; i < x.size(); i++) norm += x[i] * x[i];
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
template <typename T> double normInf(const std::valarray<T> & x) {
    double norm = std::abs(x[0]);
    for (size_t i = 1; i < x.size(); i++) {
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