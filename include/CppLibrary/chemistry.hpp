#ifndef CL_chemistry_hpp
#define CL_chemistry_hpp

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>

#include <CppLibrary/utility.hpp>
#include <CppLibrary/linalg.hpp>

namespace CL { namespace chem {

// Given element symbol, return element number
size_t symbol2number(const std::string & symbol);

// Given element number, return element symbol
std::string number2symbol(const size_t & number);

template <class T> class xyz {
    protected:
        // Symbol of each atom
        std::vector<std::string> symbols_;
        // Cartesian coordinate of each atom (Bohr or A)
        std::vector<T> coords_;
        // atomic unit or usual unit
        bool atomic_unit_;
    public:
        inline xyz() {}
        inline xyz(const std::vector<std::string> & _symbols, const std::vector<T> & _coords, bool _atomic_unit = false)
        : symbols_(_symbols), coords_(_coords), atomic_unit_(_atomic_unit) {
            if (3 * _symbols.size() != _coords.size()) throw std::invalid_argument(
            "CL::chem::xyz: inconsistent number of atoms between symbols and coordinates");
        }
        // Construct from .xyz file
        xyz(const std::string & xyz_file, bool _atomic_unit = false)
        : atomic_unit_(_atomic_unit) {
            std::ifstream ifs; ifs.open(xyz_file);
            if (! ifs.good()) throw CL::utility::file_error(xyz_file);
                std::string line;
                std::getline(ifs, line);
                size_t NAtoms = std::stoul(line);
                symbols_.resize(NAtoms);
                coords_.resize(3 * NAtoms);
                std::getline(ifs, line);
                for(size_t i = 0; i < NAtoms; i++) {
                    if (! ifs.good()) throw CL::utility::file_error(xyz_file);
                    ifs >> symbols_[i];
                    ifs >>  coords_[3 * i];
                    ifs >>  coords_[3 * i + 1];
                    ifs >>  coords_[3 * i + 2];
                }
            ifs.close();
            if (_atomic_unit) for(T & el : coords_) el *= 1.8897261339212517;
        }
        inline ~xyz() {}

        inline const std::vector<std::string> & symbols() const {return symbols_;}
        inline const std::vector<T> & coords() const {return coords_;}
        inline const bool & atomic_unit() const {return atomic_unit_;}

        inline size_t NAtoms() const {return symbols_.size();}

        // print molecular structure in xyz format
        void print(std::ofstream & ofs) const {
            ofs << NAtoms() << '\n' << '\n';
            if (atomic_unit_) for(size_t i = 0; i < NAtoms(); i++) {
                ofs << symbols_[i]                              << "    ";
                ofs <<  coords_[3 * i]     / 1.8897261339212517 << "    ";
                ofs <<  coords_[3 * i + 1] / 1.8897261339212517 << "    ";
                ofs <<  coords_[3 * i + 2] / 1.8897261339212517 << '\n';
            }
            else for(size_t i = 0; i < NAtoms(); i++) {
                ofs << symbols_[i]         << "    ";
                ofs <<  coords_[3 * i]     << "    ";
                ofs <<  coords_[3 * i + 1] << "    ";
                ofs <<  coords_[3 * i + 2] << '\n';
            }
        }
        // print molecular structure to an xyz file
        void print(const std::string & xyz_file) const {
            std::ofstream ofs; ofs.open(xyz_file);
            this->print(ofs);
            ofs.close();
        }
};

template <class T> class xyz_mass : public xyz<T> {
    protected:
        // mass of each atom (a.m.u. or a.u.)
        std::vector<T> masses_;
    public:
        inline xyz_mass() {}
        inline xyz_mass(const xyz<T> & _xyz, const std::vector<T> & _masses)
        : xyz<T>(_xyz), masses_(_masses) {
            if (_xyz.NAtoms() != _masses.size()) throw std::invalid_argument(
            "CL::chem::xyz_mass: inconsistent number of atoms between xyz and masses");
        }
        inline xyz_mass(const std::vector<std::string> & _symbols, const std::vector<T> & _coords,
                        const std::vector<T> & _masses, bool _atomic_unit = false)
        : xyz<T>(_symbols, _coords, _atomic_unit), masses_(_masses) {
            if (_symbols.size() != _masses.size()) throw std::invalid_argument(
            "CL::chem::xyz_mass: inconsistent number of atoms between symbols and masses");
        }
        // Construct from .xyz file and mass file
        // mass file can have arbitrary format in atomic mass unit
        xyz_mass(const std::string & xyz_file, const std::string & mass_file, bool _atomic_unit = false)
        : xyz<T>(xyz_file, _atomic_unit) {
            std::ifstream ifs; ifs.open(mass_file);
            if (! ifs.good()) throw CL::utility::file_error(mass_file);
            masses_.resize(xyz<T>::NAtoms());
            for(T & mass : masses_) {
                if (! ifs.good()) throw CL::utility::file_error(mass_file);
                ifs >> mass;
            }
            ifs.close();
            if (_atomic_unit) for(T & mass : masses_) mass *= 1822.888486192;
        }
        // Construct from Columbus7 geom file
        xyz_mass(const std::string & geom_file, bool _atomic_unit = true) {
            xyz<T>::atomic_unit_ = _atomic_unit;
            size_t NAtoms = utility::NLines(geom_file);
            std::ifstream ifs; ifs.open(geom_file);
            if (! ifs.good()) throw CL::utility::file_error(geom_file);
            xyz<T>::symbols_.resize(NAtoms);
            xyz<T>::coords_.resize(3 * NAtoms);
            masses_.resize(NAtoms);
            for(size_t i = 0; i < NAtoms; i++) {
                if (! ifs.good()) throw CL::utility::file_error(geom_file);
                ifs >> xyz<T>::symbols_[i];
                float temp; ifs >> temp;
                ifs >> xyz<T>::coords_[3 * i];
                ifs >> xyz<T>::coords_[3 * i + 1];
                ifs >> xyz<T>::coords_[3 * i + 2];
                ifs >> masses_[i];
            }
            ifs.close();
            if (_atomic_unit) for(T & mass : masses_) mass *= 1822.888486192;
            else for (T & coord : xyz<T>::coords_) coord /= 1.8897261339212517;
        }
        inline ~xyz_mass() {}

        inline const std::vector<T> & masses() const {return masses_;}
};

template <class T> class xyz_vib : public xyz<T> {
    protected:
        // Vibrational frequencies
        std::vector<T> frequencies_;
        // Cartesian normal modes
        CL::utility::matrix<T> modes_;
    public:
        inline xyz_vib() {}
        inline xyz_vib(const xyz<T> & _xyz, const std::vector<T> & _frequencies, const CL::utility::matrix<T> & _modes)
        : xyz<T>(_xyz), frequencies_(_frequencies), modes_(_modes) {
            if (_frequencies.size() != _modes.size()) throw std::invalid_argument(
            "CL::chem::xyz_vib: inconsistent number of normal modes between frequencies and normal modes");
        }
        inline xyz_vib(const std::vector<std::string> & _symbols, const std::vector<T> & _coords,
        const std::vector<T> & _frequencies, const CL::utility::matrix<T> & _modes, bool _atomic_unit = false)
        : xyz<T>(_symbols, _coords, _atomic_unit), frequencies_(_frequencies), modes_(_modes) {
            if (_frequencies.size() != _modes.size()) throw std::invalid_argument(
            "CL::chem::xyz_vib: inconsistent number of normal modes between frequencies and normal modes");
        }
        inline ~xyz_vib() {}

        inline const std::vector<T> & frequencies() const {return frequencies_;}
        inline const std::vector<std::vector<T>> & modes() const {return modes_;}

        // Print molecular structure and normal modes to an Avogadro file
        void print(const std::string & avogadro_file) const {
            std::ofstream ofs; ofs.open(avogadro_file);
            ofs << "Gaussian, Inc.  All Rights Reserved.\n"
                << " # freq hf/3-21g\n"
                << " Charge =  0 Multiplicity = 1\n\n"
                << "                         Standard orientation:                         \n"
                << " ---------------------------------------------------------------------\n"
                << " Center     Atomic      Atomic             Coordinates (Angstroms)\n"
                << " Number     Number       Type             X           Y           Z\n"
                << " ---------------------------------------------------------------------\n";
            auto coords = xyz<T>::coords_;
            if (xyz<T>::atomic_unit_) coords /= 1.8897261339212517;
            for (size_t i = 0; i < xyz<T>::NAtoms(); i++)
            ofs << std::setw(7) << i + 1
                << std::setw(11) << symbol2number(xyz<T>::symbols_[i])
                << std::setw(12) << 0 << "    "
                << std::fixed << std::setw(12) << std::setprecision(6) << coords[3 * i + 0]
                << std::fixed << std::setw(12) << std::setprecision(6) << coords[3 * i + 1]
                << std::fixed << std::setw(12) << std::setprecision(6) << coords[3 * i + 2] << '\n';
            ofs << " ---------------------------------------------------------------------\n";
            auto freqs = frequencies_;
            if (xyz<T>::atomic_unit_) freqs /= 4.556335830019422e-6;
            auto modes = modes_;
            for (auto & mode : modes) mode *= 9.99 / CL::linalg::normInf(mode);
            for (size_t i = 0; i < frequencies_.size() / 3; i++) {
                ofs << std::setw(23) << 3 * i + 1
                    << std::setw(23) << 3 * i + 2
                    << std::setw(23) << 3 * i + 3 << '\n'
                    << " Frequencies --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << freqs[3 * i + 0]
                    << std::fixed << std::setw(23) << std::setprecision(4) << freqs[3 * i + 1]
                    << std::fixed << std::setw(23) << std::setprecision(4) << freqs[3 * i + 2] << '\n'
                    << " Red. masses --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Frc consts  --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " IR Inten    --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Raman Activ --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (P) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (U) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << "  Atom  AN      X      Y      Z        X      Y      Z        X      Y      Z\n";
                for (size_t j = 0; j < xyz<T>::NAtoms(); j++)
                ofs << std::setw(6) << j + 1
                    << std::setw(4) << symbol2number(xyz<T>::symbols_[j]) << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 2] << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 2] << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 2][3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 2][3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 2][3 * j + 2] << '\n';
            }
            if (frequencies_.size() % 3 == 1) {
                ofs << std::setw(23) << frequencies_.size() << '\n'
                    << " Frequencies --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << freqs.back() << '\n'
                    << " Red. masses --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << " Frc consts  --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << " IR Inten    --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << " Raman Activ --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (P) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (U) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0 << '\n'
                    << "  Atom  AN      X      Y      Z\n";
                for (size_t j = 0; j < xyz<T>::NAtoms(); j++)
                ofs << std::setw(6) << j + 1
                    << std::setw(4) << symbol2number(xyz<T>::symbols_[j]) << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes.back()[3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes.back()[3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes.back()[3 * j + 2] << '\n';
            }
            else if (frequencies_.size() % 3 == 2) {
                size_t i = frequencies_.size() / 3;
                ofs << std::setw(23) << 3 * i + 1
                    << std::setw(23) << 3 * i + 2 << '\n'
                    << " Frequencies --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << freqs[3 * i + 0]
                    << std::fixed << std::setw(23) << std::setprecision(4) << freqs[3 * i + 1] << '\n'
                    << " Red. masses --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Frc consts  --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " IR Inten    --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Raman Activ --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (P) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << " Depolar (U) --"
                    << std::fixed << std::setw(12) << std::setprecision(4) << 0.0
                    << std::fixed << std::setw(23) << std::setprecision(4) << 0.0 << '\n'
                    << "  Atom  AN      X      Y      Z        X      Y      Z\n";
                for (size_t j = 0; j < xyz<T>::NAtoms(); j++)
                ofs << std::setw(6) << j + 1
                    << std::setw(4) << symbol2number(xyz<T>::symbols_[j]) << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 0][3 * j + 2] << "  "
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 0]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 1]
                    << std::fixed << std::setw(7) << std::setprecision(2) << modes[3 * i + 1][3 * j + 2] << '\n';
            }
            ofs.close();
        }
};

} // namespace chem
} // namespace CL

#endif