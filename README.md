# Matriz Esparsa
## Status: Em construção :hammer:

## :books: Contexto 
Projeto acadêmico feito para a disciplina de ***Estrutura de Dados***.

## :pencil2: Introdução
Matrizes esparsas são por definição matrizes em que a maioria de suas posições são preenchidas por 0. Por essa razão, elas possuem grande potencial em economia de memória,
uma vez que só será necessário armazenar os valores diferentes de zero. Dado isso, essas matrizes são amplamente utilizadas em cenários e contextos mais especializados, 
como por exemplo, na área de aprendizagem de máquinas e de estatísticas. Visto essa importância, foi implementado o ***Tipo Abstrato de Dado (TAD)*** SparseMatrix em C++.

## :round_pushpin: TAD SparseMatrix
A implementação utiliza os princípios de **Programação Orientada a Objetos (POO)** e uma estrutura de **listas encadeadas circulares** com nós sentinelas.

### Estrutura da Classe
A classe `SparseMatrix` gerencia a estrutura através dos seguintes atributos privados:
* `m_head`: Ponteiro para o nó inicial.
* `m_linhas`: Quantidade total de linhas da matriz.
* `m_colunas`: Quantidade total de colunas da matriz.

### Struct Node
Cada célula da matriz é representada por um `Node`, que armazena:
* **Valor**: Um dado do tipo `double`.
* **Ponteiros**: Referências para o próximo nó à direita (mesma linha) e para o nó abaixo (mesma coluna).
* **Posicionamento**: Inteiros que guardam as coordenadas exatas (linha e coluna) na matriz.

### Implementação com Nós Sentinelas
Cada linha e cada coluna possui um **nó sentinela** inicial, que não armazena dados, mas facilita a navegação e operações de inserção/remoção. 

O ponteiro `m_head` aponta para o sentinela inicial na posição (0,0). Abaixo, uma representação visual de uma matriz 2x2 vazia (apenas com a estrutura de sentinelas):

<div align="center">
  <img width="800" height="auto" alt="Estrutura de Sentinelas" src="https://github.com/user-attachments/assets/80bf7385-a5ff-4847-885d-d6f7c275d3d9" />
</div>

## :open_file_folder: Estrutura do Projeto
O projeto está dividido entre a implementação do **TAD SparseMatrix** e as funcionalidades auxiliares de manipulação contidas no arquivo principal (`main.cpp`).

### Classe SparseMatrix
* **Gerenciamento de Memória**: Inclui construtor padrão, de cópia e destrutor para liberar a memória alocada dinamicamente.
* **Principais Métodos**:
    * `insert`: Insere valores, trata atualizações de células preenchidas e remoções (quando o valor é zero).
    * `get`: Retorna o valor de uma célula específica de forma constante.
    * `clear`: Zera todos os elementos da matriz mantendo sua estrutura básica.
    * `read` (privado): Responsável por criar a estrutura inicial de nós sentinelas.

### Funções da Main (Interface e Operações)
Funções desenvolvidas fora da classe para facilitar a interação com o usuário através de um vetor de matrizes.

* **Operações Matemáticas**: 
    * `sum`: Realiza a soma de duas matrizes.
    * `multiply`: Realiza a multiplicação de duas matrizes.
* **Arquivos**: 
    * `readSparseMatrix`: Lê dados de arquivos `.txt` dentro de uma pasta específica para criar novas matrizes.
* **Validação**: 
    * `matrizValida`: Garante que os índices acessados pelo usuário no sistema de comandos sejam válidos.

## :rocket: Como Compilar e Executar

Este projeto utiliza um sistema de interação via terminal para manipular as matrizes esparsas por meio de um vetor gerenciado no arquivo principal.

### :clipboard: Pré-requisitos
Você precisará de um compilador C++ instalado (como o `g++`) para processar a interface principal.

### :hammer_and_pick: Compilação e execução
Para compilar o projeto, abra o terminal na pasta raiz e execute o comando abaixo:

```
g++ main.cpp -o main
```

Após a compilação, inicie o programa com o comando:

```
./main
```

### :page_facing_up: Preparação para Leitura de Arquivos
O programa possui uma funcionalidade específica para criar matrizes a partir de arquivos `.txt` externos. Para que o processo funcione corretamente, siga as instruções abaixo:

1. Deve existir uma pasta nomeada `matrizes` no diretório raiz do projeto.
2. Insira seus arquivos de matriz (como `m1.txt`, `mA.txt`) dentro desta pasta.
3. **Formatação do Arquivo**:
    * A primeira linha deve conter o número de linhas e o número de colunas, separados por espaço.
    * As linhas seguintes devem conter o índice da linha, o índice da coluna e o valor (`double`), todos separados por espaços.
4. No console do programa, utilize o comando `createWith file nome_do_arquivo`. 
    * **Importante**: Digite o nome do arquivo sem aspas, sem a extensão `.txt` e sem mencionar o nome da pasta.

### :bulb: Comandos de Ajuda e Documentação

Caso tenha dúvidas sobre a sintaxe de comandos como soma, multiplicação ou limpeza de matrizes durante a execução, utilize o utilitário interno:
* **`help`**: Imprime no terminal a lista completa de todos os comandos disponíveis e suas respectivas funções.

Para uma compreensão aprofundada sobre as decisões de projeto e sanar dúvidas ou curiosidades, o **[relatório técnico](./relatorio.pdf)** do projeto está disponível para consulta.

### :woman_technologist: Autora e contato

* **Ana Beatriz Martins Santiago**.
* **Estudante do curso de Ciência da Computação**, Universidade Federal do Ceará (UFC) — Campus Quixadá.
* **E-mail**: anabsantiago0@gmail.com.