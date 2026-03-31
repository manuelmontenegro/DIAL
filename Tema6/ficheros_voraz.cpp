// ----------------------------------------------------
// Problema de los ficheros mediante un algoritmo voraz
// ----------------------------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas


#include <iostream>
#include <vector>

using namespace std;

// Suponemos que el vector s está ordenado de manera
// ascendente.
vector<bool> ficheros(const vector<int> &s, int d) {
  int n = s.size();
  vector<bool> seleccionados(n, false);

  int espacio_ocupado = 0;
  int i = 0;
  while (i < n && espacio_ocupado + s[i] <= d) {
    seleccionados[i] = true;
    espacio_ocupado += s[i];
    i++;
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
  imprimir_vector(ficheros({3, 3, 5, 10, 15}, 20));
  imprimir_vector(ficheros({3, 3, 3, 10, 15}, 20));
  return 0;
}

