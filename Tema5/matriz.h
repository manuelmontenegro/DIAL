// ------------------------------------
// Definición de tipo de datos `matriz`
// ------------------------------------

// Diseño de Algoritmos
// Grado en Matemáticas

#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <vector>
#include <cassert>
#include <iostream>


/*
 * Definimos una matriz de N x M como un vector de vectores. Es decir, un
 * vector de N elementos (uno por fila), donde cada componente es un vector
 * con las M celdas de esa fila.
 */
template <typename T>
using matriz = std::vector<std::vector<T>>;



/*
 * Crea una matriz nueva de tamaño `num_filas` x `num_columnas`.
 * Inicializa todos los elementos de la matriz a `valor_inicial`.
 */
template <typename T>
matriz<T> crear_matriz(int num_filas, int num_columnas, const T &valor_inicial) {
  assert (num_filas > 0 && num_columnas > 0);
  return std::vector<std::vector<T>>(num_filas, std::vector<T>(num_columnas, valor_inicial));
}

/*
 * Devuelve el número de filas de la matriz
 */
template <typename T>
int num_filas(const matriz<T> &m) {
  return m.size();
}

/*
 * Devuelve el número de columnas de la matriz
 */
template <typename T>
int num_columnas(const matriz<T> &m) {
  return m[0].size();
}

/*
 * Sobrecarga el operador << para poder imprimir matrices.
 *
 * Si m es una matriz, podemos hacer cout << m; para imprimirla
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const matriz<T> &matriz) {
  int n = num_filas(matriz), m = num_columnas(matriz);
  for (int i = 0; i < n; i++) {
    out << matriz[i][0];
    for (int j = 1; j < m ; j++) {
      out << '\t' << matriz[i][j];
    }
    out << '\n';
  }
  return out;
}

#endif
