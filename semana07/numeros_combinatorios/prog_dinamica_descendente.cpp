// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del número combinatorio "n sobre k" utilizando programación
// dinámica descendente.

#include <iostream>
#include <vector>

using namespace std;

// Definimos una matriz como un vector de vectores
template <typename T>
using Matriz = vector<vector<T>>;

// Función auxiliar que devuelve una matriz de `num_filas` x `num_columnas`,
// donde todos los elementos de la matriz tienen el mismo `valor`.
template <typename T>
Matriz<T> nueva_matriz(int num_filas, int num_columnas, T valor) {
  return vector<vector<T>>(num_filas, vector<T>(num_columnas, valor));
}

// Calcula "n sobre k" rellenando la matriz `m`, que es un parámetro de E/S.
long num_combinatorio(int n, int k, Matriz<long> &m) {
  if (m[n][k] != -1) {
    return m[n][k];
  } else {
    if (k == 0 || k == n) {
      m[n][k] = 1;
    } else {
      m[n][k] = num_combinatorio(n - 1, k - 1, m) + num_combinatorio(n - 1, k, m);
    }
    return m[n][k];
  }
}

// Calcula "n sobre k" mediante la función anterior
long num_combinatorio(int n, int k) {
  Matriz<long> m = nueva_matriz<long>(n + 1, k + 1, -1);
  return num_combinatorio(n, k, m);
}


int main() {  
  // La versión con recursión no era capaz de obtener "45 sobre 10"
  // de manera eficiente. ¿Y ahora?
	cout << num_combinatorio(45, 10) << '\n';
  return 0;
}