#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/MagiaCura.hpp"
#include "../include/MagiaFogo.hpp"

TEST_CASE("Teste das classes de Magias") {
    
    SUBCASE("Teste da Magia Cura") {
        MagiaCura cura;
        
        CHECK(cura.getNome() == "Cura");
        CHECK(cura.getCustoMP() == 8);
        CHECK(cura.getNivelMinimo() == 1);
    }
    
    SUBCASE("Teste da Magia Bola de Fogo") {
        MagiaFogo bolaFogo;
        
        CHECK(bolaFogo.getNome() == "Bola de Fogo");
        CHECK(bolaFogo.getCustoMP() == 10);
        CHECK(bolaFogo.getNivelMinimo() == 2);
    }
    
    SUBCASE("Teste de comparação entre magias") {
        MagiaCura cura;
        MagiaFogo bolaFogo;
        
        // Bola de Fogo deve ter custo maior que Cura
        CHECK(bolaFogo.getCustoMP() > cura.getCustoMP());
        
        // Bola de Fogo deve ter nível mínimo maior
        CHECK(bolaFogo.getNivelMinimo() > cura.getNivelMinimo());
        
        // Ambas devem ter custo de MP
        CHECK(cura.getCustoMP() > 0);
        CHECK(bolaFogo.getCustoMP() > 0);
        
        // Ambas devem ter nível mínimo válido
        CHECK(cura.getNivelMinimo() > 0);
        CHECK(bolaFogo.getNivelMinimo() > 0);
    }
    
    SUBCASE("Teste de características das magias") {
        MagiaCura cura;
        MagiaFogo bolaFogo;
        
        // Cura deve ser magia de suporte (nível baixo)
        CHECK(cura.getNivelMinimo() <= 2);
        CHECK(cura.getCustoMP() <= 10);
        
        // Bola de Fogo deve ser magia ofensiva (nível médio)
        CHECK(bolaFogo.getNivelMinimo() >= 2);
        CHECK(bolaFogo.getCustoMP() >= 8);
    }
} 