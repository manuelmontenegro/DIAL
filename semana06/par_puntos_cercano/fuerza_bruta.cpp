// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmo de fuerza bruta para encontrar el par de puntos más cercano
// en un vector. Tiene coste cuadrático con respecto al número de puntos
// de entrada.

#include <cassert>
#include <algorithm>
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

struct Solucion {
  Punto p1, p2;
  double distancia;
};

// Calcula la distancia euclidiana entre dos puntos
double distancia(const Punto &p1, const Punto &p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Resuelve el problema por fuerza bruta
Solucion fuerza_bruta(const std::vector<Punto> &puntos) {
  assert(puntos.size() >= 2);

  double dist_minima = numeric_limits<double>::infinity();
  Solucion sol;

  // Para cada punto 'puntos[i]'
  for (int i = 0; i < puntos.size(); ++i) {

    // Calculamos la distancia con los restantes 'puntos[j]'
    // y actualizamos la distancia mínima, en caso necesario
    for (int j = i + 1; j < puntos.size(); ++j) {
      double d = distancia(puntos[i], puntos[j]);
      if (d < dist_minima) {
        dist_minima = d;
        sol = {puntos[i], puntos[j], d};
      }
    }
  }

  return sol;
}

bool comparar_x(const Punto &p1, const Punto &p2) { return p1.x < p2.x; }

int main() {
  srand(3);
  vector<Punto> puntos;
  for (int i = 0; i < 100; i++) {
    double x = (((double)rand()) / RAND_MAX) * 2.0 - 1.0;
    double y = (((double)rand()) / RAND_MAX) * 20.0 - 10.0;
    puntos.push_back({x, y});
  }
  sort(puntos.begin(), puntos.end(), comparar_x);

  Solucion sol = fuerza_bruta(puntos);
  cout << "La distancia mínima entre dos puntos es: " << sol.distancia << '\n';
  cout << "correspondiente a los puntos de coordenadas " << sol.p1 << " y "
       << sol.p2 << '\n';
  return 0;
}
