// --------------------------
// Diseño de Algoritmos   
// Manuel Montenegro Montes
// --------------------------

// Verificación de función simple, sin bucles


method max(a: int, b: int) returns (m: int)
ensures m >= a && m >= b && (m == a || m == b)
{
  if a > b { m := a; } else { m := b; }
}


