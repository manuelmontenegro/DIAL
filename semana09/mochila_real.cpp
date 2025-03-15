// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Solución al problema de la mochila real.

// Se ordenan los elementos según su densidad. Se van metiendo los elementos
// de mayor a menor densidad. El último elemento que no quepa entero se
// fracciona hasta completar la capacidad máxima de la mochila.

#include <algorithm>
#include <functional> // para greater<T>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Objeto {
  double peso;
  double valor;
};

struct Densidad {
  int id_objeto;
  double densidad;
};

// Definimos una relación de orden entre objetos de tipo `Densidad`
bool operator>(const Densidad &d1, const Densidad &d2) {
  return d1.densidad > d2.densidad;
}

/*
  Devuelve una tupla con:
  - El valor máximo acumulado en la mochila.
  - Las fracciones de cada objeto que hay que introducir en la mochila
*/
pair<double, vector<double>> mochila(const vector<Objeto> &objetos, int m) {
  int n = objetos.size();

  // Calculamos el vector de densidades y lo ordenamos de mayor a menor
  vector<Densidad> densidades(n);
  for (int i = 0; i < n; i++) {
    densidades[i].densidad = objetos[i].valor / objetos[i].peso;
    densidades[i].id_objeto = i;
  }

    // Utilizamos greater<Densidad>() para que se utilice el operador `>` y
  // se ordenen de mayor a menor.
  sort(densidades.begin(), densidades.end(), greater<Densidad>());

  double valor = 0.0;            // Valor acumulado en la mochila
  double restante = m;           // Capacidad restante en la mochila
  vector<double> result(n, 0.0); // Fracción de cada objeto introducido

  // Recorremos el vector de densidades hasta encontrar con un
  // objeto que no quepa completamente en el espacio restante.

  int i = 0;
  while (i < n && objetos[densidades[i].id_objeto].peso <= restante) {
    int id_objeto = densidades[i].id_objeto;
    // Introducimos el objeto actual en su totalidad
    result[id_objeto] = 1.0;
    // Actualizamos valor y peso totales
    valor += objetos[id_objeto].valor;
    restante -= objetos[id_objeto].peso;
    // Pasamos al siguiente objeto de menor densidad
    i++;
  }

  // Si todavía nos quedan objetos por meter y queda espacio en la mochila
  if (i < n && restante > 0) {
    int id_objeto = densidades[i].id_objeto;
    // Calculamos la fracción del objeto que hay que introducir
    double fraccion = restante / objetos[id_objeto].peso;
    // Introducimos esa fracción en la mochila
    result[id_objeto] = fraccion;
    // Aumentamos el valor proporcionalmente
    valor += objetos[id_objeto].valor * fraccion;
  }

  return {valor, result};
}

int main() {
  vector<Objeto> objetos = {{10, 20}, {20, 30}, {30, 66}, {40, 40}, {50, 60}};
  auto [valor_total, fracciones] = mochila(objetos, 100);
  cout << "Valor total: " << valor_total << '\n';
  cout << "Fracciones:";
  for (double f : fracciones) {
    cout << ' ' << f;
  }
  cout << '\n';
  return 0;
}