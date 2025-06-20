#ifndef GOLPE_PESADO_HPP
#define GOLPE_PESADO_HPP

#include "Ataque.hpp"
#include "Personagem.hpp"

/**
 * @brief Implementação do ataque Golpe Pesado.
 *
 * Representa um ataque poderoso mas lento, ideal para machados.
 */
class GolpePesado : public Ataque {
public:
    /**
     * @brief Construtor do Golpe Pesado.
     */
    GolpePesado() : Ataque(
        "Golpe Pesado",
        TipoAtaque::ESPECIAL,
        ModificadoresAtaque(1.8f, 0.75f, 0.25f, 5, 2, false, false),
        "Um golpe devastador que causa muito dano, mas é lento."
    ) {}

    /**
     * @brief Executa o ataque Golpe Pesado.
     * @param atacante Personagem atacante.
     * @param alvo Personagem alvo.
     * @param danoBase Dano base da arma.
     * @return Dano causado (0 se errou).
     */
    int executarAtaque(Personagem& atacante, Personagem& alvo, int danoBase) const override {
        std::cout << atacante.getNome() << " concentra energia para um " << nome << "...\n";
        
        // Verificar se tem MP suficiente
        if (atacante.getMP() < modificadores.custoEnergia) {
            std::cout << "❌ " << atacante.getNome() << " não tem MP suficiente para " << nome << "!\n";
            return 0;
        }

        // Consumir MP
        int mpAnterior = atacante.getMP();
        atacante.setMP(atacante.getMP() - modificadores.custoEnergia);
        std::cout << "🔮 MP consumido: " << mpAnterior << " → " << atacante.getMP() << "\n";

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
            dano = static_cast<int>(dano * 2.0f);
            std::cout << "💥 CRÍTICO DEVASTADOR! ";
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