// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmo de búsqueda binaria en un vector

method BusquedaBinaria(V: array<int>, x: int) returns (k: int)
  requires forall i, j | 0 <= i <= j < V.Length :: V[i] <= V[j]
  ensures 0 <= k <= V.Length
          && (forall i | 0 <= i < k :: V[i] < x)
          && (forall i | k <= i < V.Length :: V[i] >= x)
{
  k := BusquedaBinariaGen(V, x, 0, V.Length);
}

method BusquedaBinariaGen(V: array<int>, x: int, c: int, f: int) returns (k: int)
  requires forall i, j | 0 <= i <= j < V.Length :: V[i] <= V[j]
  requires 0 <= c <= f <= V.Length
  ensures c <= k <= f
          && (forall i | c <= i < k :: V[i] < x)
          && (forall i | k <= i < f :: V[i] >= x)
  decreases f - c
{
  if c == f {
    k := c;
  } else {
    var m := (c + f) / 2;
    if V[m] < x {
      k := BusquedaBinariaGen(V, x, m + 1, f);
    } else {
      k := BusquedaBinariaGen(V, x, c, m);
    }
  }
}

