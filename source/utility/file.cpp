// General basic routines for file

#include <fstream>
#include <vector>
#include <cctype>
#include <cstring>

#include <CppLibrary/utility/file.hpp>

namespace CL { namespace utility {

file_error::file_error() {}
file_error::file_error(const std::string & _file_name) : file_name_(_file_name) {}
file_error::~file_error() {}

const char * file_error::what() const throw () {
    std::string message = "Error during processing file " + file_name_;
    char * c_str = new char[message.length() + 1];
    std::strcpy(c_str, message.c_str());
    return c_str;
}





// Get the file name from a path (no need to use this since c++17)
std::string GetFileName(std::string path, bool extension, char seperator) {
	std::size_t dotPos = path.rfind('.');
	std::size_t sepPos = path.rfind(seperator);
	if(sepPos == std::string::npos)
	return path.substr(0, path.size() - (extension || dotPos == std::string::npos ? 0 : (dotPos+1)));
	else
    return path.substr(sepPos+1, path.size() - (extension || dotPos == std::string::npos ? 0 : (dotPos+1)));
}

// Get the prefix from a path (no need to use this since c++17)
std::string GetPrefix(std::string path, char seperator) {
    std::size_t sepPos = path.rfind(seperator);
    return path.substr(0, (sepPos+1) < path.size() ? (sepPos+1) : path.size());
}

// Get the number of lines in a file
size_t NLines(const std::string & file) {
    size_t n = 0;
    std::ifstream ifs; ifs.open(file);
    while (true) {
        std::string line;
        std::getline(ifs, line);
        if (! ifs.good()) break;
        n++;
    }
    ifs.close();
    return n;
}

// Get the number of strings in a file
size_t NStrings(const std::string & file) {
    size_t n = 0;
    std::ifstream ifs; ifs.open(file);
    while (true) {
        std::string str;
        ifs >> str;
        if (! ifs.good()) break;
        n++;
    }
    ifs.close();
    return n;
}

// Read a vector from file
std::vector<double> read_vector(std::ifstream & ifs) {
    std::vector<double> data;
    double reader;
    ifs >> reader;
    while(ifs.good()) {
        data.push_back(reader);
        ifs >> reader;
    }
    return data;
}
std::vector<double> read_vector(const std::string & file) {
    std::vector<double> data;
    std::ifstream ifs; ifs.open(file);
        double reader;
        ifs >> reader;
        while(ifs.good()) {
            data.push_back(reader);
            ifs >> reader;
        }
    ifs.close();
    return data;
}

} // namespace utility
} // namespace CL