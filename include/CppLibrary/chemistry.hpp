#ifndef CL_chemistry_hpp
#define CL_chemistry_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

#include "utility.hpp"

namespace CL { namespace chem {

template <class T> class xyz {
    protected:
        // Symbol of each atom
        std::vector<std::string> symbols_;
        // Cartesian coordinate of each atom
        std::vector<T> coords_;
    public:
        inline xyz() {}
        inline xyz(const std::vector<std::string> & _symbols, const std::vector<T> & _coords) : symbols_(_symbols), coords_(_coords) {}
        // Construct from .xyz file
        xyz(const std::string & xyz_file, bool atomic_unit = false) {
            std::ifstream ifs; ifs.open(xyz_file);
                std::string line;
                std::getline(ifs, line);
                size_t NAtoms = std::stoul(line);
                symbols_.resize(NAtoms);
                coords_.resize(3 * NAtoms);
                std::getline(ifs, line);
                for(size_t i = 0; i < NAtoms; i++) {
                    assert(("There must be a same number of atoms as claimed", ifs.good()));
                    ifs >> symbols_[i];
                    ifs >>  coords_[3 * i];
                    ifs >>  coords_[3 * i + 1];
                    ifs >>  coords_[3 * i + 2];
                }
            ifs.close();
            if (atomic_unit) for(T & el : coords_) el *= 1.8897261339212517;
        }
        inline ~xyz() {}

        inline std::vector<std::string> symbols() const {return symbols_;}
        inline std::vector<T> coords() const {return coords_;}

        inline size_t NAtoms() const {return symbols_.size();}

        void print(const std::string & xyz_file) {
            std::ofstream ofs; ofs.open(xyz_file);
                ofs << NAtoms() << '\n' << '\n';
                for(size_t i = 0; i < NAtoms(); i++) {
                    ofs << symbols_[i]         << "    ";
                    ofs <<  coords_[3 * i]     << "    ";
                    ofs <<  coords_[3 * i + 1] << "    ";
                    ofs <<  coords_[3 * i + 2] << '\n';
                }
            ofs.close();
        }
};

template <class T> class xyz_mass : public xyz<T> {
    protected:
        // mass of each atom
        std::vector<T> masses_;
    public:
        inline xyz_mass() {}
        inline xyz_mass(const std::vector<std::string> & _symbols, const std::vector<T> & _coords, const std::vector<T> & _masses) : xyz<T>(_symbols, _coords), masses_(_masses) {}
        // Construct from .xyz file and mass file
        // mass file can have arbitrary format in atomic mass unit
        xyz_mass(const std::string & xyz_file, const std::string & massfile, bool atomic_unit = false)
        : xyz<T>(xyz_file, atomic_unit) {
            std::ifstream ifs; ifs.open(massfile);
                masses_.resize(xyz<T>::NAtoms());
                for(T & mass : masses_) {
                    assert(("There must be a same number of masses as atoms", ifs.good()));
                    ifs >> mass;
                }
            ifs.close();
            if (atomic_unit) for(T & mass : masses_) mass *= 1822.888486192;
        }
        // Construct from Columbus7 geom file
        xyz_mass(const std::string & geom_file, bool atomic_unit = false) {
            size_t NAtoms = utility::NLines(geom_file);
            std::ifstream ifs; ifs.open(geom_file);
                xyz<T>::symbols_.resize(NAtoms);
                xyz<T>::coords_.resize(3 * NAtoms);
                masses_.resize(NAtoms);
                for(size_t i = 0; i < NAtoms; i++) {
                    ifs >> xyz<T>::symbols_[i];
                    float temp; ifs >> temp;
                    ifs >> xyz<T>::coords_[3 * i];
                    ifs >> xyz<T>::coords_[3 * i + 1];
                    ifs >> xyz<T>::coords_[3 * i + 2];
                    ifs >> masses_[i];
                }
            ifs.close();
            if (atomic_unit) for(T & mass : masses_) mass *= 1822.888486192;
            else for (T & coord : xyz<T>::coords_) coord /= 1.8897261339212517;
        }
        inline ~xyz_mass() {}

        inline std::vector<T> masses() const {return masses_;}
};

} // namespace chem
} // namespace CL

#endif