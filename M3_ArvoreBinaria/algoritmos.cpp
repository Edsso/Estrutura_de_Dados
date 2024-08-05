// Cada grupo deve escolher e implementar todos os algoritmos de ordenação visto em sala: inserção direta, shellsort, bolha (bubblesort), 
//quicksort, seleção direta e mergesort. 
// O seu programa deverá preparar um conjunto de M vetores de tamanho N de números inteiros que deverão ser submetidos X vezes aos
//algoritmos implementados (com X, M e N solicitados ao usuário). 
// Desses vetores, um deve ser o melhor caso (valores já ordenados), outro deve ser o pior caso (valores na ordem inversa) e os demais devem ser
//gerados aleatoriamente. 
// Solicite ao usuário a quantidade M de vetores e o tamanho N de cada um deles.
// Seu algoritmo também deverá solicitar ao usuário quantas vezes ele deseja executar (X) cada um dos
//métodos. 
// Feito isso, ele irá chamar cada um dos métodos, para cada um dos vetores, todas as vezes solicitadas. 
// Em cada uma delas, você deve pegar o horário do computador antes da chamada e imediatamente na sua volta. 
// Ao final, você deve apresentar a diferença entre a hora inicial e a final para mostrar quanto tempo levou a execução. 
// Além disso, quanto tudo terminar, para cada método você deverá mostrar: qual vetor demorou mais, qual demorou menos e a média dos casos. 

// Trabalho feito por: Douglas Scheffer Lopes e Edson Luiz Sartori Junior - Julho 2024

#include <iostream>

using namespace std;

// Todos as funções foi implementado usando como base os slides do professor Carrard

// Função que faz a Insercao Direta
template <typename T>
void insercaoDireta(T vet[], int TAM) {
    for (int j = 1; j < TAM; ++j) {
        int chave = vet[j];
        int i = j - 1;
        while (i >= 0 && vet[i] > chave) {
            vet[i + 1] = vet[i];
            --i;
        }
        vet[i + 1] = chave;
    }
}

// Função que faz o Shell Sort
template <typename T>
void shellSort(T vet[], int TAM) {
    for (int np = TAM / 2; np > 0; np /= 2) {
        for (int i = np; i < TAM; ++i) {
            T chave = vet[i];
            int j = i;
            while (j >= np && vet[j - np] > chave) {
                vet[j] = vet[j - np];
                j -= np;
            }
            vet[j] = chave;
        }
    }
}

// Função que faz a Bolha (Bubble Sort)
template <typename T>
void bolha(T vet[], int TAM) {
    bool troca = true;
    int lim = TAM - 1;

    while (troca) {
        troca = false;
        for (int i = 0; i < lim; ++i) {
            if (vet[i] > vet[i + 1]) {
                T temp = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = temp;
                troca = true;
            }
        }
        --lim;
    }
}

// Função que faz o Quick Sort
template <typename T>
void quickSort(T vet[], int esq, int dir) {
    int i = esq;
    int j = dir;
    T x = vet[(i + j) / 2];

    do {
        while (x > vet[i]) {
            ++i;
        }
        while (x < vet[j]) {
            --j;
        }
        if (i <= j) {
            T aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            ++i;
            --j;
        }
    } while (i <= j);

    if (esq < j) {
        quickSort(vet, esq, j);
    }
    if (dir > i) {
        quickSort(vet, i, dir);
    }
}

// Função que faz a Seleção Direta
template <typename T>
void selecaoDireta(T vet[], int TAM) {
    for (int i = 0; i < TAM - 1; ++i) {
        int pos_menor = i;
        for (int j = i + 1; j < TAM; ++j) {
            if (vet[j] < vet[pos_menor]) {
                pos_menor = j;
            }
        }
        T temp = vet[i];
        vet[i] = vet[pos_menor];
        vet[pos_menor] = temp;
    }
}

// Função que Mescla para poder usar a Merge Sort
template <typename T>
void mesclar(T v[], int comeco, int meio, int fim) {
    int com1 = comeco;
    int com2 = meio + 1;
    int tam = fim - comeco + 1;
    T* vetAux = new T[tam];
    int comAux = 0;

    while (com1 <= meio && com2 <= fim) {
        if (v[com1] < v[com2]) {
            vetAux[comAux] = v[com1];
            com1++;
        } else {
            vetAux[comAux] = v[com2];
            com2++;
        }
        comAux++;
    }

    while (com1 <= meio) {
        vetAux[comAux] = v[com1];
        comAux++;
        com1++;
    }

    while (com2 <= fim) {
        vetAux[comAux] = v[com2];
        comAux++;
        com2++;
    }

    for (comAux = comeco; comAux <= fim; comAux++) {
        v[comAux] = vetAux[comAux - comeco];
    }

    delete[] vetAux;
}

// Função que faz a Merge Sort
template <typename T>
void mergeSort(T v[], int comeco, int fim) {
    if (comeco == fim) {
        return;
    }

    int meio = (comeco + fim) / 2;
    mergeSort(v, comeco, meio);
    mergeSort(v, meio + 1, fim);
    mesclar(v, comeco, meio, fim);
}