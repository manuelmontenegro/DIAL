// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

// Multiplicación de matrices encadenadas

// -----------------------------------------------------------
// Representación de matrices
// -----------------------------------------------------------

// Definimos una matriz como un vector de vectores
template <typename T>
using Matriz = vector<vector<T>>;

// Función auxiliar que devuelve una matriz de `num_filas` x `num_columnas`,
// donde todos los elementos de la matriz tienen el mismo `valor`.
template <typename T>
Matriz<T> nueva_matriz(int num_filas, int num_columnas, T valor) {
  return vector<vector<T>>(num_filas, vector<T>(num_columnas, valor));
}

template <typename T>
void imprimir_matriz(ostream &out, const Matriz<T> &m, int ancho) {
  // Si una de las dimensiones es 0, no hacemos nada
  if (m.size() == 0 || m[0].size() == 0) return;
  
  // Recorremos las filas
  for (const auto &fila : m) {
    // Para cada fila, imprimimos sus elementos
    for (const T &col : fila) {
      out << setw(ancho) << col;
    }
    out << '\n';
  }
}

// Tomamos como infinito el valor máximo permitido por un entero
constexpr int INFINITO = numeric_limits<int>::max();


// -----------------------------------------------------------
// Multiplicación de matrices encadenada
// -----------------------------------------------------------


// Suponemos `n` matrices A1, ..., An. Necesitamos un vector `ds` para
// almacenar las `n + 1` dimensiones, de modo que la matriz Ai tiene
// dimensión ds[i-1] x ds[i]. 

// Devuelve dos componentes:
//  - Número mínimo de multiplicaciones entre escalares
//  - Matriz que indica, para cada elemento [i][j], dónde debemos 'partir' la
//    cadena de multiplicaciones Ai ··· Aj para realizar las multiplicaciones
//    de manera óptima.

pair<int, Matriz<int>> mult_matrices_encadenadas(const vector<int> &ds) {
  // El número de matrices es el número de dimensiones menos uno.
  int n = ds.size() - 1;
  // mults[i][j] = número de multiplicaciones mínimo para multiplicar Ai ··· Aj
  Matriz<int> mults = nueva_matriz(n + 1, n + 1, 0);
  // result[i][j] = posición en la que debemos partir la multiplicación Ai ··· Aj
  // para llegar al óptimo mults[i][j]
  Matriz<int> result = nueva_matriz(n + 1, n + 1, 0);

  // Rellenamos la matriz por diagonales, de abajo a arriba.
  // La diagonal d = 1 es la que está por encima de la diagonal principal. Tiene n - 1 elementos
  // La diagonal d = 2 es la que está encima de esta. Tiene n - 2 elementos
  // etc.
  // La diagonal d = n - 1 es la que se compone de un único elemento (esq. sup. derecha). Tiene 1 elemento.

  for (int d = 1; d < n; d++) {
    // Para cada diagonal, recorremos sus elementos de arriba a abajo
    // La diagonal d tiene n - d elementos.
    for (int i = 1; i <= n - d; i++) {
      // Calculamos la columna correspondiente
      int j = d + i;
      mults[i][j] = INFINITO;
      for (int k = i; k < j; k++) {
        // Suponemos el corte (Ai ... Ak)(A{k+1} ... Aj)
        int m = mults[i][k] + mults[k + 1][j] + ds[i - 1] * ds[k] * ds[j];
        // Si con eso mejoramos el número de multiplicaciones, actualizamos
        // la matriz `result`
        if (m < mults[i][j]) {
          mults[i][j] = m;
          result[i][j] = k;
        }
      }
    }
  }


  return {mults[1][n], result};
}


// -----------------------------------------------------------
// Reconstrucción solución
// -----------------------------------------------------------

void imprime_solucion(int i, int j, const Matriz<int> &cortes) {
  if (i == j) {
    cout << "A" << i;
  } else {
    bool parentesis_izq = i < cortes[i][j];
    bool parentesis_der = cortes[i][j] + 1 < j;
    
    if (parentesis_izq) cout << "(";
    imprime_solucion(i, cortes[i][j], cortes);
    if (parentesis_izq) cout << ")";
    cout << ' ';
    if (parentesis_der) cout << "(";
    imprime_solucion(cortes[i][j] + 1, j, cortes);
    if (parentesis_der) cout << ")";
  }
}


int main() {
  vector<int> v = {13, 5, 89, 3, 34};
  auto [num_mults, cortes] = mult_matrices_encadenadas(v);
  cout << "Número de multiplicaciones mínimo: " << num_mults << '\n';
  imprime_solucion(1, cortes.size() - 1, cortes);
  cout << '\n';
  return 0;
}