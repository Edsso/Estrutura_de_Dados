// Cada grupo deve escolher e implementar todos os algoritmos de ordena��o visto em sala: inser��o direta, shellsort, bolha (bubblesort), 
//quicksort, sele��o direta e mergesort. 
// O seu programa dever� preparar um conjunto de M vetores de tamanho N de n�meros inteiros que dever�o ser submetidos X vezes aos
//algoritmos implementados (com X, M e N solicitados ao usu�rio). 
// Desses vetores, um deve ser o melhor caso (valores j� ordenados), outro deve ser o pior caso (valores na ordem inversa) e os demais devem ser
//gerados aleatoriamente. 
// Solicite ao usu�rio a quantidade M de vetores e o tamanho N de cada um deles.
// Seu algoritmo tamb�m dever� solicitar ao usu�rio quantas vezes ele deseja executar (X) cada um dos
//m�todos. 
// Feito isso, ele ir� chamar cada um dos m�todos, para cada um dos vetores, todas as vezes solicitadas. 
// Em cada uma delas, voc� deve pegar o hor�rio do computador antes da chamada e imediatamente na sua volta. 
// Ao final, voc� deve apresentar a diferen�a entre a hora inicial e a final para mostrar quanto tempo levou a execu��o. 
// Al�m disso, quanto tudo terminar, para cada m�todo voc� dever� mostrar: qual vetor demorou mais, qual demorou menos e a m�dia dos casos. 

// Trabalho feito por: Douglas Scheffer Lopes e Edson Luiz Sartori Junior - Junho 2024

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric> // Para a fun��o accumulate

#include "algoritmos.cpp"

using namespace std;
using namespace std::chrono;

// Fun��es de ordena��o aqui (como insercaoDireta, shellSort, bolha, quickSort, selecaoDireta, mergeSort)

int main() {

    setlocale(LC_ALL, "Portuguese");

    int M, N, X;
    cout << "Digite a quantidade de vetores (M): ";
    cin >> M;
    cout << "Digite o tamanho de cada vetor (N): ";
    cin >> N;
    cout << "Digite a quantidade de execu��es (X): ";
    cin >> X;

    vector<vector<int>> vetores(M, vector<int>(N));

    // Registro do hor�rio de in�cio
    auto inicio_programa = system_clock::now();
    time_t inicio_programa_time_t = system_clock::to_time_t(inicio_programa);
    cout << "\nHor�rio de in�cio do programa: " << ctime(&inicio_programa_time_t);

    // Gerando vetores
    for (int i = 0; i < M; ++i) {
        if (i == 0) {
            // Melhor caso: vetor ordenado
            iota(vetores[i].begin(), vetores[i].end(), 1);
        } else if (i == 1) {
            // Pior caso: vetor em ordem inversa
            iota(vetores[i].rbegin(), vetores[i].rend(), 1);
        } else {
            // Casos aleat�rios
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, N);
            generate(vetores[i].begin(), vetores[i].end(), [&]() { return dis(gen); });
        }
    }

    // Fun��es de ordena��o para testar
    vector<string> metodos = {"Insercao Direta", "Shell Sort", "Bolha", "Quick Sort", "Selecao Direta", "Merge Sort"};
    vector<void(*)(int[], int)> funcoes = {insercaoDireta<int>, shellSort<int>, bolha<int>, 
                                           [](int arr[], int tam) { quickSort(arr, 0, tam - 1); }, 
                                           selecaoDireta<int>, 
                                           [](int arr[], int tam) { mergeSort(arr, 0, tam - 1); }};

    for (size_t idx = 0; idx < metodos.size(); ++idx) {
        string metodo = metodos[idx];
        auto func = funcoes[idx];

        vector<double> tempos;

        cout << "\nExecutando " << metodo << "...\n";
        for (int i = 0; i < M; ++i) {
            for (int x = 0; x < X; ++x) {
                vector<int> v = vetores[i]; // Copia o vetor original para ser ordenado

                auto start = high_resolution_clock::now();
                func(v.data(), N);
                auto end = high_resolution_clock::now();

                duration<double> diff = end - start;
                tempos.push_back(diff.count());

                // Verifica��o opcional se necess�rio
                if (!is_sorted(v.begin(), v.end())) {
                    cout << "Erro: Vetor n�o est� ordenado corretamente!\n";
                }
            }
        }

        // Calculando estat�sticas
        double tempo_max = *max_element(tempos.begin(), tempos.end());
        double tempo_min = *min_element(tempos.begin(), tempos.end());
        double tempo_media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();

        cout << "Tempo m�ximo: " << tempo_max << " segundos\n";
        cout << "Tempo m�nimo: " << tempo_min << " segundos\n";
        cout << "Tempo m�dio: " << tempo_media << " segundos\n";
    }

    // Registro do hor�rio de t�rmino
    auto fim_programa = system_clock::now();
    time_t fim_programa_time_t = system_clock::to_time_t(fim_programa);
    cout << "\nHor�rio de t�rmino do programa: " << ctime(&fim_programa_time_t);

    // Calculando a diferen�a de tempo
    duration<double> duracao_programa = fim_programa - inicio_programa;
    cout << "Tempo total de execu��o do programa: " << duracao_programa.count() << " segundos\n";

    return 0;
}