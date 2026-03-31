// ----------------------------------------------------------
// Problema de la mochila real mediante programación dinámica
// ----------------------------------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;

vector<double> mochila_real(const vector<double> &peso, const vector<double> &valor, double capacidad) {
  int n = peso.size();
  vector<double> ids(n);
  iota(ids.begin(), ids.end(), 0);
  sort(ids.begin(), ids.end(), [&valor, &peso](int i, int j) { 
      return  valor[i] / peso[i] > valor[j] / peso[j]; 
  });

  vector<double> result(n, 0);
  double capacidad_restante = capacidad;
  int i = 0;
  while (i < n && capacidad_restante > 0) {
    int actual = ids[i];
    double fraccion = min(1.0, capacidad_restante / peso[actual]);
    result[actual] = fraccion;
    capacidad_restante -= fraccion * peso[actual];
    i++;
  }

  return result;
}


int main() {
  vector<double> result = mochila_real({10, 4, 20, 30}, {15, 10, 20, 15}, 19);
  copy(result.begin(), result.end(), ostream_iterator<double>(cout, " "));
}
