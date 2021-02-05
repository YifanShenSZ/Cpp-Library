// General basic routine

#include <cctype>
#include <iostream>
#include <ctime>

namespace CL { namespace utility {

void show_time(std::ostream & stream) {
    time_t now = time(0);
    char * dt = ctime(&now);
    stream << dt;
}

void echo_command(const size_t & argc, const char** argv, std::ostream & stream) {
    stream << "Echo of user command line input:\n";
    stream << argv[0];
    for (size_t i = 1; i < argc; i++) stream << ' ' << argv[i];
    stream << '\n';
}

} // namespace utility
} // namespace CL