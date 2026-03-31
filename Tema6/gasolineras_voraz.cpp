// ---------------------------
// Problema de las gasolineras
// ---------------------------

// Diseño de Algoritmos
// Grado en Matemáticas


#include <iostream>
#include <vector>

using namespace std;

int gasolineras(const vector<int> &t, int l) {
  int n = t.size();
  int num_paradas = 0;

  int distancia_restante = l;
  for (int i = 0; i < n; i++) {
    if (distancia_restante < t[i]) {
      num_paradas++;
      distancia_restante = l;
    }
    distancia_restante -= t[i];
  }

  return num_paradas;
}

int main() {
  cout << gasolineras({100, 30, 70, 50, 10, 90, 40, 30, 20, 50}, 150) << endl;
  return 0;
}

