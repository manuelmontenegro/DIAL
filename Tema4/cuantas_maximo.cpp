// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Dado un vector `v`, resolvemos el problema de determinar cuántas veces
// aparece el máximo de un vector en ese vector.

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Devuelve un par con dos componentes:
//  - Máximo del segmento v[c..f)
//  - Cuántas veces aparece ese máximo en el segmento v[c..f)
template <typename T>
pair<T, T> cuantas_maximo(const vector<T> &v, int c, int f) {
  assert(0 <= c && c < f && f <= v.size());

  if (c + 1 == f) { // Caso base: vector unitario
    // El máximo es el único elemento, y aparece una única vez
    return {v[c], 1};
  } else { // Caso recursivo
    int m = (c + f) / 2;

    auto [max1, cuantas1] = cuantas_maximo(v, c, m);
    auto [max2, cuantas2] = cuantas_maximo(v, m, f);

    if (max1 == max2) { // Si los máximos coinciden, entonces sumamos las
                        // cantidades de ambos máximos en cada subvector
      return {max1, cuantas1 + cuantas2};
    } else if (max1 < max2) {
      return {max2, cuantas2};
    } else {
      return {max1, cuantas1};
    }
  }
}

// Llamada inicial
template <typename T> int cuantas_maximo(const vector<T> &v) {
  auto [_max, n] = cuantas_maximo(v, 0, v.size());
  return n;
}

int main() {
  cout << cuantas_maximo<int>({3, 5, 5, 8, 5, 8, 2, 1, 8, 8, 8}) << '\n';
  return 0;
}