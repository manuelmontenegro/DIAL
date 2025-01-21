// --------------------------
// Diseño de Algoritmos   
// Manuel Montenegro Montes
// --------------------------

// Definición del operador potencia y lemas asociados

// Definición recursiva del operador de potencia

ghost function pot(a: int, b: nat): int {
    if b == 0 then 1 else a * pot(a, b - 1)
}

