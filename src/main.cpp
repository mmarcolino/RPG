#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/Personagem.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Paladino.hpp"
#include "../include/Humano.hpp"
#include "../include/MagiaCura.hpp"
#include "../include/MagiaFogo.hpp"
#include "../include/EspadaCurta.hpp"
#include "../include/Cajado.hpp"
#include "../include/Machado.hpp"
#include "../include/GolpeRapido.hpp"
#include "../include/GolpePesado.hpp"
#include "../include/SistemaDeCombate.hpp"

class RPGManager {
private:
    std::vector<Personagem*> personagens;
    std::vector<Classe*> classes;
    std::vector<Race*> racas;
    std::vector<Magia*> magias;
    std::vector<Arma*> armas;
    std::vector<Ataque*> ataques;
    SistemaDeCombate sistemaCombate;
    
    void inicializarClasses() {
        classes.push_back(new Guerreiro());
        classes.push_back(new Mago());
        classes.push_back(new Paladino());
    }
    
    void inicializarRacas() {
        racas.push_back(new Humano());
        // Adicionar outras raças aqui
    }
    
    void inicializarMagias() {
        magias.push_back(new MagiaCura());
        magias.push_back(new MagiaFogo());
        // Adicionar outras magias aqui
    }
    
    void inicializarArmas() {
        armas.push_back(new EspadaCurta());
        armas.push_back(new Cajado());
        armas.push_back(new Machado());
        // Adicionar outras armas aqui
    }
    
    void inicializarAtaques() {
        ataques.push_back(new GolpeRapido());
        ataques.push_back(new GolpePesado());
        // Adicionar outros ataques aqui
    }
    
    void mostrarMenu() {
        std::cout << "\n=== RPG CMD ===\n";
        std::cout << "1. Criar novo personagem\n";
        std::cout << "2. Listar personagens\n";
        std::cout << "3. Gerenciar personagem\n";
        std::cout << "4. Salvar personagens\n";
        std::cout << "5. Carregar personagens\n";
        std::cout << "6. Iniciar combate\n";
        std::cout << "7. Sair\n";
        std::cout << "Escolha uma opção: ";
    }
    
    void mostrarClasses() {
        std::cout << "\nClasses disponíveis:\n";
        for (size_t i = 0; i < classes.size(); ++i) {
            std::cout << i + 1 << ". " << classes[i]->getNome() << "\n";
        }
    }
    
    void mostrarRacas() {
        std::cout << "\nRaças disponíveis:\n";
        for (size_t i = 0; i < racas.size(); ++i) {
            std::cout << i + 1 << ". " << racas[i]->getNome() << "\n";
        }
    }
    
    void mostrarMagias() {
        std::cout << "\nMagias disponíveis:\n";
        for (size_t i = 0; i < magias.size(); ++i) {
            std::cout << i + 1 << ". " << magias[i]->getNome() 
                      << " (MP: " << magias[i]->getCustoMP() 
                      << ", Nível: " << magias[i]->getNivelMinimo() << ")\n";
        }
    }
    
    void mostrarArmas() {
        std::cout << "\nArmas disponíveis:\n";
        for (size_t i = 0; i < armas.size(); ++i) {
            std::cout << i + 1 << ". " << armas[i]->getNome() 
                      << " (Nível: " << armas[i]->getNivelMinimo() << ")\n";
        }
    }
    
    void criarPersonagem() {
        std::string nome;
        std::cout << "\nDigite o nome do personagem: ";
        std::cin.ignore();
        std::getline(std::cin, nome);
        
        mostrarClasses();
        int escolhaClasse;
        std::cout << "Escolha a classe: ";
        std::cin >> escolhaClasse;
        
        mostrarRacas();
        int escolhaRaca;
        std::cout << "Escolha a raça: ";
        std::cin >> escolhaRaca;
        
        if (escolhaClasse > 0 && escolhaClasse <= static_cast<int>(classes.size()) &&
            escolhaRaca > 0 && escolhaRaca <= static_cast<int>(racas.size())) {
            
            Classe* classe = classes[escolhaClasse - 1];
            Race* raca = racas[escolhaRaca - 1];
            
            std::vector<int> atributosBase = classe->getAtributosBase();
            
            Personagem* personagem = new Personagem(
                nome, classe, raca,
                atributosBase[0], atributosBase[1], atributosBase[2],
                atributosBase[3], atributosBase[4], atributosBase[5]
            );
            
            // Adicionar algumas magias básicas baseadas na classe
            if (classe->getNome() == "Mago") {
                personagem->adicionarMagia(magias[0]); // Cura
                personagem->adicionarMagia(magias[1]); // Bola de Fogo
            } else if (classe->getNome() == "Paladino") {
                personagem->adicionarMagia(magias[0]); // Cura
            }
            
            // Adicionar alguns itens básicos
            personagem->getInventario().adicionarItem(ItemTipo::POTION_HP, 3);
            personagem->getInventario().adicionarItem(ItemTipo::POTION_MANA, 2);
            
            personagens.push_back(personagem);
            std::cout << "Personagem criado com sucesso!\n";
        } else {
            std::cout << "Escolha inválida!\n";
        }
    }
    
