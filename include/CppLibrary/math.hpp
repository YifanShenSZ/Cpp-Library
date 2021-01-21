#ifndef CL_math_hpp
#define CL_math_hpp

namespace CL { namespace math {

// exact factorial for 0 <= N <= 20
// double precision for 21 <= N <= 40
// 8 significant figures for N >= 41
double dFactorial(const int & N);

// exact double factorial for -1 <= N <= 30
// double precision for 31 <= N <= 40
// depending on factorial for N >= 41
double dFactorial2(const int & N);

// exact permutation for 0 <= M <= 10 or N < 10
// depending on factorial otherwise
double dPermutation(const int & M, const int & N);

// exact combination for 0 <= M <= 11 or (N = 0 or N = 1 or N = M - 1 or N = M)
// depending on permutation and factorial otherwise
double dCombination(const int & M, const int & N);

// exact factorial for N <= 20
// 8 bytes integer cannot represent N >= 21
unsigned long long iFactorial(const int & N);

// exact double factorial for N <= 33
// 8 bytes integer cannot represent N >= 34
unsigned long long iFactorial2(const int & N);

// exact permutation for 0 <= M <= 10 or N < 10
// depending on factorial otherwise
unsigned long long iPermutation(const int & M, const int & N);

// exact combination for 0 <= M <= 11 or (N = 0 or N = 1 or N = M - 1 or N = M)
// depending on permutation and factorial otherwise
unsigned long long iCombination(const int & M, const int & N);

} // namespace math
} // namespace CL

#endif