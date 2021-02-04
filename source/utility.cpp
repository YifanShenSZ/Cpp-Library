// General basic routine

#include <cctype>
#include <iostream>
#include <ctime>

namespace CL { namespace utility {

void ShowTime() {
    time_t now = time(0);
    char * dt = ctime(&now);
    std::cout << dt;
}

void EchoCommand(const size_t & argc, const char** argv) {
    std::cout << "Echo of user command line input:\n";
    std::cout << argv[0];
    for (size_t i = 1; i < argc; i++) std::cout << ' ' << argv[i];
    std::cout << '\n';
}

} // namespace utility
} // namespace CL