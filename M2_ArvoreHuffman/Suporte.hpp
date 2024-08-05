#include <iostream>
using namespace std;

template <typename T>
struct NoArvore{
    T infoA;
    int frequencia;
    NoArvore *esq=NULL, *dir=NULL;
};

template <typename T>
struct No{
    NoArvore <T> *info;
    No *elo;
};

template <typename T>
struct LUE{
    No <T> *comeco;
    No <T> *fim;
};

//
// Inicializa a lista dada por parímetro
//
template <typename T>
void inicializarLUE(LUE <T> &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

//
// Mostra todo o conteúdo da lista na tela
//
template <typename T>
void mostrarLUE(LUE <T> lista){
    No <T> *aux = lista.comeco;

    while(aux != NULL){
        cout << aux->info->infoA << "(" << aux -> info -> frequencia << ")" << " ";
        aux = aux->elo;
    }
    if( lista.comeco == NULL ) cout << "<Vazio>";
}

template <typename T>
void mostrar_arvore(NoArvore  <T> *raiz, int tab ){
    cout << endl;
    for( int i=0; i<tab; i++ ) cout << " ";
    if( raiz == NULL ){
        cout << "*";
        return;
    }
    cout << raiz->infoA;
    mostrar_arvore( raiz->esq, tab+3 );
    mostrar_arvore( raiz->dir, tab+3 );
}

template <typename T>
void prefixado(NoArvore <T> *raiz){
    if( raiz == NULL ) return;
    cout << raiz->infoA << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

template <typename T>
void infixado(NoArvore <T> *raiz){
    if( raiz == NULL ) return;
    infixado(raiz->esq);
    cout << raiz->infoA << " ";
    infixado(raiz->dir);
}

template <typename T>
void posfixado(NoArvore <T> *raiz){
    if( raiz == NULL ) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->infoA << " ";
}

//
// Insere o valor na lista dada respeitando a ordem crescente
//
template <typename T>
bool inserirLUE(LUE <T> &lista, NoArvore <T> *valor){

    No <T> *novo;

    // Criar o novo no
    novo = new No<T>;
    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    // Lista vazia
    if( lista.comeco  == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserção no comeco
    if( valor->frequencia <= lista.comeco->info -> frequencia ){
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }

    // Inserção no final
    if( valor->frequencia >= lista.fim->info -> frequencia ){
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio
    No <T> *aux = lista.comeco;
    while( aux->info->frequencia < valor->frequencia && aux->elo->info->frequencia <= valor->frequencia )
        aux = aux->elo;

    novo->elo = aux->elo;
    aux->elo = novo;
    return true;
}


// Insere o valor na lista dada respeitando a ordem decrescente

template <typename T>
bool inserirLUE_D(LUE <T> &lista, T valor){

    No <T> *novo;

    // Criar o novo no
    novo = new No<T>;
    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    // Lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserção no comeco
    if( valor >= lista.comeco->info ){
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }

    // Inserção no final
    if( valor <= lista.fim->info ){
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio
    No <T> *aux = lista.comeco;
    while( aux->info > valor && aux->elo->info >= valor )
        aux = aux->elo;

    novo->elo = aux->elo;
    aux->elo = novo;
    return true;
}


// Insere o valor dado sempre no final da lista

template <typename T>
bool inserirFinalLUE(LUE <T> &lista, T valor){
    No <T> *novo;

    // Criar o novo no
    novo = new No<T>;
    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    // Lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    lista.fim->elo = novo;
    lista.fim = novo;
    return true;
}


// Pesquisar se o valor está na lista
// retornar o endereço do valor ou nulo se não estiver

template <typename T>
No <T> * pesquisarLUE(LUE <T> lista, T valor){
    No <T> *aux = lista.comeco;

    while( aux != NULL ){
        if( aux->info == valor ) return aux;
        aux = aux->elo;
    }
    return NULL;
}

// Retirar o valor da lista
// retornar verdadeiro ou false se não achar

template <typename T>
bool retirarLUE(LUE <T> &lista, T valor ){
    No <T> *aux = lista.comeco, *anterior=NULL;

    while( aux != NULL && aux->info != valor ){
        anterior = aux;
        aux = aux->elo;
    }
    if( aux == NULL ) return false;

    if( aux == lista.comeco ){ // Casos 1 e 2
        lista.comeco = lista.comeco->elo;
        if( aux == lista.fim ) lista.fim = NULL;
    } else { // Casos 3 e 4
        anterior->elo = aux->elo;
        if( aux == lista.fim ) lista.fim = anterior;
    }
    delete aux;
    return true;
}

// Retorna verdadeiro se a lista estiver vazia e falso caso contrário.

template <typename T>
bool listaVazia(LUE<T> lista) {
    return lista.comeco == NULL;
}

// Libera toda a memória alocada para a lista fornecida

template <typename T>
void liberarLUE(LUE <T> &lista){
    No <T> *aux = lista.comeco;
    No <T> *aux2;

    while( aux != NULL ){
        aux2 = aux->elo;
        delete aux;
        aux = aux2;
    }
}

// Libera toda a memória alocada para a arvore

template <typename T>
void liberarArvore(NoArvore <T> *raiz){
    if( raiz == NULL ) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    delete raiz;
}