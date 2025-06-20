#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/SistemaDeCombate.hpp"
#include "../include/Personagem.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Humano.hpp"

TEST_CASE("Teste do Sistema de Combate") {
    
    SUBCASE("Teste de inicialização do sistema") {
        SistemaDeCombate sistema;
        
        CHECK(sistema.getNumeroCombatentes() == 0);
        CHECK(sistema.getCombatente(0) == nullptr);
    }
    
    SUBCASE("Teste de adição de combatentes") {
        SistemaDeCombate sistema;
        
        Guerreiro* classe1 = new Guerreiro();
        Humano* raca1 = new Humano();
        Personagem* p1 = new Personagem("Guerreiro", classe1, raca1, 100, 20, 35, 10, 25, 15, 1);
        
        Guerreiro* classe2 = new Guerreiro();
        Humano* raca2 = new Humano();
        Personagem* p2 = new Personagem("Mago", classe2, raca2, 80, 50, 10, 40, 15, 20, 1);
        
        sistema.adicionarCombatente(p1);
        sistema.adicionarCombatente(p2);
        
        CHECK(sistema.getNumeroCombatentes() == 2);
        CHECK(sistema.getCombatente(0) == p1);
        CHECK(sistema.getCombatente(1) == p2);
        
        delete classe1;
        delete raca1;
        delete classe2;
        delete raca2;
        delete p1;
        delete p2;
    }
    
    SUBCASE("Teste de limpeza de combatentes") {
        SistemaDeCombate sistema;
        
        Guerreiro* classe = new Guerreiro();
        Humano* raca = new Humano();
        Personagem* p = new Personagem("Teste", classe, raca, 100, 20, 35, 10, 25, 15, 1);
        
        sistema.adicionarCombatente(p);
        CHECK(sistema.getNumeroCombatentes() == 1);
        
        sistema.limparCombatentes();
        CHECK(sistema.getNumeroCombatentes() == 0);
        
        delete classe;
        delete raca;
        delete p;
    }
    
    SUBCASE("Teste de verificação de vida") {
        SistemaDeCombate sistema;
        
        Guerreiro* classe = new Guerreiro();
        Humano* raca = new Humano();
        Personagem* p1 = new Personagem("Vivo", classe, raca, 100, 20, 35, 10, 25, 15, 1);
        Personagem* p2 = new Personagem("Morto", classe, raca, 0, 20, 35, 10, 25, 15, 1);
        
        // Teste indireto através do sistema
        sistema.adicionarCombatente(p1);
        sistema.adicionarCombatente(p2);
        
        CHECK(sistema.getCombatente(0)->getHP() > 0);
        CHECK(sistema.getCombatente(1)->getHP() == 0);
        
        delete classe;
        delete raca;
        delete p1;
        delete p2;
    }
    
    SUBCASE("Teste de ordem de iniciativa") {
        SistemaDeCombate sistema;
        
        Guerreiro* classe1 = new Guerreiro();
        Humano* raca1 = new Humano();
        Personagem* p1 = new Personagem("Lento", classe1, raca1, 100, 20, 35, 10, 25, 10, 1);
        
        Guerreiro* classe2 = new Guerreiro();
        Humano* raca2 = new Humano();
        Personagem* p2 = new Personagem("Rápido", classe2, raca2, 100, 20, 35, 10, 25, 25, 1);
        
        sistema.adicionarCombatente(p1);
        sistema.adicionarCombatente(p2);
        
        // Verificar se a agilidade está correta
        CHECK(sistema.getCombatente(0)->getAgilidade() == 10);
        CHECK(sistema.getCombatente(1)->getAgilidade() == 25);
        
        delete classe1;
        delete raca1;
        delete classe2;
        delete raca2;
        delete p1;
        delete p2;
    }
} 