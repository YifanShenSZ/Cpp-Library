#ifndef CL_utility_matrix_hpp
#define CL_utility_matrix_hpp

#include <vector>

namespace CL { namespace utility {

// Wrap the ugly std::vector<std::vector<T>> when it is a matrix
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
        if (dim != 0 && dim != 1) throw std::invalid_argument(
        "Dimension must be 0 or 1");
        if (dim == 0) return rows.size();
        else          return rows[0].size();
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

    void operator-=(const T & sub) {
        for (auto & row : rows) for (auto & el : row) el -= sub;
    }
};

} // namespace utility
} // namespace CL

#endif