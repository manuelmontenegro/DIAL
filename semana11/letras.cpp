// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de coloreado de grafos mediante vuelta atrás
// Imprime todas las soluciones

#include "Grafo.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void imprimir_solucion(const vector<char> &sol) {
  string str(sol.begin(), sol.end());
  cout << str << '\n';
}

bool es_factible(const vector<char> &sol, int k, char l) {
  bool factible = true;
  for (int i = 0; i < k && factible; i++) {
    if (sol[i] == l) {
      factible = false;
    }
  }
  return factible;
}

void letras(const vector<char> &ls, int longitud, int k, vector<char> &sol) {
  if (k == longitud) {
    imprimir_solucion(sol);
  } else {
    for (char l : ls) {
      if (es_factible(sol, k, l)) {
        sol[k] = l;
        letras(ls, longitud, k + 1, sol);
      }
    }
  }
}

void letras(const vector<char> &ls, int longitud) {
  vector<char> sol(longitud);
  letras(ls, longitud, 0, sol);
}

int main() {
  vector<char> ls = {'a', 'b', 'c', 'd'};
  letras(ls, 3);
}