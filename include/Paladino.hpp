#ifndef PALADINO_HPP
#define PALADINO_HPP

#include "Classe.hpp"

/**
 * @brief Implementação da classe Paladino.
 *
 * Representa uma classe jogável balanceada entre combate físico e mágico.
 * Herda de Classe e define os atributos base típicos de um paladino.
 */
class Paladino : public Classe {
public:
    /**
     * @brief Retorna os atributos base da classe Paladino.
     *
     * Atributos na seguinte ordem:
     * - 0: HP = 100
     * - 1: MP = 30
     * - 2: Ataque Físico = 25
     * - 3: Ataque Mágico = 20
     * - 4: Defesa = 30
     * - 5: Agilidade = 15
     *
     * @return Vetor de inteiros representando os atributos base.
     */
    std::vector<int> getAtributosBase() const override {
        return {100, 30, 25, 20, 30, 15}; // HP, MP, AtkF, AtkM, Def, Agi
    }

    /**
     * @brief Retorna o nome da classe.
     */
    std::string getNome() override {
        return "Paladino";
    }
};

#endif // PALADINO_HPP 