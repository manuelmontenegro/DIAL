// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema del viajante mediante vuelta atrás
// No utiliza estimación optimista

#include <iostream>
#include <limits>
#include <vector>

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

// Algoritmo de vuelta atrás
// -------------------------

bool es_factible(const grafo<int> &g, int k, int ciudad, const vector<int> &sol,
                 const vector<bool> &visitadas) {
  return adyacentes(g, sol[k - 1], ciudad) && !visitadas[ciudad] &&
         (k != sol.size() - 1 || adyacentes(g, ciudad, sol[0]));
}

void viajante(const grafo<int> &g, int k, vector<int> &sol, int coste_acum,
              vector<bool> &visitadas, vector<int> &sol_mejor,
              int &coste_mejor) {
  if (k == sol.size()) {
    coste_acum += g[sol[k - 1]][0];
    if (coste_acum < coste_mejor) {
      coste_mejor = coste_acum;
      sol_mejor = sol;
    }
  } else {
    for (int c = 0; c < num_vertices(g); c++) {
      if (es_factible(g, k, c, sol, visitadas)) {
        sol[k] = c;

        visitadas[c] = true;
        viajante(g, k + 1, sol, coste_acum + g[sol[k - 1]][c], visitadas,
                 sol_mejor, coste_mejor);
        visitadas[c] = false;
      }
    }
  }
}

vector<int> viajante(const grafo<int> &g) {
  vector<int> sol(num_vertices(g));
  vector<int> sol_mejor(num_vertices(g));
  vector<bool> visitadas(num_vertices(g), false);
  sol[0] = 0;
  visitadas[0] = true;
  int coste_mejor = numeric_limits<int>::max();
  viajante(g, 1, sol, 0, visitadas, sol_mejor, coste_mejor);
  return sol_mejor;
}

int coste_camino(const grafo<int> &g, const vector<int> &sol) {
  if (sol[1] == 0)
    return numeric_limits<int>::max();
  int result = 0;
  int n = sol.size();
  for (int i = 1; i < n; i++) {
    result += g[sol[i - 1]][sol[i]];
  }
  result += g[sol[n - 1]][sol[0]];
  return result;
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

  vector<int> sol = viajante(g);

  cout << sol[0];
  for (int i = 1; i < sol.size(); i++) {
    cout << ' ' << sol[i];
  }
  cout << '\n';

  cout << "Coste: " << coste_camino(g, sol) << '\n';

  return 0;
}
