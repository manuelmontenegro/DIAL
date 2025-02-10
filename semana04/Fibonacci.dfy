// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------


// Definición matemática de la sucesión de fibonacci
ghost function fib(n: int): int
  requires n >= 0
{
  if n == 0 then 0
  else if n == 1 then 1
  else fib(n - 1) + fib(n - 2)
}

// Función Fibonacci generalizada. Devuelve fib(n) y fib(n - 1)
method FibonacciGen(n: int) returns (f0: int, f1: int)
  requires n >= 1
  ensures f0 == fib(n) && f1 == fib(n - 1)
{
  if n == 1 {
    f0 := 1; f1 := 0;
  } else {
    var f0', f1' := FibonacciGen(n - 1);
    f0 := f0' + f1';
    f1 := f0';
  }
}


// Llamada inicial a FibonacciGen. Como la anterior requiere que n >= 1, tenemos
// que tratar el caso n == 0 aparte.

method Fibonacci(n: int) returns (f: int)
  requires n >= 0
  ensures f == fib(n)
{
  if n == 0 {
    f := 0;
  } else {
    var f0, _ := FibonacciGen(n);
    f := f0;
  }
}


