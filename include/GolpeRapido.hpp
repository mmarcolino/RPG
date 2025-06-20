#ifndef GOLPE_RAPIDO_HPP
#define GOLPE_RAPIDO_HPP

#include "Ataque.hpp"
#include "Personagem.hpp"

/**
 * @brief Implementação do ataque Golpe Rápido.
 *
 * Representa um ataque básico rápido e preciso, ideal para espadas curtas.
 */
class GolpeRapido : public Ataque {
public:
    /**
     * @brief Construtor do Golpe Rápido.
     */
    GolpeRapido() : Ataque(
        "Golpe Rápido",
        TipoAtaque::NORMAL,
        ModificadoresAtaque(1.0f, 0.95f, 0.15f, 0, 0, false, false),
        "Um golpe rápido e preciso com a espada."
    ) {}

    /**
     * @brief Executa o ataque Golpe Rápido.
     * @param atacante Personagem atacante.
     * @param alvo Personagem alvo.
     * @param danoBase Dano base da arma.
     * @return Dano causado (0 se errou).
     */
    int executarAtaque(Personagem& atacante, Personagem& alvo, int danoBase) const override {
        std::cout << atacante.getNome() << " prepara um " << nome << "...\n";
        
        // Verificar se acertou
        if (!verificarAcerto(atacante.getAgilidade(), alvo.getAgilidade())) {
            std::cout << "❌ " << atacante.getNome() << " errou o " << nome << "!\n";
            return 0;
        }

        // Calcular dano
        int dano = calcularDano(danoBase, atacante.getAtaqueFisico(), 
                               atacante.getAtaqueMagico(), alvo.getDefesa());

        // Verificar crítico
        bool critico = verificarCritico();
        if (critico) {
            dano = static_cast<int>(dano * 1.5f);
            std::cout << "💥 CRÍTICO! ";
        }

        // Aplicar dano
        int hpAnterior = alvo.getHP();
        alvo.setHP(std::max(0, alvo.getHP() - dano));

        // Mensagem de resultado
        std::cout << "⚔️ " << atacante.getNome() << " usou " << nome 
                  << " em " << alvo.getNome() << "!\n";
        std::cout << "   Dano causado: " << dano << " (HP: " << hpAnterior 
                  << " → " << alvo.getHP() << ")\n";

        return dano;
    }
};

#endif 