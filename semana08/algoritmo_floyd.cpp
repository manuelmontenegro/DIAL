// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <deque>

using namespace std;

// Cálculo de caminos mínimos entre todo par de vértices.

// -----------------------------------------------------------
// Representación de matrices
// -----------------------------------------------------------

// Definimos una matriz como un vector de vectores
template <typename T>
using Matriz = vector<vector<T>>;

// Función auxiliar que devuelve una matriz de `num_filas` x `num_columnas`,
// donde todos los elementos de la matriz tienen el mismo `valor`.
template <typename T>
Matriz<T> nueva_matriz(int num_filas, int num_columnas, T valor) {
  return vector<vector<T>>(num_filas, vector<T>(num_columnas, valor));
}

template <typename T>
void imprimir_matriz(ostream &out, const Matriz<T> &m, int ancho) {
  // Si una de las dimensiones es 0, no hacemos nada
  if (m.size() == 0 || m[0].size() == 0) return;
  
  // Recorremos las filas
  for (const auto &fila : m) {
    // Para cada fila, imprimimos sus elementos
    for (const T &col : fila) {
      out << setw(ancho) << col;
    }
    out << '\n';
  }
}

// -----------------------------------------------------------
// Representación de números enteros con infinito
// -----------------------------------------------------------

// Tomamos como infinito el valor máximo permitido por un entero
constexpr int INFINITO = numeric_limits<int>::max();

class EntInf {
public:
  // Construye a partir de un entero
  EntInf(int i) : n(i) { }
  // Construye infinito
  EntInf() : n(INFINITO) { }

  // Suma dos enteros
  EntInf operator+(const EntInf &otro) {
    // Si this u otro son infinitos, o al sumarlos habría desbordamiento, devolver infinito.
    if (this->n == INFINITO || otro.n == INFINITO || otro.n == INFINITO - this->n) {
      return EntInf();
    } else {
      return EntInf(this->n + otro.n);
    }
  }

  // Operadores relacionales: ==, !=, <
  bool operator==(const EntInf &otro) const {
    return this->n == otro.n;
  }

  bool operator!=(const EntInf &otro) const {
    return this->n != otro.n;
  }

  bool operator<(const EntInf &otro) const {
    return this->n < otro.n;
  }

  bool infinito() const { return this->n == INFINITO; }
  
  friend ostream & operator<<(ostream &out, const EntInf &e);
private:
  int n;
};

const EntInf Inf = EntInf();

// Imprime un EntInf por pantalla
ostream & operator<<(ostream &out, const EntInf &e) {
  if (e.n == INFINITO) {
    out << "∞";
  } else {
    out << e.n;
  }
  return out;
}

// -----------------------------------------------------------
// Representación de grafos y algoritmo de Floyd
// -----------------------------------------------------------


using Grafo = Matriz<EntInf>;

// Dado un grafo, devuelve la matriz c con el coste del camino mínimo
// entre todo par de vértices, y la matriz a con el anterior a cada vértice
//
// Devuelve false si el grafo contiene un ciclo de coste negativo, true en
// caso contrario.
bool caminos_floyd(const Grafo &g, Matriz<EntInf> &c, Matriz<int> &a) {
  int n = g.size();
  c = g;
  a = nueva_matriz(n, n, -1);

  // Inicialización de `c` y `a`
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && !g[i][j].infinito()) {
        a[i][j] = i;
      }
    }
  }

  // Calculamos las distintas matrices c^(k) y a^(k)
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        EntInf temp = c[i][k] + c[k][j];
        if (temp < c[i][j]) {
          c[i][j] = temp;
          a[i][j] = a[k][j];
        }
      }
      if (c[i][i] < 0) return false;
    }
  }
  return true;
}

// -----------------------------------------------------------
// Representación de caminos y reconstrucción de caminos
// -----------------------------------------------------------

using Camino = deque<int>;

Camino ir_de(int i, int j, const Matriz<int> &a) {
  Camino result;
  while (j != i) {
    result.push_front(j);
    j = a[i][j];
  }
  result.push_front(i);
  return result;
}

void imprimir_camino(ostream &out, const Camino &c) {
  bool primero = true;
  for (int i : c) {
    out << (primero ? "" : " -> ") << i;
    primero = false;
  }
}

// -----------------------------------------------------------
// Representación de caminos y reconstrucción de caminos
// -----------------------------------------------------------


int main() {
  Grafo g = nueva_matriz(5, 5, Inf);
  for (int i = 0; i < g.size(); i++) { g[i][i] = 0; }
  g[0][1] = 3; g[0][2] = 8; g[0][4] = -4;
  g[1][3] = 1; g[1][4] = 7;
  g[2][1] = 4;
  g[3][0] = 2; g[3][2] = -5;
  g[4][3] = 6;

  Matriz<EntInf> c;
  Matriz<int> a;

  caminos_floyd(g, c, a);

  imprimir_matriz(cout, c, 4);
  cout << "---\n";
  imprimir_matriz(cout, a, 4);

  cout << "\nCamino mínimo de 0 a 1: ";
  imprimir_camino(cout, ir_de(0, 1, a));
  cout << "\n";

  return 0;
}