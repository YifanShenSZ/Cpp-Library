// Vector & matrix & high order tensor operation
// for pointer and std::vector

#include <cmath>
#include <vector>

namespace CL { namespace LA {

// 2-norm of vector x
double norm2(const double * x, const int & N) {
    double norm = x[0] * x[0];
    for (int i = 1; i < N; i++) norm += x[i] * x[i];
    return std::sqrt(norm);
}
double norm2(const std::vector<double> & x) {
    double norm = x[0] * x[0];
    for (size_t i = 1; i < x.size(); i++) norm += x[i] * x[i];
    return std::sqrt(norm);
}

} // namespace LA
} // namespace CL