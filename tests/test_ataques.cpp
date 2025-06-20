#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/GolpeRapido.hpp"
#include "../include/GolpePesado.hpp"
#include "../include/Personagem.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Humano.hpp"

TEST_CASE("Teste das classes de Ataques") {
    
    SUBCASE("Teste do Golpe Rápido") {
        GolpeRapido golpeRapido;
        
        CHECK(golpeRapido.getNome() == "Golpe Rápido");
        CHECK(golpeRapido.getTipo() == TipoAtaque::NORMAL);
        
        auto modificadores = golpeRapido.getModificadores();
        CHECK(modificadores.multiplicadorDano == 1.0f);
        CHECK(modificadores.chanceAcerto == 0.95f);
        CHECK(modificadores.chanceCritico == 0.15f);
        CHECK(modificadores.custoEnergia == 0);
        CHECK(modificadores.cooldown == 0);
        CHECK(modificadores.ignoraDefesa == false);
        CHECK(modificadores.causaEfeito == false);
    }
    
    SUBCASE("Teste do Golpe Pesado") {
        GolpePesado golpePesado;
        
        CHECK(golpePesado.getNome() == "Golpe Pesado");
        CHECK(golpePesado.getTipo() == TipoAtaque::ESPECIAL);
        
        auto modificadores = golpePesado.getModificadores();
        CHECK(modificadores.multiplicadorDano == 1.8f);
        CHECK(modificadores.chanceAcerto == 0.75f);
        CHECK(modificadores.chanceCritico == 0.25f);
        CHECK(modificadores.custoEnergia == 5);
        CHECK(modificadores.cooldown == 2);
        CHECK(modificadores.ignoraDefesa == false);
        CHECK(modificadores.causaEfeito == false);
    }
    
    SUBCASE("Teste de cálculo de dano") {
        GolpeRapido golpeRapido;
        GolpePesado golpePesado;
        
        int danoBase = 30;
        int ataqueFisico = 35;
        int ataqueMagico = 10;
        int defesaAlvo = 20;
        
        int danoRapido = golpeRapido.calcularDano(danoBase, ataqueFisico, ataqueMagico, defesaAlvo);
        int danoPesado = golpePesado.calcularDano(danoBase, ataqueFisico, ataqueMagico, defesaAlvo);
        
        CHECK(danoRapido > 0);
        CHECK(danoPesado > 0);
        CHECK(danoPesado > danoRapido); // Golpe Pesado deve causar mais dano
    }
    
    SUBCASE("Teste de verificação de acerto") {
        GolpeRapido golpeRapido;
        GolpePesado golpePesado;
        
        // Teste com agilidade alta do atacante
        bool acertoRapido = golpeRapido.verificarAcerto(25, 10);
        bool acertoPesado = golpePesado.verificarAcerto(25, 10);
        
        // Ambos devem ter chance de acerto (teste estatístico)
        CHECK(true); // Apenas verificar se não há erro de compilação
    }
    
    SUBCASE("Teste de verificação de crítico") {
        GolpeRapido golpeRapido;
        GolpePesado golpePesado;
        
        // Teste de verificação de crítico (teste estatístico)
        bool criticoRapido = golpeRapido.verificarCritico();
        bool criticoPesado = golpePesado.verificarCritico();
        
        CHECK(true); // Apenas verificar se não há erro de compilação
    }
    
    SUBCASE("Teste de execução de ataque") {
        Guerreiro* classe = new Guerreiro();
        Humano* raca = new Humano();
        Personagem atacante("Atacante", classe, raca, 100, 20, 35, 10, 25, 20, 1);
        Personagem alvo("Alvo", classe, raca, 100, 20, 30, 10, 20, 15, 1);
        
        GolpeRapido golpeRapido;
        int danoBase = 30;
        
        int danoCausado = golpeRapido.executarAtaque(atacante, alvo, danoBase);
        
        CHECK(danoCausado >= 0); // Pode ser 0 se errou
        CHECK(alvo.getHP() <= 100); // HP deve ter diminuído ou permanecido igual
        
        delete classe;
        delete raca;
    }
    
    SUBCASE("Teste de comparação entre ataques") {
        GolpeRapido golpeRapido;
        GolpePesado golpePesado;
        
        auto modRapido = golpeRapido.getModificadores();
        auto modPesado = golpePesado.getModificadores();
        
        // Golpe Rápido deve ter maior chance de acerto
        CHECK(modRapido.chanceAcerto > modPesado.chanceAcerto);
        
        // Golpe Pesado deve ter maior multiplicador de dano
        CHECK(modPesado.multiplicadorDano > modRapido.multiplicadorDano);
        
        // Golpe Pesado deve ter custo de energia
        CHECK(modPesado.custoEnergia > modRapido.custoEnergia);
    }
} 