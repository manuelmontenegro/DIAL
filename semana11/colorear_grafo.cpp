// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de coloreado de grafos mediante vuelta atrás
// Imprime todas las soluciones

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

// bool es_factible(const Grafo &g, vector<int> &sol, int k, int i) {
//   const vector<int> &ady = g.ady(k);
//   // Recorremos los vértices adyacentes
//   bool factible = true;
//   int j = 0;
//   while (j < ady.size() && factible) {
//     int v = ady[j];
//     // Si el vértice v (adyacente a k) tiene color asignado, y además
//     // coincide con el color i, entonces no podemos asignar el color i al
//     // vértice k.
//     if (v < k && sol[v] == i) {
//       factible = false;
//     }
//     j++;
//   }
//   return factible;
// }

// Alternativa: utilizar función `any_of` de C++, que devuelve `true` si
// algún elemento del vector satisface un predicado pasado como tercer
// parámetro.

bool es_factible(const Grafo &g, vector<int> &sol, int k, int color) {
  const vector<int> &ady = g.ady(k);
  return !any_of(ady.begin(), ady.end(),
                 [&sol, color, k](int v) { return v < k && sol[v] == color; });
}

void colorear_grafo(const Grafo &g, int num_colores, int k, vector<int> &sol) {
  if (k == sol.size()) {
    imprimir_solucion(sol);
  } else {
    for (int i = 0; i < num_colores; i++) {
      if (es_factible(g, sol, k, i)) {
        sol[k] = i;
        colorear_grafo(g, num_colores, k + 1, sol);
      }
    }
  }
}

void colorear_grafo(const Grafo &g, int num_colores) {
  vector<int> sol(g.V());
  colorear_grafo(g, num_colores, 0, sol);
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

  colorear_grafo(g, 3);

  return 0;
}