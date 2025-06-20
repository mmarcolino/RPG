# RPG CMD - Sistema de RPG por Linha de Comando

Um sistema completo de RPG desenvolvido em C++ com combate interativo, sistema de classes, inventário, magias e persistência de dados.

## 🎮 Funcionalidades

### Sistema de Personagens
- **Classes**: Guerreiro, Mago e Paladino com atributos únicos
- **Raças**: Sistema de raças (atualmente Humano implementado)
- **Atributos**: HP, MP, Ataque Físico, Ataque Mágico, Defesa e Agilidade
- **Níveis**: Sistema de progressão por níveis

### Sistema de Combate
- **Combate por Turnos**: Sistema baseado em iniciativa (agilidade)
- **Ações Interativas**: Cada jogador escolhe suas ações manualmente
- **Armas**: Espada Curta, Cajado e Machado com modificadores únicos
- **Ataques**: Golpe Rápido e Golpe Pesado com diferentes características
- **Magias**: Cura e Bola de Fogo com custos de MP
- **Itens**: Poções de HP e Mana para uso durante o combate

### Sistema de Inventário
- **Gerenciamento de Itens**: Adicionar, usar e visualizar itens
- **Persistência**: Itens são salvos e carregados automaticamente
- **Tipos de Itens**: Poções de HP e Mana (expansível)

### Sistema de Magias
- **Magias por Classe**: Diferentes classes começam com magias diferentes
- **Custos de MP**: Cada magia tem seu próprio custo
- **Efeitos**: Cura restaura HP, Bola de Fogo causa dano mágico

### Persistência de Dados
- **Arquivos Separados**: Cada personagem tem seu próprio arquivo
- **Formato Legível**: Dados salvos em formato de texto simples
- **Carregamento Automático**: Sistema de lista de personagens

## Como Executar

### Pré-requisitos
- Compilador C++ (GCC, Clang ou MSVC)
- Make 

### Compilação e Execução

#### Usando Makefile (Recomendado)
```bash
# Compilar o programa principal
make rpg

# Executar o RPG
./bin/rpg

# Compilar e executar todos os testes
make test

# Limpar arquivos compilados
make clean

# Gerar documentação Doxygen
make docs
```

#### Compilação Manual
```bash
# Criar diretório bin se não existir
mkdir -p bin

# Compilar o programa principal
g++ -std=c++17 -I./include -o bin/rpg src/*.cpp

# Executar
./bin/rpg
```

##  Como Jogar

### 1. Criar Personagens
- Escolha entre Guerreiro, Mago ou Paladino
- Cada classe tem atributos únicos e magias iniciais
- Personagens começam com poções básicas

### 2. Gerenciar Personagens
- Ver e adicionar itens ao inventário
- Aprender novas magias
- Verificar status e atributos

### 3. Iniciar Combate
- Selecione 2 ou mais personagens para combater
- Cada turno, escolha entre:
  - Ataque Básico (Golpe Rápido)
  - Ataque Especial (Golpe Pesado) - Custo: 5 MP
  - Usar Poção de HP/Mana
  - Usar Magia
  - Ver status dos combatentes

### 4. Salvar Progresso
- Use a opção "Salvar personagens" para persistir dados
- Arquivos são criados automaticamente no diretório do projeto

##  Estrutura do Projeto

```
RPG/
├── include/          # Headers (.hpp)
├── src/             # Implementações (.cpp)
├── tests/           # Testes unitários
├── bin/             # Executáveis compilados
├── docs/            # Documentação Doxygen
├── branches-descriptions/  # Histórico de desenvolvimento
├── Makefile         # Scripts de compilação
└── README.md        # Este arquivo
```

##  Testes

O projeto inclui testes unitários abrangentes para todas as classes:

```bash
# Executar todos os testes
make test

# Testes individuais disponíveis:
# - test_personagem
# - test_guerreiro, test_mago, test_paladino
# - test_armas, test_ataques
# - test_magias, test_inventario
# - test_sistema_combate
```

##  Documentação

A documentação completa está disponível em `docs/html/index.html` após executar `make docs`.

## Desenvolvimento

### Arquitetura
- **Polimorfismo**: Uso extensivo de herança e interfaces
- **Separação de Responsabilidades**: Cada classe tem uma função específica

### Extensibilidade
O sistema foi projetado para fácil expansão:
- Novas classes e raças
- Novas armas e ataques
- Novas magias e itens
- Sistema de missões