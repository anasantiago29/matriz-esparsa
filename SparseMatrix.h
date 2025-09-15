// Aluna: Ana Beatriz Martins Santiago
// Matrícula: 570493
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "Node.h"
#include <iostream>
class SparseMatrix{
private:
    Node* m_head; // ponteiro para o sentinela
    int m_linhas; // quantidade de linhas
    int m_colunas; // quantidade de colunas
    
    // Função que cria os nós sentinelas. 
    // Cria uma lista simplesmente encadeada circular para cada linha e
    // uma lista simplesmente encadeada circular para cada coluna
    void read(){
        Node *aux = m_head;
        for(int i=1;i<=m_linhas;i++){ // criar os sentinelas para as linhas
            Node *novo = new Node(0, i, 0, nullptr, nullptr);
            aux->abaixo = novo;
            novo->direita = novo;
            aux = aux->abaixo;
        }
        aux->abaixo = m_head; // último sentinela aponta para m_head

        aux = m_head; 
        for(int i=1;i<=m_colunas;i++){ // criar os sentinelas para as colunas
            Node *novo = new Node(0, 0, i, nullptr, nullptr);
            aux->direita = novo;
            novo->abaixo = novo;
            aux = aux->direita;
        }
        aux->direita = m_head; // último sentinela aponta para m_head
    }

    // Função que recebe dois inteiros, i e j
    // e retorna uma referencia para o valor double 
    // da linha i, coluna j da matriz
    double& getRef(const int& i, const int& j){
        if(i<=0 || j<=0 || i>m_linhas || j>m_colunas) throw std::invalid_argument("Argumento Invalido");
        Node *aux1 = m_head;
        Node *aux2;
        for(int m=0;m<i;m++) aux1 = aux1->abaixo; // navegar até a i
        aux2 = aux1->direita;
        while(aux2->col != j) { // navegar até j
            aux2 = aux2->direita;
            if(aux2 == aux1) return aux1->valor; // se não encontrar valor em j
        }
        return aux2->valor;
    }

    // Função que recebe uma double value e dois inteiros m e n,
    // e atualiza o valor na celula (m, n) para value.
    void set(const double& value, const int& m, const int& n){
        double& novo = getRef(m, n); 
        novo = value;
    }
public:
    // Construtor default
    // Constroi uma matriz esparsa vazia com 
    // apenas um nó sentinela apontando para si
    SparseMatrix(){
        m_linhas = 0;
        m_colunas = 0;
        m_head = new Node(0, 0, 0, m_head, m_head);
    }

    // Construtor que recebe dois inteiros, m e n e
    // constroi uma matriz esparsa com m linhas e n colunas
    SparseMatrix(const int& m, const int& n){
        if(m>0 && n>0){
            m_linhas = m;
            m_colunas = n;
            m_head = new Node(0, 0, 0, nullptr, nullptr);
            read();
        } else {
            throw std::invalid_argument("Argumento Invalido");
        }
    }
    
    // Construtor de copia: recebe uma matriz esparsa e
    // cria uma cópia
    SparseMatrix(const SparseMatrix& a) : SparseMatrix(){
        m_linhas = a.m_linhas;
        m_colunas = a.m_colunas;
        m_head = new Node(0, 0, 0, nullptr, nullptr);
        read();
        for(int i=1;i<=m_linhas;i++){
            for(int j=1;j<=m_colunas;j++){
                insert(a.get(i, j), i, j);
            }
        }
    }
    
    // Destrutor: libera a memória alocada dinamicamente.
    ~SparseMatrix(){
        Node* linha = m_head;
        Node* atual = linha->direita;
        for(int i=0;i<m_linhas;i++){
            while(atual != linha){ 
                Node* aux = atual;
                atual = atual->direita;
                delete aux; // deletar os nós da linha
            }
            if(i==m_linhas-1){ // se for a última iteração
                delete linha; // deleta o último nó
            } else {
                Node* aux = linha;
                linha = linha->abaixo;
                atual = linha->direita;
                delete aux; // deleta o sentinela da linha i
            }   
        }   
    }

    // Função que retorna true se e somente se a matriz está vazia,
    // retorna false caso contrário.
    bool empty() const{
        Node* atual = m_head->abaixo;
        Node* linha = m_head->abaixo;
        while(atual->direita == linha) {
            linha = linha->abaixo;
            atual = linha;
            if(atual == m_head) return true;
        }
        return false;
    }

    // Função que remove os elementos da matriz.
    // Obs.: mantém o número de linhas e colunas.
    void clear(){
        if(!empty()){
            Node* linha = m_head->abaixo;
            Node* atual = linha->direita;
            while(linha != m_head){
                while(atual != linha){
                    Node* aux = atual;
                    atual = atual->direita;
                    delete aux;
                }
                linha->direita = linha;
                linha = linha->abaixo;
                atual = linha->direita;
            }  
        }
    }
    
