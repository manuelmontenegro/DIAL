// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema del viajante mediante vuelta atrás
// Utiliza ramificación y poda con estimación optimista

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

// Representación de grafo mediante matrices de adyacencia
// -------------------------------------------------------


template <typename T>
using grafo = vector<vector<T>>;

grafo<int> nuevo_grafo(int n) {
  return vector<vector<int>>(n, vector<int>(n, -1));
}

void anyadir_arista(grafo<int> &g, int v, int w, int coste) {
  g[v][w] = coste;
  g[w][v] = coste;
}

bool adyacentes(const grafo<int> &g, int v, int w) { return g[v][w] != -1; }

int num_vertices(const grafo<int> &g) {
  return g.size();
}

// Representación de nodos
// -----------------------

struct Nodo {
  vector<int> sol;          // Camino seguido por el viajante
  int k;                    // Nivel de la solución
  vector<bool> visitadas;   // Ciudades visitadas
  int coste_acum;           // Coste acumulado
  int estimacion_optimista; // Estimación optimista
};

bool operator<(const Nodo &n1, const Nodo &n2) {
  return n1.estimacion_optimista > n2.estimacion_optimista;
}

// Algoritmo de vuelta atrás
// -------------------------

bool es_factible(const grafo<int> &g, int k, int ciudad, const vector<int> &sol,
                 const vector<bool> &visitadas) {
  return adyacentes(g, sol[k - 1], ciudad) && !visitadas[ciudad] &&
         (k != sol.size() - 1 || adyacentes(g, ciudad, sol[0]));
}

// Obtiene el coste de la arista de menor coste en todo el grafo
int coste_min_arista(const grafo<int> &g) {
  int result = numeric_limits<int>::max();
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g.size(); j++) {
      if (g[i][j] != -1) {
        result = min(result, g[i][j]);
      }
    }
  }
  return result;
}

pair<vector<int>, int> viajante(const grafo<int> &g) {
  int n = num_vertices(g);
  int min_arista = coste_min_arista(g);
  priority_queue<Nodo> cp;

  Nodo raiz;
  raiz.sol = vector<int>(n);
  raiz.sol[0] = 0;
  raiz.k = 1;
  raiz.visitadas = vector<bool>(n, false);
  raiz.visitadas[0] = true;
  raiz.coste_acum = 0;
  raiz.estimacion_optimista = num_vertices(g) * min_arista;
  cp.push(raiz);

  int coste_mejor = numeric_limits<int>::max();
  vector<int> sol_mejor;

  while (!cp.empty() && cp.top().estimacion_optimista < coste_mejor) {
    Nodo x = cp.top(); cp.pop();
    for (int c = 0; c < num_vertices(g); c++) {
      if (es_factible(g, x.k, c, x.sol, x.visitadas)) {
        Nodo hijo = x;
        hijo.sol[x.k] = c;
        hijo.k = x.k + 1;
        hijo.visitadas[c] = true;
        hijo.coste_acum = x.coste_acum + g[hijo.sol[x.k - 1]][c];
        hijo.estimacion_optimista = hijo.coste_acum + (num_vertices(g) - hijo.k + 1) * min_arista;

        if (hijo.k == n) {
          hijo.coste_acum += g[hijo.sol[n-1]][0];
          if (hijo.coste_acum < coste_mejor) {
            coste_mejor = hijo.coste_acum;
            sol_mejor = hijo.sol;
          }
        } else if (hijo.estimacion_optimista < coste_mejor) {
          cp.push(hijo);
        }
      }
    }
  }

  return {sol_mejor, coste_mejor};
}



int main() {
  grafo<int> g = nuevo_grafo(8);
  anyadir_arista(g, 0, 1, 20);
  anyadir_arista(g, 0, 2, 10);
  anyadir_arista(g, 0, 6, 9);
  anyadir_arista(g, 1, 2, 15);
  anyadir_arista(g, 1, 3, 7);
  anyadir_arista(g, 2, 3, 9);
  anyadir_arista(g, 2, 4, 14);
  anyadir_arista(g, 2, 5, 15);
  anyadir_arista(g, 3, 4, 21);
  anyadir_arista(g, 3, 7, 10);
  anyadir_arista(g, 4, 7, 9);
  anyadir_arista(g, 5, 6, 7);
  anyadir_arista(g, 5, 7, 30);

  auto [sol, coste] = viajante(g);

  cout << sol[0];
  for (int i = 1; i < sol.size(); i++) {
    cout << ' ' << sol[i];
  }
  cout << '\n';

  cout << "Coste: " << coste << '\n';

  return 0;
}
