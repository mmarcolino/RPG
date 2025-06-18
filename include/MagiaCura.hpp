#ifndef MAGIA_CURA_HPP
#define MAGIA_CURA_HPP

#include "Magia.hpp"

class MagiaCura : public Magia {
public:
    std::string getNome() const override { return "Cura"; }
    int getCustoMP() const override { return 8; }
    int getNivelMinimo() const override { return 1; }
};

#endif 