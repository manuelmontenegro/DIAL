// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Cálculo del número combinatorio "n sobre k" utilizando una función
// recursiva que imita la recurrencia dada.

#include <iostream>

using namespace std;

long num_combinatorio(int n, int k) {
  if (k == 0 || k == n) {
    return 1;
  } else {
    return num_combinatorio(n - 1, k - 1) + num_combinatorio(n - 1, k);
  }
}

int main() {
  // Comenta y descomenta cada una de las siguientes llamadas para ver
  // el tiempo de ejecución

	cout << num_combinatorio(35, 10) << '\n';	
  // cout << num_combinatorio(40, 10) << '\n';
	// cout << num_combinatorio(45, 20) << '\n';

  return 0;
}