// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de la mochila implementado mediante ramificación y poda

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

struct Objeto {
  double peso;
  double valor;
};

// Definimos una relación de orden entre objetos, según su densidad
bool compara_densidad(const Objeto &d1, const Objeto &d2) {
  return (d1.valor / d1.peso) > (d2.valor / d2.peso);
}

// Representación de un nodo del árbol de exploración.
// Ojo! Al contrario que en el vídeo, aquí utilizamos intervalos
// semiabiertos en la solución. De este modo, la solución parcial sería
// sol[0..k)

struct Nodo {
  vector<bool> sol;
  int k;
  double peso_ac;
  double beneficio_ac;
  double estimacion_beneficio;

  bool operator<(const Nodo &otro) const {
    return estimacion_beneficio < otro.estimacion_beneficio;
  }
};



/*
  Calcula el valor máximo que puede obtenerse metiendo los objetos
  a partir del índice k en la mochila (k incluido), suponiendo que se pueden
  fraccionar.

  Se requiere que los objetos estén ordenados en orden creciente de
  densidad (es decir, en orden creciente de valor / peso).
*/
double mochila_real(const vector<Objeto> &objetos, double capacidad, const Nodo &nodo) {
    int n = objetos.size();
  
    double valor = nodo.beneficio_ac;  // Valor acumulado en la mochila
    double restante = capacidad - nodo.peso_ac; // Capacidad restante en la mochila
  
    // Recorremos el vector de objetos hasta encontrar con un
    // objeto que no quepa completamente en el espacio restante.
  
    int i = nodo.k;

    while (i < n && objetos[i].peso <= restante) {
      // Actualizamos valor y peso totales
      valor += objetos[i].valor;
      restante -= objetos[i].peso;
      // Pasamos al siguiente objeto de menor densidad
      i++;
    }
  
    // Si todavía nos quedan objetos por meter y queda espacio en la mochila
    if (i < n && restante > 0) {
      // Calculamos la fracción del objeto que hay que introducir
      double fraccion = restante / objetos[i].peso;
      // Aumentamos el valor proporcionalmente
      valor += objetos[i].valor * fraccion;
    }
  
    return valor;
  }
  

// Precondición: las tareas están ordenadas de manera ascendente por
// plazo máximo.
pair<vector<bool>, int> mochila_entera(const vector<Objeto> &objetos, double capacidad) {
  int n = objetos.size();

  priority_queue<Nodo, vector<Nodo>> cola;
  vector<bool> sol_mejor;
  double beneficio_mejor = -1;

  // Nodo raíz. Ninguna tarea realizada y ningún coste.
  Nodo x;
  x.sol = vector<bool>(n, false);
  x.k = 0;
  x.peso_ac = 0.0;
  x.beneficio_ac = 0.0;
  x.estimacion_beneficio = mochila_real(objetos, capacidad, x);

  cola.push(x);

  while (!cola.empty() && cola.top().estimacion_beneficio > beneficio_mejor) {
    Nodo y = cola.top();
    cola.pop();
    int k = y.k;

    // Caso 1. Introducimos el objeto en la mochila
    if (y.peso_ac + objetos[k].peso <= capacidad) {
      Nodo si;
      si.sol = y.sol;
      si.sol[k] = true;
      si.k = k + 1;
      si.peso_ac = y.peso_ac + objetos[k].peso;
      si.beneficio_ac = y.beneficio_ac + objetos[k].valor;
      si.estimacion_beneficio = y.estimacion_beneficio;
      if (si.k == n) {
          sol_mejor = si.sol;
          beneficio_mejor = si.beneficio_ac;
      } else {
          cola.push(si);
      }
    }

    // Caso 2. No realizamos la tarea k-ésima
    Nodo no;
    no.sol = y.sol;
    no.sol[k] = false;
    no.k = k + 1;
    no.peso_ac = y.peso_ac;
    no.beneficio_ac = y.beneficio_ac;
    no.estimacion_beneficio = mochila_real(objetos, capacidad, no);
    if (no.estimacion_beneficio > beneficio_mejor) {
      if (no.k == n) {
        sol_mejor = no.sol;
        beneficio_mejor = no.beneficio_ac;
      } else {
        cola.push(no);
      }
    }
  }

  return {sol_mejor, beneficio_mejor};
}

int main() {
  vector<Objeto> objetos = {{10, 20}, {20, 30}, {30, 66}, {40, 40}, {50, 60}};
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

  auto [sol, valor_total] = mochila_entera(objetos, 80);
  cout << "Valor total: " << valor_total << '\n';
  cout << "Objetos:";
  for (bool b : sol) {
    cout << ' ' << b;
  }
  cout << '\n';
  return 0;
}