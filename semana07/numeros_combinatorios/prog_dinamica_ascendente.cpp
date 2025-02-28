// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del número combinatorio "n sobre k" utilizando programación
// dinámica ascendente.

#include <iostream>
#include <vector>

using namespace std;

// Devuelve "n sobre k"
long num_combinatorio(int n, int k) {
  // No necesitamos la matriz. El segmento [j..k) contendrá
  // los resultados de la fila actual, y el segmento [0..j)
  // los resultados de la fila anterior de la matriz.
  vector<long> v(k + 1, 0);
  v[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = k; j >= 1; j--) {
      v[j] = v[j - 1] + v[j];
    }
  }
  return v[k];
}

int main() {
  cout << num_combinatorio(45, 10) << '\n';
  return 0;
}