// -------------------------
// El problema de la mochila
// -------------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <iostream>
#include "matriz.h"

using namespace std;


// ---------------------------------------------
// Versión con programación dinámica descendente
// ---------------------------------------------

int mochila_pd_desc(const vector<int> &p, const vector<int> &v, int i, int j, matriz<int> &tabla) {
  if (tabla[i][j] == -1) {
    if (j == 0 || i == 0) {
      tabla[i][j] = 0;
    } else if (j < p[i - 1]) {
      tabla[i][j] = mochila_pd_desc(p, v, i - 1, j, tabla);
    } else {
      tabla[i][j] = max(
	  mochila_pd_desc(p, v, i - 1, j, tabla),
	  mochila_pd_desc(p, v, i - 1, j - p[i-1], tabla) + v[i-1]
      );
    }
  }
  return tabla[i][j];
}


int mochila_pd_desc(const vector<int> &p, const vector<int> &v, int m) {
  int n = p.size();
  matriz<int> tabla = crear_matriz(n + 1, m + 1, -1);
  return mochila_pd_desc(p, v, n, m, tabla);
}

// --------------------------------------------
// Versión con programación dinámica ascendente
// sin optimizar espacio
// --------------------------------------------

// Devuelve un par:
//  - La primera componente es el valor máximo obtenible
//  - La segunda componente indica los objetos que debemos meter en la mochila
//    para obtener ese valor

pair<int, vector<int>> mochila_pd_asc(const vector<int> &p, const vector<int> &v, int m) {
  int n = p.size();
  matriz<int> tabla = crear_matriz(n + 1, m + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      tabla[i][j] = j < p[i-1] ? tabla[i - 1][j] : max(tabla[i - 1][j], tabla[i - 1][j - p[i-1]] + v[i - 1]);
    }
  }

  vector<int> objetos_seleccionados;
  int i = n, j = m;
  while (i > 0 && j > 0) {
    if (tabla[i][j] == tabla[i-1][j]) {
      i--;
    } else {
      objetos_seleccionados.push_back(i-1);
      j -= p[i-1];
      i--;
    }
  }
  
  return {tabla[n][m], objetos_seleccionados};
}


int main() {
  vector<int> pesos = {2, 1, 3, 4};
  vector<int> valores = {60, 50, 70, 80};
  cout << mochila_pd_desc(pesos, valores, 5) << endl;
  auto [val, seleccion] = mochila_pd_asc(pesos, valores, 5);
  cout << val << endl;
  cout << "Objetos seleccionados:";
  for (int x : seleccion) { cout << ' ' << x; }
  cout << endl;
  return 0;
}

