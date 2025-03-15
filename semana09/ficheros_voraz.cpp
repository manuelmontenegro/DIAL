// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Solución al problema de los ficheros mediante un algoritmo voraz.

// Supone que los ficheros están ordenados de menor a mayor tamaño
// y los va seleccionando de izquierda a derecha mientras quepan en el
// disco de capacidad d.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Precondición: el vector está ordenado
vector<bool> ficheros(const vector<int> &s, int d) {
  int n = s.size();

  vector<bool> result(n, false);

  int capacidad_restante = d;
  int i = 0;

  // Mientras el fichero i-ésimo quepa en el disco
  while (i < n && s[i] <= capacidad_restante) {
    // Lo movemos al disco
    result[i] = true;
    // Decrementamos la capacidad
    capacidad_restante -= s[i];
    // Pasamos al siguiente fichero
    i++;
  }

  return result;
}

int main() {
  vector<int> fichs = {5, 10, 15, 20, 30};

  for (bool b : ficheros(fichs, 40))
    cout << b << ' ';

  cout << '\n';
  return 0;
}