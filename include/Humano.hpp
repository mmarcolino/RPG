#ifndef HUMANO_HPP
#define HUMANO_HPP

#include "Race.hpp"

class Humano : public Race{
public:

    std::string getNome() override {
        return "Humano";
    }
};

#endif
