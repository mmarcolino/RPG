#include "../include/Personagem.hpp"

Personagem::Personagem(const std::string& nome,
                       Classe* classe,
                       Race* raca,
                       const std::vector<int>& atributosBase,
                       int nivel)
    : nome(nome), classe(classe), raca(raca), atributos(atributosBase), nivel(nivel) {}

const std::string& Personagem::getNome() const {
    return nome;
}

Classe* Personagem::getClasse() const {
    return classe;
}

Race* Personagem::getRaca() const {
    return raca;
}

Inventario& Personagem::getInventario() {
    return inventario;
}

const std::vector<Magia*>& Personagem::getMagias() const {
    return magias;
}

void Personagem::adicionarMagia(Magia* magia) {
    magias.push_back(magia);
}

const std::vector<int>& Personagem::getAtributos() const {
    return atributos;
}

int Personagem::getHP() const {
    return atributos[0];
}

int Personagem::getMP() const {
    return atributos[1];
}

int Personagem::getAtk() const {
    return atributos[2];
}

int Personagem::getDef() const {
    return atributos[3];
}

int Personagem::getNivel() const {
    return nivel;
}

void Personagem::setHP(int novoHP) {
    atributos[0] = novoHP;
}

void Personagem::setMP(int novoMP) {
    atributos[1] = novoMP;
}

void Personagem::setAtk(int novoAtk) {
    atributos[2] = novoAtk;
}

void Personagem::setDef(int novoDef) {
    atributos[3] = novoDef;
}

void Personagem::setNivel(int novoNivel) {
    nivel = novoNivel;
}

void Personagem::adicionarPontos(int hp, int mp, int atk, int def) {
    atributos[0] += hp;
    atributos[1] += mp;
    atributos[2] += atk;
    atributos[3] += def;
} 