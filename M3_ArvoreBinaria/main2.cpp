// Cada grupo deve escolher e implementar todos os algoritmos de ordenaçðo visto em sala: inserçðo direta, shellsort, bolha (bubblesort), 
//quicksort, seleçðo direta e mergesort. 
// O seu programa deverá preparar um conjunto de M vetores de tamanho N de números inteiros que deverðo ser submetidos X vezes aos
//algoritmos implementados (com X, M e N solicitados ao usuário). 
// Desses vetores, um deve ser o melhor caso (valores já ordenados), outro deve ser o pior caso (valores na ordem inversa) e os demais devem ser
//gerados aleatoriamente. 
// Solicite ao usuário a quantidade M de vetores e o tamanho N de cada um deles.
// Seu algoritmo também deverá solicitar ao usuário quantas vezes ele deseja executar (X) cada um dos
//métodos. 
// Feito isso, ele irá chamar cada um dos métodos, para cada um dos vetores, todas as vezes solicitadas. 
// Em cada uma delas, você deve pegar o horário do computador antes da chamada e imediatamente na sua volta. 
// Ao final, você deve apresentar a diferença entre a hora inicial e a final para mostrar quanto tempo levou a execuçðo. 
// Além disso, quanto tudo terminar, para cada método você deverá mostrar: qual vetor demorou mais, qual demorou menos e a média dos casos. 

// Trabalho feito por: Douglas Scheffer Lopes e Edson Luiz Sartori Junior - Junho 2024

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric> // Para a função accumulate

#include "algoritmos.cpp"

using namespace std;
using namespace std::chrono;

// Funções de ordenação aqui (como insercaoDireta, shellSort, bolha, quickSort, selecaoDireta, mergeSort)

int main() {

    setlocale(LC_ALL, "Portuguese");

    int M, N, X;
    cout << "Digite a quantidade de vetores (M): ";
    cin >> M;
    cout << "Digite o tamanho de cada vetor (N): ";
    cin >> N;
    cout << "Digite a quantidade de execuções (X): ";
    cin >> X;

    vector<vector<int>> vetores(M, vector<int>(N));

    // Registro do horário de início
    auto inicio_programa = system_clock::now();
    time_t inicio_programa_time_t = system_clock::to_time_t(inicio_programa);
    cout << "\nHorário de início do programa: " << ctime(&inicio_programa_time_t);

    // Gerando vetores
    for (int i = 0; i < M; ++i) {
        if (i == 0) {
            // Melhor caso: vetor ordenado
            iota(vetores[i].begin(), vetores[i].end(), 1);
        } else if (i == 1) {
            // Pior caso: vetor em ordem inversa
            iota(vetores[i].rbegin(), vetores[i].rend(), 1);
        } else {
            // Casos aleatórios
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, N);
            generate(vetores[i].begin(), vetores[i].end(), [&]() { return dis(gen); });
        }
    }

    // Funções de ordenação para testar
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

                // Verificação opcional se necessário
                if (!is_sorted(v.begin(), v.end())) {
                    cout << "Erro: Vetor não está ordenado corretamente!\n";
                }
            }
        }

        // Calculando estatísticas
        double tempo_max = *max_element(tempos.begin(), tempos.end());
        double tempo_min = *min_element(tempos.begin(), tempos.end());
        double tempo_media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();

        cout << "Tempo máximo: " << tempo_max << " segundos\n";
        cout << "Tempo mínimo: " << tempo_min << " segundos\n";
        cout << "Tempo médio: " << tempo_media << " segundos\n";
    }

    // Registro do horário de término
    auto fim_programa = system_clock::now();
    time_t fim_programa_time_t = system_clock::to_time_t(fim_programa);
    cout << "\nHorário de término do programa: " << ctime(&fim_programa_time_t);

    // Calculando a diferença de tempo
    duration<double> duracao_programa = fim_programa - inicio_programa;
    cout << "Tempo total de execução do programa: " << duracao_programa.count() << " segundos\n";

    return 0;
}