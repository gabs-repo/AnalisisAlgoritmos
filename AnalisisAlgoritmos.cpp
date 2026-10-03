#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>

using namespace std;
using namespace chrono;


// BB es Búsqueda Binaria
int BB(const vector<int>& arreglo, int objetivo) {
    int izquierda = 0;
    int derecha = arreglo.size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (arreglo[medio] == objetivo) {
            return medio;
        }

        if (arreglo[medio] < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1;
}


// MS es Merge Sort
void merge(vector<int>& arreglo,
           vector<int>& arreglo_aux,
           int izquierda,
           int medio,
           int derecha) {

    int i = izquierda;
    int j = medio + 1;
    int k = izquierda;

    while (i <= medio && j <= derecha) {

        if (arreglo[i] <= arreglo[j]) {
            arreglo_aux[k] = arreglo[i];
            i++;
        } else {
            arreglo_aux[k] = arreglo[j];
            j++;
        }

        k++;
    }

    while (i <= medio) {
        arreglo_aux[k] = arreglo[i];
        i++;
        k++;
    }

    while (j <= derecha) {
        arreglo_aux[k] = arreglo[j];
        j++;
        k++;
    }

    for (int x = izquierda; x <= derecha; x++) {
        arreglo[x] = arreglo_aux[x];
    }
}


void mergeSortRecursivo(vector<int>& arreglo, vector<int>& arreglo_aux, int izquierda, int derecha) {

    if (izquierda >= derecha) {
        return;
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    mergeSortRecursivo(arreglo, arreglo_aux, izquierda, medio);
    mergeSortRecursivo(arreglo, arreglo_aux, medio + 1, derecha);

    merge(arreglo, arreglo_aux, izquierda, medio, derecha);
}


void mergeSort(vector<int>& arreglo) {

    if (arreglo.empty()) {
        return;
    }

    vector<int> arreglo_aux(arreglo.size());

    mergeSortRecursivo(
        arreglo, arreglo_aux, 0, arreglo.size() - 1
    );
}

int main() {

    // diferentes tamaños de arreglos
    vector<int> tamanos_arreglos = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1000000};

    // números aleatorios
    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> distribucion(1,10000000);

    ofstream archivo("resultados.csv");

    archivo
        << "Tamano de entrada (n),"
        << "Busqueda Binaria Experimental (ns),"
        << "MergeSort Experimental (ns),"
        << "Busqueda Binaria Teorico (log2_n),"
        << "MergeSort Teorico(n_log2_n)"
        << endl;


    cout << "Ejecutando benchmarks..." << endl;
    cout << endl;


    for (int n : tamanos_arreglos) {

        // arreglo random
        vector<int> numeros(n);

        for (int i = 0; i < n; i++) {
            numeros[i] = distribucion(generador);
        }

        // benchmark Búsqueda Binaria (BB requiere numeros ordenados)
        vector<int> numeros_ordenados = numeros;

        sort(
            numeros_ordenados.begin(),
            numeros_ordenados.end()
        );

        // Búsqueda Binaria ocurre demasiado rapido por eso tantas
        const int ejecuciones_BB = 50000;

        uniform_int_distribution<int> indice_random(0,n - 1);

        // se obtiene numeros_buscados antes de medir timing
        vector<int> numeros_buscados(ejecuciones_BB);

        for (int i = 0; i < ejecuciones_BB; i++) {

            int indice = indice_random(generador);

            numeros_buscados[i] = numeros_ordenados[indice];
        }


        long long indices_acumulados = 0;


        auto inicio_BB =
            high_resolution_clock::now();


        for (int i = 0;
             i < ejecuciones_BB;
             i++) {

            indices_acumulados += BB(
                numeros_ordenados,
                numeros_buscados[i]
            );
        }


        auto fin_BB =
            high_resolution_clock::now();


        auto tiempoTotal_BB =
            duration_cast<nanoseconds>(
                fin_BB - inicio_BB
            ).count();


        double tiempoPromedio_BB =
            static_cast<double>(tiempoTotal_BB)
            / ejecuciones_BB;

        // benchmark MergeSort (más lento que BB por eso menos ejecuciones)
        const int ejecuciones_MS = 3;

        long long tiempoTotal_MS = 0;


        for (int ejecucion = 0;
             ejecucion < ejecuciones_MS;
             ejecucion++) {

            // se crea copia para que cada prueba inicie con los mismos numeros desordenados fuera de cronometro

            vector<int> copia = numeros;


            auto inicio_MS =
                high_resolution_clock::now();


            mergeSort(copia);


            auto fin_MS =
                high_resolution_clock::now();


            tiempoTotal_MS +=
                duration_cast<nanoseconds>(
                    fin_MS - inicio_MS
                ).count();
        }

        double tiempoPromedio_MS =
            static_cast<double>(tiempoTotal_MS)
            / ejecuciones_MS;


        // valores teóricos
        double logN = log2(n); // BB

        double nLogN = n * log2(n); // MS


        cout
            << "n = "
            << n
            << " | Búsqueda Binaria = "
            << tiempoPromedio_BB
            << " ns"
            << " | MergeSort = "
            << tiempoPromedio_MS
            << " ns"
            << endl;

        // guarda CSV
        archivo
            << n << ","
            << tiempoPromedio_BB << ","
            << tiempoPromedio_MS << ","
            << logN << ","
            << nLogN
            << endl;

        if (indices_acumulados == -1) {
            cout << "";
        }
    }

    archivo.close();

    cout << endl;
    cout << "Benchmark terminado." << endl;
    cout << "Se creó el archivo resultados.csv" << endl;

    return 0;
}