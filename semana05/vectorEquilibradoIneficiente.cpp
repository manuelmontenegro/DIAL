#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

// Implementación en C++ de la función que determina
// si un vector está equilibrado.
//
// Versión con coste O(n log n), donde n es el tamaño del vector.


using namespace std;

/*
 * Cuenta el número de elementos positivos en el segmento v[c..f) de un vector
 */
int numPositivos(const vector<int> &v, int c, int f) {
  return count_if(v.begin() + c, v.begin() + f, [](int x) { return x > 0; });
}

/*
 * Cuenta el número de elementos negativos en el segmento v[c..f) de un vector
 */
int numNegativos(const vector<int> &v, int c, int f) {
  return count_if(v.begin() + c, v.begin() + f, [](int x) { return x < 0; });
}

/*
 * Determina si el segmento v[c..f) del vector `v` está equilibrado o no.
 */
bool equilibrado(const vector<int> &v, int c, int f) {
  if (f - c <= 1) {
    return true;
  } else {
    int m = (c + f) / 2;
    return equilibrado(v, c, m) && equilibrado(v, m, f) &&
           abs(numPositivos(v, c, f) - numNegativos(v, c, f)) <= 1;
  }
}

/*
 * Llamada inicial a la función `equilibrado` de arriba.
 */
bool equilibrado(const vector<int> &v) { return equilibrado(v, 0, v.size()); }

int main() {
  // El manipulador `boolalpha` hace que los booleanos se impriman como
  // `true` o `false`, en lugar de imprimirse como `1` y `0`  respectivamente.
  cout << boolalpha << equilibrado({0, -2, 5, 0, -6, 0, 9, -3}) << '\n';
  cout << boolalpha << equilibrado({0, -2, 5, 9, -6, 0, 9, -3}) << '\n';
  cout << boolalpha << equilibrado({0, 0, 0, 0}) << '\n';
  return 0;
}