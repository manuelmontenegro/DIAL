// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del n-ésimo número de la sucesión de Fibonacci, utilizando
// programación dinámica ascendente.

// Cada posición del vector se rellena a partir de las dos anteriores.
// Por tanto, no necesitamos almacenar todo el vector; tan solo necesitamos
// las posiciones `i - 1` e `i - 2`, que se guardan en las variables `prev1`
// y `prev2` respectivamente.

#include <iostream>
#include <vector>

using namespace std;

long fib(int n) {
  // Lo siguiente solo funciona a partir de 1. Por tanto,
  // tratamos de manera especial el 0.
  if (n == 0)
    return 0;

  vector<int> v(n + 1, -1);
  int prev1 = 0;
  int prev2 = 1;
  for (int i = 2; i <= n; i++) {
    int act = prev1 + prev2;
    prev1 = prev2;
    prev2 = act;
  }
  return prev2;
}

int main() { cout << fib(45) << '\n'; }
