// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del n-ésimo número de la sucesión de Fibonacci, utilizando
// recursión directa.

#include <iostream>

using namespace std;

long fib(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fib(n - 1) + fib(n - 2);
  }
}

int main() { cout << fib(45) << '\n'; }
