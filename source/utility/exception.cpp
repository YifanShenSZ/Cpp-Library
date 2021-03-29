#include <CppLibrary/utility/exception.hpp>

#include <cstring>

namespace CL { namespace utility {

not_ready::not_ready() {}
not_ready::not_ready(const std::string & _function_name) : function_name_(_function_name) {}
not_ready::~not_ready() {}

const char * not_ready::what() const throw () {
    std::string message = function_name_ + " is not ready";
    char * c_str = new char[message.length() + 1];
    std::strcpy(c_str, message.c_str());
    return c_str;
}

} // namespace utility
} // namespace CL