// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmos para cálculo de potencias.

include "../util/potencia.dfy"

// Primera versión: coste lineal con respecto al exponente

method potencia(x: int, y: int) returns (p: int)
  requires y >= 0
  ensures p == pot(x, y)
  decreases y
{
  if y == 0 {
    p := 1;
  } else {
    var z := potencia(x, y - 1);
    p := x * z;
  }
}

// Segunda versión: coste logarítmico con respecto al exponente


method potenciaLog(x: int, y: int) returns (p: int)
  requires y >= 0
  ensures p == pot(x, y)
  decreases y
{
  if y == 0 {
    p := 1;
  } else if (y % 2 == 0) {
    var z := potenciaLog(x, y / 2);
    p := z * z;
    // Hay que demostrar a Dafny que pot(x, y / 2) * pot(x, y / 2) == pot(x, y)
    // En general, se hace uso de la propiedad de las potencias pot(x, y) * pot(x, z) == pot(x, y + z),
    // que está demostrada en un lema aparte (pot_suma).
    assert pot(x, y) == pot(x, y / 2) * pot(x, y / 2) by { pot_suma(x, y / 2, y / 2); }
  } else {
    var z := potenciaLog(x, y / 2);
    p := z * z * x;
    assert pot(x, y) == pot(x, y / 2) * pot(x, y / 2) * x by { pot_suma(x, y / 2, y / 2); }
  }
}


