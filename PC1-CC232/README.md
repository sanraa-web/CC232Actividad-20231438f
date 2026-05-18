# PC1 — Evaluate Reverse Polish Notation

## Integrantes
- Ronaldo David Sahuarico Canaquiri
- Santiago Alejandro Ramirez Aguilar

link video: https://drive.google.com/file/d/1AzsRTwgeKdBMZ5vjZNrv_SOylnTrNrLs/view?usp=sharing

## Problema asignado
**LeetCode 150 — Evaluate Reverse Polish Notation**
https://leetcode.com/problems/evaluate-reverse-polish-notation/

---

## Especificación del problema

Dada una expresión aritmética en notación polaca inversa (RPN) representada como
un vector de strings, evaluar la expresión y retornar su resultado como entero.

**Entrada:**
Vector de strings `tokens` donde cada elemento es un número entero o uno de los
operadores `"+"`, `"-"`, `"*"`, `"/"`.

**Salida:**
Un entero con el resultado de la expresión.

**Restricciones:**
- `1 <= tokens.length <= 10^4`
- Tokens son operadores o enteros en `[-200, 200]`
- La expresión RPN siempre es válida
- El resultado y todos los cálculos intermedios caben en un entero de 32 bits

---

## Tamaño de entrada relevante

`n = tokens.length`, es decir, el número de tokens en la expresión.
Este es el parámetro que determina el costo del algoritmo.

---

## Descripción de la solución

Se usa una pila (`Stack<int>`) como estructura central:
- Si el token es un número: se inserta en la pila (`push`).
- Si el token es un operador: se extraen los dos operandos del tope (`pop`),
  se aplica la operación y se inserta el resultado (`push`).
- Al finalizar el recorrido, el único elemento en la pila es el resultado.

---

## Justificación de determinismo

El algoritmo es **determinista**: para la misma entrada `tokens`, siempre produce
la misma salida. No hay aleatoriedad, concurrencia ni dependencia de estado externo.
Cada token se procesa exactamente una vez en orden secuencial.

---

## Justificación de factibilidad

Las operaciones involucradas son: comparación de strings, `push` y `pop` sobre
un vector dinámico, y aritmética entera básica. Todas son operaciones O(1)
ejecutables en el modelo RAM. No requiere recursos extraordinarios.

---

## Argumento de finitud

El bucle principal itera exactamente `n` veces, una por cada token del vector.
No hay recursión ni bucles anidados. El algoritmo termina en un número fijo
de pasos proporcional a `n`.

---

## Argumento de correctitud

**Invariante:** al finalizar el procesamiento del token `i`, la pila contiene
exactamente los resultados correctos de todas las subexpresiones completamente
evaluadas hasta ese punto.

**Caso base:** antes de procesar cualquier token, la pila está vacía (invariante
trivialmente satisfecho).

**Paso inductivo:** si la pila contiene resultados correctos antes del token `i`,
entonces tras procesarlo (número → push; operador → pop dos, operar, push resultado)
la pila sigue conteniendo resultados correctos.

**Conclusión:** al terminar el bucle, la pila contiene exactamente un elemento
que es el resultado correcto de toda la expresión.

---

## Invariante

> La pila contiene resultados correctos de todas las subexpresiones ya evaluadas.

---

## Monotonicidad

El índice de recorrido `i` avanza de 0 a `n-1` monótonamente. El tamaño de la
pila nunca supera `n`. Ambas propiedades garantizan progreso hacia la terminación.

---

## Complejidad temporal

**O(n)** — se recorre el vector una vez. Cada operación sobre la pila es O(1)
amortizado (push/pop sobre `std::vector`). Las comparaciones de string son O(1)
porque los operadores tienen longitud fija (1 carácter).

---

## Complejidad espacial

**O(n)** — en el peor caso la pila almacena todos los tokens (expresión con solo
números). El espacio adicional es proporcional al número de tokens.

---

## Mejor caso, peor caso y caso promedio

| Caso          | Complejidad | Situación                              |
|---------------|-------------|----------------------------------------|
| Mejor caso    | O(n)        | Un solo token (número)                 |
| Peor caso     | O(n)        | Expresión completamente anidada        |
| Caso promedio | O(n)        | No depende de distribución de entrada  |

Los tres casos son O(n) porque el bucle siempre recorre todos los tokens.

---

## Ubicación en la jerarquía de crecimiento

```
O(1) < O(log n) < O(n) ← aquí < O(n log n) < O(n²) < O(2^n)
```

La solución es **lineal O(n)**, óptima para este problema ya que se debe leer
al menos cada token una vez.

---

## Alternativa ingenua o menos eficiente

Convertir la expresión RPN a notación infija y luego evaluarla usando un parser
de precedencia. Esto requiere dos pasadas sobre la expresión y lógica adicional
de paréntesis, resultando en mayor complejidad de código aunque mantiene O(n).

Otra alternativa más ingenua sería usar recursión sin memoización evaluando
subexpresiones repetidamente, lo que puede llevar a O(n²) en casos degenerados.

La solución con stack es la forma canónica y más eficiente de evaluar RPN.

---

## Robustez y casos borde

| Caso borde              | Manejo                                              |
|-------------------------|-----------------------------------------------------|
| Un solo número          | Se inserta y retorna directamente                   |
| Números negativos       | `std::stoi` los maneja correctamente (`"-3"` → -3) |
| División entera         | C++17 trunca hacia cero (`-7/2 == -3`)              |
| División por cero       | Lanza `std::invalid_argument`                       |
| Expresión inválida      | Lanza `std::invalid_argument` si stack < 2          |
| Número fuera de rango   | Lanza `std::out_of_range` si fuera de `[-200, 200]` |