    void listarPersonagens() {
        if (personagens.empty()) {
            std::cout << "\nNenhum personagem criado.\n";
            return;
        }
        
        std::cout << "\n=== Personagens ===\n";
        for (size_t i = 0; i < personagens.size(); ++i) {
            Personagem* p = personagens[i];
            std::cout << i + 1 << ". " << p->getNome() 
                      << " (" << p->getClasse()->getNome() 
                      << " " << p->getRaca()->getNome() << ")\n";
            std::cout << "   HP: " << p->getHP() 
                      << " | MP: " << p->getMP()
                      << " | AtkF: " << p->getAtaqueFisico()
                      << " | AtkM: " << p->getAtaqueMagico()
                      << " | Def: " << p->getDefesa()
                      << " | Agi: " << p->getAgilidade()
                      << " | Nível: " << p->getNivel() << "\n";
        }
    }
    
    void gerenciarPersonagem() {
        if (personagens.empty()) {
            std::cout << "\nNenhum personagem criado.\n";
            return;
        }
        
        listarPersonagens();
        int escolha;
        std::cout << "\nEscolha o personagem (número): ";
        std::cin >> escolha;
        
        if (escolha > 0 && escolha <= static_cast<int>(personagens.size())) {
            Personagem* p = personagens[escolha - 1];
            mostrarMenuPersonagem(p);
        } else {
            std::cout << "Escolha inválida!\n";
        }
    }
    
    void mostrarMenuPersonagem(Personagem* p) {
        int opcao;
        do {
            std::cout << "\n=== " << p->getNome() << " ===\n";
            std::cout << "1. Ver inventário\n";
            std::cout << "2. Adicionar item\n";
            std::cout << "3. Usar item\n";
            std::cout << "4. Ver magias\n";
            std::cout << "5. Adicionar magia\n";
            std::cout << "6. Ver armas disponíveis\n";
            std::cout << "7. Voltar\n";
            std::cout << "Escolha uma opção: ";
            std::cin >> opcao;
            
            switch (opcao) {
                case 1:
                    p->getInventario().mostrarInventario();
                    break;
                case 2:
                    adicionarItem(p);
                    break;
                case 3:
                    usarItem(p);
                    break;
                case 4:
                    mostrarMagiasPersonagem(p);
                    break;
                case 5:
                    adicionarMagia(p);
                    break;
                case 6:
                    mostrarArmas();
                    break;
                case 7:
                    break;
                default:
                    std::cout << "Opção inválida!\n";
            }
        } while (opcao != 7);
    }
    
    void adicionarItem(Personagem* p) {
        std::cout << "\nTipos de item:\n";
        std::cout << "1. Poção de HP\n";
        std::cout << "2. Poção de Mana\n";
        std::cout << "Escolha o tipo: ";
        int tipo;
        std::cin >> tipo;
        
        std::cout << "Quantidade: ";
        int quantidade;
        std::cin >> quantidade;
        
        if (tipo == 1) {
            p->getInventario().adicionarItem(ItemTipo::POTION_HP, quantidade);
            std::cout << "Item adicionado!\n";
        } else if (tipo == 2) {
            p->getInventario().adicionarItem(ItemTipo::POTION_MANA, quantidade);
            std::cout << "Item adicionado!\n";
        } else {
            std::cout << "Tipo inválido!\n";
        }
    }
    
