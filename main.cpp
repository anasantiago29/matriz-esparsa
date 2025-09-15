// Aluna: Ana Beatriz Martins Santiago
// Matrícula: 570493
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "SparseMatrix.h"
using namespace std;

// Função que recebe como entrada uma matriz esparsa vazia e
// o nome de um arquivo de entrada.
// Ela lê o arquivo e monta a matriz correspondente
void readSparseMatrix(SparseMatrix& m, string file){
    fstream arq(file);
    if(arq.is_open()){ // verificar se o arquivo esta aberto
        int i, j;
        double v;
        arq>>i>>j;
        m = SparseMatrix(i, j);
        while(arq>>i>>j>>v){
            try{
                m.insert(v, i, j);
            } catch (invalid_argument e){
                cout<<e.what()<<endl;
            }
        }
    } else {
        throw invalid_argument("Arquivo invalido");
    }
}

// Funcao que recebe duas matrizes esparsas A e B como entrada e
// retorna uma matriz C que é a soma de A e B.
SparseMatrix sum(SparseMatrix& A, SparseMatrix& B){ 
    if(A.getLinhas() == B.getLinhas() && A.getCol() == B.getCol()){ 
        SparseMatrix C(A.getLinhas(), B.getCol()); 
        for(int i=1;i<=A.getLinhas();i++){ 
            for(int j=1;j<=B.getCol();j++){ 
                try {
                    C.insert(A.get(i, j)+B.get(i, j), i, j); 
                } catch (invalid_argument e){
                    cout<<e.what()<<endl;
                }
            }
        }
        return C; 
    } else {
        throw invalid_argument("As matrizes possuem dimensoes diferentes");
    }
}

// Funcao que recebe duas matrizes esparsas A e B como entrada e
// retorna uma matriz C que é a multiplicacao de A e B.
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B){
    if(A.getCol() == B.getLinhas()){
        double value = 0.0;
        SparseMatrix C(A.getLinhas(), B.getCol());
        for(int i=1;i<=C.getLinhas();i++){
            for(int j=1;j<=C.getCol();j++){
                value = 0.0;
                for(int k=1;k<=B.getLinhas();k++){
                    value = value + A.get(i, k)*B.get(k, j);
                    try {
                        C.insert(value, i, j);
                    } catch (invalid_argument e){
                        cout<<e.what()<<endl;
                    }
                }
            }
        }
        return C;
    } else {
        throw invalid_argument("Nao foi possivel multiplicar as matrizes por nao possuirem as dimensoes ideais");
    }
}

