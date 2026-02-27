// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del máximo de un vector mediante Divide y Vencerás

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Calcula el máximo del segmento [c..f) del vector v dado.
template <typename T> T maximo(const vector<T> &v, int c, int f) {
  assert (0 <= c && c < f && f <= v.size());

  
  if (c + 1 == f) {   // Caso base: vector unitario
    return v[c];
  } else {            // Caso recursivo
    int m = (c + f) / 2;

    T max1 = maximo(v, c, m);
    T max2 = maximo(v, m, f);

    return max(max1, max2);
  }
}


// Calcula el máximo de un vector. Para ello realiza la llamada inicial
// a la función `maximo` definida arriba.
template <typename T> T maximo(const vector<T> &v) {
  return maximo(v, 0, v.size());
}

int main() {
  cout << maximo<int>({4, 5, 1, 3, -3, 6}) << '\n';
  cout << maximo<int>({4}) << '\n';
}