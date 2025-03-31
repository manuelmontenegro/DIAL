// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de coloreado de grafos mediante vuelta atrás
// Imprime solamente una solución

#include "Grafo.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void imprimir_solucion(const vector<int> &sol) {
  cout << "[0: " << sol[0];
  for (int i = 1; i < sol.size(); i++) {
    cout << ", " << i << ": " << sol[i];
  }
  cout << "]\n";
}

bool es_factible(const Grafo &g, vector<int> &sol, int k, int color) {
  const vector<int> &ady = g.ady(k);
  return all_of(ady.begin(), ady.end(),
                [&sol, color, k](int v) { return v >= k || sol[v] != color; });
}

bool colorear_grafo(const Grafo &g, int num_colores, int k, vector<int> &sol) {
  if (k == sol.size()) {
    return true;
  } else {
    bool hay_solucion = false;
    for (int i = 0; i < num_colores && !hay_solucion; i++) {
      if (es_factible(g, sol, k, i)) {
        sol[k] = i;
        hay_solucion = colorear_grafo(g, num_colores, k + 1, sol);
      }
    }
    return hay_solucion;
  }
}

int main() {
  Grafo g(5);
  g.ponArista(0, 1);
  g.ponArista(1, 2);
  g.ponArista(2, 3);
  g.ponArista(1, 3);
  g.ponArista(1, 4);
  g.ponArista(3, 4);
  g.ponArista(0, 4);

  vector<int> sol(5, 0);
  if (colorear_grafo(g, 3, 0, sol)) {
    imprimir_solucion(sol);
  }

  return 0;
}