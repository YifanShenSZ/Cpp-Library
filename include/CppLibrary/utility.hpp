// General basic routine

#ifndef CL_utility_hpp
#define CL_utility_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <forward_list>
#include <iterator>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace CL { namespace utility {

void ShowTime();

void EchoCommand(const int & argc, const char** argv);

// Get the file name from a path (no need to use this since c++17)
std::string GetFileName(std::string path, bool withExtension = true, char seperator = '/');

// Get the prefix from a path (no need to use this since c++17)
std::string GetPrefix(std::string path, char seperator = '/');

// Get the number of lines in a file
size_t NLines(const std::string & file);

// Get the number of strings in a file
size_t NStrings(const std::string & file);

// Trim from start
void ltrim(std::string & s);
// Trim from end
void rtrim(std::string & s);
// Trim from both ends
void trim(std::string & s);

// Split text with white space
std::vector<std::string> split(const std::string & text);
// text_split harvests the splitted string vector
void split(const std::string & text, std::vector<std::string> & text_split);
// text_split harvests the splitted string forward list
void split(const std::string & text, std::forward_list<std::string> & text_split);

// Split text with any single character
std::vector<std::string> split(const std::string & text, const char & delimiter);
// text_split harvests the splitted string vector
void split(const std::string & text, std::vector<std::string> & text_split, const char & delimiter);

// Allocate (deallocate) continuous memory for an n-dimensional array A(N1, N2, ..., Nn)
// Matrix
template <typename T> void CreateArray(T ** & A, const int & N1, const int & N2) {
    if (nullptr != A) std::cout << "CreateArray warning: pointer != nullptr, the matrix may has been allocated\n";
    if (N1 == 0) throw std::invalid_argument("CreateArray error: 1st dimensionality = 0");
    if (N2 == 0) throw std::invalid_argument("CreateArray error: 2nd dimensionality = 0");
    try {
        A = new T * [N1];
        A[0] = new T[N1*N2];
        for (int i = 1; i < N1; i++) A[i] = A[i-1] + N2;
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
template <typename T> void CreateArray(T *** & A, const int & N1, const int & N2, const int & N3) {
    if (nullptr != A) std::cout << "CreateArray warning: pointer != nullptr, the 3rd-order tensor may has been allocated\n";
    if (N1 == 0) throw std::invalid_argument("CreateArray error: 1st dimensionality = 0");
    if (N2 == 0) throw std::invalid_argument("CreateArray error: 2nd dimensionality = 0");
    if (N3 == 0) throw std::invalid_argument("CreateArray error: 3rd dimensionality = 0");
    try {
        int i, j;
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
template <typename T> void DeleteArray(T *** & A, const int & N1) {
    if (nullptr == A) {
        std::cout << "DeleteArray warning: pointer == nullptr, the 3rd-order tensor has been deallocated\n";
    }
    else {
        delete [] A[0][0];
        for (int i = 0; i < N1; i++) delete [] A[i];
        delete [] A;
        A = nullptr;
    }
}

} // namespace utility
} // namespace CL

#endif