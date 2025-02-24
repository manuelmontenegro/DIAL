// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmo DyV para encontrar el par de puntos más cercano en un vector. Tiene
// coste cuadrático, porque utiliza el algoritmo de fuerza bruta para encontrar
// la mínima distancia entre los pares de puntos de la franja.

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

ostream &operator<<(ostream &out, const Punto &p) {
  out << '(' << p.x << ", " << p.y << ')';
  return out;
}

bool comparar_x(const Punto &p1, const Punto &p2) { return p1.x < p2.x; }

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
  assert(puntos.size() >= 2);

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

Solucion divide_y_venceras(const vector<Punto> &puntos, int c, int f) {
  assert(f - c >= 2);
  if (f - c <= 3) {
    return fuerza_bruta(puntos, c, f);
  } else {
    int m = (c + f) / 2;
    double frontera_x = puntos[m].x;

    Solucion sol1 = divide_y_venceras(puntos, c, m);
    Solucion sol2 = divide_y_venceras(puntos, m, f);
    Solucion sol = sol1.distancia < sol2.distancia ? sol1 : sol2;

    // Determinamos qué puntos pertenecen a la franja
    vector<Punto> franja;
    for (int i = c; i < f; i++) {
      if (abs(puntos[i].x - frontera_x) < sol.distancia)
        franja.push_back(puntos[i]);
    }

    if (franja.size() >= 2) {
      // Si hay dos puntos o más en la franja, determina el par de
      // puntos más cercano dentro de la franja.
      Solucion sol_franja = fuerza_bruta(franja, 0, franja.size());
      return sol_franja.distancia < sol.distancia ? sol_franja : sol;
    } else {
      return sol;
    }
  }
}

Solucion par_puntos_cercano(vector<Punto> &puntos) {
  sort(puntos.begin(), puntos.end(), comparar_x);
  return divide_y_venceras(puntos, 0, puntos.size());
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
