// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación en C++ del algoritmo de ordenación por mezclas

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

/*
 * Dados dos vectores `u` y `w` ordenados, mezcla sus elementos en
 * `v`, de modo que este último también esté ordenado.
 */
template <typename T>
void merge(const vector<T> &u, const vector<T> &w, vector<T> &v) {
  int i = 0, j = 0, k = 0;
  while (i < u.size() && j < w.size()) {
    if (u[i] <= w[j]) {
      v[k] = u[i];
      i++;
      k++;
    } else {
      v[k] = w[j];
      j++;
      k++;
    }
  }

  copy(u.begin() + i, u.end(), v.begin() + k);
  copy(w.begin() + j, w.end(), v.begin() + k);
}

/*
 * Ordena el vector `v` pasado como parámetro
 */
template <typename T> void mergesort(vector<T> &v) {
  if (v.size() > 1) {
    // Partimos el vector por la mitad
    int m = v.size() / 2;
    // Creamos dos vectores auxiliares
    vector<T> u(m), w(v.size() - m);
    // Copiamos los elementos de `v` a los vectores auxiliares
    copy(v.begin(), v.begin() + m, u.begin());
    copy(v.begin() + m, v.end(), w.begin());
    // Ordenamos recursivamente los vectores auxiliares
    mergesort(u);
    mergesort(w);
    // Mezclamos los vectores auxiliares en el vector `v` original
    merge(u, w, v);
  }
}

int main() {
  vector<int> v = {1, 7, 2, 4, 5, -3, 9, 10, 32, 1};
  mergesort(v);

  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}
