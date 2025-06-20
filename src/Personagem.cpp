#include "../include/Personagem.hpp"

Personagem::Personagem(const std::string& nome,
                       Classe* classe,
                       Race* raca,
                       int hp, int mp, int ataqueFisico, int ataqueMagico, int defesa, int agilidade,
                       int nivel)
    : nome(nome), classe(classe), raca(raca), hp(hp), mp(mp), ataqueFisico(ataqueFisico), 
      ataqueMagico(ataqueMagico), defesa(defesa), agilidade(agilidade), nivel(nivel) {}

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

int Personagem::getHP() const {
    return hp;
}

int Personagem::getMP() const {
    return mp;
}

int Personagem::getAtaqueFisico() const {
    return ataqueFisico;
}

int Personagem::getAtaqueMagico() const {
    return ataqueMagico;
}

int Personagem::getDefesa() const {
    return defesa;
}

int Personagem::getAgilidade() const {
    return agilidade;
}

int Personagem::getNivel() const {
    return nivel;
}

void Personagem::setHP(int novoHP) {
    hp = novoHP;
}

void Personagem::setMP(int novoMP) {
    mp = novoMP;
}

void Personagem::setAtaqueFisico(int novoAtaqueFisico) {
    ataqueFisico = novoAtaqueFisico;
}

void Personagem::setAtaqueMagico(int novoAtaqueMagico) {
    ataqueMagico = novoAtaqueMagico;
}

void Personagem::setDefesa(int novaDefesa) {
    defesa = novaDefesa;
}

void Personagem::setAgilidade(int novaAgilidade) {
    agilidade = novaAgilidade;
}

void Personagem::setNivel(int novoNivel) {
    nivel = novoNivel;
}

void Personagem::adicionarPontos(int hpExtra, int mpExtra, int ataqueFisicoExtra, int ataqueMagicoExtra, int defesaExtra, int agilidadeExtra) {
    hp += hpExtra;
    mp += mpExtra;
    ataqueFisico += ataqueFisicoExtra;
    ataqueMagico += ataqueMagicoExtra;
    defesa += defesaExtra;
    agilidade += agilidadeExtra;
}
