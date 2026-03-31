// --------------------------------------------
// Problema del cambio mediante algoritmo voraz
// --------------------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas


#include <iostream>
#include <vector>
#include <utility>
#include <iterator>

using namespace std;

pair<bool, vector<int>> cambio_monedas(const vector<int> &m, int c) {
  vector<int> result(m.size(), 0);

  int cantidad_restante = c;
  int i = 0;
  while (i < m.size() && cantidad_restante > 0) {
    if (m[i] <= cantidad_restante) {
      result[i]++;
      cantidad_restante -= m[i];
    } else {
      i++;
    }
  }

  if (cantidad_restante == 0) {
    return {true, result};
  } else {
    return {false, {}};
  }
}

int main() {
  auto [_, result] = cambio_monedas({200, 100, 50, 20, 10, 5, 2, 1}, 192);
  cout << result.size() << endl;
  copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
  return 0;
}

