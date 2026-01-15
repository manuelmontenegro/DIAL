// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Especificaciones de ejemplo

include "../util/real.dfy"

// Todas las especificaciones tienen el atributo {:axiom} de Dafny
// para evitar los warnings acerca de funciones especificadas y no
// implementadas.


// buscarElem
// ----------

// Primera versión. Si hay varias apariciones de x, no se indica
// cuál se devuelve.

// No ponemos la restricción v.Length >= 0, porque Dafny supone
// implícitamente que las longitudes de los arrays no son negativas.

method {:axiom} BuscarElem1(v: array<int>, x: int) returns (i: nat)
  requires exists i | 0 <= i < v.Length :: v[i] == x
  ensures 0 <= i < v.Length && v[i] == x


// Segunda versión. Indicamos que se devuelve la primera aparición
// de x en v

method {:axiom} BuscarElem2(v: array<int>, x: int) returns (i: nat)
  requires exists i | 0 <= i < v.Length :: v[i] == x
  ensures 0 <= i < v.Length && v[i] == x && forall j | 0 <= j < i :: v[j] != x

// Tercera versión. Además de lo anterior, ya no exigimos que x esté
// en el vector v. Si no se encuentra, se devuelve -1

method {:axiom} BuscarElem3(v: array<int>, x: int) returns (i: nat)
  ensures -1 <= i < v.Length
          && (i >= 0 ==> v[i] == x && forall j | 0 <= j < i :: v[j] != x)
          && (i == -1 ==> forall j | 0 <= j < v.Length :: v[j] != x)



// Divide
// ------

method {:axiom} Divide(a: nat, b: nat) returns (q: nat, r: nat)
  requires b > 0
  ensures a == b * q + r && 0 <= r < b


// Raiz Real
// ---------

method {:axiom} RaizReal(a: real) returns (r: real)
  requires a >= 0.0
  ensures r >= 0.0 && abs(r * r - a) <= 0.0001

method {:axiom} RaizEntera(a: nat) returns (r: nat)
  ensures 0 <= r * r <= a < (r + 1) * (r + 1)



