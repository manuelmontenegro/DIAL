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


// Lema: Descomposición de un sumatorio por el límite izquierdo
//
// (Σi : c <= i < f : V[i]) == v[c] + (Σi : c + 1 <= i < f : V[i])

lemma sumaPorLaIzquierda(V: array<int>, c: int, f: int)
  requires 0 <= c < f <= V.Length
  ensures sum(V, c, f) == V[c] + sum(V, c + 1, f)
  decreases f - c
{ }


// Lema: Descomposición de un sumatorio de un segmento en dos segmentos
//
// Suponiendo que c <= m <= f
//
// (Σi : c <= i < f : V[i]) ==  (Σi : c <= i < m : V[i]) + (Σi : m <= i < f : V[i])

lemma sumaDescomp(V: array<int>, c: int, f: int, m: int)
  requires 0 <= c <= m <= f <= V.Length
  ensures sum(V, c, f) == sum(V, c, m) + sum(V, m, f)
  decreases m - c
{
  if c == m {
    calc {
        sum(V, c, f);
    ==
        sum(V, m, f);
    ==
        0 + sum(V, m, f);
    ==
        sum(V, m, m) + sum(V, m, f);
    ==
        sum(V, c, m) + sum(V, m, f);
    }
  } else {
    calc {
        sum(V, c, f);
    == { sumaPorLaIzquierda(V, c, f); }
        V[c] + sum(V, c + 1, f);
    == { sumaDescomp(V, c + 1, f, m); }
        V[c] + sum(V, c + 1, m) + sum(V, m, f);
    == { sumaPorLaIzquierda(V, c, f); }
        sum(V, c, m) + sum(V, m, f);
    }
  }
}