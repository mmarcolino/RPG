#ifndef MAGIA_FOGO_HPP
#define MAGIA_FOGO_HPP

#include "Magia.hpp"

class MagiaFogo : public Magia {
public:
    std::string getNome() const override { return "Bola de Fogo"; }
    int getCustoMP() const override { return 10; }
    int getNivelMinimo() const override { return 2; }
};

#endif 