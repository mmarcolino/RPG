# Evolução do Sistema: Classes, Sistema Principal, Salvamento, Combate e Interatividade

---

## Sistema de Atributos Atualizado

O sistema de atributos foi padronizado em todas as classes para usar os seguintes 6 atributos:
- **HP** - Pontos de Vida
- **MP** - Pontos de Mana
- **Ataque Físico** - Dano físico
- **Ataque Mágico** - Dano mágico
- **Defesa** - Proteção contra ataques
- **Agilidade** - Velocidade/reflexos

## Classes Implementadas

### Guerreiro
- **Foco**: Combate físico com alta resistência
- **Atributos**: HP: 120, MP: 10, AtkF: 35, AtkM: 5, Def: 25, Agi: 15

### Mago
- **Foco**: Magias com alto poder mágico
- **Atributos**: HP: 80, MP: 50, AtkF: 10, AtkM: 40, Def: 15, Agi: 20

### Paladino
- **Foco**: Balanceado entre combate físico e mágico
- **Atributos**: HP: 100, MP: 30, AtkF: 25, AtkM: 20, Def: 30, Agi: 15

A classe `Personagem` foi atualizada para usar os mesmos 6 atributos, permitindo integração perfeita com o sistema de classes. Cada classe define seus atributos base via `getAtributosBase()`.

---

# Sistema Principal do RPG

## Interface de Linha de Comando

Sistema completo de RPG via linha de comando com as seguintes funcionalidades:

### Menu Principal
- Criar novo personagem (escolha de classe e raça)
- Listar personagens (com atributos)
- Gerenciar personagem (inventário e magias)
- Salvar/carregar personagens
- Sair

### Criação de Personagem
- Nome, classe e raça interativos
- Atributos definidos pela classe
- Itens e magias iniciais por classe
- Suporte a múltiplos personagens

### Gerenciamento de Personagem
- Ver/adicionar/usar itens
- Ver/adicionar magias

### Sistema de Inventário
- Poções de HP e Mana
- Persistência no salvamento

### Sistema de Magias
- Cura (MP: 8, Nível: 1) e Bola de Fogo (MP: 10, Nível: 2)
- Aprendizado por classe
- Expansível

### Persistência de Dados
- Cada personagem salvo em arquivo próprio
- Estrutura clara: dados básicos, atributos, inventário, magias

#### Exemplo de Arquivo de Personagem
```
=== DADOS BÁSICOS ===
Nome: Gandalf
Classe: Mago
Raça: Humano
Nível: 1

=== ATRIBUTOS ===
HP: 80
MP: 50
Ataque Físico: 10
Ataque Mágico: 40
Defesa: 15
Agilidade: 20

=== INVENTÁRIO ===
Poção de HP: 3
Poção de Mana: 2

=== MAGIAS ===
Cura
Bola de Fogo
```

---

# Melhorias no Sistema de Salvamento e Carregamento

- Cada personagem tem seu próprio arquivo `.txt` com todas as informações
- Inventário salvo e carregado com quantidades
- Lista de personagens em `personagens_lista.txt`
- Função `sanitizarNomeArquivo()` para nomes válidos

## Vantagens
- Organização, legibilidade, manutenibilidade e escalabilidade
- Suporte a muitos personagens sem complexidade

---

# Sistema de Combate

## Arquitetura
- **Arma.hpp**: Classe base, enums de tipo de arma e dano, modificadores
- **Ataque.hpp**: Classe base, enums de tipo de ataque, modificadores
- **SistemaDeCombate.hpp**: Gerencia batalhas, turnos, iniciativa, seleção de alvo, cálculo de dano

## Mecânicas
- Dano: `(Ataque Base × Modificador Arma × Modificador Ataque) - (Defesa × 0.5)`
- Acerto: `Chance Base + (Agilidade Atacante - Agilidade Alvo) × 0.01`
- Críticos: Golpe Rápido (15%, 1.5x), Golpe Pesado (25%, 2.0x)
- Ordem de iniciativa baseada em agilidade

## Integração
- Menu de combate no sistema principal
- Seleção de combatentes
- Interface de combate com status e mensagens

#### Exemplo de Uso
```cpp
// Criar personagens
Personagem* guerreiro = new Personagem("Aragorn", new Guerreiro(), new Humano(), ...);
Personagem* mago = new Personagem("Gandalf", new Mago(), new Humano(), ...);

// Configurar sistema de combate
SistemaDeCombate combate;
combate.adicionarCombatente(guerreiro);
combate.adicionarCombatente(mago);
combate.adicionarArma(new EspadaCurta());
combate.adicionarArma(new Cajado());
combate.adicionarAtaque(new GolpeRapido());
combate.adicionarAtaque(new GolpePesado());

// Iniciar combate
std::string vencedor = combate.iniciarCombate();
```

