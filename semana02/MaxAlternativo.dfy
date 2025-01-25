// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Versión alternativa de la función `maximo`, pero recorriendo el vector de derecha
// a izquierda

include "../util/max.dfy"

method maximo(V: array<int>) returns (m: int)
  requires V.Length >= 1
  ensures m == maxArray(V, 0, V.Length)
{
  var i: int;
  i := V.Length - 1; m := V[V.Length - 1];
  while i != 0
    invariant 0 <= i <= V.Length - 1 && m == maxArray(V, i, V.Length)
    decreases i
  {
    m := max(m, V[i - 1]);
    i := i - 1;

    // La definición recursiva de `maxArray` decompone el vector por la derecha.
    // Tenemos que usar el lema (definido en ../util/max.dfy) de que es lo mismo
    // que descomponer max por la izquierda.
    assert maxArray(V, i, V.Length) == max(V[i], maxArray(V, i + 1, V.Length)) by {
      maxArrayDecompLeft(V, i, V.Length);
    }
  }
}

