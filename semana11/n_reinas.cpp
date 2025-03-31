// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de las n reinas mediante vuelta atrás
// No utiliza marcaje

#include "Grafo.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void imprimir_solucion(const vector<int> &sol) {
  cout << "[" << sol[0];
  for (int i = 1; i < sol.size(); i++) {
    cout << ", " << sol[i];
  }
  cout << "]\n";
}

bool es_factible(const vector<int> &sol, int k, int col) {
  bool factible = true;
  for (int i = 0; i < k && factible; i++) {
    if (sol[i] == col || abs(k - i) == abs(col - sol[i])) {
      factible = false;
    }
  }
  return factible;
}

void n_reinas(int n, int k, vector<int> &sol) {
  if (k == n) {
    imprimir_solucion(sol);
  } else {
    for (int col = 0; col < n; col++) {
      if (es_factible(sol, k, col)) {
        sol[k] = col;
        n_reinas(n, k + 1, sol);
      }
    }
  }
}

void n_reinas(int n) {
  vector<int> sol(n);
  n_reinas(n, 0, sol);
}

int main() {
  n_reinas(8);
  return 0;
}