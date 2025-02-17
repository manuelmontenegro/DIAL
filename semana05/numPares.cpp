// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del número de elementos pares de un vector

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Calcula el número de elementos pares en el segmento [c..f) del vector v dado.
int numPares(const vector<int> &v, int c, int f){
  assert (0 <= c && c <= f && f <= v.size());

  if (c == f) {                 // Caso base 1: vector vacío
    return 0;
  } else if (c + 1 == f) {      // Caso base 2: vector unitario
    // Si `v[c]` es par, devolvemos 1; si no, devolvemos 0.
    return (v[c] % 2 == 0 ? 1 : 0);
  } else {                      // Caso recursivo
    int m = (c + f) / 2;
    return numPares(v, c, m) + numPares(v, m, f);
  } 
}


// Calcula el número de elementos pares en el vector v.
int numPares(const vector<int> &v) {
  return numPares(v, 0, v.size());
}

int main() {
  cout << numPares({-2, 2, 3, 5, 6, 7, 3, 4}) << '\n';
}