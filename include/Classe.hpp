#ifndef CLASSE_HPP
#define CLASSE_HPP // evita dupla importação

#include <string>
#include <vector>

/**
 * @brief Classe base abstrata para todas as classes jogáveis no RPG.
 *
 * Representa uma interface para classes como Guerreiro, Mago, Paladino, etc.
 * Fornece uma assinatura para recuperar o nome da classe e seus atributos base.
 */
class Classe {
public:
    /**
     * @brief Destrutor virtual necessário para permitir destruição polimórfica.
     */
    virtual ~Classe() {}

    /**
     * @brief Retorna o nome da classe.
     *
     * @return Nome da classe como string (ex: "Guerreiro", "Mago").
     */
    virtual std::string getNome() = 0;

    /**
     * @brief Retorna os atributos base da classe.
     *
     * Os atributos seguem esta ordem no vetor:
     * - 0: HP
     * - 1: MP
     * - 2: Ataque Físico
     * - 3: Ataque Mágico
     * - 4: Defesa
     * - 5: Agilidade
     *
     * @return Vetor de inteiros com os valores base dos atributos.
     */
    virtual std::vector<int> getAtributosBase() const = 0;
};

#endif

