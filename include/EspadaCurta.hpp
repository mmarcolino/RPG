#ifndef ESPADA_CURTA_HPP
#define ESPADA_CURTA_HPP

#include "Arma.hpp"

/**
 * @brief Implementação da Espada Curta.
 *
 * Representa uma arma rápida e ágil, ideal para guerreiros que preferem
 * velocidade sobre poder bruto.
 */
class EspadaCurta : public Arma {
public:
    /**
     * @brief Construtor da Espada Curta.
     */
    EspadaCurta() : Arma(
        "Espada Curta",
        TipoArma::ESPADA_CURTA,
        TipoDano::CORTE,
        ModificadoresArma(1.2f, 0.8f, 1.0f, 1.3f, 5, 1),
        1,
        "Uma espada curta e ágil, perfeita para ataques rápidos."
    ) {}

    /**
     * @brief Retorna os ataques disponíveis para a Espada Curta.
     * @return Vetor com os nomes dos ataques.
     */
    std::vector<std::string> getAtaquesDisponiveis() const override {
        return {
            "Golpe Rápido",
            "Estocada",
            "Corte Lateral",
            "Golpe Duplo"
        };
    }
};

#endif 