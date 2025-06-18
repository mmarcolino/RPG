#ifndef SISTEMA_DE_MAGIAS_HPP
#define SISTEMA_DE_MAGIAS_HPP

#include <memory>
#include "Magia.hpp"

class SistemaDeMagias {
public:
    // Verifica se o personagem pode conjurar a magia
    bool podeConjurar(const Personagem& caster, const Magia& magia) const;

    // Executa a magia, consumindo MP e aplicando efeitos
    void conjurar(Personagem& caster, Personagem& alvo, const Magia& magia);
};

#endif 