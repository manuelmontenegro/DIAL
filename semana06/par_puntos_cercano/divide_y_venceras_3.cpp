// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmo DyV para encontrar el par de puntos más cercano en un vector. Tiene
// coste n log n.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

struct Punto {
  double x, y;
};

bool operator==(const Punto &p1, const Punto &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

ostream &operator<<(ostream &out, const Punto &p) {
  out << '(' << p.x << ", " << p.y << ')';
  return out;
}

bool comparar_x(const Punto &p1, const Punto &p2) { return p1.x < p2.x; }

bool comparar_y(const Punto &p1, const Punto &p2) { return p1.y < p2.y; }

struct Solucion {
  Punto p1, p2;
  double distancia;
};

// Calcula la distancia euclidiana entre dos puntos
double distancia(const Punto &p1, const Punto &p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Resuelve el problema por fuerza bruta
Solucion fuerza_bruta(const std::vector<Punto> &puntos, int c, int f) {
  assert(f - c >= 2);

  double dist_minima = numeric_limits<double>::infinity();
  Solucion sol;

  // Para cada punto 'puntos[i]'
  for (int i = c; i < f; ++i) {

    // Calculamos la distancia con los restantes 'puntos[j]'
    // y actualizamos la distancia mínima, en caso necesario
    for (int j = i + 1; j < f; ++j) {
      double d = distancia(puntos[i], puntos[j]);
      if (d < dist_minima) {
        dist_minima = d;
        sol = {puntos[i], puntos[j], d};
      }
    }
  }

  return sol;
}

// Ahora ya no ordena por coordenada y. Supone que el vector `franja` recibido
// como parámetro ya está ordenado.
Solucion par_puntos_franja(vector<Punto> &franja, double d) {
  assert(franja.size() >= 2);

  // Solución preliminar: los dos primeros puntos de la franja
  Solucion sol = {franja[0], franja[1], distancia(franja[0], franja[1])};

  // Recorremos cada punto i
  for (int i = 0; i < franja.size(); i++) {
    int j = i + 1;
    // Y comparamos ese punto con los j siguientes de la franja, siempre
    // que su coordenada y sea menor que el franja[i] + d
    while (j < franja.size() && franja[j].y < franja[i].y + d) {
      double dist = distancia(franja[i], franja[j]);
      if (dist < sol.distancia) {
        sol = {franja[i], franja[j], dist};
      }
      j++;
    }
  }

  return sol;
}

// Algoritmo de mezclas, similar al de Mergesort. Dadas dos listas de puntos
// ordenadas por coordenada y, devuelve otra lista ordenada por coordenada y.
vector<Punto> mezcla(const vector<Punto> &ps1, const vector<Punto> &ps2) {
  vector<Punto> result;

  int i = 0, j = 0;
  while (i < ps1.size() && j < ps2.size()) {
    Punto menor;
    if (ps1[i].y <= ps2[j].y) {
      result.push_back(ps1[i]);
      i++;
    } else {
      result.push_back(ps2[j]);
      j++;
    }
  }

  while (i < ps1.size()) {
    result.push_back(ps1[i]);
    i++;
  }

  while (j < ps2.size()) {
    result.push_back(ps2[j]);
    j++;
  }

  return result;
}

// Devuelve un par:
// - Primera componente: par de puntos más cercano..
// - Segunda componente: elementos del segmento puntos[c..f) ordenados de menor a mayor
pair<Solucion, vector<Punto>> divide_y_venceras(const vector<Punto> &puntos,
                                                int c, int f) {
  assert(f - c >= 2);
  if (f - c <= 3) {
    Solucion sol = fuerza_bruta(puntos, c, f);
    vector<Punto> result(puntos.begin() + c, puntos.begin() + f);
    sort(result.begin(), result.end(), comparar_y);
    return {sol, result};
  } else {
    int m = (c + f) / 2;
    double frontera_x = puntos[m].x;

    auto [sol1, ps1] = divide_y_venceras(puntos, c, m);
    auto [sol2, ps2] = divide_y_venceras(puntos, m, f);
    Solucion sol = sol1.distancia < sol2.distancia ? sol1 : sol2;

    vector<Punto> ps = mezcla(ps1, ps2);

    vector<Punto> franja;
    for (Punto p : ps) {
      if (abs(p.x - frontera_x) < sol.distancia)
        franja.push_back(p);
    }

    if (franja.size() >= 2) {
      Solucion sol_franja = par_puntos_franja(franja, sol.distancia);
      if (sol_franja.distancia < sol.distancia) {
        return {sol_franja, ps};
      } else {
        return {sol, ps};
      }
    } else {
      return {sol, ps};
    }
  }
}

Solucion par_puntos_cercano(vector<Punto> &puntos) {
  sort(puntos.begin(), puntos.end(), comparar_x);
  auto [sol, ps] = divide_y_venceras(puntos, 0, puntos.size());
  return sol;
}

// Mediante pruebas, comprobamos que el algoritmo DyV devuelve
// los mismos resultados que el algoritmo de fuerza bruta

constexpr int NUM_CASOS = 10000;
constexpr int NUM_PUNTOS = 100;

int main() {
  srand(3);
  for (int i = 0; i < NUM_CASOS; i++) {
    vector<Punto> puntos;
    for (int i = 0; i < NUM_PUNTOS; i++) {
      double x = (((double)rand()) / RAND_MAX) * 20.0 - 10.0;
      double y = (((double)rand()) / RAND_MAX) * 20.0 - 10.0;
      puntos.push_back({x, y});
    }

    cout << "-------------------------------\n";
    cout << "CASO " << i << '\n';
    cout << "-------------------------------\n";

    cout << "FUERZA BRUTA\n";
    Solucion sol = fuerza_bruta(puntos, 0, puntos.size());
    cout << "La distancia mínima entre dos puntos es: " << sol.distancia
         << '\n';
    cout << "Correspondiente a los puntos de coordenadas " << sol.p1 << " y "
         << sol.p2 << '\n';

    cout << "DIVIDE Y VENCERÁS\n";
    Solucion sol2 = par_puntos_cercano(puntos);
    cout << "La distancia mínima entre dos puntos es: " << sol2.distancia
         << '\n';
    cout << "Correspondiente a los puntos de coordenadas " << sol2.p1 << " y "
         << sol2.p2 << endl;

    assert(sol.distancia == sol2.distancia);
  }
  return 0;
}
