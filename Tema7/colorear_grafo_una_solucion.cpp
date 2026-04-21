// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de coloreado de grafos mediante vuelta atrás
// Imprime solamente una solución

#include <iostream>
#include <vector>

using namespace std;


// Definición de tipo de datos `grafo` y operaciones asociadas
// -----------------------------------------------------------
// Los grafos son no dirigidos. Por tanto, cada vez que añadimos
// una arista X --- Y, añadimos esa arista tanto a la lista de 
// adyacencia de X como a la lista de adyacencia de Y.

struct arista {
  int origen;
  int destino;
  int coste;
};

using lista_aristas = vector<arista>;
using grafo = vector<lista_aristas>;

grafo crear_grafo(int num_vertices) {
  return vector<vector<arista>>(num_vertices);
}

void anyadir_arista(grafo &g, int origen, int destino, int coste) {
  g[origen].push_back({origen, destino, coste});
  g[destino].push_back({destino, origen, coste});
}

const lista_aristas & aristas(const grafo &g, int origen) {
  return g[origen];
}

int num_vertices(const grafo &g) {
  return g.size();
}

// Algoritmo de vuelta atrás
// -------------------------

vector<string> nombres_colores = {"R", "A", "V"};

void imprimir_solucion(const vector<int> &sol) {
  cout << "[" << nombres_colores[sol[0]];
  for (int i = 1; i < sol.size(); i++) {
    cout << ", " << nombres_colores[sol[i]];
  }
  cout << "]\n";
}

bool es_factible(const grafo &g, vector<int> &sol, int k, int i) {
  const vector<arista> &as = aristas(g, k);
  // Recorremos las aristas adyacentes
  bool factible = true;
  int j = 0;
  while (j < as.size() && factible) {
    int v = as[j].destino;
    // Si el vértice v (adyacente a k) tiene color asignado, y además
    // coincide con el color i, entonces no podemos asignar el color i al
    // vértice k.
    if (v < k && sol[v] == i) {
      factible = false;
    }
    j++;
  }
  return factible;
}

bool colorear_grafo_gen(const grafo &g, int num_colores, int k, vector<int> &sol) {
  if (k == sol.size()) {
    return true;
  } else {
    bool solucion_encontrada = false;
    int i = 0;
    while (i < num_colores && !solucion_encontrada) {
      if (es_factible(g, sol, k, i)) {
        sol[k] = i;
        solucion_encontrada = colorear_grafo_gen(g, num_colores, k + 1, sol);
      }
      i++;
    }
    return solucion_encontrada;
  }
}

void colorear_grafo(const grafo &g, int num_colores) {
  vector<int> sol(num_vertices(g));
  colorear_grafo_gen(g, num_colores, 0, sol);
}

int main() {
  grafo g = crear_grafo(5);
  anyadir_arista(g, 0, 1, 0);
  anyadir_arista(g, 1, 2, 0);
  anyadir_arista(g, 2, 3, 0);
  anyadir_arista(g, 1, 3, 0);
  anyadir_arista(g, 1, 4, 0);
  anyadir_arista(g, 3, 4, 0);
  anyadir_arista(g, 0, 4, 0);

  vector<int> sol(5, 3);
  if (colorear_grafo_gen(g, 3, 0, sol)) {
    imprimir_solucion(sol);
  }

  return 0;
}
