// Aluna: Ana Beatriz Martins Santiago
// Matrícula: 570493
#ifndef NODE_H
#define NODE_H

struct Node {
    double valor;
    int linha;
    int col;
    Node *abaixo;
    Node *direita;
    
    Node(double valor, int m, int n, Node* abaixo, Node* direita){
        this->valor = valor;
        linha = m;
        col = n;
        this->abaixo = abaixo;
        this->direita = direita;
    }
};
#endif