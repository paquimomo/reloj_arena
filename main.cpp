#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void lectura(int**& arr, int& f, int& c) {
    string archivo = "matriz.txt";
    ifstream file(archivo);

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    vector<vector<int>> temp_matrix;
    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        vector<int> row;
        int num;
        while (ss >> num) {
            row.push_back(num);
        }
        if (!row.empty()) {
            temp_matrix.push_back(row);
        }
    }

    file.close();

    f = temp_matrix.size();
    if (f > 0) {
        c = temp_matrix[0].size();
        for (const auto& row : temp_matrix) {
            if (row.size() != c) {
                cout << "Error: Las filas no tienen el mismo número de columnas" << endl;
                return;
            }
        }
    } else {
        cout << "Error: El archivo está vacío o las filas no tienen columnas válidas" << endl;
        return;
    }

    arr = new int*[f];
    for (int i = 0; i < f; ++i) {
        arr[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            arr[i][j] = temp_matrix[i][j];
        }
    }
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
    if (f < 3 || c < 3) {
        cout << "No existe ningun reloj de arena" << endl;
        cin >> exit;
        return 0;
    }

    int relojes_totales = (f - 2) * (c - 2);
    reloj_arena suma[relojes_totales];
    int counter = 0;

    if (arr != nullptr) 
    {
        for (int i = 1; i < f - 1; i++) 
        {
            for (int j = 1; j < c - 1; j++) 
            {
                suma[counter].numero = arr[i][j] + arr[i - 1][j] + arr[i + 1][j] +
                                        arr[i - 1][j - 1] + arr[i - 1][j + 1] +
                                        arr[i + 1][j - 1] + arr[i + 1][j + 1];
                counter++;
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
        if (suma[i].numero > max)
        {
            max = suma[i].numero;
        }
    }

    cout << "La suma mínima es: " << min << endl;
    cout << "La suma máxima es: " << max << endl;

    cout << "Presione cualquier tecla para salir: ";
    cin >> exit;

    return 0;
}
