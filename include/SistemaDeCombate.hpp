#ifndef SISTEMA_DE_COMBATE_HPP
#define SISTEMA_DE_COMBATE_HPP

#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>
#include <limits>
#include <iostream>
#include "Personagem.hpp"
#include "Arma.hpp"
#include "Ataque.hpp"

/**
 * @brief Estrutura que representa o resultado de um turno de combate.
 */
struct ResultadoTurno {
    bool combateContinua;         /**< Se o combate deve continuar */
    std::string vencedor;         /**< Nome do vencedor (se houver) */
    int danoCausado;              /**< Dano causado no turno */
    std::string descricao;        /**< Descrição do que aconteceu */
    
    ResultadoTurno(bool continua = true, const std::string& vencedor = "", 
                   int dano = 0, const std::string& desc = "")
        : combateContinua(continua), vencedor(vencedor), danoCausado(dano), descricao(desc) {}
};

/**
 * @brief Classe que gerencia o sistema de combate do RPG.
 *
 * Responsável por coordenar batalhas entre personagens, incluindo
 * seleção de ataques, cálculo de dano, e determinação de vencedores.
 */
class SistemaDeCombate {
private:
    std::vector<Personagem*> combatentes;
    std::vector<Arma*> armas;
    std::vector<Ataque*> ataques;
    int turnoAtual;
    
    /**
     * @brief Inicializa o gerador de números aleatórios.
     */
    void inicializarRandom() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        srand(seed);
    }
    
    /**
     * @brief Determina a ordem de iniciativa dos combatentes.
     * @return Vetor com os índices dos combatentes em ordem de iniciativa.
     */
    std::vector<int> determinarIniciativa() {
        std::vector<std::pair<int, int>> iniciativa; // <agilidade, índice>
        
        for (size_t i = 0; i < combatentes.size(); ++i) {
            iniciativa.push_back({combatentes[i]->getAgilidade(), i});
        }
        
        // Ordenar por agilidade (maior primeiro)
        std::sort(iniciativa.begin(), iniciativa.end(), 
                  std::greater<std::pair<int, int>>());
        
        std::vector<int> ordem;
        for (const auto& pair : iniciativa) {
            ordem.push_back(pair.second);
        }
        
        return ordem;
    }
    
    /**
     * @brief Verifica se um personagem está vivo.
     * @param personagem Personagem a verificar.
     * @return true se está vivo, false caso contrário.
     */
    bool estaVivo(const Personagem* personagem) const {
        return personagem->getHP() > 0;
    }
    
    /**
     * @brief Conta quantos combatentes estão vivos.
     * @return Número de combatentes vivos.
     */
    int contarVivos() const {
        int vivos = 0;
        for (const auto& combatente : combatentes) {
            if (estaVivo(combatente)) vivos++;
        }
        return vivos;
    }
    
    /**
     * @brief Encontra o próximo alvo vivo.
     * @param atacante Índice do atacante.
     * @return Índice do alvo, ou -1 se não houver alvos.
     */
    int encontrarAlvo(int atacante) {
        for (size_t i = 0; i < combatentes.size(); ++i) {
            if (i != atacante && estaVivo(combatentes[i])) {
                return i;
            }
        }
        return -1;
    }
    
    /**
     * @brief Seleciona um ataque aleatório para o personagem.
     * @param personagem Personagem que vai atacar.
     * @return Ponteiro para o ataque selecionado.
     */
    Ataque* selecionarAtaque(Personagem* personagem) {
        // Por enquanto, retorna o primeiro ataque disponível
        // Em uma implementação mais avançada, isso seria baseado na IA do personagem
        if (!ataques.empty()) {
            return ataques[0]; // Golpe Rápido por padrão
        }
        return nullptr;
    }
    
    /**
     * @brief Executa o turno de um combatente.
     * @param indiceCombatente Índice do combatente no vetor.
     * @return Resultado do turno.
     */
    ResultadoTurno executarTurno(int indiceCombatente) {
        Personagem* atacante = combatentes[indiceCombatente];
        
        // Verificar se o atacante está vivo
        if (!estaVivo(atacante)) {
            return ResultadoTurno(true, "", 0, atacante->getNome() + " está inconsciente.");
        }
        
        // Verificar se há alvos disponíveis
        bool haAlvos = false;
        for (size_t i = 0; i < combatentes.size(); ++i) {
            if (i != indiceCombatente && estaVivo(combatentes[i])) {
                haAlvos = true;
                break;
            }
        }
        
        if (!haAlvos) {
            return ResultadoTurno(false, atacante->getNome(), 0, "Não há mais alvos!");
        }
        
        std::cout << "\n🎯 Turno de " << atacante->getNome() << "\n";
        
        // Permitir que o jogador escolha a ação
        bool acaoExecutada = false;
        while (!acaoExecutada) {
            acaoExecutada = escolherAcao(atacante, nullptr);
        }
        
        // Verificar se algum combatente morreu
        for (size_t i = 0; i < combatentes.size(); ++i) {
            if (!estaVivo(combatentes[i])) {
                std::string descricao = combatentes[i]->getNome() + " foi derrotado!";
                
                // Verificar se há apenas um sobrevivente
                if (contarVivos() == 1) {
                    for (const auto& combatente : combatentes) {
                        if (estaVivo(combatente)) {
                            return ResultadoTurno(false, combatente->getNome(), 0, descricao);
                        }
                    }
                }
                
                return ResultadoTurno(true, "", 0, descricao);
            }
        }
        
        return ResultadoTurno(true, "", 0, "");
    }

