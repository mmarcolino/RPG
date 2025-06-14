#ifndef RACE_HPP
#define RACE_HPP

#include <string>

/**
 * @brief Classe base abstrata para todas as raças jogáveis no RPG.
 *
 * Representa uma interface para raças como Humano, Elfo, Anão, etc.
 * Fornece uma assinatura para recuperar o nome da raça.
 */

class Race{
public:
     /**
     * @brief Destrutor virtual necessário para permitir destruição polimórfica.
     */
     virtual ~Race() {}

    virtual std::string getNome() =  0;
};




#endif