    void usarItem(Personagem* p) {
        std::cout << "\nTipos de item:\n";
        std::cout << "1. Poção de HP\n";
        std::cout << "2. Poção de Mana\n";
        std::cout << "Escolha o tipo: ";
        int tipo;
        std::cin >> tipo;
        
        if (tipo == 1) {
            p->getInventario().usarItem(ItemTipo::POTION_HP);
        } else if (tipo == 2) {
            p->getInventario().usarItem(ItemTipo::POTION_MANA);
        } else {
            std::cout << "Tipo inválido!\n";
        }
    }
    
    void mostrarMagiasPersonagem(Personagem* p) {
        const auto& magiasPersonagem = p->getMagias();
        if (magiasPersonagem.empty()) {
            std::cout << "\nNenhuma magia aprendida.\n";
            return;
        }
        
        std::cout << "\n=== Magias de " << p->getNome() << " ===\n";
        for (size_t i = 0; i < magiasPersonagem.size(); ++i) {
            std::cout << i + 1 << ". " << magiasPersonagem[i]->getNome()
                      << " (MP: " << magiasPersonagem[i]->getCustoMP()
                      << ", Nível: " << magiasPersonagem[i]->getNivelMinimo() << ")\n";
        }
    }
    
    void adicionarMagia(Personagem* p) {
        mostrarMagias();
        std::cout << "Escolha a magia: ";
        int escolha;
        std::cin >> escolha;
        
        if (escolha > 0 && escolha <= static_cast<int>(magias.size())) {
            p->adicionarMagia(magias[escolha - 1]);
            std::cout << "Magia adicionada!\n";
        } else {
            std::cout << "Escolha inválida!\n";
        }
    }
    
    void iniciarCombate() {
        if (personagens.size() < 2) {
            std::cout << "\nPrecisa de pelo menos 2 personagens para iniciar um combate!\n";
            return;
        }
        
        std::cout << "\n=== SELECIONAR COMBATENTES ===\n";
        listarPersonagens();
        
        std::vector<Personagem*> combatentesSelecionados;
        
        std::cout << "\nQuantos personagens participarão do combate? (2-" << personagens.size() << "): ";
        int numCombatentes;
        std::cin >> numCombatentes;
        
        if (numCombatentes < 2 || numCombatentes > static_cast<int>(personagens.size())) {
            std::cout << "Número inválido de combatentes!\n";
            return;
        }
        
        for (int i = 0; i < numCombatentes; ++i) {
            std::cout << "Escolha o combatente " << (i + 1) << " (número): ";
            int escolha;
            std::cin >> escolha;
            
            if (escolha > 0 && escolha <= static_cast<int>(personagens.size())) {
                Personagem* p = personagens[escolha - 1];
                
                // Verificar se já foi selecionado
                bool jaSelecionado = false;
                for (const auto& combatente : combatentesSelecionados) {
                    if (combatente == p) {
                        jaSelecionado = true;
                        break;
                    }
                }
                
                if (jaSelecionado) {
                    std::cout << "Este personagem já foi selecionado!\n";
                    i--; // Tentar novamente
                } else {
                    combatentesSelecionados.push_back(p);
                }
            } else {
                std::cout << "Escolha inválida!\n";
                i--; // Tentar novamente
            }
        }
        
        // Configurar sistema de combate
        sistemaCombate.limparCombatentes();
        for (Personagem* p : combatentesSelecionados) {
            sistemaCombate.adicionarCombatente(p);
        }
        
        // Adicionar armas e ataques ao sistema
        for (Arma* arma : armas) {
            sistemaCombate.adicionarArma(arma);
        }
        for (Ataque* ataque : ataques) {
            sistemaCombate.adicionarAtaque(ataque);
        }
        
        // Iniciar combate
        std::string vencedor = sistemaCombate.iniciarCombate();
        
        if (!vencedor.empty()) {
            std::cout << "\nParabéns, " << vencedor << " venceu o combate!\n";
        }
    }
    
    std::string sanitizarNomeArquivo(const std::string& nome) {
        std::string sanitizado = nome;
        // Remover caracteres especiais e substituir espaços por underscore
        for (char& c : sanitizado) {
            if (c == ' ') c = '_';
            else if (!isalnum(c) && c != '_') c = '_';
        }
        return sanitizado;
    }
    
