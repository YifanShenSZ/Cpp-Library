#ifndef CL_utility_exception_hpp
#define CL_utility_exception_hpp

#include <iostream>
#include <exception>

namespace CL { namespace utility {

class not_ready : public std::exception {
    private:
        std::string function_name_;
    public:
        not_ready();
        not_ready(const std::string & _function_name);
        ~not_ready();

        const char * what() const throw();
};

} // namespace utility
} // namespace CL

#endif