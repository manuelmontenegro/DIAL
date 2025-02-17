// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación en C++ de la función que determina
// si un vector está equilibrado.
//
// Versión con coste O(n), donde n es el tamaño del vector.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

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
 *
 * Devuelve una tupla con tres componentes:
 *   - Un booleano que indica si el vector está equilibrado.
 *   - El número de elementos positivos en el vector.
 *   - El número de elementos negativos en el vector.
 */
tuple<bool, int, int> equilibrado(const vector<int> &v, int c, int f) {
  if (f - c <= 1) {
    return {true, numPositivos(v, c, f), numNegativos(v, c, f)};
  } else {
    int m = (c + f) / 2;
    auto [eq_iz, pos_iz, neg_iz] = equilibrado(v, c, m);
    auto [eq_dr, pos_dr, neg_dr] = equilibrado(v, m, f);
    int pos = pos_iz + pos_dr;
    int neg = neg_iz + neg_dr;
    bool eq = eq_iz && eq_dr && abs(pos - neg) <= 1;

    return {eq, pos, neg};
  }
}

/*
 * Llamada inicial a la función `equilibrado` de arriba.
 */
bool equilibrado(const vector<int> &v) {
  auto [eq, pos, neg] = equilibrado(v, 0, v.size());
  return eq;
}

int main() {
  // El manipulador `boolalpha` hace que los booleanos se impriman como
  // `true` o `false`, en lugar de imprimirse como `1` y `0`  respectivamente.
  cout << boolalpha << equilibrado({0, -2, 5, 0, -6, 0, 9, -3}) << '\n';
  cout << boolalpha << equilibrado({0, -2, 5, 9, -6, 0, 9, -3}) << '\n';
  cout << boolalpha << equilibrado({0, 0, 0, 0}) << '\n';
  return 0;
}