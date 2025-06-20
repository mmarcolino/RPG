#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/EspadaCurta.hpp"
#include "../include/Cajado.hpp"
#include "../include/Machado.hpp"

TEST_CASE("Teste das classes de Armas") {
    
    SUBCASE("Teste da Espada Curta") {
        EspadaCurta espada;
        
        CHECK(espada.getNome() == "Espada Curta");
        CHECK(espada.getTipo() == TipoArma::ESPADA_CURTA);
        CHECK(espada.getTipoDano() == TipoDano::CORTE);
        CHECK(espada.getNivelMinimo() == 1);
        
        auto ataques = espada.getAtaquesDisponiveis();
        CHECK(ataques.size() == 4);
        CHECK(ataques[0] == "Golpe Rápido");
        CHECK(ataques[1] == "Estocada");
        
        auto modificadores = espada.getModificadores();
        CHECK(modificadores.modificadorAtaqueFisico == 1.2f);
        CHECK(modificadores.modificadorAgilidade == 1.3f);
        CHECK(modificadores.bonusDano == 5);
        CHECK(modificadores.alcance == 1);
        
        // Teste de cálculo de dano
        int dano = espada.calcularDanoBase(30, 10);
        CHECK(dano > 0);
    }
    
    SUBCASE("Teste do Cajado") {
        Cajado cajado;
        
        CHECK(cajado.getNome() == "Cajado");
        CHECK(cajado.getTipo() == TipoArma::CAJADO);
        CHECK(cajado.getTipoDano() == TipoDano::MAGICO);
        CHECK(cajado.getNivelMinimo() == 1);
        
        auto ataques = cajado.getAtaquesDisponiveis();
        CHECK(ataques.size() == 4);
        CHECK(ataques[0] == "Bastão Mágico");
        CHECK(ataques[1] == "Onda de Energia");
        
        auto modificadores = cajado.getModificadores();
        CHECK(modificadores.modificadorAtaqueMagico == 1.8f);
        CHECK(modificadores.modificadorAtaqueFisico == 0.5f);
        CHECK(modificadores.bonusDano == 8);
        CHECK(modificadores.alcance == 2);
        
        // Teste de cálculo de dano mágico
        int dano = cajado.calcularDanoBase(10, 40);
        CHECK(dano > 0);
    }
    
    SUBCASE("Teste do Machado") {
        Machado machado;
        
        CHECK(machado.getNome() == "Machado");
        CHECK(machado.getTipo() == TipoArma::MACHADO);
        CHECK(machado.getTipoDano() == TipoDano::CORTE);
        CHECK(machado.getNivelMinimo() == 3);
        
        auto ataques = machado.getAtaquesDisponiveis();
        CHECK(ataques.size() == 4);
        CHECK(ataques[0] == "Golpe Pesado");
        CHECK(ataques[1] == "Corte Giratório");
        
        auto modificadores = machado.getModificadores();
        CHECK(modificadores.modificadorAtaqueFisico == 1.5f);
        CHECK(modificadores.modificadorAgilidade == 0.7f);
        CHECK(modificadores.bonusDano == 15);
        CHECK(modificadores.alcance == 1);
        
        // Teste de cálculo de dano
        int dano = machado.calcularDanoBase(35, 5);
        CHECK(dano > 0);
    }
    
    SUBCASE("Teste de comparação entre armas") {
        EspadaCurta espada;
        Cajado cajado;
        Machado machado;
        
        // Espada Curta deve ser mais ágil
        auto modEspada = espada.getModificadores();
        auto modCajado = cajado.getModificadores();
        auto modMachado = machado.getModificadores();
        
        CHECK(modEspada.modificadorAgilidade > modMachado.modificadorAgilidade);
        CHECK(modCajado.modificadorAtaqueMagico > modEspada.modificadorAtaqueMagico);
        CHECK(modMachado.modificadorAtaqueFisico > modEspada.modificadorAtaqueFisico);
    }
} 