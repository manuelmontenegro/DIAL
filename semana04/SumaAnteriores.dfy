// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------


// Función que determina si un elemento de un vector es igual a la suma de los anteriores
// Realizamos inmersión de parámetro `s` por motivos de eficiencia.


include "../util/sum.dfy"

method SumaAnteriores(V: array<int>) returns (b: bool)
  ensures b <==> exists k | 0 <= k < V.Length :: V[k] == sum(V, 0, k)
{
  b := SumaAnterioresGen(V, 0, 0);
}


method SumaAnterioresGen(V: array<int>, i: int, s: int) returns (b: bool)
  requires 0 <= i <= V.Length && s == sum(V, 0, i)
  ensures b <==> exists k | i <= k < V.Length :: V[k] == sum(V, 0, k)
  decreases V.Length - i
{
  var b': bool;
  if i == V.Length {
    b := false;
  } else {
    b' := SumaAnterioresGen(V, i + 1, s + V[i]);
    b := b' || V[i] == s;
  }
}