    // Função que recebe dois inteiros i e j, e
    // retorna uma referência constante para o valor double na linha i, coluna j da matriz
    const double& get(const int& i, const int& j) const{ 
        if(i<=0 || j<=0 || i>m_linhas || j>m_colunas) throw std::invalid_argument("Argumento Invalido"); 
        Node *aux1 = m_head; 
        Node *aux2; 
        for(int m=0;m<i;m++) aux1 = aux1->abaixo; 
        aux2 = aux1->direita; 
        while(aux2->col != j) {
            aux2 = aux2->direita; 
            if(aux2 == aux1) return aux2->valor; 
        }
        return aux2->valor; 
    }
    
    // Função que retorna o número de linhas da matriz
    const int getLinhas() const{
        return m_linhas;
    }
    
    // Função que retorna o número de colunas da matriz
    const int getCol() const{
        return m_colunas;
    }
    
    // Função que recebe um double value e dois inteiros m e n e
    // insere value na linha m, coluna n da matriz se e somente se
    // value, m e n forem válidos. Lança uma exceção caso contrário.
    void insert(const double& value, const int& m, const int& n){ 
        if(m<=0 || n<=0 || m>m_linhas || n>m_colunas) throw std::invalid_argument("Argumento Invalido");
        if(value == 0) { 
            if(get(m, n) != 0){ // se houver um valor na celula (i, j) 
                Node *aux1 = m_head;
                Node *aux2;
                for(int i=0;i<m;i++) aux1 = aux1->abaixo; 
                while(aux1->direita->col != n) aux1 = aux1->direita; 
                aux2 = aux1->direita;
                aux1->direita = aux2->direita;
                delete aux2; // deleta a celula
            }
            return; 
        }
        if(get(m, n) != 0) { // se houver um valor na celula (i, j) 
            set(value, m, n); // atualiza o valor da celula 
            return;
        }
        Node *linhaAtual = m_head;
        Node *colAtual = m_head;
        Node *auxLinha, *auxCol;
        for(int i=0;i<m;i++) linhaAtual = linhaAtual->abaixo; 
        for(int i=0;i<n;i++) colAtual = colAtual->direita; 
        auxLinha = linhaAtual;
        auxCol = colAtual;
        if(linhaAtual->direita != linhaAtual){ // se houver uma celula na linha
            while(auxLinha->direita->col < n && auxLinha->direita != linhaAtual){
                auxLinha = auxLinha->direita; // navega ate a celula que vem antes da nova celula (i, j) na mesma linha
            }
        }
        if(colAtual->abaixo != colAtual){ // se houver uma celula na coluna
            while(auxCol->abaixo->linha < m && auxCol->abaixo != colAtual){
                auxCol = auxCol->abaixo; // navega ate a celula que vem antes da nova celula (i, j) na mesma coluna
            }
        }
        Node *novo = new Node(value, m, n, auxCol->abaixo, auxLinha->direita);
        auxLinha->direita = novo;
        auxCol->abaixo = novo;
    }
    
    
    // Imprime os valores da matriz no terminal
    void print() const{
        Node *aux = m_head->abaixo;
        for(int i=0;i<m_linhas;i++){
            if(aux->direita == aux){ // Se não houver nós à direita
                for(int j=0;j<m_colunas;j++){
                    std::cout<<std::setw(10)<<std::setfill(' ')<<"0";
                }
            } else {
                Node *temp = aux->direita;
                for(int j=1;j<=m_colunas;j++){
                    if(temp->col == j){
                        std::cout<<std::setw(10)<<std::setfill(' ')<<temp->valor;
                        temp = temp->direita;
                    } else std::cout<<std::setw(10)<<std::setfill(' ')<<"0";
                }
            }
            std::cout<<std::endl;
            aux = aux->abaixo;
        }
    }
    
    // Sobrecarga do operador =
    SparseMatrix& operator=(const SparseMatrix& a){
        Node* linha = m_head;
        Node* atual = linha->direita;
        for(int i=0;i<m_linhas;i++){ // limpar a matriz atual antes de copiar os dados de 'a'
            while(atual != linha){
                Node* aux = atual;
                atual = atual->direita;
                delete aux;
            }
            if(i==m_linhas-1){
                delete linha;
            } else {
                Node* aux = linha;
                linha = linha->abaixo;
                atual = linha->direita;
                delete aux;
            }   
        }
        m_linhas = a.m_linhas;
        m_colunas = a.m_colunas;
        m_head = new Node(0, 0, 0, nullptr, nullptr);
        read();
        for(int i=1;i<=m_linhas;i++){
            for(int j=1;j<=m_colunas;j++){
                insert(a.get(i, j), i, j);
            }
        }
        return *this;
    }
};
#endif