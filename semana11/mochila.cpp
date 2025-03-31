// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de la mochila mediante vuelta atrás.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Objeto {
  double peso;
  double valor;
};

void mochila_entera(const vector<Objeto> &objetos, int m, int k,
                    vector<bool> &sol, double peso_acum, double valor_acum,
                    vector<bool> &sol_mejor, double &valor_mejor) {
  if (k == objetos.size()) {
    // Si ya hemos considerado todos los objetos, tenemos una solución
    // completa. La comparamos con la mejor obtenida hasta el momento y,
    // en su caso, actualizamos la mejor solución.
    if (valor_acum > valor_mejor) {
      sol_mejor = sol;
      valor_mejor = valor_acum;
    }
  } else {
    // Opción 1. Meter objeto k en la mochila
    // --------------------------------------
    sol[k] = true;
    if (peso_acum + objetos[k].peso <= m) {
      mochila_entera(objetos, m, k + 1, sol, peso_acum + objetos[k].peso,
                     valor_acum + objetos[k].valor, sol_mejor, valor_mejor);
    }

    // Opción 2. No meter objeto k en la mochila
    // -----------------------------------------

    sol[k] = false;
    mochila_entera(objetos, m, k + 1, sol, peso_acum, valor_acum, sol_mejor,
                   valor_mejor);
  }
}

pair<double, vector<bool>> mochila_entera(const vector<Objeto> &objetos,
                                          int m) {
  vector<bool> sol(objetos.size());
  vector<bool> sol_mejor(objetos.size());
  double valor_mejor = -1;

  mochila_entera(objetos, m, 0, sol, 0.0, 0.0, sol_mejor, valor_mejor);

  return {valor_mejor, sol_mejor};
}

int main() {
  vector<Objeto> objetos = {{10, 20}, {20, 30}, {30, 66}, {40, 40}, {50, 60}};

  cout << "Objeto: ";
  for (int i = 0; i < objetos.size(); i++) {
    cout << setw(5) << i;
  }
  cout << '\n';

  cout << "Valor:  ";
  for (const Objeto &o : objetos) {
    cout << setw(5) << o.valor;
  }
  cout << '\n';

  cout << "Peso:   ";
  for (const Objeto &o : objetos) {
    cout << setw(5) << o.peso;
  }
  cout << "\n\n";

  auto [valor_total, sol] = mochila_entera(objetos, 80);
  cout << "Valor total: " << valor_total << '\n';
  cout << "Objetos:";
  for (bool b : sol) {
    cout << ' ' << b;
  }
  cout << '\n';
  return 0;
}