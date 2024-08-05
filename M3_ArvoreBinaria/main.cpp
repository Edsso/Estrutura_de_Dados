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

// Trabalho feito por: Douglas Scheffer Lopes e Edson Luiz Sartori Junior - Julho 2024

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "algoritmos.cpp"

using namespace std;
using namespace std::chrono;

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

    vector<double> todos_tempos;
    vector<double> medias_metodos;

    double tempo_max_metodo = 0.0;
    double tempo_min_metodo = numeric_limits<double>::max();
    string metodo_max, metodo_min;

    for (size_t idx = 0; idx < metodos.size(); ++idx) {
        string metodo = metodos[idx];
        auto func = funcoes[idx];

        vector<double> tempos;

        // Registro do hor�rio de in�cio de cada m�todo
        auto inicio_metodo = system_clock::now();
        time_t inicio_metodo_time_t = system_clock::to_time_t(inicio_metodo);
        cout << "\nHor�rio de in�cio do m�todo " << metodo << ": " << ctime(&inicio_metodo_time_t);
        cout << "Executando " << metodo << "...\n";

        for (int i = 0; i < M; ++i) {
            for (int x = 0; x < X; ++x) {
                vector<int> v = vetores[i]; // Copia o vetor original para ser ordenado

                auto start = high_resolution_clock::now();
                func(v.data(), N);
                auto end = high_resolution_clock::now();

                duration<double> diff = end - start;
                tempos.push_back(diff.count());
                todos_tempos.push_back(diff.count());

                // Verifica��o opcional se necess�rio
                if (!is_sorted(v.begin(), v.end())) {
                    cout << "Erro: Vetor n�o est� ordenado corretamente!\n";
                }
            }
        }

        // Calculando estat�sticas para cada m�todo
        double tempo_max = *max_element(tempos.begin(), tempos.end());
        double tempo_min = *min_element(tempos.begin(), tempos.end());
        double tempo_media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
        medias_metodos.push_back(tempo_media);

        cout << "Tempo m�ximo: " << tempo_max << " segundos\n";
        cout << "Tempo m�nimo: " << tempo_min << " segundos\n";
        cout << "Tempo m�dio: " << tempo_media << " segundos\n";

        // Registro do hor�rio de t�rmino de cada m�todo
        auto fim_metodo = system_clock::now();
        time_t fim_metodo_time_t = system_clock::to_time_t(fim_metodo);
        cout << "Hor�rio de t�rmino do m�todo " << metodo << ": " << ctime(&fim_metodo_time_t);
        
        // Atualizando m�todo que demorou mais e menos
        if (tempo_media > tempo_max_metodo) {
            tempo_max_metodo = tempo_media;
            metodo_max = metodo;
        }
        if (tempo_media < tempo_min_metodo) {
            tempo_min_metodo = tempo_media;
            metodo_min = metodo;
        }
    }

    // Estat�sticas gerais
    double tempo_max_geral = *max_element(todos_tempos.begin(), todos_tempos.end());
    double tempo_min_geral = *min_element(todos_tempos.begin(), todos_tempos.end());
    double tempo_media_geral = accumulate(todos_tempos.begin(), todos_tempos.end(), 0.0) / todos_tempos.size();

    cout << "\nEstat�sticas gerais:\n";
    cout << "Tempo m�ximo geral: " << tempo_max_geral << " segundos\n";
    cout << "Tempo m�nimo geral: " << tempo_min_geral << " segundos\n";
    cout << "Tempo m�dio geral: " << tempo_media_geral << " segundos\n";

    // Mostrando m�todo que demorou mais, menos e a m�dia geral
    cout << "\nM�todo que demorou mais: " << metodo_max << " com tempo m�dio de " << tempo_max_metodo << " segundos\n";
    cout << "M�todo que demorou menos: " << metodo_min << " com tempo m�dio de " << tempo_min_metodo << " segundos\n";
    cout << "Tempo m�dio geral dos m�todos: " << tempo_media_geral << " segundos\n";

    // Registro do hor�rio de t�rmino
    auto fim_programa = system_clock::now();
    time_t fim_programa_time_t = system_clock::to_time_t(fim_programa);
    cout << "\nHor�rio de t�rmino do programa: " << ctime(&fim_programa_time_t);

    // Calculando a diferen�a de tempo
    duration<double> duracao_programa = fim_programa - inicio_programa;
    cout << "Tempo total de execu��o do programa: " << duracao_programa.count() << " segundos\n";

    return 0;
}
