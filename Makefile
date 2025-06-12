
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = $(wildcard src/*.cpp)
TESTS = $(wildcard tests/*.cpp)
BIN_DIR = bin

all: test

# o comando abaixo irá:
# 1- Compilar todos os arquivos de teste em tests/
# 2- Linkar com os arquivos fonte de src/ e include/;
# 3- Criar os binários em bin/;
# 4- Executar todos os testes e mostrar os resultados.
test: $(TESTS)
	@mkdir -p $(BIN_DIR)
	@for file in $(TESTS); do \
		name=$$(basename $$file .cpp); \
		$(CXX) $(CXXFLAGS) $$file $(SRC) -o $(BIN_DIR)/$$name && \
		echo "Running $$name:" && ./$(BIN_DIR)/$$name && echo ""; \
	done

