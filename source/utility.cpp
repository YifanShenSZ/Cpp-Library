// General basic routine

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

void ShowTime() {
    time_t now = time(0);
    char * dt = ctime(&now);
    std::cout << dt;
}

void EchoCommand(const int & argc, const char** argv) {
    std::cout << "Echo of user command line input:\n";
    std::cout << argv[0];
    for (size_t i = 1; i < argc; i++) std::cout << ' ' << argv[i];
    std::cout << '\n';
}

// Get the file name from a path (no need to use this since c++17)
std::string GetFileName(std::string path, bool extension = true, char seperator = '/') {
	std::size_t dotPos = path.rfind('.');
	std::size_t sepPos = path.rfind(seperator);
	if(sepPos == std::string::npos)
	return path.substr(0, path.size() - (extension || dotPos == std::string::npos ? 0 : (dotPos+1)));
	else
    return path.substr(sepPos+1, path.size() - (extension || dotPos == std::string::npos ? 0 : (dotPos+1)));
}

// Get the prefix from a path (no need to use this since c++17)
std::string GetPrefix(std::string path, char seperator = '/') {
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
        while (ifs.good()) {
            std::string str;
            ifs >> str;
            n++;
        } n--;
    ifs.close();
    return n;
}

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