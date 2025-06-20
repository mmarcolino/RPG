#ifndef MAGO_HPP
#define MAGO_HPP

#include "Classe.hpp"

/**
 * @brief Implementação da classe Mago.
 *
 * Representa uma classe jogável voltada para magias com alto poder mágico.
 * Herda de Classe e define os atributos base típicos de um mago.
 */
class Mago : public Classe {
public:
    /**
     * @brief Retorna os atributos base da classe Mago.
     *
     * Atributos na seguinte ordem:
     * - 0: HP = 80
     * - 1: MP = 50
     * - 2: Ataque Físico = 10
     * - 3: Ataque Mágico = 40
     * - 4: Defesa = 15
     * - 5: Agilidade = 20
     *
     * @return Vetor de inteiros representando os atributos base.
     */
    std::vector<int> getAtributosBase() const override {
        return {80, 50, 10, 40, 15, 20}; // HP, MP, AtkF, AtkM, Def, Agi
    }

    /**
     * @brief Retorna o nome da classe.
     */
    std::string getNome() override {
        return "Mago";
    }
};

#endif // MAGO_HPP 