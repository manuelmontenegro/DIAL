// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Técnicas de inmersión para el cálculo de la raíz cuadrada
// entera de un número.


// 1. Inmersión final. Coste O(sqrt(a))

method raizEntera1(a: int) returns (r: int)
  requires a >= 0
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{
    r := raizEnteraGen1(a, 0);
} 


method raizEnteraGen1(a: int, rac: int) returns (r: int)
  requires a >= 0 && rac >= 0 && rac * rac <= a
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
  decreases a - rac * rac
{
    if a < (rac + 1) * (rac + 1) {
        r := rac;
    } else {
        r := raizEnteraGen1(a, rac + 1);
    }
} 

// 2. Inmersión final. Coste O(a)

method raizEntera2(a: int) returns (r: int)
  requires a >= 0
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{
    r := raizEnteraGen2(a, a);
} 

method raizEnteraGen2(a: int, rac: int) returns (r: int)
  requires a >= 0 && rac >= 0 && a < (rac + 1) * (rac + 1)
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{
    if rac * rac <= a {
        r := rac;
    } else {
        r := raizEnteraGen2(a, rac - 1);
    }
} 


// 3. Inmersión no final. Coste O(log a)

method raizEntera3(a: int) returns (r: int)
  requires a >= 0
  ensures r >= 0 && r * r <= a < (r + 1) * (r + 1)
{
    r := raizEnteraGen3(a, 1);
}

method raizEnteraGen3(a: int, i: int) returns (r: int)
  requires a >= 0 && i >= 1
  ensures r >= 0 && r * r <= a < (r + i) * (r + i)
  decreases a - i
{
  if a < i * i {
    r := 0;
  } else {
    var r' := raizEnteraGen3(a, i * 2);
    if a < (r' + i) * (r' + i) {
      r := r';
    } else {
      r := r' + i;
    }
  }
}


