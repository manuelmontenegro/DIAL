// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación en C++ del algoritmo Quicksort

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

/*
 * Algoritmo de partición. Particiona el segmento v[c..f) del vector `v`
 * utilizando el pivote pasado como parámetro.
 *
 * Devuelve un par (p, q), donde `p` es la posición que contiene el primer
 * elemento igual al pivote, y `q` es la posición que contiene el primer
 * elemento mayor que el pivote.
 */
template <typename T>
pair<int, int> partition(vector<T> &v, int c, int f, int pivote) {
  int p = c;
  int j = c;
  int q = f;

  while (j != q) {
    if (v[j] == pivote) {
      j++;
    } else if (v[j] < pivote) {
      swap(v[p], v[j]);
      p++;
      j++;
    } else {
      swap(v[j], v[q - 1]);
      q--;
    }
  }
  return {p, q};
}

/*
 * Algoritmo Quicksort. Ordena el segmento v[c..f) del vector
 * pasado como parámetro.
 */
template <typename T> void quicksort(vector<T> &v, int c, int f) {
  if (c < f) {
    auto [p, q] = partition(v, c, f, v[c]);
    quicksort(v, c, p);
    quicksort(v, q, f);
  }
}

/*
 * Llamada inicial a la función `quicksort` de arriba.
 */
template <typename T> void quicksort(vector<T> &v) {
  quicksort(v, 0, v.size());
}

int main() {
  vector<int> v = {1, 7, 2, 4, 5, -3, 9, 10, 32, 1};
  quicksort(v);

  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}
