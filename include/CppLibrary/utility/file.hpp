// General basic routines for file

#ifndef CL_utility_file_hpp
#define CL_utility_file_hpp

#include <cctype>
#include <string>
#include <vector>

namespace CL { namespace utility {

// Get the file name from a path (no need to use this since c++17)
std::string GetFileName(std::string path, bool withExtension = true, char seperator = '/');

// Get the prefix from a path (no need to use this since c++17)
std::string GetPrefix(std::string path, char seperator = '/');

// Get the number of lines in a file
size_t NLines(const std::string & file);

// Get the number of strings in a file
size_t NStrings(const std::string & file);

// Read a vector from file
std::vector<double> read_vector(const std::string & file);

} // namespace utility
} // namespace CL

#endif