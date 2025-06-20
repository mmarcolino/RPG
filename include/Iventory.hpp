#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Enum que representa os tipos de itens possíveis no inventário.
 */
enum class ItemTipo {
    POTION_HP,    /**< Poção de vida */
    POTION_MANA   /**< Poção de mana */
    // Futuras adições: ESPADA, ESCUDO, etc.
};

/**
 * @brief Estrutura que representa um item no inventário.
 */
struct Item {
    ItemTipo tipo;      /**< Tipo do item */
    int quantidade;     /**< Quantidade disponível */

    /**
     * @brief Construtor da struct Item.
     * @param tipo Tipo do item.
     * @param quantidade Quantidade inicial.
     */
    Item(ItemTipo tipo, int quantidade);
};

/**
 * @brief Classe que representa o inventário do jogador.
 *
 * Permite adicionar, utilizar e visualizar os itens presentes.
 */
class Inventario {
private:
    std::vector<Item> slots;  /**< Vetor de itens (slots) no inventário */

    /**
     * @brief Procura um item no inventário pelo tipo.
     * @param tipo Tipo de item a procurar.
     * @return Ponteiro para o item encontrado, ou nullptr se não existir.
     */
    Item* encontrarItem(ItemTipo tipo);

public:
    /**
     * @brief Construtor padrão do inventário.
     */
    Inventario();

    /**
     * @brief Adiciona uma quantidade de um item ao inventário.
     * @param tipo Tipo do item a adicionar.
     * @param quantidade Quantidade a ser adicionada.
     */
    void adicionarItem(ItemTipo tipo, int quantidade);

    /**
     * @brief Usa um item do inventário, reduzindo sua quantidade.
     * @param tipo Tipo do item a usar.
     */
    void usarItem(ItemTipo tipo);

    /**
     * @brief Mostra todos os itens e quantidades no inventário.
     */
    void mostrarInventario() const;
    
    /**
     * @brief Salva o inventário em um arquivo.
     * @param arquivo Arquivo de saída onde salvar.
     */
    void salvarInventario(std::ofstream& arquivo) const;
    
    /**
     * @brief Carrega o inventário de um arquivo.
     * @param arquivo Arquivo de entrada de onde carregar.
     */
    void carregarInventario(std::ifstream& arquivo);
    
    /**
     * @brief Limpa todos os itens do inventário.
     */
    void limparInventario();
};

#endif

