// -------------------------------------------------------
// Problema de los ficheros mediante programación dinámica
// -------------------------------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas


#include <iostream>
#include <vector>
#include "../Tema5/matriz.h"

using namespace std;

vector<bool> ficheros(const vector<int> &s, int d) {
  int n = s.size();
  matriz<int> tabla = crear_matriz(n + 1, d + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= d; j++) {
      if (s[i-1] > j) {
	tabla[i][j] = tabla[i-1][j];
      } else {
	tabla[i][j] = max(tabla[i-1][j], 1 + tabla[i-1][j - s[i-1]]);
      }
    }
  }

  vector<bool> seleccionados(n, false);
  int i = n, j = d;
  while (i > 0 && j > 0) {
    if (tabla[i][j] == tabla[i-1][j]) {
      i--;
    } else {
      seleccionados[i-1] = true;
      j -= s[i-1]; i--;
    }
  }

  return seleccionados;
}

void imprimir_vector(const vector<bool> &v) {
  if (v.empty()) cout << '\n';
  cout << boolalpha << v[0];
  for (int i = 1; i < v.size(); i++) {
    cout << ' ' << boolalpha << v[i];
  }
  cout << '\n';
}

int main() {
  imprimir_vector(ficheros({10, 3, 15, 3, 5}, 20));
  imprimir_vector(ficheros({10, 3, 15, 3, 3}, 20));
  return 0;
}