    void salvarPersonagem(Personagem* p) {
        std::string nomeArquivo = sanitizarNomeArquivo(p->getNome()) + ".txt";
        std::ofstream arquivo(nomeArquivo);
        
        if (!arquivo.is_open()) {
            std::cout << "Erro ao criar arquivo para " << p->getNome() << "\n";
            return;
        }
        
        // Salvar dados básicos
        arquivo << "=== DADOS BÁSICOS ===" << std::endl;
        arquivo << "Nome: " << p->getNome() << std::endl;
        arquivo << "Classe: " << p->getClasse()->getNome() << std::endl;
        arquivo << "Raça: " << p->getRaca()->getNome() << std::endl;
        arquivo << "Nível: " << p->getNivel() << std::endl;
        arquivo << std::endl;
        
        // Salvar atributos
        arquivo << "=== ATRIBUTOS ===" << std::endl;
        arquivo << "HP: " << p->getHP() << std::endl;
        arquivo << "MP: " << p->getMP() << std::endl;
        arquivo << "Ataque Físico: " << p->getAtaqueFisico() << std::endl;
        arquivo << "Ataque Mágico: " << p->getAtaqueMagico() << std::endl;
        arquivo << "Defesa: " << p->getDefesa() << std::endl;
        arquivo << "Agilidade: " << p->getAgilidade() << std::endl;
        arquivo << std::endl;
        
        // Salvar inventário
        arquivo << "=== INVENTÁRIO ===" << std::endl;
        p->getInventario().salvarInventario(arquivo);
        arquivo << std::endl;
        
        // Salvar magias
        arquivo << "=== MAGIAS ===" << std::endl;
        const auto& magiasPersonagem = p->getMagias();
        if (magiasPersonagem.empty()) {
            arquivo << "Nenhuma magia aprendida" << std::endl;
        } else {
            for (const auto& magia : magiasPersonagem) {
                arquivo << magia->getNome() << std::endl;
            }
        }
        
        arquivo.close();
        std::cout << "Personagem " << p->getNome() << " salvo em '" << nomeArquivo << "'\n";
    }
    
    void salvarPersonagens() {
        if (personagens.empty()) {
            std::cout << "Nenhum personagem para salvar.\n";
            return;
        }
        
        for (Personagem* p : personagens) {
            salvarPersonagem(p);
        }
        
        // Salvar lista de personagens
        std::ofstream listaArquivo("personagens_lista.txt");
        if (listaArquivo.is_open()) {
            for (Personagem* p : personagens) {
                listaArquivo << p->getNome() << std::endl;
            }
            listaArquivo.close();
            std::cout << "Lista de personagens salva em 'personagens_lista.txt'\n";
        }
    }
    
    void carregarPersonagens() {
        std::ifstream listaArquivo("personagens_lista.txt");
        if (!listaArquivo.is_open()) {
            std::cout << "Arquivo 'personagens_lista.txt' não encontrado.\n";
            return;
        }
        
        // Limpar personagens existentes
        for (Personagem* p : personagens) {
            delete p;
        }
        personagens.clear();
        
        std::string nomePersonagem;
        while (std::getline(listaArquivo, nomePersonagem)) {
            if (!nomePersonagem.empty()) {
                carregarPersonagem(nomePersonagem);
            }
        }
        
        listaArquivo.close();
        std::cout << "Personagens carregados com sucesso!\n";
    }
    
