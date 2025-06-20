#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Mago.hpp"

TEST_CASE("Teste da classe Mago") {
    Mago mago;
    
    SUBCASE("Teste do nome da classe") {
        CHECK(mago.getNome() == "Mago");
    }
    
    SUBCASE("Teste dos atributos base") {
        std::vector<int> atributos = mago.getAtributosBase();
        
        CHECK(atributos.size() == 6);
        CHECK(atributos[0] == 80);  // HP
        CHECK(atributos[1] == 50);  // MP
        CHECK(atributos[2] == 10);  // Ataque Físico
        CHECK(atributos[3] == 40);  // Ataque Mágico
        CHECK(atributos[4] == 15);  // Defesa
        CHECK(atributos[5] == 20);  // Agilidade
    }
    
    SUBCASE("Teste de características do Mago") {
        std::vector<int> atributos = mago.getAtributosBase();
        
        // Mago deve ter alto MP e ataque mágico
        CHECK(atributos[1] > 30);  // MP alto
        CHECK(atributos[3] > 30);  // Ataque mágico alto
        
        // Mago deve ter baixo HP e ataque físico
        CHECK(atributos[0] < 100); // HP baixo
        CHECK(atributos[2] < 20);  // Ataque físico baixo
    }
} 