// Função que recebe um vector de SparseMatrix e um inteiro k,
// e retorna true se e somente se k é um índice válido do vector.
bool matrizValida(vector<SparseMatrix>& vet, const int& k){
    if(k>=vet.size() || k<0) return false;
    return true;
}
int main(){
    vector <SparseMatrix> vet;
    cout<<"Digite \"help\" para ver os comandos disponiveis"<<endl;
    while(true){
        cout<<">> ";
        string linha, parte;
        getline(cin, linha);
        istringstream iss(linha);
        iss>>parte;

        if(parte == "help"){
            cout<<"Comandos disponiveis: "<<endl;
            cout<<setw(40)<<setfill('.')<<left<<"create m n "<<right<<" cria uma matriz com m linhas e n colunas"<<endl

                <<setw(40)<<left<<"createWith sum i_matrix j_matrix "<<right<<" cria uma matriz a partir da soma de duas matrizes do vector"<<endl

                <<setw(40)<<left<<"createWith multiply i_matrix j_matrix "<<right<<" cria uma matriz a partir da multiplicacao de duas matrizes do vector"<<endl

                <<setw(40)<<left<<"createWith file nameFile"<<right<<" cria uma matriz a partir da matriz lida no arquivo .txt \"nameFile\" presente na pasta \"matrizes\""<<endl

                <<setw(40)<<left<<"createWith i_matrix"<<right<<" cria uma copia da matriz i do vector"<<endl

                <<setw(40)<<left<<"print"<<right<<" imprime no terminal todas as matrizes criadas"<<endl

                <<setw(40)<<left<<"print i_matrix"<<right<<" imprime no terminal a matriz i"<<endl

                <<setw(40)<<left<<"insert i_matrix value m n"<<right<<" insere value na matriz i, na linha m e coluna n"<<endl

                <<setw(40)<<left<<"get i_matrix m n"<<right<<" imprime no terminal o valor da linha m, coluna n da matriz i"<<endl

                <<setw(40)<<left<<"sum i_matrix j_matrix"<<right<<" imprime no terminal a soma de duas matrizes do vector"<<endl

                <<setw(40)<<left<<"multiply i_matrix j_matrix"<<right<<" imprime no terminal a multiplicacao de duas matrizes do vector"<<endl

                <<setw(40)<<left<<"clear i_matrix"<<right<<" limpa, zerando todas as posicoes, da matriz i do vector"<<endl

                <<setw(40)<<left<<"clearAll"<<right<<" limpa, zerando todas as posicoes, de todas as matrizes do vector"<<endl

                <<setw(40)<<left<<"delete i_matrix"<<right<<" deleta a matriz i do vector"<<endl

                <<setw(40)<<left<<"deleteAll"<<right<<" deleta todas as matrizes do vector"<<endl

                <<setw(40)<<left<<"help"<<right<<" imprime os comandos disponiveis no terminal"<<endl

                <<setw(40)<<left<<"exit"<<right<<" encerra o programa"<<endl;

        }
        // create m n
        else if(parte == "create"){
            int m=0, n=0;
            if(iss>>m>>n){
                try {
                    vet.push_back(SparseMatrix(m, n));
                    cout<<"$create "<<m<<" "<<n<<endl;
                } catch(invalid_argument e){
                    cout<<e.what()<<endl;
                }
            } else cout<<"Comando incorreto"<<endl;
        }
        // createWith (...)
        else if(parte == "createWith"){
            string p2;
            if(iss>>p2){
                // createWith sum i_matrix j_matrix
                if(p2 == "sum"){
                    int matA=0, matB=0;
                    if(iss>>matA>>matB){
                        try {
                            vet.push_back(sum(vet[matA], vet[matB]));
                            cout<<"$createWith sum "<<matA<<" "<<matB<<endl;
                        } catch (invalid_argument e) {
                            cout<<e.what()<<endl;
                        }
                    } else cout<<"Comando incompleto"<<endl;
                } 
                // createWith multiply i_matrix j_matrix
                else if(p2 == "multiply"){
                    int matA=0, matB=0;
                    if(iss>>matA>>matB){
                        try {
                            vet.push_back(multiply(vet[matA], vet[matB]));
                            cout<<"$createWith multiply "<<matA<<" "<<matB<<endl;
                        } catch (invalid_argument e) {
                            cout<<e.what()<<endl;
                        }
                    } else cout<<"Comando incompleto"<<endl;
                } 
                // createWith file nameFile
                else if(p2 == "file"){
                    string file = "matrizes/", parte;
                    if(iss>>parte){
                        vet.push_back(SparseMatrix());
                        file+=parte;
                        file+=".txt";
                        try{
                            readSparseMatrix(vet.back(), file);
                            cout<<"$createWith file "<<file<<endl;
                        } catch(invalid_argument e){
                            cout<<e.what()<<endl;
                            vet.pop_back();
                        }    
                    } else cout<<"Comando incompleto";
                } 
                // createWith i_matrix
                else {
                    try {
                        int mat=stoi(p2);
                        if(matrizValida(vet, mat)){ 
                            vet.push_back(SparseMatrix(vet[mat]));
                            cout<<"$createWith matriz "<<mat<<endl;
                        } else {
                            cout<<"Matriz invalida"<<endl;
                        }  
                    } catch(invalid_argument e){
                        cout<<"Argumento invalido"<<endl;
                    }
                }
            } else cout<<"Comando incompleto"<<endl;
        }
        // print (...)
        else if(parte == "print"){
            // print i_matrix
            int m;
            if(iss>>m){
                if(matrizValida(vet, m)){
                    cout<<"$print "<<m<<": "<<endl;
                    vet[m].print();
                } else {
                    cout<<"Matriz invalida"<<endl;
                    continue;
                }
            } 
            // print
            else {
                cout<<"$print"<<endl;
                if(vet.size() > 0){
                    for(int i=0;i<vet.size();i++){
                        cout<<"Matriz "<<i<<": "<<endl;
                        vet[i].print();
                    }
                } else cout<<"Nao ha matrizes criadas"<<endl;
            }
        }
        // insert i_matrix valor m n
        else if(parte == "insert") {
            int mat, m, n;
            double valor;
            if(iss>>mat>>valor>>m>>n){
                if(!matrizValida(vet, mat)){
                    cout<<"Matriz invalida"<<endl;
                    continue;
                }
                try{
                    vet[mat].insert(valor, m, n);
                    cout<<"$insert "<<mat<<" "<<valor<<" "<<m<<" "<<n<<endl;
                } catch (invalid_argument e){
                    cout<<e.what()<<endl;
                }
            } else cout<<"Comando incompleto"<<endl;
        }
        // get i_matrix m n
        else if(parte == "get"){
            int mat=0, m=0, n=0;
            if(iss>>mat>>m>>n){
                if(!matrizValida(vet, mat)){
                    cout<<"Matriz invalida"<<endl;
                    continue;
                }
                try {
                    cout<<"$get "<<mat<<" "<<m<<" "<<n<<endl;
                    cout<<vet[mat].get(m, n)<<endl;
                } catch (out_of_range e) {
                    cout<<e.what()<<endl;
                }
            } else cout<<"Comando incompleto"<<endl;
        }
        // clear i_matrix
        else if(parte == "clear"){
            int mat=0;
            if(iss>>mat){
                if(matrizValida(vet, mat)){
                    vet[mat].clear();
                    cout<<"$clear "<<mat<<endl;
                } else cout<<"Matriz invalida"<<endl; 
            } else cout<<"Comando incompleto"<<endl;
        }
        // clearAll
        else if(parte == "clearAll"){
            for(int i=0;i<vet.size();i++){
                vet[i].clear();
            }
            cout<<"$clearAll"<<endl;
        }
        // delete i_matrix
        else if(parte == "delete"){
            int mat=0;
            if(iss>>mat){
               if(matrizValida(vet, mat)) {
                vet.erase(vet.begin()+mat);
                cout<<"$delete "<<mat<<endl;
               } else cout<<"Matriz invalida"<<endl; 
            } else cout<<"Comando incompleto"<<endl;
        }
        // deleteAll
        else if(parte ==  "deleteAll"){
            vet.clear();
            cout<<"$deleteAll"<<endl;
        }
        // sum i_matrix j_matrix
        else if(parte == "sum"){
            int matA=0, matB=0;
            if(iss>>matA>>matB){
                if(matrizValida(vet, matA) && matrizValida(vet, matB)){
                    try {
                        SparseMatrix matC = sum(vet[matA], vet[matB]);
                        cout<<"$sum "<<matA<<" "<<matB<<endl;
                        matC.print();
                    } catch (invalid_argument e) {
                        cout<<e.what()<<endl;
                    }
                } else cout<<"Matriz invalida"<<endl;
            } else cout<<"Comando incompleto"<<endl;
        }
        // multiply i_matrix j_matrix
        else if(parte == "multiply"){
            int matA=0, matB=0;
            if(iss>>matA>>matB){
                if(matrizValida(vet, matA) && matrizValida(vet, matB)){
                    try {
                        SparseMatrix matC = multiply(vet[matA], vet[matB]);
                        cout<<"$multiply "<<matA<<" "<<matB<<endl;
                        matC.print();
                    } catch (invalid_argument e) {
                        cout<<e.what()<<endl;
                    }
                } else cout<<"Matriz invalida"<<endl;
            } else cout<<"Comando incompleto";
        }
        // exit
        else if(parte == "exit") return 0;
        else {
            cout<<"Comando invalido"<<endl;
        }
    }
}