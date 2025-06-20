#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Paladino.hpp"

TEST_CASE("Teste da classe Paladino") {
    Paladino paladino;
    
    SUBCASE("Teste do nome da classe") {
        CHECK(paladino.getNome() == "Paladino");
    }
    
    SUBCASE("Teste dos atributos base") {
        std::vector<int> atributos = paladino.getAtributosBase();
        
        CHECK(atributos.size() == 6);
        CHECK(atributos[0] == 100); // HP
        CHECK(atributos[1] == 30);  // MP
        CHECK(atributos[2] == 25);  // Ataque Físico
        CHECK(atributos[3] == 20);  // Ataque Mágico
        CHECK(atributos[4] == 30);  // Defesa
        CHECK(atributos[5] == 15);  // Agilidade
    }
    
    SUBCASE("Teste de características do Paladino") {
        std::vector<int> atributos = paladino.getAtributosBase();
        
        // Paladino deve ser balanceado
        CHECK(atributos[0] >= 100); // HP alto
        CHECK(atributos[4] >= 30);  // Defesa alta
        CHECK(atributos[2] >= 20);  // Ataque físico decente
        CHECK(atributos[3] >= 15);  // Ataque mágico decente
    }
} 