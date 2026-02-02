# Matriz Esparsa
## Status: Em construção :hammer:

### :books: Contexto 
Projeto acadêmico feito para a disciplina de Estrutura de Dados.

### :pencil2: Introdução
Matrizes esparsas são por definição matrizes em que a maioria de suas posições são preenchidas por 0. Por essa razão, elas possuem grande potencial em economia de memória,
uma vez que só será necessário armazenar os valores diferentes de zero. Dado isso, essas matrizes são amplamente utilizadas em cenários e contextos mais especializados, 
como por exemplo, na área de aprendizagem de máquinas e de estatísticas. Visto essa importância, foi implementado o Tipo Abstrato de Dado (TAD) SparseMatrix utilizando listas encadeadas em C++.
### :round_pushpin: SparseMatrix
* TAD implementado utilizando-se dos conceitos de Programação Orientada a Objetos (POO).
* Classe SparseMatrix utiliza (importa) o struct Node e possui os seguintes atributos privados:
  * Ponteiro para Node nomeado m_head,
  * inteiro para a quantidade de linhas entitulado m_linhas, e
  * inteiro para a quantidade de colunas (m_colunas).

:bulb: Cada Node é uma célula (nó) da matriz e possui:
* Um valor double,
* ponteiro para o Node à direita na matriz (próxima coluna),
* ponteiro para o Node abaixo na matriz (próxima linha), e
* dois inteiros para indicar a linha e a coluna em que o Node se encontra na matriz.

  A partir disso, SparseMatrix utiliza-se de listas simplesmente encadeadas circulares, com nós sentinelas no começo de cada linha e coluna. Dessa forma, m_head é um ponteiro para o primeiro sentinela da matriz com posição (0, 0).