---

## Degeneración

No hay degeneración algorítmica: el costo es siempre O(n) independiente del
contenido de la expresión. El único riesgo práctico es una expresión inválida
(más operadores que operandos), que está protegido con excepción.

---

## Reutilización y encapsulación

- `Stack<T>` es un ADT genérico reutilizable para cualquier tipo T.
- `evalRPN` es una función independiente, separada de `main`.
- La interfaz del stack (`push`, `pop`, `top`, `empty`, `size`) está
  desacoplada de su implementación interna (`std::vector`).

---

## ADT utilizado

**Stack<T>** — pila genérica con interfaz mínima:

| Operación | Descripción                  | Complejidad |
|-----------|------------------------------|-------------|
| `push(x)` | Inserta elemento en el tope  | O(1) amort. |
| `pop()`   | Elimina elemento del tope    | O(1)        |
| `top()`   | Consulta elemento del tope   | O(1)        |
| `empty()` | Verifica si está vacío       | O(1)        |
| `size()`  | Retorna número de elementos  | O(1)        |

Implementación interna: `std::vector<T>`.

---

## Instrucciones para compilar

```bash
# Desde la raíz del repositorio

# Build debug
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic -o main_O0 src/main.cpp src/solution.cpp

# Build release
g++ -std=c++17 -O2 -DNDEBUG -o main src/main.cpp src/solution.cpp

# Con CMake
mkdir build && cd build
cmake ..
cmake --build .
```

---

## Instrucciones para ejecutar

```bash
./main
# Salida esperada: 9
```

---

## Instrucciones para correr tests

```bash
# Compilación manual
g++ -std=c++17 -O0 -I src -o tests test/tests.cpp src/solution.cpp
./tests
# Sin salida = todos los assert pasaron

# Con CMake + CTest
cd build
ctest --output-on-failure
```

---

## Benchmark realizado

Se comparó `Stack<int>` propio vs `std::stack<int>` de la STL ejecutando
`evalRPN` 1,000,000 veces con el mismo input.

```
Stack propio : 644.743 ms
std::stack   : 780.677 ms
Stack propio es 17.41% más rápido
```

El stack propio es más rápido porque usa `std::vector` directamente, mientras
que `std::stack` usa `std::deque` por defecto, que tiene peor localidad de memoria.

Ver detalles en `bench/benchmark.cpp` y `report/profiling_report.md`.

---

## Tabla de builds

| Build      | Flags                          | Tamaño  | Tiempo real | Warnings |
|------------|--------------------------------|---------|-------------|----------|
| Debug      | `-O0 -g -Wall -Wextra`         | 412 KB  | 0.347 s     | Ninguno  |
| Debug opt. | `-Og -g -Wall -Wextra`         | 350 KB  | 0.206 s     | Ninguno  |
| Release    | `-O2 -DNDEBUG`                 | 145 KB  | 0.195 s     | —        |
| Compacto   | `-Os`                          | 146 KB  | 0.204 s     | —        |

Ver análisis completo en `report/optimization_report.md`.

---

## Observaciones de sanitizers

Se intentó compilar con `-fsanitize=address,undefined` pero MinGW en Windows
(MSYS2/UCRT64) no incluye `libasan` ni `libubsan`.

Lo que habrían detectado:
- **ASan:** acceso a memoria inválida en `pop()`/`top()` sin guard → cubierto
  con `std::underflow_error` explícito.
- **UBSan:** desbordamiento de enteros con signo → no aplica, constraints
  garantizan resultados en 32 bits.

Ver detalles en `report/optimization_report.md`.

---

## Resumen de cobertura

Cobertura estimada manualmente (~95%) dado que gcov no funcionó en MinGW:

- Todos los operadores (`+`, `-`, `*`, `/`) cubiertos.
- Números negativos cubiertos.
- División por cero cubierta.
- Expresión inválida cubierta.
- Única rama no cubierta: validación de rango `[-200, 200]` (no alcanzable
  con entradas válidas de LeetCode).

Ver detalles en `report/coverage_report.md`.

---

## Resumen de profiling

`gprof` no produjo datos útiles en Windows/MinGW (sin tiempo acumulado).
Como alternativa se usó `std::chrono` en el benchmark.

Función de mayor costo esperada: `evalRPN`, por ser el núcleo lineal.
Esto es consistente con la complejidad O(n) analizada teóricamente.

Ver detalles en `report/profiling_report.md`.

---

## Microoptimización vs algoritmo

La comparación más importante no es entre flags de compilación sino entre
estructuras de datos: `Stack<int>` con `std::vector` vs `std::stack` con
`std::deque`. La diferencia de ~17% proviene de la elección de estructura,
no de flags.

Entre flags, el salto más grande es de `-O0` (412 KB, 0.347 s) a `-O2`
(145 KB, 0.195 s): ~44% más rápido y ~65% más compacto. Aun así, el
algoritmo O(n) con stack es la mejora fundamental frente a alternativas
ingenuas O(n²).

---

## Uso de Copilot

- **Sugerencia aceptada:** estructura inicial del include guard (`#ifndef`/`#define`/`#endif`) en `solution.hpp`.
- **Sugerencia rechazada:** uso de `std::stack` directamente en `evalRPN` en lugar del ADT propio, porque el enunciado requería implementar el stack como ADT separado.

**Uso para diseño (Claude):**
- Se usó para dar formato correcto a tablas y secciones en archivos `.md`debido a nuestra inexperiencia en este.
  (optimization_report, profiling_report, coverage_report, README).