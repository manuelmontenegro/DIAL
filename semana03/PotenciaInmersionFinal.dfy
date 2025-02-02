// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Ejercicio: cálculo de potencias con inmersión final

include "../util/potencia.dfy"

// Función sumergida
method potencia(x: int, y: int) returns (p: int)
  requires y >= 0
  ensures p == pot(x, y)
{
  p := potenciaGen(x, y, 0, 1);
}

// Función inmersora. La variable `ac` contiene la potencia de x acumulada
// hasta el momento
method potenciaGen(x: int, y: int, i: int, ac: int) returns (p: int)
  requires y >= 0 && 0 <= i <= y && ac == pot(x, i)
  ensures p == pot(x, y)
  decreases y - i
{
  if i == y {
    p := ac;
  } else {
    p := potenciaGen(x, y, i + 1, ac * x);
  }
}