---

# Melhorias na Visualização do Sistema de Combate

## Stats Detalhados
- Exibe todos os atributos dos personagens

## Sistema de Turnos
- Visualização clara da ordem de iniciativa
- Status dos combatentes após cada turno

## Ataques Detalhados
- Mensagens de preparação, execução, dano e crítico
- Emojis e separadores visuais
- Pausas interativas entre ações

#### Exemplo de Combate
```
=== COMBATE INICIADO ===
Combatentes:
1. Gandalf (Mago Humano)
   HP: 80 | MP: 50 | AtkF: 10 | AtkM: 40 | Def: 15 | Agi: 20 | Nível: 1
2. Aragorn (Guerreiro Humano)
   HP: 120 | MP: 10 | AtkF: 35 | AtkM: 5 | Def: 25 | Agi: 15 | Nível: 1

==================================================
           TURNO 1
==================================================

--- ORDEM DE INICIATIVA ---
1. Gandalf (Agi: 20)
2. Aragorn (Agi: 15)
---------------------------

--- Gandalf ATACA ---
Gandalf prepara um Golpe Rápido...
⚔️ Gandalf usou Golpe Rápido em Aragorn!
   Dano causado: 25 (HP: 120 → 95)

Pressione ENTER para continuar...

--- Aragorn ATACA ---
Aragorn concentra energia para um Golpe Pesado...
🔮 MP consumido: 10 → 5
⚔️ Aragorn usou Golpe Pesado em Gandalf!
   Dano causado: 45 (HP: 80 → 35)

Pressione ENTER para continuar...

=== STATUS DOS COMBATENTES ===
1. Gandalf [VIVO] HP: 35 | MP: 50
2. Aragorn [VIVO] HP: 95 | MP: 5
==============================

Pressione ENTER para o próximo turno...
```

---

# Sistema de Combate Interativo

## Menu de Ações por Turno
- Ataque Básico (Golpe Rápido)
- Ataque Especial (Golpe Pesado)
- Usar Poção de HP/Mana
- Usar Magia
- Ver status dos combatentes
- Ver magias disponíveis

## Seleção de Alvo Inteligente
- Alvo único ou múltiplo, com informações de HP/MP
- Opção de cancelar ação

## Sistema de Magias no Combate
- Lista de magias aprendidas
- Verificação de MP
- Efeitos: Cura (restaura 25 HP), Bola de Fogo (dano mágico + 15)

## Uso de Itens no Combate
- Poções restauram HP/MP
- Verificação de inventário
- Feedback visual

## Interface Melhorada
- Emojis, separadores, mensagens informativas
- Pausas controladas pelo jogador

#### Exemplo de Turno Interativo
```
=== TURNO 1 ===
--- ORDEM DE INICIATIVA ---
1. Mago (Agi: 20)
2. Guerreiro (Agi: 15)

🎯 Turno de Mago

=== AÇÕES DISPONÍVEIS ===
1. Ataque Básico (Golpe Rápido)
2. Ataque Especial (Golpe Pesado) - Custo: 5 MP
3. Usar Poção de HP
4. Usar Poção de Mana
5. Usar Magia
6. Ver status dos combatentes
7. Ver magias disponíveis
========================

Mago, escolha sua ação (1-7): 5

=== MAGIAS DISPONÍVEIS ===
1. Cura (MP: 8, Nível: 1)
2. Bola de Fogo (MP: 10, Nível: 2)
0. Cancelar
==========================

Escolha a magia (0-2): 2

=== ALVOS DISPONÍVEIS ===
1. Guerreiro (HP: 120 | MP: 10)
0. Cancelar ação
========================

Escolha o alvo (0-1): 1

🔮 Mago conjura Bola de Fogo!
MP consumido: 50 → 40
🔥 Guerreiro foi atingido pela bola de fogo!
Dano causado: 55 (HP: 120 → 65)
✅ Ataque executado com sucesso!
```

---

## Vantagens Gerais
- Sistema modular, expansível e fácil de manter
- Experiência de combate rica, visual e interativa
- Pronto para futuras expansões: mais armas, ataques, IA, efeitos visuais e interface gráfica 