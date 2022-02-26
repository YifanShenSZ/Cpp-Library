#ifndef CL_utility_matrix_hpp
#define CL_utility_matrix_hpp

#include <vector>

namespace CL { namespace utility {

// wrap the ugly std::vector<std::vector<T>> when it is a matrix
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

    std::vector<T> & operator[](const size_t & index) {return rows[index];}
    const std::vector<T> & operator[](const size_t & index) const {return rows[index];}
    std::vector<T> & back() {return rows.back();}
    const std::vector<T> & back() const {return rows.back();}

    typename std::vector<std::vector<T>>::iterator begin() noexcept {return rows.begin();}
    typename std::vector<std::vector<T>>::const_iterator begin() const noexcept {return rows.begin();}
    typename std::vector<std::vector<T>>::iterator end() noexcept {return rows.end();}
    typename std::vector<std::vector<T>>::const_iterator end() const noexcept {return rows.end();}
    typename std::vector<std::vector<T>>::iterator rbegin() noexcept {return rows.rbegin();}
    typename std::vector<std::vector<T>>::const_iterator rbegin() const noexcept {return rows.rbegin();}
    typename std::vector<std::vector<T>>::iterator rend() noexcept {return rows.rend();}
    typename std::vector<std::vector<T>>::const_iterator rend() const noexcept {return rows.rend();}

    bool empty() const {return rows.empty();}
    size_t size(const size_t & dim = 0) const {
        if (dim == 0) return rows.size();
        else if(dim == 1) return rows[0].size();
        else throw std::invalid_argument("Dimension must be 0 or 1");
    }

    void resize(const size_t & N) {
        rows.resize(N);
        for (auto & row : rows) row.resize(N);
    }
    void resize(const size_t & M, const size_t & N) {
        rows.resize(M);
        for (auto & row : rows) row.resize(N);
    }

    void pretty_print(std::ostream & stream) const {
        for (const auto & row : rows) {
            for (const auto & el : row) stream << el << ' ';
            stream << '\n';
        }
    }

    // matrix = broadcast scalar
    void operator=(const T & scalar) {
        for (auto & row : rows) std::fill(row.begin(), row.end(), scalar);
    }
    // matrix + broadcast scalar
    CL::utility::matrix<T> operator+(const T & scalar) const {
        CL::utility::matrix<T> result = *this;
        for (auto & row : result) for (auto & el : row) el += scalar;
        return result;
    }
    void operator+=(const T & scalar) {
        for (auto & row : rows) for (auto & el : row) el += scalar;
    }
    // matrix - broadcast scalar
    CL::utility::matrix<T> operator-(const T & scalar) const {
        CL::utility::matrix<T> result = *this;
        for (auto & row : result) for (auto & el : row) el -= scalar;
        return result;
    }
    void operator-=(const T & scalar) {
        for (auto & row : rows) for (auto & el : row) el -= scalar;
    }
    // matrix * broadcast scalar
    CL::utility::matrix<T> operator*(const T & scalar) const {
        CL::utility::matrix<T> result = *this;
        for (auto & row : result) for (auto & el : row) el *= scalar;
        return result;
    }
    void operator*=(const T & scalar) {
        for (auto & row : rows) for (auto & el : row) el *= scalar;
    }
    // matrix / broadcast scalar
    CL::utility::matrix<T> operator/(const T & scalar) const {
        CL::utility::matrix<T> result = *this;
        for (auto & row : result) for (auto & el : row) el /= scalar;
        return result;
    }
    void operator/=(const T & scalar) {
        for (auto & row : rows) for (auto & el : row) el /= scalar;
    }
    // matrix + another matrix
    CL::utility::matrix<T> operator+(const CL::utility::matrix<T> & other) const {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator+: The 2 matrices must share a same shape");
        CL::utility::matrix<T> result(m, n);
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        result[i][j] = (*this)[i][j] + other[i][j];
        return result;
    }
    void operator+=(const CL::utility::matrix<T> & other) {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator+=: The 2 matrices must share a same shape");
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        (*this)[i][j] += other[i][j];
    }
    // matrix - another matrix
    CL::utility::matrix<T> operator-(const CL::utility::matrix<T> & other) const {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator-: The 2 matrices must share a same shape");
        CL::utility::matrix<T> result(m, n);
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        result[i][j] = (*this)[i][j] - other[i][j];
        return result;
    }
    void operator-=(const CL::utility::matrix<T> & other) {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator-=: The 2 matrices must share a same shape");
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        (*this)[i][j] -= other[i][j];
    }
    // matrix * another matrix
    CL::utility::matrix<T> operator*(const CL::utility::matrix<T> & other) const {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator*: The 2 matrices must share a same shape");
        CL::utility::matrix<T> result(m, n);
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        result[i][j] = (*this)[i][j] * other[i][j];
        return result;
    }
    void operator*=(const CL::utility::matrix<T> & other) {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator*=: The 2 matrices must share a same shape");
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        (*this)[i][j] *= other[i][j];
    }
    // matrix / another matrix
    CL::utility::matrix<T> operator/(const CL::utility::matrix<T> & other) const {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator/: The 2 matrices must share a same shape");
        CL::utility::matrix<T> result(m, n);
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        result[i][j] = (*this)[i][j] / other[i][j];
        return result;
    }
    void operator/=(const CL::utility::matrix<T> & other) {
        size_t m = this->size(0), n = this->size(1);
        if (m != other.size(0) || n != other.size(1)) throw std::invalid_argument(
        "CL::utility::matrix::operator/=: The 2 matrices must share a same shape");
        for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        (*this)[i][j] /= other[i][j];
    }
};

} // namespace utility
} // namespace CL

#endif