// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmos de recorridos de vectores

include "../util/max.dfy"

// Ejemplo 1: búsqueda lineal

method buscarElem(V: array<int>, x: int) returns (k: int)
  ensures 0 <= k <= V.Length && (k < V.Length ==> V[k] == x) && (forall j | 0 <= j < k :: V[j] != x)
{
  k := 0;
  while k < V.Length && V[k] != x
    invariant 0 <= k <= V.Length && forall j | 0 <= j < k :: V[j] != x
    decreases V.Length - k
  { k := k + 1; }
}


// Ejemplo 2: máximo de un array de enteros

method maximo(V: array<int>) returns (m: int)
  requires V.Length >= 1
  ensures m == maxArray(V, 0, V.Length)
{
  var i: int;
  i := 1; m := V[0];
  while i != V.Length
    invariant 1 <= i <= V.Length && m == maxArray(V, 0, i)
    decreases V.Length - i
  {
    m := max(m, V[i]);
    i := i + 1;
  }
}

