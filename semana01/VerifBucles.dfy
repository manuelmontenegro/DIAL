// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Verificación de funciones con bucles

include "../util/potencia.dfy"
include "../util/sum.dfy"

// Potencia de dos
// ---------------

// Se hace uso de la función fantasma `pot`, definida recursivamente aparte,
// porque Dafny no soporta directamente el operador de potenciación.

method Exp2(n: nat) returns (p: nat)
  ensures p == pot(2, n)
{
  var i := 0;
  p := 1;
  while i < n
    invariant i <= n && p == pot(2, i)
  {
    p := p * 2;
    i := i + 1;
  }
}


// Suma de los elementos de un vector
// ----------------------------------

// Se hace uso de la función fantasma `sum`, definida recursivamente aparte,
// porque Dafny no soporta directamente el cuantificador de sumatorio.


method SumaVector(v: array<int>) returns (s: int)
  ensures s == sum(v, 0, v.Length)
{
  s := 0;
  var i := 0;
  while i < v.Length
    invariant 0 <= i <= v.Length && s == sum(v, 0, i)
  {
    s := s + v[i];
    i := i + 1;
  }
}

