// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación del algoritmo de Kruskal para ARM en grafos valorados

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T> class Kruskal {
public:
  Kruskal(const GrafoValorado<T> &g);

  // Devuelve el coste del ARM encontrado
  T coste() { return coste_total; }

  // Devuelve las aristas del ARM
  const vector<Arista<T>> &aristasARM() const { return arm; }

private:
  vector<Arista<T>> arm;
  int coste_total;
};

template <typename T>
Kruskal<T>::Kruskal(const GrafoValorado<T> &g) : coste_total(0) {
  // Inicialmente metemos las aristas en la cola de prioridad
  vector<Arista<int>> aristas = g.aristas();
  priority_queue<Arista<T>, vector<Arista<T>>, greater<Arista<T>>> pq(
      aristas.begin(), aristas.end());

  // Inicialmente, los vértices están todos desconectados en el ARM
  ConjuntosDisjuntos cd(g.V());

  // Mientras queden aristas por procesar y no tengamos ya V - 1 aristas.
  while (!pq.empty() && arm.size() < g.V() - 1) {
    // Sacamos la arista de menor coste
    Arista<int> a = pq.top();
    pq.pop();
    int v = a.uno();
    int w = a.otro(v);
    // Si esa arista no forma un ciclo, la añadimos al ARM
    if (!cd.unidos(v, w)) {
      arm.push_back(a);
      coste_total += a.valor();
      cd.unir(v, w);
    }
  }
}

int main() {
  GrafoValorado<int> g(8);
  g.ponArista({0, 2, 25});
  g.ponArista({0, 4, 65});
  g.ponArista({0, 6, 85});
  g.ponArista({0, 7, 10});
  g.ponArista({1, 2, 55});
  g.ponArista({1, 3, 35});
  g.ponArista({1, 5, 40});
  g.ponArista({1, 7, 20});
  g.ponArista({2, 3, 15});
  g.ponArista({2, 6, 70});
  g.ponArista({2, 7, 45});
  g.ponArista({3, 6, 80});
  g.ponArista({4, 5, 50});
  g.ponArista({4, 6, 90});
  g.ponArista({4, 7, 60});
  g.ponArista({5, 7, 30});

  Kruskal k(g);
  cout << "Coste: " << k.coste() << '\n';

  for (const Arista<int> &a : k.aristasARM()) {
    cout << a.valor() << ' ';
  }
  cout << '\n';
  return 0;
}