    void carregarPersonagem(const std::string& nome) {
        std::string nomeArquivo = sanitizarNomeArquivo(nome) + ".txt";
        std::ifstream arquivo(nomeArquivo);
        
        if (!arquivo.is_open()) {
            std::cout << "Arquivo '" << nomeArquivo << "' não encontrado.\n";
            return;
        }
        
        std::string linha;
        std::string classeNome, racaNome;
        int nivel = 1, hp = 0, mp = 0, atkF = 0, atkM = 0, def = 0, agi = 0;
        bool carregandoInventario = false;
        bool carregandoMagias = false;
        std::vector<std::string> magiasNomes;
        
        while (std::getline(arquivo, linha)) {
            if (linha == "=== INVENTÁRIO ===") {
                carregandoInventario = true;
                carregandoMagias = false;
                continue;
            } else if (linha == "=== MAGIAS ===") {
                carregandoInventario = false;
                carregandoMagias = true;
                continue;
            } else if (linha.find("===") == 0) {
                carregandoInventario = false;
                carregandoMagias = false;
                continue;
            }
            
            if (carregandoInventario && !linha.empty()) {
                // O inventário será carregado depois
                continue;
            } else if (carregandoMagias && !linha.empty() && linha != "Nenhuma magia aprendida") {
                magiasNomes.push_back(linha);
            } else if (!carregandoInventario && !carregandoMagias) {
                if (linha.find("Classe: ") == 0) {
                    classeNome = linha.substr(8);
                } else if (linha.find("Raça: ") == 0) {
                    racaNome = linha.substr(6);
                } else if (linha.find("Nível: ") == 0) {
                    nivel = std::stoi(linha.substr(7));
                } else if (linha.find("HP: ") == 0) {
                    hp = std::stoi(linha.substr(4));
                } else if (linha.find("MP: ") == 0) {
                    mp = std::stoi(linha.substr(4));
                } else if (linha.find("Ataque Físico: ") == 0) {
                    atkF = std::stoi(linha.substr(15));
                } else if (linha.find("Ataque Mágico: ") == 0) {
                    atkM = std::stoi(linha.substr(15));
                } else if (linha.find("Defesa: ") == 0) {
                    def = std::stoi(linha.substr(8));
                } else if (linha.find("Agilidade: ") == 0) {
                    agi = std::stoi(linha.substr(11));
                }
            }
        }
        
        arquivo.close();
        
        // Encontrar classe e raça
        Classe* classe = nullptr;
        Race* raca = nullptr;
        
        for (Classe* c : classes) {
            if (c->getNome() == classeNome) {
                classe = c;
                break;
            }
        }
        
        for (Race* r : racas) {
            if (r->getNome() == racaNome) {
                raca = r;
                break;
            }
        }
        
        if (classe && raca) {
            Personagem* personagem = new Personagem(
                nome, classe, raca, hp, mp, atkF, atkM, def, agi, nivel
            );
            
            // Carregar inventário
            std::ifstream arquivoInventario(nomeArquivo);
            if (arquivoInventario.is_open()) {
                bool naSecaoInventario = false;
                std::string linhaInventario;
                while (std::getline(arquivoInventario, linhaInventario)) {
                    if (linhaInventario == "=== INVENTÁRIO ===") {
                        naSecaoInventario = true;
                        continue;
                    } else if (linhaInventario.find("===") == 0) {
                        naSecaoInventario = false;
                        continue;
                    }
                    
                    if (naSecaoInventario && !linhaInventario.empty()) {
                        size_t pos = linhaInventario.find(": ");
                        if (pos != std::string::npos) {
                            std::string nomeItem = linhaInventario.substr(0, pos);
                            int quantidade = std::stoi(linhaInventario.substr(pos + 2));
                            
                            if (nomeItem == "Poção de HP") {
                                personagem->getInventario().adicionarItem(ItemTipo::POTION_HP, quantidade);
                            } else if (nomeItem == "Poção de Mana") {
                                personagem->getInventario().adicionarItem(ItemTipo::POTION_MANA, quantidade);
                            }
                        }
                    }
                }
                arquivoInventario.close();
            }
            
            // Carregar magias
            for (const std::string& magiaNome : magiasNomes) {
                for (Magia* m : magias) {
                    if (m->getNome() == magiaNome) {
                        personagem->adicionarMagia(m);
                        break;
                    }
                }
            }
            
            personagens.push_back(personagem);
        }
    }
    
public:
    RPGManager() {
        inicializarClasses();
        inicializarRacas();
        inicializarMagias();
        inicializarArmas();
        inicializarAtaques();
    }
    
    ~RPGManager() {
        for (Personagem* p : personagens) {
            delete p;
        }
        for (Classe* c : classes) {
            delete c;
        }
        for (Race* r : racas) {
            delete r;
        }
        for (Magia* m : magias) {
            delete m;
        }
        for (Arma* a : armas) {
            delete a;
        }
        for (Ataque* at : ataques) {
            delete at;
        }
    }
    
    void executar() {
        int opcao;
        
        do {
            mostrarMenu();
            std::cin >> opcao;
            
            switch (opcao) {
                case 1:
                    criarPersonagem();
                    break;
                case 2:
                    listarPersonagens();
                    break;
                case 3:
                    gerenciarPersonagem();
                    break;
                case 4:
                    salvarPersonagens();
                    break;
                case 5:
                    carregarPersonagens();
                    break;
                case 6:
                    iniciarCombate();
                    break;
                case 7:
                    std::cout << "Saindo...\n";
                    break;
                default:
                    std::cout << "Opção inválida!\n";
            }
        } while (opcao != 7);
    }
};

int main() {
    RPGManager rpg;
    rpg.executar();
    return 0;
} 