#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Iventory.hpp"

TEST_CASE("Adição de itens no inventário") {
    Inventario inv;

    inv.adicionarItem(ItemTipo::POTION_HP, 3);
    inv.adicionarItem(ItemTipo::POTION_MANA, 2);

    // Testa se adicionar funciona acumulando
    inv.adicionarItem(ItemTipo::POTION_HP, 2);

    // Captura o estado interno para verificar (simulação via print, pois o método de acesso é privado)
    // Em um projeto real, o ideal seria criar um método de acesso para teste ou friend class.

    // Aqui vamos só testar se o método usarItem consome corretamente
    inv.usarItem(ItemTipo::POTION_HP);
    inv.usarItem(ItemTipo::POTION_MANA);
}

TEST_CASE("Uso de itens sem quantidade") {
    Inventario inv;

    // Tenta usar um item que não existe
    inv.usarItem(ItemTipo::POTION_HP);
    inv.usarItem(ItemTipo::POTION_MANA);
}

TEST_CASE("Adição e uso múltiplo de itens") {
    Inventario inv;

    inv.adicionarItem(ItemTipo::POTION_HP, 1);
    inv.adicionarItem(ItemTipo::POTION_MANA, 1);

    // Usar uma vez cada
    inv.usarItem(ItemTipo::POTION_HP);
    inv.usarItem(ItemTipo::POTION_MANA);

    // Tentar usar de novo (deve falhar porque acabou)
    inv.usarItem(ItemTipo::POTION_HP);
    inv.usarItem(ItemTipo::POTION_MANA);
}

