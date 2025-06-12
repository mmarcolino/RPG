#ifndef GUERREIRO_HPP
#define GUERREIRO_HPP

#include "Classe.hpp"

/**
 * @brief Implementação da classe Guerreiro.
 *
 * Representa uma classe jogável voltada para combate físico com alta resistência.
 * Herda de Classe e define os atributos base típicos de um guerreiro.
 */
class Guerreiro : public Classe {
public:
    /**
     * @brief Retorna os atributos base da classe Guerreiro.
     *
     * Atributos na seguinte ordem:
     * - 0: HP = 120
     * - 1: MP = 10
     * - 2: Ataque Físico = 35
     * - 3: Ataque Mágico = 5
     * - 4: Defesa = 25
     * - 5: Agilidade = 15
     *
     * @return Vetor de inteiros representando os atributos base.
     */
    std::vector<int> getAtributosBase() const override {
        return {120, 10, 35, 5, 25, 15}; // HP, MP, AtkF, AtkM, Def, Agi
    }

     /**
     * @brief Retorna o nome da classe.
     */
    std::string getNome() override {
        return "Guerreiro";
    }
};

#endif // GUERREIRO_HPP

