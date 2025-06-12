#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/Guerreiro.hpp"

TEST_CASE("Guerreiro retorna atributos corretos") {
    Guerreiro g;
    std::vector<int> atributos = g.getAtributosBase();

    CHECK(atributos[0] == 120); // HP
    CHECK(atributos[1] == 10);  // MP
    CHECK(atributos[2] == 35);  // Ataque Físico
    CHECK(atributos[3] == 5);   // Ataque Mágico
    CHECK(atributos[4] == 25);  // Defesa
    CHECK(atributos[5] == 15);  // Agilidade
}

TEST_CASE("Polimorfismo com Classe* para Guerreiro") {
    Classe* c = new Guerreiro();
    std::vector<int> atributos = c->getAtributosBase();

    CHECK(atributos[2] == 35); // Ataque Físico

    delete c;
}

