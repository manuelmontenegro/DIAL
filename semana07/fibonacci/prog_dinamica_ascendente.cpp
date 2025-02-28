// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del n-ésimo número de la sucesión de Fibonacci, utilizando
// programación dinámica ascendente.

// En este caso, rellenamos un vector tal que v[i] = fib(i).

#include <iostream>
#include <vector>

using namespace std;

long fib(int n) {
  vector<int> v(n + 1, -1);
  v[0] = 0;
  v[1] = 1;
  for (int i = 2; i <= n; i++) {
    v[i] = v[i - 1] + v[i - 2];
  }
  return v[n];
}

int main() { cout << fib(45) << '\n'; }
