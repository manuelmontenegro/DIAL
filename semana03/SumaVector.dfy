// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Técnicas de inmersión para el desarrollo de un algoritmo que
// calcule la suma de elementos de un vector.

include "../util/sum.dfy"

// 1. Inmersión no final, recorriendo el vector de derecha a izquierda

method sumaVector1(V: array<int>) returns (s: int)
  ensures s == sum(V, 0, V.Length)
{
  s := sumaVectorGen(V, 0);
}

method sumaVectorGen(V: array<int>, j: int) returns (s: int)
  requires 0 <= j <= V.Length
  ensures s == sum(V, j, V.Length)
  decreases V.Length - j
{
  if j == V.Length {
    s := 0;
  } else {
    var s' := sumaVectorGen(V, j + 1);
    s := s' + V[j];
    assert sum(V, j, V.Length) == V[j] + sum(V, j + 1, V.Length) by { sumaPorLaIzquierda(V, j, V.Length); }
  }
}


// 2. Inmersión no final, recorriendo el vector de izquierda a derecha


method sumaVector2(V: array<int>) returns (s: int)
  ensures s == sum(V, 0, V.Length)
{
  s := sumaVectorGen2(V, V.Length);
}


method sumaVectorGen2(V: array<int>, j: int) returns (s: int)
  requires 0 <= j <= V.Length
  ensures s == sum(V, 0, j)
  decreases j
{
  if j == 0 {
    s := 0;
  } else {
    var s' := sumaVectorGen2(V, j - 1);
    s := s' + V[j - 1];
  }
}

// 3. Inmersión no final, partiendo el segmento por la mitad en cada
//    llamada recursiva

method sumaVector3(V: array<int>) returns (s: int)
  ensures s == sum(V, 0, V.Length)
{
  s := sumaVectorGen3(V, 0, V.Length);
}


method sumaVectorGen3(V: array<int>, j: int, k: int) returns (s: int)
  requires 0 <= j <= k <= V.Length
  ensures s == sum(V, j, k)
  decreases k - j
{
  if j == k {
    s := 0;
  } else if j + 1 == k {
    s := V[j];
  } else {
    var m := (j + k) / 2;
    var s1 := sumaVectorGen3(V, j, m);
    var s2 := sumaVectorGen3(V, m, k);
    s := s1 + s2;
    assert sum(V, j, k) == sum(V, j, m) + sum(V, m, k) by { sumaDescomp(V, j, k, m); }
  }
}

// 4. Inmersión final, recorriendo el vector de izquierda a derecha y manteniendo
//    el resultado en una variable acumuladora


method sumaVector4(V: array<int>) returns (s: int)
  ensures s == sum(V, 0, V.Length)
{
  s := sumaVectorGen4(V, 0, 0);
}


method sumaVectorGen4(V: array<int>, j: int, ac: int) returns (s: int)
  requires 0 <= j <= V.Length && ac == sum(V, 0, j)
  ensures s == sum(V, 0, V.Length)
  decreases V.Length - j
{
  if j == V.Length {
    s := ac;
  } else {
    s := sumaVectorGen4(V, j + 1, ac + V[j]);
  }
}
