// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de las n reinas mediante vuelta atrás
// Utiliza marcaje

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

bool es_factible(int n, int k, int col, const vector<bool> &cols,
                 const vector<bool> &diag_ps, const vector<bool> &diag_ss) {
  return !cols[col] && !diag_ps[col - k + (n - 1)] && !diag_ss[k + col];
}

void n_reinas(int n, int k, vector<int> &sol, vector<bool> &cols,
              vector<bool> &diag_ps, vector<bool> &diag_ss) {
  if (k == n) {
    imprimir_solucion(sol);
  } else {
    for (int col = 0; col < n; col++) {
      if (es_factible(n, k, col, cols, diag_ps, diag_ss)) {
        sol[k] = col;

        cols[col] = true;
        diag_ps[col - k + (n - 1)] = true;
        diag_ss[k + col] = true;

        n_reinas(n, k + 1, sol, cols, diag_ps, diag_ss);

        cols[col] = false;
        diag_ps[col - k + (n - 1)] = false;
        diag_ss[k + col] = false;
      }
    }
  }
}

void n_reinas(int n) {
  vector<int> sol(n);
  vector<bool> cols(n, false);
  vector<bool> diag_ps(2 * n - 1, false);
  vector<bool> diag_ss(2 * n - 1, false);
  n_reinas(n, 0, sol, cols, diag_ps, diag_ss);
}

int main() {
  n_reinas(8);
  return 0;
}