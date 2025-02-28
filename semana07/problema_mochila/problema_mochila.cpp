// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Problema de la mochila (versión ascendente)

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T> using Matriz = vector<vector<T>>;

template <typename T>
Matriz<T> nueva_matriz(int num_filas, int num_columnas, T valor) {
  return vector<vector<T>>(num_filas, vector<T>(num_columnas, valor));
}

struct objeto {
  string nombre;
  int peso;
  double valor;
};

void rellenar_matriz(const vector<objeto> &objs, int peso_max, Matriz<double> &m) {
  int num_elems = objs.size();
  for (int i = 1; i <= num_elems; i++) {
    for (int j = 1; j <= peso_max; j++) {
      if (objs[i - 1].peso > j) {
        m[i][j] = m[i - 1][j];
      } else {
        m[i][j] = max(m[i - 1][j], m[i - 1][j - objs[i - 1].peso] + objs[i - 1].valor);
      }
    }
  }
}

vector<objeto> reconstruir_solucion(const vector<objeto> &objs, const Matriz<double> &m) {
  int i = m.size() - 1;
  int j = m[0].size() - 1;
  
  vector<objeto> result;

  while (i > 0 && j > 0) {
    if (m[i][j] == m[i - 1][j - objs[i - 1].peso] + objs[i - 1].valor) {
      result.push_back(objs[i - 1]);
      j -= objs[i - 1].peso;
    }
    i--;
  }

  return result;
}

pair<double, vector<objeto>> problema_mochila(const vector<objeto> &objs, int peso_max) {
  int num_elems = objs.size();
  Matriz<double> m = nueva_matriz(num_elems + 1, peso_max + 1, 0.0);
  rellenar_matriz(objs, peso_max, m);
  
  for (int i = 0; i <= num_elems; i++) {
    cout <<'|';
    for (int j = 0; j <= peso_max; j++) {
      cout << setw(5) << m[i][j] << '|';
    }
    cout << '\n';
  }

  vector<objeto> sol = reconstruir_solucion(objs, m);

  return {m[num_elems][peso_max], sol};
}

int main() {
  vector<objeto> vs = {{"Cámara", 4, 60.0}, {"Tablet", 1, 50.0}, {"Portátil", 3, 70.0}, {"Dron", 4, 80.0}};
  auto [valor_max, objs] = problema_mochila(vs, 5);

  cout << "Valor máximo: " << valor_max << '\n';
  cout << "Objetos:";
  for (const objeto &o: objs) {
    cout << ' ' << o.nombre;
  }
  cout << '\n';
}