#ifndef MAGIA_HPP
#define MAGIA_HPP

#include <string>

class Magia {
public:
    virtual ~Magia() = default;

    virtual std::string getNome() const = 0;
    virtual int getCustoMP() const = 0;
    virtual int getNivelMinimo() const = 0;
};

#endif 