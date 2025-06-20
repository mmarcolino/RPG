#ifndef CAJADO_HPP
#define CAJADO_HPP

#include "Arma.hpp"

/**
 * @brief Implementação do Cajado.
 *
 * Representa uma arma mágica, ideal para magos que focam em poder mágico
 * e ataques à distância.
 */
class Cajado : public Arma {
public:
    /**
     * @brief Construtor do Cajado.
     */
    Cajado() : Arma(
        "Cajado",
        TipoArma::CAJADO,
        TipoDano::MAGICO,
        ModificadoresArma(0.5f, 1.8f, 0.8f, 1.1f, 8, 2),
        1,
        "Um cajado mágico que amplifica o poder das magias."
    ) {}

    /**
     * @brief Retorna os ataques disponíveis para o Cajado.
     * @return Vetor com os nomes dos ataques.
     */
    std::vector<std::string> getAtaquesDisponiveis() const override {
        return {
            "Bastão Mágico",
            "Onda de Energia",
            "Projétil Mágico",
            "Explosão Arcana"
        };
    }
};

#endif 