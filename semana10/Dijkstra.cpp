// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación del algoritmo de Dijkstra en digrafos valorados

#include "DigrafoValorado.h" // ver Campus Virtual
#include "IndexPQ.h"         // ver Campus Virtual
#include <iostream>
#include <limits>
#include <list>
#include <vector>

using namespace std;

template <typename T> class Dijkstra {
public:
  using Camino = list<AristaDirigida<T>>;
  const T INF = std::numeric_limits<T>::max();

  Dijkstra(const DigrafoValorado<T> &g, int origen);

  T distancia(int v) const { return dist[v]; }

  Camino camino(int v) const;

private:
  // Distancias mínimas desde el origen a cada vértice
  vector<T> dist;
  // Para cada vértice, última arista del camino mínimo que llega
  // a ese vértice
  vector<AristaDirigida<T>> ulti;
  // Vértice origen. Se necesita para reconstruir el camino.
  int orig;

  void relajar(IndexPQ<int> &pq, const AristaDirigida<T> &a);
};

template <typename T>
Dijkstra<T>::Dijkstra(const DigrafoValorado<T> &g, int origen)
    : dist(g.V(), INF), ulti(g.V()), orig(origen) {
  // Creamos una cola de prioridad para los vértices. La prioridad de cada
  // vértice es la distancia mínima al origen encontrada hasta ahora.
  IndexPQ<int> pq(g.V());

  // Metemos el origen con prioridad 0
  dist[origen] = 0;
  pq.push(origen, 0);

  // Mientras queden vértices por procesar
  while (!pq.empty()) {
    auto [v, _] = pq.top();
    pq.pop();
    // Para cada arista adyacente, miramos si da lugar a un camino más
    // corto al destino que el ya explorado anteriormente.
    for (const AristaDirigida<T> &a : g.ady(v)) {
      relajar(pq, a);
    }
  }
}

// Comprueba si la aparición la arista pasada como parámetro provoca que
// hayamos encontrado un nuevo camino mínimo al destino. En caso afirmativo,
// actualizamos el vector de distancias y la prioridad del vértice de destino.
template <typename T>
void Dijkstra<T>::relajar(IndexPQ<int> &pq, const AristaDirigida<T> &a) {
  int v = a.desde();
  int w = a.hasta();

  if (dist[w] > dist[v] + a.valor()) {
    dist[w] = dist[v] + a.valor();
    ulti[w] = a;
    pq.update(w, dist[w]);
  }
}

// Obtiene el camino mínimo a partir del vector `ulti`, recorriendo
// el camino hacia atrás.
template <typename T>
typename Dijkstra<T>::Camino Dijkstra<T>::camino(int v) const {
  Camino result;
  AristaDirigida<T> actual = ulti[v];
  while (actual.desde() != orig) {
    result.push_front(actual);
    actual = ulti[actual.desde()];
  }
  result.push_front(actual);
  return result;
}

int main() {
  DigrafoValorado<int> dg(8);
  dg.ponArista({0, 2, 3});
  dg.ponArista({0, 4, 11});
  dg.ponArista({1, 3, 15});
  dg.ponArista({2, 7, 7});
  dg.ponArista({3, 6, 8});
  dg.ponArista({4, 5, 5});
  dg.ponArista({4, 7, 14});
  dg.ponArista({5, 1, 8});
  dg.ponArista({5, 7, 7});
  dg.ponArista({5, 4, 4});
  dg.ponArista({6, 2, 5});
  dg.ponArista({6, 0, 10});
  dg.ponArista({7, 3, 12});
  dg.ponArista({7, 5, 5});

  Dijkstra<int> d(dg, 0);

  for (int i = 1; i < dg.V(); i++) {
    cout << "Distancia minima a " << i << ": " << d.distancia(i) << '\n';
    for (const AristaDirigida<int> &a : d.camino(i)) {
      cout << a.desde() << ' ';
    }
    cout << '\n';
  }
}