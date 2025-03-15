// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Solución al problema de los ficheros mediante programación dinámica

/*
  Utilizamos la siguiente recurrencia:

  maxFicheros(i, j) ≡ número máximo de ficheros que podemos mover a un disco de
  capacidad j , teniendo en cuenta solamente los ficheros [1..i].

  maxFicheros(0, j) = 0
  maxFicheros(i, j) = maxFicheros(i − 1, j) si s[i] > j
  maxFicheros(i, j) = máx(maxFicheros(i − 1, j),
                          1 + maxFicheros(i − 1, j − s[i])) si s[i] <= j

*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T> using Matriz = vector<vector<T>>;

template <typename T>
Matriz<T> nueva_matriz(int num_filas, int num_columnas, T valor) {
  return vector<vector<T>>(num_filas, vector<T>(num_columnas, valor));
}

vector<bool> ficheros(const vector<int> &s, int d) {
  int n = s.size();
  Matriz<int> maxFicheros = nueva_matriz(n + 1, d + 1, 0);

  // Ya hemos inicializado maxFicheros[0][j] a 0.

  // Rellenamos las filas restantes [1..n]
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= d; j++) {
      if (s[i - 1] > j) {
        maxFicheros[i][j] = maxFicheros[i - 1][j];
      } else {
        maxFicheros[i][j] =
            max(maxFicheros[i - 1][j], 1 + maxFicheros[i - 1][j - s[i - 1]]);
      }
    }
  }

  // Reconstruimos solución. result[i] = true si y solo si
  // se incluye el fichero i-ésimo en el disco.

  vector<bool> result(n, false);
  int i = n, j = d;
  while (i > 0) {
    if (s[i - 1] > j) {
      result[i - 1] = false;
      i--;
    } else {
      if (maxFicheros[i][j] == 1 + maxFicheros[i - 1][j - s[i - 1]]) {
        result[i - 1] = true;
        j -= s[i - 1];
        i--;
      } else {
        result[i - 1] = false;
        i--;
      }
    }
  }

  return result;
}

int main() {
  vector<int> fichs = {30, 10, 20, 5, 15};

  for (bool b : ficheros(fichs, 40))
    cout << b << ' ';

  cout << '\n';
  return 0;
}