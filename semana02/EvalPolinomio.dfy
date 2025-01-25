// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Función para evaluar un polinomio en un determinado valor

include "../util/potencia.dfy"

// Dafny no permite expresar directamente el sumatorio
// (Σj  : 0 <= j < P : P[j] * v^j). Por este motivo, definimos
// una función fantasma aparte `evalPolinomioFun` que calcula
// esta suma recursivamente.

method EvalPolinomio(P: array<int>, v: int) returns (r: int)
  requires P.Length >= 0
  ensures r == evalPolinomioFun(P, v, 0, P.Length)
{
  var s := 1;
  var i := 0;
  r := 0;
  while i < P.Length
    invariant 0 <= i <= P.Length && r == evalPolinomioFun(P, v, 0, i) && s == pot(v, i)
  {
    r := r + P[i] * s;
    s := s * v;
    i := i + 1;
  }
}


ghost function evalPolinomioFun(P: array<int>, v: int, c: nat, f: nat): int
  reads P
  requires 0 <= c <= f <= P.Length
{
  if c == f then 0 else evalPolinomioFun(P, v, c, f - 1) + P[f - 1] * pot(v, f - 1)
}

