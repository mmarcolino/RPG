#ifndef MACHADO_HPP
#define MACHADO_HPP

#include "Arma.hpp"

/**
 * @brief Implementação do Machado.
 *
 * Representa uma arma pesada e poderosa, ideal para guerreiros que preferem
 * dano bruto sobre velocidade.
 */
class Machado : public Arma {
public:
    /**
     * @brief Construtor do Machado.
     */
    Machado() : Arma(
        "Machado",
        TipoArma::MACHADO,
        TipoDano::CORTE,
        ModificadoresArma(1.5f, 0.5f, 0.9f, 0.7f, 15, 1),
        3,
        "Um machado pesado que causa dano devastador, mas é lento."
    ) {}

    /**
     * @brief Retorna os ataques disponíveis para o Machado.
     * @return Vetor com os nomes dos ataques.
     */
    std::vector<std::string> getAtaquesDisponiveis() const override {
        return {
            "Golpe Pesado",
            "Corte Giratório",
            "Machadada",
            "Fúria Berserker"
        };
    }
};

#endif 