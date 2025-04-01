// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de la mochila mediante vuelta atrás, con estimación optimista
// y suponiendo que tenemos varias unidades de cada tipo de objeto

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Extendemos los objetos con el número de unidades de cada objeto
struct Objeto {
  double peso;
  double valor;
  int num_unidades;
};

// Definimos una relación de orden entre objetos, según su densidad
bool compara_densidad(const Objeto &d1, const Objeto &d2) {
  return (d1.valor / d1.peso) > (d2.valor / d2.peso);
}

/*
  Calcula el valor máximo que puede obtenerse metiendo los objetos
  a partir del índice k en la mochila (k incluido), suponiendo que se pueden
  fraccionar.

  Se requiere que los objetos estén ordenados en orden creciente de
  densidad (es decir, en orden creciente de valor / peso).
*/
double mochila_real(const vector<Objeto> &objetos, int m, int k) {
  int n = objetos.size();

  double valor = 0.0;  // Valor acumulado en la mochila
  double restante = m; // Capacidad restante en la mochila

  // Recorremos el vector de objetos hasta encontrar con un
  // objeto del cual no podamos meter todas las unidades

  int i = k;
  while (i < n && objetos[i].num_unidades * objetos[i].peso <= restante) {
    // Actualizamos valor y peso de todas las unidades de ese objeto
    valor += objetos[i].num_unidades * objetos[i].valor;
    restante -= objetos[i].num_unidades * objetos[i].peso;
    // Pasamos al siguiente tipo objeto de menor densidad
    i++;
  }

  // Si todavía nos quedan objetos por meter y queda espacio en la mochila
  if (i < n && restante > 0) {
    // Calculamos cuantas unidades del objeto actual podemos introducir. Puede
    // ser un número con decimales, en el caso en que tenga que fraccionar
    // alguna unidad
    double fraccion = restante / (objetos[i].peso * objetos[i].num_unidades);
    // Aumentamos el valor proporcionalmente
    valor += (objetos[i].valor * objetos[i].num_unidades) * fraccion;
  }

  return valor;
}

// Cambiamos el vector de booleanos que representa una solución por un vector de
// enteros, porque ahora tenemos que indicar, para cada objeto, cuántas unidades
// llevamos en la mochila.
void mochila_entera(const vector<Objeto> &objetos, int m, int k,
                    vector<int> &sol, double peso_acum, double valor_acum,
                    vector<int> &sol_mejor, double &valor_mejor) {
  if (k == objetos.size()) {
    // Si ya hemos considerado todos los objetos, tenemos una solución
    // completa. La comparamos con la mejor obtenida hasta el momento y,
    // en su caso, actualizamos la mejor solución.
    if (valor_acum > valor_mejor) {
      sol_mejor = sol;
      valor_mejor = valor_acum;
    }
  } else {
    // Podemos meter entre 0 y num_unidades del objeto actual.
    for (int i = 0; i <= objetos[k].num_unidades; i++) {
        sol[k] = i;
        if (peso_acum + objetos[k].peso * i <= m) {
            int valor_estimado =
                valor_acum + i * objetos[k].valor + mochila_real(objetos, m - peso_acum - i * objetos[k].peso, k + 1);
            if (valor_estimado > valor_mejor) {
                mochila_entera(objetos, m, k + 1, sol, peso_acum + i * objetos[k].peso,
                    valor_acum + i * objetos[k].valor, sol_mejor, valor_mejor);
            }
        }
    }
  }
}

// Predondición: los objetos están ordenados de manera decreciente según su
// densidad (valor / peso).
pair<double, vector<int>> mochila_entera(const vector<Objeto> &objetos,
                                          int m) {
  vector<int> sol(objetos.size());
  vector<int> sol_mejor(objetos.size());
  double valor_mejor = -1;

  mochila_entera(objetos, m, 0, sol, 0.0, 0.0, sol_mejor, valor_mejor);

  return {valor_mejor, sol_mejor};
}

int main() {
  vector<Objeto> objetos = {{10, 20, 1}, {20, 30, 3}, {30, 66, 2}, {40, 40, 1}, {50, 60, 1}};
  sort(objetos.begin(), objetos.end(), compara_densidad);

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
  for (int b : sol) {
    cout << ' ' << b;
  }
  cout << '\n';
  return 0;
}