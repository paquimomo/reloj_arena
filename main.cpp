#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void lectura(int**& arr, int& f, int& c) {
    string archivo = "matriz.txt";
    ifstream file(archivo);

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string line;
    int i = 0;

    while (getline(file, line)) {
        istringstream ss(line);
        if (i == 0) {
            ss >> f;
            if (ss.fail() || f <= 0) {
                cout << "Error leyendo la cantidad de filas" << endl;
                return;
            }
        } else if (i == 1) {
            ss >> c;
            if (ss.fail() || c <= 0) {
                cout << "Error leyendo la cantidad de columnas" << endl;
                return;
            }

            arr = new int*[f];
            for (int j = 0; j < f; j++) {
                arr[j] = new int[c];
            }
        } else {
            int k = 0;
            while (ss >> arr[i - 2][k]) {
                k++;
                if (k >= c) break; // Ensure no overflow on columns
            }
            if (k != c) {
                cout << "Error: la fila " << (i - 2) << " no tiene el número correcto de columnas" << endl;
                return;
            }
        }
        i++;
    }

    if (i - 2 != f) {
        cout << "Error: el número de filas no coincide con el especificado" << endl;
    }

    file.close();
}

struct reloj_arena
{
    int numero;
};

int main(void) {
    char exit;
    int** arr = nullptr;
    int f = 0, c = 0;
    lectura(arr, f, c);
    if (f <= 2 && c <= 2)
    {
        cout << "No existe ningun reloj de arena" << endl;
        cin >> exit;
        return 0;
    }
    int relojes_totales = (f-2)*(c-2);
    reloj_arena suma[relojes_totales];
    int counter = 0;

    if (arr != nullptr) 
    {
        for (int i = 0; i < f; i++) 
        {
            for (int j = 0; j < c; j++) 
            {
                if (i > 0 && j > 0 && i < f - 1 && j < f - 1)
                {
                    suma[counter].numero = arr[i][j] + arr[i-1][j] + arr[i+1][j] + arr[i-1][j-1] + arr[i-1][j+1] + arr[i+1][j-1] + arr[i+1][j+1];
                    counter++;
                }
            }
        }

        for (int i = 0; i < f; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    int min = suma[0].numero;
    int max = suma[0].numero;

    for (int i = 0; i < relojes_totales; ++i)
    {
        if (suma[i].numero < min)
        {
            min = suma[i].numero;
        }
        else if (suma[i].numero > max)
        {
            max = suma[i].numero;
        }
    }

    cout << "la suma minima es: " << min << endl;
    cout << "la suma maxima es: " << max << endl;


    cout << "presione cualquier tecla para salir: ";
    cin >> exit;

    return 0;
}
