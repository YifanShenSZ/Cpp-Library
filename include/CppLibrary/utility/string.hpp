// General basic routines for string

#ifndef CL_utility_string_hpp
#define CL_utility_string_hpp

#include <cctype>
#include <string>
#include <vector>
#include <forward_list>

namespace CL { namespace utility {

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

} // namespace utility
} // namespace CL

#endif