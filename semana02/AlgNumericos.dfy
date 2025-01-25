// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Ejemplo 1: Cálculo de raíz entera (versión 1)

method raizEntera(a: int) returns (r: int)
  requires a >= 0
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{ 
  r := 0;
  while a >= (r + 1) * (r + 1)
    invariant r >= 0 && r * r <= a
    decreases a - r * r
  { r := r + 1; }
}

// Ejemplo 2: Cálculo de raíz entera (versión 2)


method raizEntera2(a: int) returns (r: int)
  requires a >= 0
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{ 
  r := a / 2 + 1;
  while r * r > a
    invariant r >= 0 && 0 <= a < (r + 1) * (r + 1)
    decreases r
  { r := r - 1; }
}


// Ejemplo 3: División entera

method divide(a: nat, b: nat) returns (q: nat, r: nat)
  requires b > 0
  ensures a == b * q + r && r < b
{
  q := 0; r := a;
  while r >= b 
    invariant a == b * q + r && b > 0
    decreases r
  {
    q := q + 1; r := r - b;
  }
}
