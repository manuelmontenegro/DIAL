// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del n-ésimo número de la sucesión de Fibonacci, utilizando
// programación dinámica descendente.

// En este caso, tenemos un vector tal que v[i] = fib(i)


#include <iostream>
#include <vector>

using namespace std;

long fib(int n, vector<int> &v) {
  if (v[n] != -1) {
    return v[n];
  } else {
    if (n == 0) {
      v[n] = 0;
    } else if (n == 1) {
      v[n] = 1;
    } else {
      v[n] = fib(n - 1, v) + fib(n - 2, v);
    }
    return v[n];
  }
}

long fib(int n) {
  vector<int> v(n + 1, -1);
  return fib(n, v);
}

int main() { cout << fib(45) << '\n'; }
