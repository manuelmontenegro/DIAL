// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

#include <iostream>

using namespace std;

/* Tipo de datos para representar vectores columna */
struct VectorC {
  long elems[2];

  // Constructor. Permite inicializar vectores mediante la notación {x, y};
  VectorC(long x, long y) {
    elems[0] = x;
    elems[1] = y;
  }
};

/* Tipo de datos para representar matrices de 2x2 */
struct Matriz {
  long elems[2][2];

  // Constructor. Permite inicializar matrices mediante la notación {a00, a01, a10, a11};
  Matriz(long a00, long a01, long a10, long a11) {
    elems[0][0] = a00;
    elems[0][1] = a01;
    elems[1][0] = a10;
    elems[1][1] = a11;
  }
};


// Definimos multiplicación de matrices
Matriz operator*(const Matriz &a, const Matriz &b) {
  return {a.elems[0][0] * b.elems[0][0] + a.elems[0][1] * b.elems[1][0],
          a.elems[0][0] * b.elems[0][1] + a.elems[0][1] * b.elems[1][1],
          a.elems[1][0] * b.elems[0][0] + a.elems[1][1] * b.elems[1][0],
          a.elems[1][0] * b.elems[0][1] + a.elems[1][1] * b.elems[1][1]};
}


// Definimos multiplicación de una matriz por un vector columna
VectorC operator*(const Matriz &a, const VectorC &x) {
  return { a.elems[0][0] * x.elems[0] + a.elems[0][1] * x.elems[1],
           a.elems[1][0] * x.elems[0] + a.elems[1][1] * x.elems[1] };
}

// Cálculo de la potencia de una matriz
Matriz potencia(const Matriz &a, int n) {
  if (n == 0) {
    return {1, 0, 0, 1};
  } else if (n % 2 == 0) {
    Matriz p = potencia(a, n / 2);
    return p * p;
  } else {
    Matriz p = potencia(a, n / 2);
    return p * p * a;
  }
}

// Obtención del $n$-ésimo número de fibonacci utilizando la matriz
// ┌     ┐n   ┌   ┐   ┌          ┐ 
// │ 0 1 │    │ 0 │   │ fib(n)   │
// │     │  * │   │ = │          │
// │ 1 1 │    │ 1 │   │ fib(n+1) │
// └     ┘    └   ┘   └          ┘

long fibonacci(int n) {
  Matriz m = {0, 1, 1, 1};
  VectorC v = {0, 1};

  return (potencia(m, n) * v).elems[0];
}

int main() {
  for (int i = 0; i < 30; i++) {
    cout << fibonacci(i) << '\n';
  }
}