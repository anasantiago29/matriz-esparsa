# Matriz Esparsa
## Status: Em construção :hammer:

### :books: Contexto 
Projeto acadêmico feito para a disciplina de Estrutura de Dados.

### :pencil2: Introdução
Matrizes esparsas são por definição matrizes em que a maioria de suas posições são preenchidas por 0. Por essa razão, elas possuem grande potencial em economia de memória,
uma vez que só será necessário armazenar os valores diferentes de zero. Dado isso, essas matrizes são amplamente utilizadas em cenários e contextos mais especializados, 
como por exemplo, na área de aprendizagem de máquinas e de estatísticas. Visto essa importância, foi implementado o Tipo Abstrato de Dado (TAD) SparseMatrix utilizando listas encadeadas em C++.
### :round_pushpin: SparseMatrix
O TAD em questão foi implementado utilizando-se dos conceitos de Programação Orientada a Objetos (POO), do qual foi criada a classe SparseMatrix que utiliza (importa) o struct Node e possui os seguintes atributos privados: um ponteiro para Node nomeado m_head, um inteiro para a quantidade de linhas entitulado m_linhas e um inteiro para a quantidade de colunas (m_colunas).
Sobre o struct Node: cada Node é uma célula (nó) da matriz, possuindo um valor double, um ponteiro para o Node à direita na matriz (próxima coluna), um ponteiro para o Node abaixo na matriz (próxima linha) e dois inteiros para indicar a linha e a coluna em que o Node se encontra na matriz. Além disso, SparseMatrix utiliza-se de listas simplesmente encadeadas circulares, com nós sentinelas no começo de cada linha e coluna. Dessa forma, m_head é um ponteiro para o primeiro sentinela da matriz, que foi decidido ter sua posição em (0, 0).
