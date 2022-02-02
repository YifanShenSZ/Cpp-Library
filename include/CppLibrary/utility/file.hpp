// General basic routines for file

#ifndef CL_utility_file_hpp
#define CL_utility_file_hpp

#include <cctype>
#include <string>
#include <vector>

namespace CL { namespace utility {

class file_error : public std::exception {
    private:
        std::string file_name_;
    public:
        file_error();
        file_error(const std::string & _file_name);
        ~file_error();

        const char * what() const throw();
};

// get the file name from a path (no need to use this since c++17)
std::string GetFileName(std::string path, bool withExtension = true, char seperator = '/');

// get the prefix from a path (no need to use this since c++17)
std::string GetPrefix(std::string path, char seperator = '/');

// get the number of lines in a file
size_t NLines(const std::string & file);

// get the number of strings in a file
size_t NStrings(const std::string & file);

// read a vector from file
std::vector<double> read_vector(std::ifstream & ifs);
std::vector<double> read_vector(const std::string & file);

} // namespace utility
} // namespace CL

#endif