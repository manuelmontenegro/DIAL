// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación del algoritmo de Prim para ARM en grafos valorados
// Solo funciona si el grafo es conexo. De lo contrario, solamente calcula
// el ARM de la parte del grafo alcanzable desde el vértice 0.

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T> class Prim {
public:
  Prim(const GrafoValorado<T> &g);

  // Devuelve el coste del ARM encontrado
  T coste() { return coste_total; }

  // Devuelve las aristas del ARM
  const vector<Arista<T>> &aristasARM() const { return arm; }

private:
  vector<Arista<T>> arm;
  int coste_total;
};

template <typename T>
Prim<T>::Prim(const GrafoValorado<T> &g) : coste_total(0) {
  // Conjunto de los vértices que ya forman parte del ARM.
  // Si pertenece_arm[v] = true, entonces el vértice ya está conectado
  // al ARM.
  vector<bool> pertenece_arm(g.V(), false);

  // Inicialmente solo tenemos las aristas que parten del 0 en la cola
  // de prioridad
  priority_queue<Arista<T>, vector<Arista<T>>, greater<Arista<T>>> pq;

  for (const Arista<int> &a : g.ady(0)) {
    pq.push(a);
  }

  pertenece_arm[0] = true;

  // Mientras queden aristas por procesar y no tengamos ya V - 1 aristas.
  while (!pq.empty() && arm.size() < g.V() - 1) {
    // Sacamos la arista de menor coste
    Arista<int> a = pq.top();
    pq.pop();
    int v = a.uno();
    int w = a.otro(v);

    // Solo añadimos la arista si uno de sus extremos está ya en el ARM
    // y el otro no. No es posible que ninguno de los dos extremos esté en el
    // ARM, y si los dos extremos estuvieran en el ARM, entonces al añadir
    // la arista se formaría un ciclo.
    if (pertenece_arm[v] != pertenece_arm[w]) {
      // Miramos el nuevo vértice que conectaremos con el ARM
      arm.push_back(a);
      coste_total += a.valor();
      int nuevo = pertenece_arm[v] ? w : v;
      pertenece_arm[nuevo] = true;
      // Añadimos las aristas del nuevo
      for (const Arista<T> &a : g.ady(nuevo)) {
        // Si la arista va a crear un ciclo en el ARM, entonces
        // no la metemos en la cola de prioridad.
        if (!pertenece_arm[a.otro(nuevo)]) {
          pq.push(a);
        }
      }
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

  Prim k(g);
  cout << "Coste: " << k.coste() << '\n';

  for (const Arista<int> &a : k.aristasARM()) {
    cout << a.valor() << ' ';
  }
  cout << '\n';
  return 0;
}