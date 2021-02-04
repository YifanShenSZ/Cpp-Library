// General basic routines for string

#include <sstream>
#include <vector>
#include <forward_list>
#include <iterator>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace CL { namespace utility {

// Trim from start
void ltrim(std::string & s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
}
// Trim from end
void rtrim(std::string & s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}
// Trim from both ends
void trim(std::string & s) {
    ltrim(s);
    rtrim(s);
}

// Split text with white space
std::vector<std::string> split(const std::string & text) {
    std::istringstream iss(text);
    std::vector<std::string> result(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    return result;
}
// text_split harvests the splitted string vector
void split(const std::string & text, std::vector<std::string> & text_split) {
    std::istringstream iss(text);
    std::vector<std::string> result(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    text_split = result;
}
// text_split harvests the splitted string forward list
void split(const std::string & text, std::forward_list<std::string> & text_split) {
    std::istringstream iss(text);
    std::forward_list<std::string> result(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    text_split = result;
}

// Split text with any single character
std::vector<std::string> split(const std::string & text, const char & delimiter) {
    std::vector<std::string> text_split;
    size_t current, previous = 0;
    current = text.find(delimiter);
    while (current != std::string::npos) {
        text_split.push_back(text.substr(previous, current - previous));
        previous = current + 1;
        current = text.find(delimiter, previous);
    }
    text_split.push_back(text.substr(previous, current - previous));
    return text_split;
}
// text_split harvests the splitted string vector
void split(const std::string & text, std::vector<std::string> & text_split, const char & delimiter) {
    size_t current, previous = 0;
    current = text.find(delimiter);
    while (current != std::string::npos) {
        text_split.push_back(text.substr(previous, current - previous));
        previous = current + 1;
        current = text.find(delimiter, previous);
    }
    text_split.push_back(text.substr(previous, current - previous));
}

} // namespace utility
} // namespace CL