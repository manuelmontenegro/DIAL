// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Definición del operador potencia y lemas asociados

// Definición recursiva del operador de potencia

ghost function pot(a: int, b: nat): int {
  if b == 0 then 1 else a * pot(a, b - 1)
}


lemma pot_suma(a: int, b: nat, c: nat)
  ensures pot(a, b) * pot(a, c) == pot(a, b + c)
{
  if b == 0 {
    assert pot(a, 0) * pot(a, c) == pot(a, c) == pot(a, 0 + c);
  } else {
    calc {
      pot(a, b) * pot(a, c);
    ==
      a * pot(a, b - 1) * pot(a, c);
    == { pot_suma(a, b - 1, c); }
      a * pot(a, b - 1 + c);
    ==
      pot(a, b + c);
    }
  }
}