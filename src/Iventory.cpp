#include "../include/Iventory.hpp"

Item::Item(ItemTipo tipo, int quantidade) : tipo(tipo), quantidade(quantidade) {}

Inventario::Inventario() {}

Item* Inventario::encontrarItem(ItemTipo tipo) {
    for (auto& item : slots) {
        if (item.tipo == tipo) {
            return &item;
        }
    }
    return nullptr;
}

void Inventario::adicionarItem(ItemTipo tipo, int quantidade) {
    Item* item = encontrarItem(tipo);
    if (item) {
        item->quantidade += quantidade;
    } else {
        slots.emplace_back(tipo, quantidade);
    }
}

void Inventario::usarItem(ItemTipo tipo) {
    Item* item = encontrarItem(tipo);
    if (item && item->quantidade > 0) {
        item->quantidade--;
        std::cout << "Usou uma ";
        if (tipo == ItemTipo::POTION_HP) std::cout << "Poção de HP.\n";
        else if (tipo == ItemTipo::POTION_MANA) std::cout << "Poção de Mana.\n";
    } else {
        std::cout << "Item indisponível.\n";
    }
}

void Inventario::mostrarInventario() const {
    std::cout << "Inventário:\n";
    for (const auto& item : slots) {
        std::string nome;
        if (item.tipo == ItemTipo::POTION_HP) nome = "Poção de HP";
        else if (item.tipo == ItemTipo::POTION_MANA) nome = "Poção de Mana";

        std::cout << "- " << nome << ": " << item.quantidade << "\n";
    }
}

