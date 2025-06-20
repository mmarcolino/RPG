CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

# Arquivos fonte principais
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Arquivos de teste
TEST_SOURCES = $(wildcard $(TESTDIR)/test_*.cpp)
TEST_BINARIES = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BINDIR)/%)

# Alvo principal
TARGET = $(BINDIR)/rpg

# Regra padrão
all: $(TARGET) tests

# Compilar o programa principal
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar e executar testes
tests: $(TEST_BINARIES)
	@echo "Executando todos os testes..."
	@for test in $(TEST_BINARIES); do \
		echo "Running $$(basename $$test):"; \
		$$test; \
		echo ""; \
	done

# Compilar testes individuais
$(BINDIR)/test_%: $(TESTDIR)/test_%.cpp $(filter-out $(OBJDIR)/main.o, $(OBJECTS))
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Limpar arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Executar o programa principal
run: $(TARGET)
	./$(TARGET)

# Executar testes específicos
test_guerreiro: $(BINDIR)/test_guerreiro
	./$(BINDIR)/test_guerreiro

test_humano: $(BINDIR)/test_humano
	./$(BINDIR)/test_humano

test_iventario: $(BINDIR)/test_iventario
	./$(BINDIR)/test_iventario

test_mago: $(BINDIR)/test_mago
	./$(BINDIR)/test_mago

test_paladino: $(BINDIR)/test_paladino
	./$(BINDIR)/test_paladino

test_personagem: $(BINDIR)/test_personagem
	./$(BINDIR)/test_personagem

test_armas: $(BINDIR)/test_armas
	./$(BINDIR)/test_armas

test_ataques: $(BINDIR)/test_ataques
	./$(BINDIR)/test_ataques

test_magias: $(BINDIR)/test_magias
	./$(BINDIR)/test_magias

test_sistema_combate: $(BINDIR)/test_sistema_combate
	./$(BINDIR)/test_sistema_combate

# Gerar documentação Doxygen
docs:
	doxygen Doxyfile

# Instalar dependências (se necessário)
install:
	@echo "Verificando dependências..."
	@which $(CXX) > /dev/null || (echo "Erro: $(CXX) não encontrado. Instale o compilador C++." && exit 1)
	@echo "Dependências OK!"

.PHONY: all clean run tests test_guerreiro test_humano test_iventario test_mago test_paladino test_personagem test_armas test_ataques test_magias test_sistema_combate docs install

