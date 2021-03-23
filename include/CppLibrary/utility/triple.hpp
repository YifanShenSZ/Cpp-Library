#ifndef CL_utility_triple_hpp
#define CL_utility_triple_hpp

#include <vector>
#include <stdexcept>

namespace CL { namespace utility {

// An analogy to std::pair
template <typename T1, typename T2, typename T3> struct triple {
    T1 first;
    T2 second;
    T3 third;

    triple() {}
    triple(const T1 & _1, const T2 & _2, const T3 & _3) : first(_1), second(_2), third(_3) {}
    template <typename T> triple(const std::initializer_list<T> & items) {
        std::vector<T> vec(items);
        if (vec.size() != 3) throw std::invalid_argument(
        "CL::utility::triple: there must be 3 elements");
        first = vec[0];
        second = vec[1];
        third = vec[2];
    }
    ~triple() {}
};

} // namespace utility
} // namespace CL

#endif