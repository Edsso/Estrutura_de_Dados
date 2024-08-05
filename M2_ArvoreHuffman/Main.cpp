/*
-> Programa: Receber um texto qualquer, comprimir e descomprimir usando o Algoritmo de Huffman.
-> Alunos: Edson e Douglas
*/

#include <iostream>
#include <fstream>
#include "Suporte.hpp"

using namespace std;

template <typename T>
void construirArvoreHuffman(LUE <T> &lista, string texto){
    int tabelaFrequencias[256] = {0}; // Inicializa uma tabela de frequências

    // Contar a frequência de cada caractere no texto
    for(char c : texto){
        tabelaFrequencias[c]++;
    }

    // Inseri na LUE
    for(int i = 0; i < 256; i++){
        if(tabelaFrequencias[i] > 0){
            NoArvore <T> *raiz = new NoArvore <T>;
            raiz->infoA = char(i); // Define o caractere correspondente ao valor inteiro 'i' ao campo 'infoA'
            raiz->frequencia = tabelaFrequencias[i];
            inserirLUE(lista, raiz);
        }
    }

    // Agrupar Nós
    while(lista.comeco && lista.comeco->elo){ // Percorre a lista enquanto houver mais de um nó na lista
        NoArvore <T> *Index1 = lista.comeco->info;
        NoArvore <T> *Index2 = lista.comeco->elo->info;
        No <T> *aux1 = lista.comeco;
        No <T> *aux2 = lista.comeco->elo;

        // Verifica se há pelo menos dois elementos na lista
        if(lista.comeco->elo->elo){ 
            lista.comeco = lista.comeco->elo->elo;
        }else{
            lista.comeco = NULL;
        }

        // Deleta os dois menores elementos da lista
        delete aux1;
        delete aux2;

        // Cria um novo nó que combina os dois elementos menores
        NoArvore <T> *novaRaiz = new NoArvore <T>;
        novaRaiz->infoA = '\0'; 
        novaRaiz->frequencia = Index1->frequencia + Index2->frequencia;
        novaRaiz->esq = Index1;
        novaRaiz->dir = Index2;

        // Insere o novo nó de volta na lista
        inserirLUE(lista, novaRaiz);
    }
}

template <typename T>
bool comprimirTexto(NoArvore <T> *raiz, char c, string &caminho){
    if(raiz == NULL){ // Se a raiz for nula, retorna false
        caminho = ""; 
        return false;
    }
    if(raiz->infoA != '\0'){ // Se for uma folha (caractere), verifica se é o caractere desejado
        if(raiz->infoA == c)
            return true;
        return false;
    }
    if(comprimirTexto(raiz->esq, c, caminho)){ // busca à esquerda (0)
        caminho = "0" + caminho;
        return true;
    }
    if(comprimirTexto(raiz->dir, c, caminho)){ // busca à direita (1)
        caminho = "1" + caminho;
        return true;
    }
    return false;
}

template <typename T>
void MapearBits(LUE <T> lista, string &texto, string &codificado){ 
    NoArvore <T> *arvore = lista.comeco->info;
    codificado = "";
    // Itera pelos caracteres do texto original
    for (char c : texto){ 
        string binario = " ";
        comprimirTexto(arvore, c, binario);
        codificado += binario;
    }
}

template <typename T>
string descomprimirTexto(NoArvore <T> *raiz, const string &textoComprimido){
    NoArvore <T> *arvore = raiz;
    string textoDescomprimido;
    // Itera pelos bits do texto codificado
    for(char bit : textoComprimido){ 
        if(bit == '0'){
            arvore = arvore->esq; 
        }else if(bit == '1'){
            arvore = arvore->dir;
        }
        
        if(arvore->esq == NULL && arvore->dir == NULL){
            textoDescomprimido += arvore->infoA; 
            arvore = raiz; // Reinicia a busca na raiz
        }
    }
    return textoDescomprimido;
}

template <typename T>
void desenhaArvoreHuffman(NoArvore<T>* raiz, string str = "") {
    if (raiz == nullptr) {
        return;
    }

    // Se o nó atual não é um nó interno, imprime seu caractere e frequência
    if (!raiz->esq && !raiz->dir) {
        cout << raiz->infoA << ": " << str << "\n";
    }

    // Percorre a árvore esquerda e direita
    desenhaArvoreHuffman(raiz->esq, str + "0");
    desenhaArvoreHuffman(raiz->dir, str + "1");
}

int main(){

    LUE <char> lista;
    inicializarLUE(lista);

    int Op;
    string texto;

    do{
        system("cls");

        cout << "\n+=============================+\n";
        cout << "\n\tMenu de Huffmann ";
        cout << "\n\n1. Inserir um texto: ";
        cout << "\n2. Ler um arquivo: ";
        cout << "\n3. Sair";
        cout << "\n\n+=============================+\n";

        cout << "Opcao: ";
        cin >> Op;
        
        switch(Op){

            case 1:{

                cout << "Digite o texto de entrada: ";
                cin.ignore();
                getline(cin, texto);

                construirArvoreHuffman(lista, texto);

                string codificado;
                MapearBits(lista, texto, codificado);

                cout << "\nSequencia de bits: ";
                cout << "\n" << codificado << endl;

                string textoDescomprimido = descomprimirTexto(lista.comeco->info, codificado);
                cout << "\nTexto descomprimido: \n" << textoDescomprimido << endl;

                // Desenha a Arvore de Huffman dando para visualizar cada folha e sua altura
                cout << "\nArvore de Huffmann: " << endl;
                desenhaArvoreHuffman(lista.comeco->info);

                texto = ""; // Esvazia a string

                cout << "\nPrecione Enter para continuar..." << endl;
                cin.get();

                break;
            }
            case 2:{
                string name;
                string linha;
                fstream arquivo;
        
                cout << "Por favor digite o nome do seu arquivo: ";
                cin.ignore();
                getline(cin, name);

                arquivo.open(name, fstream :: in | fstream :: app);

                if(arquivo.is_open()){
                    while(getline(arquivo, linha)){
                    texto += linha;
                    }
                }

                cout << "\nTexto de entrada: \n";
                cout << texto << endl;

                construirArvoreHuffman(lista, texto);

                string codificado;
                MapearBits(lista, texto, codificado);

                cout << "\nSequencia de bits: ";
                cout << "\n" << codificado << endl;

                string textoDescomprimido = descomprimirTexto(lista.comeco->info, codificado);
                cout << "\nTexto descomprimido: \n" << textoDescomprimido;

                cout << "\nArvore de Huffmann: " << endl;
                desenhaArvoreHuffman(lista.comeco->info);

                texto = ""; // Esvazia a string

                cout << "\nPrecione Enter para continuar..." << endl;
                cin.get();

                break;
            }
            case 3:{
                cout << "Saindo";
                liberarLUE(lista);
                liberarArvore(lista.comeco->info);

                break;
            }
            default:{
                cout << "Opcao invalida!";
                cout << "\nPrecione Enter para continuar..." << endl;
                cin.ignore();
                cin.get();
                
            }
        }

    }while(Op != 3);

    return 0;
}