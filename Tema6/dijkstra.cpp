// ---------------------
// Algoritmo de Dijkstra
// ---------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "IndexPQ.h"

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

void anyadir_arista(grafo &g, int origen, int destino, int coste) {
  g[origen].push_back({origen, destino, coste});
}

const lista_aristas & aristas(const grafo &g, int origen) {
  return g[origen];
}

int num_vertices(const grafo &g) {
  return g.size();
}

struct DijkstraResult {
  vector<int> dist;
  vector<int> ant;
};

DijkstraResult caminos_minimos(const grafo &g, int origen) {
  int n = num_vertices(g);
  // Creamos cola de prioridad vacía
  IndexPQ pq(n);

  // Inicializamos dist y ant
  vector<int> dist(n, numeric_limits<int>::max());
  vector<int> ant(n);
  dist[origen] = 0;
  ant[origen] = -1;

  // Introducimos vértice 0 en cola de prioridad
  pq.push(origen, 0);

  // Mientras queden vértices por procesar
  while (!pq.empty()) {
    // Obtenemos el vértice de menor distancia al origen
    // que no haya sido procesado, y lo sacamos de la cola
    int actual = pq.top().elem; pq.pop();
    // Recorremos las aristas que salen de ese vértice
    for (const arista &a : aristas(g, actual)) {
      // Si la arista permite mejorar el coste del camino
      // mínimo desde el origen al destino, actualizamos
      // el camino mínimo hasta destino.
      if (dist[a.vertice2] > dist[actual] + a.coste) {
	dist[a.vertice2] = dist[actual] + a.coste;
	ant[a.vertice2] = actual;
	pq.update(a.vertice2,dist[a.vertice2]);
      }
    }
  }

  return {dist, ant};
}

vector<int> reconstruir_camino(int destino, const vector<int> &ant) {
  vector<int> result;
  result.push_back(destino);
  int i = destino;
  while (ant[i] != -1) {
    result.push_back(ant[i]);
    i = ant[i];
  }

  reverse(result.begin(), result.end());
  return result;
}

int main() {
  int n = 8;
  grafo g = crear_grafo(n);
  anyadir_arista(g, 0, 1, 5);
  anyadir_arista(g, 0, 7, 8);
  anyadir_arista(g, 0, 4, 9);
  anyadir_arista(g, 1, 7, 4);
  anyadir_arista(g, 1, 2, 12);
  anyadir_arista(g, 1, 3, 15);
  anyadir_arista(g, 2, 3, 3);
  anyadir_arista(g, 2, 6, 11);
  anyadir_arista(g, 3, 6, 9);
  anyadir_arista(g, 4, 5, 4);
  anyadir_arista(g, 4, 6, 20);
  anyadir_arista(g, 4, 7, 5);
  anyadir_arista(g, 5, 2, 1);
  anyadir_arista(g, 5, 6, 13);
  anyadir_arista(g, 7, 2, 7);
  anyadir_arista(g, 7, 5, 6);
  
  DijkstraResult res = caminos_minimos(g, 0);

  for (int i = 0; i < n; i++) {
    cout << "Distancia a " << i << ": " << res.dist[i] << ". Camino mínimo:";
    for (int u : reconstruir_camino(i, res.ant)) {
      cout << ' ' << u;
    }
    cout << endl;
  }

  return 0;
}
