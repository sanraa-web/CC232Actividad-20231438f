# Reporte de Profiling

## Entorno
- OS: Windows (MSYS2/UCRT64)
- Compilador: g++ 15.2.0
- Herramienta: gprof (incluido con GCC) + chrono como alternativa

---

## Ejecución gprof

```bash
g++ -std=c++17 -O2 -pg -I src -o bench_prof bench/benchmark.cpp src/solution.cpp
./bench_prof
gprof bench_prof.exe gmon.out > gprof_output.txt
```

## Resultado gprof

```
Flat profile:
Each sample counts as 0.01 seconds.
no time accumulated
```

## Causa

`gprof` usa muestreo estadístico cada 0.01 segundos. Se intentó con el programa
principal y también con el benchmark (1,000,000 iteraciones), pero el resultado
fue igualmente vacío. Es una limitación conocida de gprof en MinGW/Windows:
el profiler no expone las señales de reloj que gprof necesita para el muestreo.

---

## Datos reales — Benchmark con chrono

Se usó `std::chrono::high_resolution_clock` como alternativa de medición:

```
Benchmark: Stack<int> propio vs std::stack<int>
Iteraciones: 1,000,000
Input: [10,6,9,3,+,-11,*,/,*,17,+,5,+]  -> esperado: 22

Stack propio : 644.743 ms
std::stack   : 780.677 ms
Stack propio es 17.41% mas rapido
```

### Interpretación

El stack propio resultó más rápido que `std::stack` en este entorno.
Esto se explica porque `std::stack` es un adaptador que por defecto usa
`std::deque` como contenedor interno, que tiene peor localidad de memoria
que `std::vector`. Nuestro `Stack<T>` usa `std::vector` directamente,
lo que reduce el overhead de gestión de memoria.

---

## Análisis esperado por complejidad

### Función que concentraría más tiempo: `evalRPN`

`evalRPN` es el núcleo del programa. Itera sobre todos los tokens una vez (O(n))
y por cada token realiza operaciones O(1) sobre el stack: `push`, `pop`, `top`,
y comparaciones de strings. No hay llamadas recursivas ni bucles anidados.

### Funciones secundarias: `Stack<T>::push`, `pop`, `top`

Cada una ejecuta una operación sobre `std::vector` en O(1) amortizado.
Estas tres funciones aparecerían con tiempo proporcional a su frecuencia de llamada
en un profiler funcional.

### ¿Coincide con el análisis de complejidad?

Sí. La complejidad es O(n) donde n = número de tokens. No existe ninguna función
con complejidad mayor, por lo que no hay cuellos de botella inesperados.
El cuello de botella principal es `evalRPN` y dentro de ella las comparaciones
de string (`token == "+"`, etc.) por ser las operaciones más frecuentes por iteración.

---

## Conclusión

gprof no produjo datos útiles en Windows/MinGW. Como alternativa, `std::chrono`
confirmó que el stack propio con `std::vector` es ~17% más rápido que `std::stack`
con `std::deque`, lo cual es consistente con el análisis de complejidad espacial
y localidad de memoria. No se observaron cuellos de botella inesperados.