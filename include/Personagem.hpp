#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include <vector>
#include "Classe.hpp"
#include "Race.hpp"
#include "Iventory.hpp"
#include "Magia.hpp"

class Personagem {
private:
    std::string nome;
    Classe* classe;
    Race* raca;
    Inventario inventario;
    std::vector<Magia*> magias;
    std::vector<int> atributos; // [HP, MP, Atk, Def]
    int nivel;
public:
    Personagem(const std::string& nome,
               Classe* classe,
               Race* raca,
               const std::vector<int>& atributosBase,
               int nivel = 1);

    // Métodos de acesso e manipulação
    const std::string& getNome() const;
    Classe* getClasse() const;
    Race* getRaca() const;
    Inventario& getInventario();
    const std::vector<Magia*>& getMagias() const;
    void adicionarMagia(Magia* magia);
    const std::vector<int>& getAtributos() const;
};

#endif 