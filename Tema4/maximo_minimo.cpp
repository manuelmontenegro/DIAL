// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del máximo y mínimo de un vector mediante Divide y Vencerás
// Utiliza la clase `pair` de C++

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Calcula el máximo y mínimo del segmento [c..f) del vector v dado.
template <typename T>
pair<T, T> maximo_minimo(const vector<T> &v, int c, int f) {
  assert(0 <= c && c < f && f <= v.size());

  if (c + 1 == f) { // Caso base: vector unitario
    return {v[c], v[c]};
  } else { // Caso recursivo
    int m = (c + f) / 2;

    auto [max1, min1] = maximo_minimo(v, c, m);
    auto [max2, min2] = maximo_minimo(v, m, f);

    return {max(max1, max2), min(min1, min2)};
  }
}

template <typename T> pair<T, T> maximo_minimo(const vector<T> &v) {
  return maximo_minimo(v, 0, v.size());
}

int main() {
  auto [mx, mn] = maximo_minimo<int>({4, 5, 1, 3, -3, 6});
  cout << mx << ' ' << mn << '\n';
  return 0;
}