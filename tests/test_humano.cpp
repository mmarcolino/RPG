#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/Humano.hpp"

TEST_CASE("Polimorfismo com Race* para Humano*") {
    Race* r = new Humano();
    std::string nome = r->getNome();

    CHECK( nome == "Humano"); // Nome da raça

    delete r;
}



