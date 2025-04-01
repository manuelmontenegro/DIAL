// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de coloreado de grafos mediante vuelta atrás
// Cuenta el número de soluciones

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

// La función devuelve el número de soluciones encontradas
int colorear_grafo(const Grafo &g, int num_colores, int k, vector<int> &sol) {
  if (k == sol.size()) {
    // Cuando terminamos una solución factible, hemos encontrado una
    // solución.
    return 1;
  } else {
    int num_encontradas = 0;
    for (int i = 0; i < num_colores; i++) {
      if (es_factible(g, sol, k, i)) {
        sol[k] = i;
        num_encontradas += colorear_grafo(g, num_colores, k + 1, sol);
      }
    }
    return num_encontradas;
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

  int num_soluciones = colorear_grafo(g, 3, 0, sol);

  cout << num_soluciones << '\n';
  return 0;
}