// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema del viajante mediante vuelta atrás
// No utiliza estimación optimista

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <typename T> using Matriz = vector<vector<T>>;

template <typename T> using Grafo = Matriz<T>;

Matriz<int> nuevo_grafo(int n) {
  return vector<vector<int>>(n, vector<int>(n, -1));
}

void pon_arista(Matriz<int> &g, int v, int w, int coste) {
  g[v][w] = coste;
  g[w][v] = coste;
}

bool adyacentes(const Matriz<int> &g, int v, int w) { return g[v][w] != -1; }

int coste(const Matriz<int> &g, const vector<int> &sol) {
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

bool es_factible(const Grafo<int> &g, int k, int ciudad, const vector<int> &sol,
                 const vector<bool> &visitadas) {
  return adyacentes(g, sol[k - 1], ciudad) && !visitadas[ciudad] &&
         (k != sol.size() - 1 || adyacentes(g, ciudad, sol[0]));
}

void viajante(const Matriz<int> &g, int k, vector<int> &sol, int coste_acum,
              vector<bool> &visitadas, vector<int> &sol_mejor,
              int &coste_mejor) {
  if (k == sol.size()) {
    coste_acum += g[sol[k - 1]][0];
    if (coste_acum < coste_mejor) {
      coste_mejor = coste_acum;
      sol_mejor = sol;
    }
  } else {
    for (int c = 0; c < g.size(); c++) {
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

vector<int> viajante(const Matriz<int> &g) {
  vector<int> sol(g.size());
  vector<int> sol_mejor(g.size());
  vector<bool> visitadas(g.size(), false);
  sol[0] = 0;
  visitadas[0] = true;
  int coste_mejor = numeric_limits<int>::max();
  viajante(g, 1, sol, 0, visitadas, sol_mejor, coste_mejor);
  return sol_mejor;
}

int main() {
  Matriz<int> g = nuevo_grafo(8);
  pon_arista(g, 0, 1, 20);
  pon_arista(g, 0, 2, 10);
  pon_arista(g, 0, 6, 9);
  pon_arista(g, 1, 2, 15);
  pon_arista(g, 1, 3, 7);
  pon_arista(g, 2, 3, 9);
  pon_arista(g, 2, 4, 14);
  pon_arista(g, 2, 5, 15);
  pon_arista(g, 3, 4, 21);
  pon_arista(g, 3, 7, 10);
  pon_arista(g, 4, 7, 9);
  pon_arista(g, 5, 6, 7);
  pon_arista(g, 5, 7, 30);

  vector<int> sol = viajante(g);

  cout << sol[0];
  for (int i = 1; i < sol.size(); i++) {
    cout << ' ' << sol[i];
  }
  cout << '\n';

  cout << "Coste: " << coste(g, sol) << '\n';

  return 0;
}