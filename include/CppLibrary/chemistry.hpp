#ifndef CL_chemistry_hpp
#define CL_chemistry_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

#include <CppLibrary/utility.hpp>

namespace CL { namespace chem {

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
        inline xyz(const std::vector<std::string> & _symbols, const std::vector<T> & _coords,
                   bool _atomic_unit = false)
        : symbols_(_symbols), coords_(_coords), atomic_unit_(_atomic_unit) {}
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

        inline size_t NAtoms() const {return symbols_.size();}

        void print(const std::string & xyz_file) {
            std::ofstream ofs; ofs.open(xyz_file);
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
            ofs.close();
        }
};

template <class T> class xyz_mass : public xyz<T> {
    protected:
        // mass of each atom (a.m.u. or a.u.)
        std::vector<T> masses_;
    public:
        inline xyz_mass() {}
        inline xyz_mass(const std::vector<std::string> & _symbols, const std::vector<T> & _coords,
                        const std::vector<T> & _masses, bool _atomic_unit = false)
         : xyz<T>(_symbols, _coords, _atomic_unit), masses_(_masses) {}
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

} // namespace chem
} // namespace CL

#endif