public:
    /**
     * @brief Construtor do sistema de combate.
     */
    SistemaDeCombate() : turnoAtual(0) {
        inicializarRandom();
    }
    
    /**
     * @brief Destrutor do sistema de combate.
     */
    ~SistemaDeCombate() {
        // Não deletar os personagens, apenas as armas e ataques
        for (auto& arma : armas) {
            delete arma;
        }
        for (auto& ataque : ataques) {
            delete ataque;
        }
    }
    
    /**
     * @brief Adiciona um combatente ao sistema.
     * @param personagem Personagem a adicionar.
     */
    void adicionarCombatente(Personagem* personagem) {
        combatentes.push_back(personagem);
    }
    
    /**
     * @brief Adiciona uma arma ao sistema.
     * @param arma Arma a adicionar.
     */
    void adicionarArma(Arma* arma) {
        armas.push_back(arma);
    }
    
    /**
     * @brief Adiciona um ataque ao sistema.
     * @param ataque Ataque a adicionar.
     */
    void adicionarAtaque(Ataque* ataque) {
        ataques.push_back(ataque);
    }
    
    /**
     * @brief Inicia um combate entre os combatentes.
     * @return Nome do vencedor.
     */
    std::string iniciarCombate() {
        if (combatentes.size() < 2) {
            std::cout << "Precisa de pelo menos 2 combatentes para iniciar um combate!\n";
            return "";
        }
        
        std::cout << "\n=== COMBATE INICIADO ===\n";
        std::cout << "Combatentes:\n";
        for (size_t i = 0; i < combatentes.size(); ++i) {
            mostrarStatsPersonagem(combatentes[i], i);
        }
        std::cout << std::endl;
        
        turnoAtual = 0;
        
        while (contarVivos() > 1) {
            turnoAtual++;
            std::cout << "\n" << std::string(50, '=') << "\n";
            std::cout << "           TURNO " << turnoAtual << "\n";
            std::cout << std::string(50, '=') << "\n";
            
            // Determinar ordem de iniciativa
            std::vector<int> ordem = determinarIniciativa();
            mostrarOrdemIniciativa(ordem);
            
            // Executar turnos
            for (int indice : ordem) {
                if (estaVivo(combatentes[indice])) {
                    std::cout << "\n--- " << combatentes[indice]->getNome() << " ATACA ---\n";
                    ResultadoTurno resultado = executarTurno(indice);
                    
                    if (!resultado.combateContinua) {
                        std::cout << "\n" << std::string(50, '=') << "\n";
                        std::cout << "        COMBATE FINALIZADO\n";
                        std::cout << "        VENCEDOR: " << resultado.vencedor << "\n";
                        std::cout << std::string(50, '=') << "\n";
                        return resultado.vencedor;
                    }
                    
                    if (!resultado.descricao.empty()) {
                        std::cout << resultado.descricao << "\n";
                    }
                    
                    // Pausa entre ataques para melhor visualização
                    std::cout << "\nPressione ENTER para continuar...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            // Mostrar status dos combatentes após o turno
            mostrarStatusCombatentes();
            
            // Pausa entre turnos
            if (contarVivos() > 1) {
                std::cout << "\nPressione ENTER para o próximo turno...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
        // Encontrar vencedor
        for (const auto& combatente : combatentes) {
            if (estaVivo(combatente)) {
                std::cout << "\n" << std::string(50, '=') << "\n";
                std::cout << "        COMBATE FINALIZADO\n";
                std::cout << "        VENCEDOR: " << combatente->getNome() << "\n";
                std::cout << std::string(50, '=') << "\n";
                return combatente->getNome();
            }
        }
        
        return "";
    }
    
    /**
     * @brief Limpa todos os combatentes do sistema.
     */
    void limparCombatentes() {
        combatentes.clear();
    }
    
    /**
     * @brief Retorna o número de combatentes.
     * @return Número de combatentes.
     */
    size_t getNumeroCombatentes() const {
        return combatentes.size();
    }
    
    /**
     * @brief Retorna um combatente pelo índice.
     * @param indice Índice do combatente.
     * @return Ponteiro para o combatente.
     */
    Personagem* getCombatente(size_t indice) const {
        if (indice < combatentes.size()) {
            return combatentes[indice];
        }
        return nullptr;
    }
    
    /**
     * @brief Mostra os stats detalhados de um personagem.
     * @param personagem Personagem para mostrar os stats.
     * @param indice Índice do personagem na lista.
     */
    void mostrarStatsPersonagem(const Personagem* personagem, int indice) const {
        std::cout << indice + 1 << ". " << personagem->getNome() 
                  << " (" << personagem->getClasse()->getNome() 
                  << " " << personagem->getRaca()->getNome() << ")\n";
        std::cout << "   HP: " << personagem->getHP() 
                  << " | MP: " << personagem->getMP()
                  << " | AtkF: " << personagem->getAtaqueFisico()
                  << " | AtkM: " << personagem->getAtaqueMagico()
                  << " | Def: " << personagem->getDefesa()
                  << " | Agi: " << personagem->getAgilidade()
                  << " | Nível: " << personagem->getNivel() << "\n";
    }
    
    /**
     * @brief Mostra o status de todos os combatentes.
     */
    void mostrarStatusCombatentes() const {
        std::cout << "\n=== STATUS DOS COMBATENTES ===\n";
        for (size_t i = 0; i < combatentes.size(); ++i) {
            const Personagem* p = combatentes[i];
            std::string status = estaVivo(p) ? "VIVO" : "DERROTADO";
            std::cout << i + 1 << ". " << p->getNome() 
                      << " [" << status << "] "
                      << "HP: " << p->getHP() 
                      << " | MP: " << p->getMP() << "\n";
        }
        std::cout << "==============================\n";
    }
    
    /**
     * @brief Mostra a ordem de iniciativa do turno.
     * @param ordem Vetor com a ordem de iniciativa.
     */
    void mostrarOrdemIniciativa(const std::vector<int>& ordem) const {
        std::cout << "\n--- ORDEM DE INICIATIVA ---\n";
        for (size_t i = 0; i < ordem.size(); ++i) {
            const Personagem* p = combatentes[ordem[i]];
            if (estaVivo(p)) {
                std::cout << i + 1 << ". " << p->getNome() 
                          << " (Agi: " << p->getAgilidade() << ")\n";
            }
        }
        std::cout << "---------------------------\n";
    }
    
    /**
     * @brief Mostra as ações disponíveis para um personagem.
     * @param personagem Personagem que vai escolher a ação.
     */
    void mostrarAcoesDisponiveis(const Personagem* personagem) const {
        std::cout << "\n=== AÇÕES DISPONÍVEIS ===\n";
        std::cout << "1. Ataque Básico (Golpe Rápido)\n";
        std::cout << "2. Ataque Especial (Golpe Pesado) - Custo: 5 MP\n";
        std::cout << "3. Usar Poção de HP\n";
        std::cout << "4. Usar Poção de Mana\n";
        std::cout << "5. Usar Magia\n";
        std::cout << "6. Ver status dos combatentes\n";
        std::cout << "7. Ver magias disponíveis\n";
        std::cout << "========================\n";
    }
    
    /**
     * @brief Permite ao jogador escolher uma ação.
     * @param personagem Personagem que vai executar a ação.
     * @param alvo Personagem alvo (se aplicável).
     * @return true se a ação foi executada com sucesso.
     */
    bool escolherAcao(Personagem* personagem, Personagem* alvo) {
        mostrarAcoesDisponiveis(personagem);
        
        int escolha;
        std::cout << personagem->getNome() << ", escolha sua ação (1-7): ";
        std::cin >> escolha;
        
        switch (escolha) {
            case 1: // Ataque Básico
                return executarAtaqueBasico(personagem);
            case 2: // Ataque Especial
                return executarAtaqueEspecial(personagem);
            case 3: // Usar Poção de HP
                return usarPocaoHP(personagem);
            case 4: // Usar Poção de Mana
                return usarPocaoMana(personagem);
            case 5: // Usar Magia
                return usarMagia(personagem);
            case 6: // Ver status
                mostrarStatusCombatentes();
                return escolherAcao(personagem, alvo); // Escolher novamente
            case 7: // Ver magias
                mostrarMagiasPersonagem(personagem);
                return escolherAcao(personagem, alvo); // Escolher novamente
            default:
                std::cout << "Escolha inválida! Tente novamente.\n";
                return escolherAcao(personagem, alvo); // Escolher novamente
        }
    }
    
    /**
     * @brief Executa um ataque básico.
     * @param atacante Personagem atacante.
     * @return true se o ataque foi executado com sucesso.
     */
    bool executarAtaqueBasico(Personagem* atacante) {
        Personagem* alvo = escolherAlvo(atacante);
        if (!alvo) {
            std::cout << "Ação cancelada.\n";
            return false;
        }
        
        Ataque* ataque = nullptr;
        for (Ataque* a : ataques) {
            if (a->getNome() == "Golpe Rápido") {
                ataque = a;
                break;
            }
        }
        
        if (!ataque) {
            std::cout << "Ataque básico não disponível!\n";
            return false;
        }
        
        int danoBase = atacante->getAtaqueFisico();
        int danoCausado = ataque->executarAtaque(*atacante, *alvo, danoBase);
        
        if (danoCausado > 0) {
            std::cout << "✅ Ataque executado com sucesso!\n";
        }
        
        return true;
    }
    
    /**
     * @brief Executa um ataque especial.
     * @param atacante Personagem atacante.
     * @return true se o ataque foi executado com sucesso.
     */
    bool executarAtaqueEspecial(Personagem* atacante) {
        Personagem* alvo = escolherAlvo(atacante);
        if (!alvo) {
            std::cout << "Ação cancelada.\n";
            return false;
        }
        
        Ataque* ataque = nullptr;
        for (Ataque* a : ataques) {
            if (a->getNome() == "Golpe Pesado") {
                ataque = a;
                break;
            }
        }
        
        if (!ataque) {
            std::cout << "Ataque especial não disponível!\n";
            return false;
        }
        
        if (atacante->getMP() < ataque->getModificadores().custoEnergia) {
            std::cout << "❌ MP insuficiente para ataque especial!\n";
            return false;
        }
        
        int danoBase = atacante->getAtaqueFisico();
        int danoCausado = ataque->executarAtaque(*atacante, *alvo, danoBase);
        
        if (danoCausado > 0) {
            std::cout << "✅ Ataque especial executado com sucesso!\n";
        }
        
        return true;
    }
    
    /**
     * @brief Usa uma poção de HP.
     * @param personagem Personagem que vai usar a poção.
     * @return true se a poção foi usada com sucesso.
     */
    bool usarPocaoHP(Personagem* personagem) {
        personagem->getInventario().usarItem(ItemTipo::POTION_HP);
        
        // Restaurar HP (implementação simples)
        int hpAtual = personagem->getHP();
        int hpMaximo = 100; // Por enquanto, usar valor fixo
        int restauracao = 30; // Restaurar 30 HP
        
        personagem->setHP(std::min(hpMaximo, hpAtual + restauracao));
        std::cout << "💚 HP restaurado: " << hpAtual << " → " << personagem->getHP() << "\n";
        
        return true;
    }
    
    /**
     * @brief Usa uma poção de mana.
     * @param personagem Personagem que vai usar a poção.
     * @return true se a poção foi usada com sucesso.
     */
    bool usarPocaoMana(Personagem* personagem) {
        personagem->getInventario().usarItem(ItemTipo::POTION_MANA);
        
        // Restaurar MP (implementação simples)
        int mpAtual = personagem->getMP();
        int mpMaximo = 50; // Por enquanto, usar valor fixo
        int restauracao = 20; // Restaurar 20 MP
        
        personagem->setMP(std::min(mpMaximo, mpAtual + restauracao));
        std::cout << "🔮 MP restaurado: " << mpAtual << " → " << personagem->getMP() << "\n";
        
        return true;
    }
    
    /**
     * @brief Mostra as magias disponíveis para um personagem.
     * @param personagem Personagem para mostrar as magias.
     */
    void mostrarMagiasPersonagem(const Personagem* personagem) const {
        const auto& magiasPersonagem = personagem->getMagias();
        if (magiasPersonagem.empty()) {
            std::cout << "\nNenhuma magia aprendida.\n";
            return;
        }
        
        std::cout << "\n=== MAGIAS DE " << personagem->getNome() << " ===\n";
        for (size_t i = 0; i < magiasPersonagem.size(); ++i) {
            std::cout << i + 1 << ". " << magiasPersonagem[i]->getNome()
                      << " (MP: " << magiasPersonagem[i]->getCustoMP()
                      << ", Nível: " << magiasPersonagem[i]->getNivelMinimo() << ")\n";
        }
        std::cout << "==========================\n";
    }
    
    /**
     * @brief Permite ao jogador escolher um alvo.
     * @param atacante Personagem atacante.
     * @return Ponteiro para o alvo escolhido, ou nullptr se cancelado.
     */
    Personagem* escolherAlvo(const Personagem* atacante) {
        std::vector<Personagem*> alvosDisponiveis;
        
        // Coletar alvos vivos
        for (size_t i = 0; i < combatentes.size(); ++i) {
            if (combatentes[i] != atacante && estaVivo(combatentes[i])) {
                alvosDisponiveis.push_back(combatentes[i]);
            }
        }
        
        if (alvosDisponiveis.empty()) {
            return nullptr;
        }
        
        if (alvosDisponiveis.size() == 1) {
            return alvosDisponiveis[0];
        }
        
        // Mostrar alvos disponíveis
        std::cout << "\n=== ALVOS DISPONÍVEIS ===\n";
        for (size_t i = 0; i < alvosDisponiveis.size(); ++i) {
            const Personagem* alvo = alvosDisponiveis[i];
            std::cout << i + 1 << ". " << alvo->getNome() 
                      << " (HP: " << alvo->getHP() 
                      << " | MP: " << alvo->getMP() << ")\n";
        }
        std::cout << "0. Cancelar ação\n";
        std::cout << "========================\n";
        
        int escolha;
        std::cout << "Escolha o alvo (0-" << alvosDisponiveis.size() << "): ";
        std::cin >> escolha;
        
        if (escolha == 0) {
            return nullptr;
        }
        
        if (escolha > 0 && escolha <= static_cast<int>(alvosDisponiveis.size())) {
            return alvosDisponiveis[escolha - 1];
        }
        
        std::cout << "Escolha inválida!\n";
        return escolherAlvo(atacante); // Tentar novamente
    }
    
    /**
     * @brief Usa uma magia.
     * @param personagem Personagem que vai usar a magia.
     * @return true se a magia foi usada com sucesso.
     */
    bool usarMagia(Personagem* personagem) {
        const auto& magiasPersonagem = personagem->getMagias();
        if (magiasPersonagem.empty()) {
            std::cout << "❌ " << personagem->getNome() << " não conhece nenhuma magia!\n";
            return false;
        }
        
        // Mostrar magias disponíveis
        std::cout << "\n=== MAGIAS DISPONÍVEIS ===\n";
        for (size_t i = 0; i < magiasPersonagem.size(); ++i) {
            const Magia* magia = magiasPersonagem[i];
            std::cout << i + 1 << ". " << magia->getNome()
                      << " (MP: " << magia->getCustoMP()
                      << ", Nível: " << magia->getNivelMinimo() << ")\n";
        }
        std::cout << "0. Cancelar\n";
        std::cout << "==========================\n";
        
        int escolha;
        std::cout << "Escolha a magia (0-" << magiasPersonagem.size() << "): ";
        std::cin >> escolha;
        
        if (escolha == 0) {
            std::cout << "Ação cancelada.\n";
            return false;
        }
        
        if (escolha < 1 || escolha > static_cast<int>(magiasPersonagem.size())) {
            std::cout << "Escolha inválida!\n";
            return usarMagia(personagem); // Tentar novamente
        }
        
        const Magia* magia = magiasPersonagem[escolha - 1];
        
        // Verificar se tem MP suficiente
        if (personagem->getMP() < magia->getCustoMP()) {
            std::cout << "❌ MP insuficiente para " << magia->getNome() << "!\n";
            return false;
        }
        
        // Escolher alvo
        Personagem* alvo = escolherAlvo(personagem);
        if (!alvo) {
            std::cout << "Ação cancelada.\n";
            return false;
        }
        
        // Executar magia (implementação simples)
        std::cout << "🔮 " << personagem->getNome() << " conjura " << magia->getNome() << "!\n";
        
        // Consumir MP
        int mpAnterior = personagem->getMP();
        personagem->setMP(personagem->getMP() - magia->getCustoMP());
        std::cout << "MP consumido: " << mpAnterior << " → " << personagem->getMP() << "\n";
        
        // Aplicar efeito da magia
        if (magia->getNome() == "Cura") {
            int hpAtual = alvo->getHP();
            int restauracao = 25;
            alvo->setHP(std::min(100, hpAtual + restauracao));
            std::cout << "💚 " << alvo->getNome() << " foi curado! HP: " 
                      << hpAtual << " → " << alvo->getHP() << "\n";
        } else if (magia->getNome() == "Bola de Fogo") {
            int dano = personagem->getAtaqueMagico() + 15;
            int hpAnterior = alvo->getHP();
            alvo->setHP(std::max(0, alvo->getHP() - dano));
            std::cout << "🔥 " << alvo->getNome() << " foi atingido pela bola de fogo!\n";
            std::cout << "Dano causado: " << dano << " (HP: " << hpAnterior 
                      << " → " << alvo->getHP() << ")\n";
        } else {
            std::cout << "✨ Efeito da magia " << magia->getNome() << " aplicado!\n";
        }
        
        return true;
    }
};

#endif 