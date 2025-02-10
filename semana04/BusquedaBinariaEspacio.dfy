// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------


// Esquema general de búsqueda binaria en espacio de soluciones


// Suponemos un predicado que nos dice si `n` es solución de un problema
predicate sePuede(n: int)

// Suposiciones sobre el espacio de soluciones:

// 1. Si n es una solución, cualquier valor mayor que n lo es
lemma {:axiom} solucionMonotonaDcha(n: int)
    requires sePuede(n)
    ensures forall k | k >= n :: sePuede(k)


// 2. Si n no es una solución, cualquier valor menor que n tampoco lo es
lemma {:axiom} solucionMonotonaIzqda(n: int)
    requires !sePuede(n)
    ensures forall k | k <= n :: !sePuede(k)

// Procedimiento de búsqueda binaria en el espacio de soluciones


method BusquedaEspacioSolucionesGen(c: int, f: int) returns (sol: int)
    requires c <= f
    requires sePuede(f)
    ensures sePuede(sol) && forall k | c <= k < sol :: !sePuede(k)
    decreases f - c
{
    if c == f {
        sol := c;
    } else {
        var m := (c + f) / 2;
        if sePuede(m) {
            solucionMonotonaDcha(m);
            sol := BusquedaEspacioSolucionesGen(c, m);
        } else {
            solucionMonotonaIzqda(m);
            sol := BusquedaEspacioSolucionesGen(m + 1, f);
        }
    }
}




// Llamada inicial al procedimiento de búsqueda de espacio de soluciones.
// Suponemos que `min` y `max` son cotas inferiores y superiores a la solución
// mínima buscada.

method BusquedaEspacioSoluciones(min: int, max: int) returns (sol: int)
    requires min <= max
    requires sePuede(max)
    ensures sePuede(sol) && forall k | min <= k < sol :: !sePuede(k)
{
    sol := BusquedaEspacioSolucionesGen(min, max);
}


