// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Solución al problema de la ruta en carretera

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, vector<bool>> gasolineras(const vector<int> &d, int k) {
  // Inicialmente ponemos todas las paradas a `false`
  vector<bool> result(d.size() - 1, false);
  // Número de paradas realizadas para repostar
  int num_paradas = 0;
  // Distancia recorrida desde la última parada
  int distancia = 0;

  for (int i = 0; i < d.size(); i++) {
    // Si llegamos a la siguiente parada sin repostar, avanzamos
    // Si no, repostamos
    if (distancia + d[i] <= k) {
      distancia += d[i];
    } else {
      result[i - 1] = true;
      num_paradas++;
      distancia = d[i];
    }
  }

  return {num_paradas, result};
}

int main() {
  vector<int> distancias = {10, 15, 15, 7, 3, 9, 4, 15, 12};
  auto [num_paradas, paradas] = gasolineras(distancias, 30);
  cout << "Número de paradas: " << num_paradas << '\n';
  cout << "Paradas en gasolineras:";
  for (int x : paradas) {
    cout << ' ' << x;
  }
  cout << '\n';
  return 0;
}