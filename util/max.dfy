// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Definición del operador `max` para enteros y para arrays


// Máximo entre dos números
function max(x: int, y: int): int
{
  if x < y then y else x
}

// Máximo entre los elementos de un segmento no vacío de array
ghost function maxArray(V: array<int>, c: nat, f: nat): int
  requires 0 <= c < f <= V.Length
  decreases f - c
  reads V
{
  if c == f - 1 then V[c] else max(maxArray(V, c, f - 1), V[f - 1])
}


// Lema auxiliar: descomposición del máximo por la izquierda
// (max i : c <= i < f : V[i]) == max(V[c], (max i : c + 1 <= i < f : V[i]))

lemma maxArrayDecompLeft(V: array<int>, c: nat, f: nat)
  requires 0 <= c < f - 1 < V.Length
  ensures maxArray(V, c, f) == max(V[c], maxArray(V, c + 1, f))
{ /* Dafny lo demuestra automáticamente */ }

