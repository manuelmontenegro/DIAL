// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------


// Definición de multiplicación rusa original
// ------------------------------------------

// Utilizamos una definición funcional, porque así es más fácil de utilizar
// en los razonamientos con Dafny

function multRusa(x: int, y: int): int
  requires x >= 0 && y >= 0
  ensures multRusa(x, y) == x * y
  decreases y
{
  if y == 0 then 0
  else if y % 2 == 0 then multRusa(2 * x, y / 2)
  else assert y % 2 == 1; multRusa(2 * x, y / 2) + x
}


// Definición de generalización de multiplicación rusa
// ---------------------------------------------------

function multRusaGen(x: int, y: int, s: int): int
  requires x >= 0 && y >= 0
{
  multRusa(x, y) + s
}


// Definición recursiva final de la función anterior
// -------------------------------------------------

function multRusaGenRF(x: int, y: int, s: int): int
  requires x >= 0 && y >= 0
{
  if y == 0 then s
    else if y % 2 == 0 then multRusaGen(2 * x, y / 2, s)
    else multRusaGen(2 * x, y / 2, (x + s))
}


// Demostración de equivalencia entre las dos versiones anteriores
// utilizando desplegado y plegado
// ---------------------------------------------------------------

method PlegadoDesplegado(x: int, y: int, s: int)
  requires x >= 0 && y >= 0
  ensures multRusaGen(x, y, s) == multRusaGenRF(x, y, s)
{
  calc {
    multRusaGen(x, y, s);
  ==
    multRusa(x, y) + s;
  ==
    (if y == 0 then 0
     else if y % 2 == 0 then multRusa(2 * x, y / 2)
     else assert y % 2 == 1; multRusa(2 * x, y / 2) + x) + s;
  ==
    if y == 0 then s
    else if y % 2 == 0 then (multRusa(2 * x, y / 2) + s)
    else (multRusa(2 * x, y / 2) + x + s);
  ==
    if y == 0 then s
    else if y % 2 == 0 then multRusaGen(2 * x, y / 2, s)
    else multRusaGen(2 * x, y / 2, (x + s));
  }
}


// Algoritmo iterativo
// -------------------

// Utilizamos variables x' e y' porque Dafny no permite
// modificar los parámetros de entrada.

method MultRusaIterativo(x: int, y: int) returns (r: int)
  requires x >= 0 && y >= 0
  ensures r == x * y
{
  var s := 0;
  var x' := x;
  var y' := y;
  while y' != 0
    invariant x' >= 0 && y' >= 0
    invariant x' * y' + s == x * y
    decreases y'    
  {
    if y' % 2 == 0 {
      x', y', s := 2 * x', y' / 2, s;
    } else {
      assert y' % 2 == 1;
      x', y', s := 2 * x', y' / 2, s + x';
    }
  }
  r := s;
}

