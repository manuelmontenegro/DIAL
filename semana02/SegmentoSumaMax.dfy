// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Algoritmo de Kadane: calcula la suma máxima de cualquier segmento no vacío
// de un vector

include "../util/sum.dfy"
include "../util/max.dfy"

/*
  Dafny no permite el uso del cuantificador max ni el uso del sumatorio.
  Por tanto, se definen tres funciones auxiliares:

  1. sum(V, c, f) == (Σi : c <= i < f : V[i])
     Definida en ../util/sum.dfy

  2. sumaMaxima(V, c, f) == (máx p, q : c <= p < q <= f : sum(V, p, q))
     Definida más abajo, en este mismo fichero

  3. sumaMaximaFinal(V, c, f) == (max p : c <= p < f : sum(V, p, f))
     Definida más abajo, en este mismo fichero
*/



method SegmentoSumaMaxima(v: array<int>) returns (s: int)
  requires v.Length >= 1
  ensures s == sumaMaxima(v, 0, v.Length)
{
  var i := 1;
  var m := v[0];
  s := v[0];

  while i != v.Length
    invariant 1 <= i <= v.Length && s == sumaMaxima(v, 0, i)
              && m == sumaMaximaFinal(v, 0, i)
  {
    m := max(m, 0) + v[i];
    /* Hay que convencer a Dafny de lo siguiente:

        (max p : 0 <= p < i + 1 : sum(V, p, i + 1))
    ==
        max((max p : 0 <= p < i : sum(V, p, i)), 0) + V[i]

        Esto se hace en un lema aparte: PropiedadSegmentoSumaMaximaFinal
    */
    assert m == sumaMaximaFinal(v, 0, i + 1) by { PropiedadSegmentoSumaMaximaFinal(v, 0, i); }
    s := max(s, m);
    i := i + 1;
  }
}

// Definiciones auxiliares
// -----------------------



/*
  Las cláusulas `ensures` demuestran, además, que esta función cumple dos
  propiedades:

    1. Que existe un segmento de V[c..f) con esa suma.

    2. Que todos los segmentos de V[c..f) tienen una suma igual o menor.

  Por tanto, esto demuestra que la función `sumaMaxima` realmente calcula
  la suma máxima de un vector
*/

ghost function sumaMaxima(v: array<int>, i: nat, j: nat): int
  reads v
  requires 0 <= i < j <= v.Length
  ensures exists p, q | i <= p < q <= j :: sumaMaxima(v, i, j) == sum(v, p, q)
  ensures forall p, q | i <= p < q <= j :: sumaMaxima(v, i, j) >= sum(v, p, q)
{
  if i == j - 1 then
    assert sum(v, i, j) == v[i];
    v[i]
  else
    max(sumaMaxima(v, i, j - 1), sumaMaximaFinal(v, i, j))
}


// Definición de la suma máxima de un segmento de V[c..f) de entre todos
// los segmentos que están "pegados" a la posición f
//
// sumaMaximaFinal(V, c, f) == (max p : c <= p < f : sum(V, p, f))

/*
    De nuevo, las cláusulas `ensures` demuestran que la definición
    recursiva que viene a continuación realmente calcula lo que entendemos
    por suma máxima.
*/


ghost function sumaMaximaFinal(v: array<int>, i: nat, j: nat): int
  reads v
  requires 0 <= i < j <= v.Length
  ensures exists p | i <= p < j :: sumaMaximaFinal(v, i, j) == sum(v, p, j)
  ensures forall p | i <= p < j :: sumaMaximaFinal(v, i, j) >= sum(v, p, j)
  decreases j - i
{
  if i == j - 1 then
    assert v[i] == sum(v, i, j);
    v[i]
  else
    max(sumaMaximaFinal(v, i + 1, j), sum(v, i, j))
}

/*
    Lema auxiliar: dados i y j, demuestra la siguiente igualdad:

        (max p : i <= p < j + 1 : sum(V, p, j + 1))
    ==
        max((max p : i <= p < j : sum(V, p, j)), 0) + v[j]


    A continuación aparece toda la demostración en detalle, pero no
    es necesario indicar todos los pasos.
 */

lemma PropiedadSegmentoSumaMaximaFinal(v: array<int>, i: nat, j: nat)
  requires 0 <= i < j < v.Length
  decreases j - i
  ensures sumaMaximaFinal(v, i, j + 1) == max(sumaMaximaFinal(v, i, j), 0) + v[j]
{
  if i == j - 1 {
    calc {
      sumaMaximaFinal(v, j - 1, j + 1);
    ==
      max(sumaMaximaFinal(v, j, j + 1), sum(v, j - 1, j + 1));
    ==
      max(v[j], sum(v, j - 1, j) + v[j]);
    ==
      max(0, sum(v, j - 1, j)) + v[j];
    ==
      max(0, v[j - 1]) + v[j];
    ==
      max(0, v[i]) + v[j];
    ==
      max(0, sumaMaximaFinal(v, i, j)) + v[j];
    }
  } else {
    calc {
      sumaMaximaFinal(v, i, j + 1);
    ==
      max(sumaMaximaFinal(v, i + 1, j + 1), sum(v, i, j + 1));
    == { PropiedadSegmentoSumaMaximaFinal(v, i + 1, j); }
      max(max(sumaMaximaFinal(v, i + 1, j), 0) + v[j], sum(v, i, j + 1));
    ==
      max(max(sumaMaximaFinal(v, i + 1, j), 0) + v[j], sum(v, i, j) + v[j]);
    ==
      max(max(sumaMaximaFinal(v, i + 1, j), 0), sum(v, i, j)) + v[j];
    ==
      max(max(sumaMaximaFinal(v, i + 1, j), sum(v, i, j)), 0) + v[j];
    ==
      max(sumaMaximaFinal(v, i, j), 0) + v[j];
    }
  }
}

