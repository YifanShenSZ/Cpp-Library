#include <cstddef>
#include <string>
#include <stdexcept>

namespace CL { namespace chem {

// Given element symbol, return element number
size_t symbol2number(const std::string & symbol) {
         if (symbol == "H" ) return 1;
    else if (symbol == "He") return 2;
    else if (symbol == "Li") return 3;
    else if (symbol == "Be") return 4;
    else if (symbol == "B" ) return 5;
    else if (symbol == "C" ) return 6;
    else if (symbol == "N" ) return 7;
    else if (symbol == "O" ) return 8;
    else if (symbol == "F" ) return 9;
    else if (symbol == "Ne") return 10;
    else if (symbol == "Na") return 11;
    else if (symbol == "Mg") return 12;
    else if (symbol == "Al") return 13;
    else if (symbol == "Si") return 14;
    else if (symbol == "P" ) return 15;
    else if (symbol == "S" ) return 16;
    else if (symbol == "Cl") return 17;
    else if (symbol == "Ar") return 18;
    else if (symbol == "K" ) return 19;
    else if (symbol == "Ca") return 20;
    else if (symbol == "Sc") return 21;
    else if (symbol == "Ti") return 22;
    else if (symbol == "V" ) return 23;
    else if (symbol == "Cr") return 24;
    else if (symbol == "Mn") return 25;
    else if (symbol == "Fe") return 26;
    else if (symbol == "Co") return 27;
    else if (symbol == "Ni") return 28;
    else if (symbol == "Cu") return 29;
    else if (symbol == "Zn") return 30;
    else if (symbol == "Ga") return 31;
    else if (symbol == "Ge") return 32;
    else if (symbol == "As") return 33;
    else if (symbol == "Se") return 34;
    else if (symbol == "Br") return 35;
    else if (symbol == "Kr") return 36;
    else throw std::invalid_argument(
    "CL::chem::symbol2number: unsupported element symbol. Current version only supports H to Kr");
}

// Given element number, return element symbol
std::string number2symbol(const size_t & number) {
    switch (number) {
    case 1 : return "H";
    case 2 : return "He";
    case 3 : return "Li";
    case 4 : return "Be";
    case 5 : return "B";
    case 6 : return "C";
    case 7 : return "N";
    case 8 : return "O";
    case 9 : return "F";
    case 10: return "Ne";
    case 11: return "Na";
    case 12: return "Mg";
    case 13: return "Al";
    case 14: return "Si";
    case 15: return "P";
    case 16: return "S";
    case 17: return "Cl";
    case 18: return "Ar";
    case 19: return "K";
    case 20: return "Ca";
    case 21: return "Sc";
    case 22: return "Ti";
    case 23: return "V";
    case 24: return "Cr";
    case 25: return "Mn";
    case 26: return "Fe";
    case 27: return "Co";
    case 28: return "Ni";
    case 29: return "Cu";
    case 30: return "Zn";
    case 31: return "Ga";
    case 32: return "Ge";
    case 33: return "As";
    case 34: return "Se";
    case 35: return "Br";
    case 36: return "Kr";
    default: throw std::invalid_argument(
    "CL::chem::number2symbol: unsupported element number. Current version only supports 1 to 36");
    }
}

} // namespace chem
} // namespace CL