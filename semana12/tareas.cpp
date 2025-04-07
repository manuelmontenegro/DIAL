// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de tareas con plazo, tiempo y coste

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Tarea {
  string id;
  int plazo;
  int duracion;
  int coste;

  bool operator<(const Tarea &otra) const { return plazo < otra.plazo; }
};

// Representación de un nodo del árbol de exploración.
// Ojo! Al contrario que en el vídeo, aquí utilizamos intervalos
// semiabiertos en la solución. De este modo, la solución parcial sería
// sol[0..k)

struct Nodo {
  vector<bool> sol;
  int k;
  double tiempo_ac;
  double coste_ac;
  double estimacion_coste;

  bool operator>(const Nodo &otro) const {
    return estimacion_coste > otro.estimacion_coste;
  }
};

double estimacion_optimista(const vector<Tarea> &ts, const Nodo &nodo) {
  double result = nodo.coste_ac;

  for (int i = nodo.k; i < ts.size(); i++) {
    // Si la tarea se va a realizar fuera de su plazo, añadimos
    // su penalización al resultado.
    if (nodo.tiempo_ac + ts[i].duracion > ts[i].plazo) {
      result += ts[i].coste;
    }
  }

  return result;
}

// Precondición: las tareas están ordenadas de manera ascendente por
// plazo máximo.
pair<vector<bool>, int> planificar_tareas(const vector<Tarea> &ts) {
  int n = ts.size();

  priority_queue<Nodo, vector<Nodo>, std::greater<Nodo>> cola;
  vector<bool> sol_mejor;
  double coste_mejor = numeric_limits<double>::infinity();

  // Nodo raíz. Ninguna tarea realizada y ningún coste.
  Nodo x;
  x.sol = vector<bool>(n, false);
  x.k = 0;
  x.tiempo_ac = 0;
  x.coste_ac = 0;
  x.estimacion_coste = estimacion_optimista(ts, x);

  cola.push(x);

  while (!cola.empty() && cola.top().estimacion_coste < coste_mejor) {
    Nodo y = cola.top();
    cola.pop();
    int k = y.k;

    // Caso 1. Realizamos la tarea k-ésima
    if (y.tiempo_ac + ts[k].duracion <= ts[k].plazo) {
      Nodo si;
      si.sol = y.sol;
      si.sol[k] = true;
      si.k = k + 1;
      si.tiempo_ac = y.tiempo_ac + ts[k].duracion;
      si.coste_ac = y.coste_ac;
      si.estimacion_coste = estimacion_optimista(ts, si);
      if (si.estimacion_coste < coste_mejor) {
        if (si.k == n) {
          sol_mejor = si.sol;
          coste_mejor = si.coste_ac;
        } else {
          cola.push(si);
        }
      }
    }

    // Caso 2. No realizamos la tarea k-ésima
    Nodo no;
    no.sol = y.sol;
    no.sol[k] = false;
    no.k = k + 1;
    no.tiempo_ac = y.tiempo_ac;
    no.coste_ac = y.coste_ac + ts[k].coste;
    no.estimacion_coste = estimacion_optimista(ts, no);
    if (no.estimacion_coste < coste_mejor) {
      if (no.k == n) {
        sol_mejor = no.sol;
        coste_mejor = no.coste_ac;
      } else {
        cola.push(no);
      }
    }
  }

  return {sol_mejor, coste_mejor};
}

int main() {
  // ID, plazo, duracion, coste
  vector<Tarea> ts = {{"A", 10, 3, 10}, {"B", 6, 3, 15}, {"C", 1, 1, 20},
                      {"D", 6, 4, 25},  {"E", 7, 3, 30}, {"F", 3, 3, 35},
                      {"G", 6, 2, 40}};
  sort(ts.begin(), ts.end());

  auto [sol, coste] = planificar_tareas(ts);

  cout << "Coste total: " << coste << '\n';
  cout << "Tareas realizadas:";
  for (int i = 0; i < sol.size(); i++) {
    if (sol[i]) {
      cout << ' ' << ts[i].id;
    }
  }
  cout << '\n';
}
