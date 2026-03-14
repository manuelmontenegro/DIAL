// ---------------------------------
// El problema del cambio de monedas
// ---------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <iostream>
#include "matriz.h"
#include "enteros_inf.h"    // Ver Campus Virtual

using namespace std;

// ---------------------------------------------
// Versión con programación dinámica descendente
// ---------------------------------------------

int_inf cambio_pd_desc(const vector<int> &v, int i, int j, matriz<int_inf> &tabla) {
  if (tabla[i][j] == -1) {
    if (j == 0) {
      tabla[i][j] = 0;
    } else if (i == 0) {
      tabla[i][j] = Infinito;
    } else if (j < v[i - 1]) {
      tabla[i][j] = cambio_pd_desc(v, i - 1, j, tabla);
    } else {
      tabla[i][j] = min(cambio_pd_desc(v, i - 1, j, tabla), cambio_pd_desc(v, i, j - v[i - 1], tabla) + 1);
    }
  }
  return tabla[i][j];
}


int_inf cambio_pd_desc(const vector<int> &v, int c) {
  matriz<int_inf> tabla = crear_matriz(v.size() + 1, c + 1, int_inf(-1));
  return cambio_pd_desc(v, v.size(), c, tabla);
}

// --------------------------------------------
// Versión con programación dinámica ascendente
// --------------------------------------------

// Algoritmo de reconstrucción de la solución a partir de la tabla
// de programación dinámica. Ver `cambio_pd_asc` más adelante para ver cómo se
// construye esta tabla.
vector<int> reconstruir(const matriz<int_inf> &tabla, const vector<int> &v, int c) {
  int n = v.size();

  vector<int> monedas;

  int i = n, j = c;
  while (j > 0) {
    if (tabla[i][j] == tabla[i-1][j]) {
      i--;
    } else {
      monedas.push_back(v[i-1]);
      j -= v[i-1];
    }
  }

  return monedas;
}

// Construye la matriz de programación dinámica y reconstruye la solución
// óptima utilizando la función anterior.

pair<int_inf, vector<int>> cambio_pd_asc(const vector<int> &v, int c) {
  matriz<int_inf> tabla = crear_matriz<int_inf>(v.size() + 1, c + 1, 0);
  
  for (int j = 1; j <= c; j++) { tabla[0][j] = Infinito; }

  for (int i = 1; i <= v.size(); i++) {
    for (int j = 1; j <= c; j++) {
      tabla[i][j] = j < v[i-1] ? tabla[i - 1][j] : min(tabla[i - 1][j], tabla[i][j - v[i-1]] + 1);
    }
  }

  int_inf optimo = tabla[v.size()][c];
  vector<int> monedas;
  if (optimo != Infinito) {
    monedas = reconstruir(tabla, v, c);
  }
  return {optimo, monedas};
}

// Misma versión, pero optimizando espacio. Utiliza un vector en lugar de una matriz.
// En este caso, no se reconstruye la solución.

int_inf cambio_pd_asc_optimizado(const vector<int> &v, int c) {
  vector<int_inf> fila_actual(c + 1, 0);
  for (int j = 1; j <= c; j++) { fila_actual[j] = Infinito; }

  for (int i = 1; i <= v.size(); i++) {
    for (int j = 1; j <= c; j++) {
      fila_actual[j] = j < v[i-1] ? fila_actual[j] : min(fila_actual[j], fila_actual[j - v[i-1]] + 1);
    }
  }

  return fila_actual[c];
}



int main() {
  cout << cambio_pd_desc({1, 4, 6}, 9) << endl;
  auto [opt, monedas] = cambio_pd_asc({1, 4, 6}, 9);
  cout << opt << endl;
  cout << "Monedas necesarias:";
  for (int x : monedas) {
    cout << ' ' << x;
  }
  cout << endl;
  cout << cambio_pd_asc_optimizado({1, 4, 6}, 9) << endl;
  return 0;
}

