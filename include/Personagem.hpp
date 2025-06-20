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
    // Atributos individuais (mesmos da Classe.hpp)
    int hp;
    int mp;
    int ataqueFisico;
    int ataqueMagico;
    int defesa;
    int agilidade;
    int nivel;
public:
    Personagem(const std::string& nome,
               Classe* classe,
               Race* raca,
               int hp, int mp, int ataqueFisico, int ataqueMagico, int defesa, int agilidade,
               int nivel = 1);

    // Métodos de acesso e manipulação
    const std::string& getNome() const;
    Classe* getClasse() const;
    Race* getRaca() const;
    Inventario& getInventario();
    const std::vector<Magia*>& getMagias() const;
    void adicionarMagia(Magia* magia);
    
    // Métodos de acesso aos atributos
    int getHP() const;
    int getMP() const;
    int getAtaqueFisico() const;
    int getAtaqueMagico() const;
    int getDefesa() const;
    int getAgilidade() const;
    int getNivel() const;
    
    // Métodos de modificação dos atributos
    void setHP(int novoHP);
    void setMP(int novoMP);
    void setAtaqueFisico(int novoAtaqueFisico);
    void setAtaqueMagico(int novoAtaqueMagico);
    void setDefesa(int novaDefesa);
    void setAgilidade(int novaAgilidade);
    void setNivel(int novoNivel);
    
    // Método para adicionar pontos extras
    void adicionarPontos(int hp, int mp, int ataqueFisico, int ataqueMagico, int defesa, int agilidade);
};

#endif 