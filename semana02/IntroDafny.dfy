// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Programas de ejemplo en Dafny


// Ejemplo 1: división de números enteros

method divide(a: nat, b: nat) returns (q: nat, r: nat)
  requires b > 0
  ensures a == b * q + r && r < b
{
  q := 0; r := a;
  while r >= b
    invariant a == b * q + r
  {
    q := q + 1;
    r := r - b;
  }
}


// Ejemplo 2: multiplicar por dos los elementos de un vector

method multDos(V: array<int>)
  ensures forall j | 0 <= j < V.Length :: V[j] == 2 * old(V[j])
  modifies V
{
  var i := 0;
  while i != V.Length
    invariant 0 <= i <= V.Length
              && (forall j | 0 <= j < i :: V[j] == old(V[j]) * 2)
              && (forall j | i <= j < V.Length :: V[j] == old(V[j]))
  {
    V[i] := V[i] * 2;
    i := i + 1;
  }
}


// Ejemplo 3: Suma de los elementos de un vector

// Función fantasma: simula el cuantificador sumatorio.
// Devuelve la suma de los elementos del segmento V[i..j)
ghost function suma(V: array<int>, i: int, j: int): int
  requires 0 <= i <= j <= V.Length
  decreases j - i
  reads V
{
  if i == j then 0 else V[i] + suma(V, i + 1, j)
}


// Algoritmo que suma los elementos del vector, recorriéndolo
// de derecha a izquierda
method sumaVector(V: array<int>) returns (s: int)
  ensures s == suma(V, 0, V.Length)
{
  s := 0;
  var i := V.Length;
  while i > 0
    invariant 0 <= i <= V.Length && s == suma(V, i, V.Length)
  {
    s := s + V[i - 1];
    i := i - 1;
  }
}


// Algoritmo que suma los elementos del vector, recorriéndolo
// de izquierda a derecha
method sumaVector2(V: array<int>) returns (s: int)
  ensures s == suma(V, 0, V.Length)
{
  s := 0;
  var i := 0;
  while i != V.Length
    invariant 0 <= i <= V.Length && s == suma(V, 0, i)
  {
    s := s + V[i];
    assert s == suma(V, 0, i + 1) by { sumaPorLaDerecha(V, 0, i); }
    i := i + 1;
  }
}


// Lema auxiliar: La suma del segmento V[i..j+1) es igual a la suma
// del segmento V[i..j) + V[j]

lemma sumaPorLaDerecha(V: array<int>, i: int, j: int)
  requires 0 <= i <= j < V.Length
  ensures suma(V, i, j + 1) == suma(V, i, j) + V[j]
  decreases j - i
{
  if i == j {
    assert suma(V, i, j + 1) == V[j] == suma(V, i, j) + V[j];
  } else {
    calc {
      suma(V, i, j + 1);
    ==
      V[i] + suma(V, i + 1, j + 1);
    == { sumaPorLaDerecha(V, i + 1, j); }
      V[i] + suma(V, i + 1, j) + V[j];
    ==
      suma(V, i, j) + V[j];
    }
  }
}
