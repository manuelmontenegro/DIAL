// --------------------
// Algoritmo de Kruskal
// --------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <vector>
#include <algorithm>
#include "UnionFind.h"

using namespace std;

struct arista {
  int vertice1;
  int vertice2;
  int coste;
};

using lista_aristas = vector<arista>;
using grafo = vector<lista_aristas>;

grafo crear_grafo(int num_vertices) {
  return vector<vector<arista>>(num_vertices);
}

void anyadir_arista(grafo &g, int vertice1, int vertice2, int coste) {
  g[vertice1].push_back({vertice1, vertice2, coste});
}

const lista_aristas & aristas(const grafo &g, int origen) {
  return g[origen];
}

int num_vertices(const grafo &g) {
  return g.size();
}

vector<arista> kruskal(const grafo &g) {
  int v = num_vertices(g);
  vector<arista> lista_aristas;
  for (int i = 0; i < v; i++) {
    for (const arista &a : aristas(g, i)) lista_aristas.push_back(a);
  }

  sort(lista_aristas.begin(), lista_aristas.end(), [](const arista &a, const arista &b) {
	return a.coste < b.coste;
  });
  
  union_find uf(v);

  vector<arista> result;
  int i = 0;
  while (i < lista_aristas.size() && result.size() < v - 1) {
    arista actual = lista_aristas[i];
    if (!uf.unidos(actual.vertice1, actual.vertice2)) {
      result.push_back(actual);
      uf.unir(actual.vertice1, actual.vertice2);
    }
    i++;
  }

  return result;
}

int main() {
  grafo g = crear_grafo(8);
  anyadir_arista(g, 0, 2, 25);
  anyadir_arista(g, 0, 4, 65);
  anyadir_arista(g, 0, 6, 85);
  anyadir_arista(g, 0, 7, 10);
  anyadir_arista(g, 1, 2, 55);
  anyadir_arista(g, 1, 3, 35);
  anyadir_arista(g, 1, 5, 40);
  anyadir_arista(g, 1, 7, 20);
  anyadir_arista(g, 2, 3, 15);
  anyadir_arista(g, 2, 6, 70);
  anyadir_arista(g, 2, 7, 45);
  anyadir_arista(g, 3, 6, 80);
  anyadir_arista(g, 4, 5, 50);
  anyadir_arista(g, 4, 6, 90);
  anyadir_arista(g, 4, 7, 60);
  anyadir_arista(g, 5, 7, 30);

  for (const arista &a : kruskal(g)) {
    cout << a.coste << ' ';
  }
  cout << '\n';
  return 0;
}
