// ---------------------
// Números combinatorios
// ---------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#include <iostream>
#include "matriz.h"

using namespace std;

// ------------------------------------------
// Función con recursión directa. Ineficiente
// ------------------------------------------

int comb(int n, int k) {
  if (k == 0) {
    return 1;
  } else if (n == 0) {
    return 0;
  } else {
    return comb(n - 1, k - 1) + comb(n - 1, k);
  }
}

// ---------------------------------------------
// Versión con programación dinámica descendente
// ---------------------------------------------

int comb_pd_desc(int n, int k, matriz<int> &tabla) {
  if (tabla[n][k] == -1) {
    if (k == 0) {
      tabla[n][k] = 1;
    } else if (n == 0) {
      tabla[n][k] = 0;
    } else {
      tabla[n][k] = comb_pd_desc(n - 1, k - 1, tabla) + comb_pd_desc(n - 1, k, tabla);
    }
  }
  return tabla[n][k];
}

int comb_pd_desc(int n, int k) {
  matriz<int> tabla = crear_matriz(n + 1, k + 1, -1);
  return comb_pd_desc(n, k, tabla);
}

// --------------------------------------------
// Versión con programación dinámica ascendente
// --------------------------------------------

int comb_pd_asc(int n, int k) {  
  matriz<int> tabla = crear_matriz(n + 1, k + 1, -1);
  
  // Empezamos por comb(0, 0) = 1
  tabla[0][0] = 1;

  // Sabemos que comb(0, j) = 0 para todo j > 0
  for (int j = 1; j <= k; j++) {
    tabla[0][j] = 0;
  }

  for (int i = 1; i <= n; i++) {
    tabla[i][0] = 1;
    for (int j = 1; j <= k; j++) {
      tabla[i][j] = tabla[i - 1][j - 1] + tabla[i - 1][j];
    }
  }

  return tabla[n][k];
}

// --------------------------------------------
// Versión con programación dinámica ascendente
// con optimización de espacio en memoria.
// --------------------------------------------

int comb_pd_asc_optimizacion(int n, int k) {  
  // Inicializamos fila 0
  vector<int> actual = vector<int>(k + 1, 0);
  actual[0] = 1;

  // Rellenamos el resto de filas, sobreescribiendo
  // el vector `actual`
  for (int i = 1; i <= n; i++) {
    for (int j = k; j >= 1; j--) {    // Recorremos el vector de derecha a izquierda
      actual[j] = actual[j - 1] + actual[j];
    }
  }

  // Tras el bucle, el vector `actual` contiene la última fila de la
  // matriz. Devolvemos la última componente.
  return actual[k];
}



int main() {
  cout << comb(5, 3) << endl;
  cout << comb(24, 18) << endl;
  cout << comb_pd_desc(5, 3) << endl;
  cout << comb_pd_desc(24, 18) << endl;
  cout << comb_pd_asc(5, 3) << endl;
  cout << comb_pd_asc(24, 18) << endl;
  cout << comb_pd_asc_optimizacion(5, 3) << endl;
  cout << comb_pd_asc_optimizacion(24, 18) << endl;
}
