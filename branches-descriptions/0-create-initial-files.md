# include/Classe.hpp

- Classe base abstrata (superclasse) usada como interface.

- Define os métodos que toda classe jogável (como Guerreiro, Mago, etc) deve implementar.

- Métodos com const = 0 são puros virtuais, obrigando subclasses a fornecerem suas próprias implementações.

- Exemplo: getAtributosBase() retorna um vetor com os atributos HP, MP, Ataque, etc.

# Guerreiro.hpp
- Primeira classe que criei para ir testando durante o desenvolvimento do projeto. Devo criar só mais uma ou duas e deixar o resto para o final. Primeiro preciso implementar as lógicas dos spells, itens etc.

# Doxyfile
- Arquivo de configuração usado pelo Doxygen para gerar documentação técnica automática a partir dos comentários no código.

- Você pode gerar a documentação HTML com: `` doxygen Doxyfile ``

- doxygen Doxyfile

- A documentação será criada na pasta docs/html, abra o index.html no navegador.

# Tests

## Localização dos testes

- Todos os testes estão no diretório tests/.

- Cada arquivo testa uma classe ou funcionalidade específica.

## Como rodar os testes

- Ter o arquivo doctest.h incluído (já presente em include/).
- make test

# O comando acima irá:

- Compilar todos os arquivos de teste em tests/;

- Linkar com os arquivos fonte de src/;

- Criar os binários em bin/;

- Executar todos os testes e mostrar os resultados.
