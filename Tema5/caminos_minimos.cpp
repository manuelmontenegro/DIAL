// ------------------
// Algoritmo de Floyd
// ------------------

// Diseño de Algoritmos
// Grado en Matemáticas


#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#include "matriz.h"
#include "enteros_inf.h"

using namespace std;

using grafo = matriz<int_inf>;

grafo construir_grafo(int num_vertices, const vector<tuple<int, int, int>> &aristas) {
  grafo result = crear_matriz(num_vertices, num_vertices, Infinito);
  for (int i = 0; i < num_vertices; i++) {
    result[i][i] = 0;
  }
  for (auto [i, j, v] : aristas) {
    result[i][j] = v;
  }
  return result;
}

// --------------------------------------------
// Versión con programación dinámica ascendente
// --------------------------------------------

matriz<int_inf> caminos_minimos(const grafo &g) {
  int n = num_filas(g);
  matriz<int_inf> actual = g;

  for (int k = 1; k <= n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	actual[i][j] = min(actual[i][j], actual[i][k-1] + actual[k-1][j]);
      }
    }
  }
  return actual;
}

// --------------------------------------------------
// Versión con programación dinámica ascendente
//
// Devuelve la información necesaria para reconstruir
// los caminos mínimos.
// --------------------------------------------------

// Devuelve un par:
//   - Primera componente: coste del camino mínimo entre cada par de vértices.
//   - Segunda componente: vértice anterior al destino en cada camino mínimo.

pair<matriz<int_inf>, matriz<int>> caminos_minimos_reconstruir(const grafo &g) {
  int n = num_filas(g);

  // Calculamos matrices cuando k = 0
  matriz<int_inf> actual = g;
  matriz<int> anterior = crear_matriz(n, n, -1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && g[i][j] != Infinito) {
	anterior[i][j] = i;
      }
    }
  }

  // Ahora calculamos las matrices para k > 0
  for (int k = 1; k <= n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	if (actual[i][j] > actual[i][k-1] + actual[k-1][j]) {
	  actual[i][j] = actual[i][k-1] + actual[k-1][j];
	  anterior[i][j] = anterior[k-1][j];
	}
      }
    }
  }
  return {actual, anterior};
}

// A partir de la segunda componente devuelta por el algoritmo anterior,
// la siguiente función reconstruye el camino mínimo entre el par de vértices
// i, j pasado como parámetro.

vector<int> reconstruir_camino(int i, int j, const matriz<int> &anterior) {
  vector<int> result;
  result.push_back(j);
  while (j != i) {
    j = anterior[i][j];
    result.push_back(j);
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  grafo g = construir_grafo(5, {{0, 2, 1}, {0, 3, 7}, {1, 4, 4}, {1, 3, 4}, {2, 3, 4}, {3, 4, -1}});
  auto [min, ant] = caminos_minimos_reconstruir(g);
  cout << "Matriz de costeGen:" << endl;
  cout << min << endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (min[i][j] != Infinito) {
	cout << "Camino mínimo entre " << i << " y " << j << " de coste " << min[i][j] << ":";
	for (int x : reconstruir_camino(i, j, ant)) {
	  cout << ' ' << x;
	}
	cout << endl;
      } else {
	cout << "No hay camino desde " << i << " hasta " << j << "\n";
      }
    }
  }
  return 0;
}
