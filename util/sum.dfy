// --------------------------
// Diseño de Algoritmos   
// Manuel Montenegro Montes
// --------------------------

// Definición del operador sumatorio y lemas asociados


// Sumatorio de los elementos de un segmento de un vector.

// Equivale a la notación (Σi : c <= i < f : V[i])

ghost function sum(v: array<int>, c: nat, f: nat): int
requires 0 <= c <= f <= v.Length
reads v
{
    if c == f then 0 else sum(v, c, f - 1) + v[f - 1]
}

