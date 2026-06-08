# PC3 - CC232

## Problema Asignado

**Link**: <https://atcoder.jp/contests/arc033/tasks/arc033_3>

**C - データ構造 (Data Structure / Estructura de Datos)**: El problema solicita administrar un conjunto dinámico de números (inicialmente vacío) que responda $Q$ consultas de dos tipos.

1. **Inserción ($T = 1$):** Agregar un número $X$ al conjunto.
2. **Consulta y Eliminación ($T = 2$):** Identificar el $X$-ésimo número más pequeño presente en el conjunto, imprimirlo y luego eliminarlo.

**Restricciones clave:**

1. Número de consultas y valores: $1 <= Q,X <= 200,000$.
2. No se insertarán números repetidos que ya existan en el conjunto.
3. Nunca se pedirá eliminar un elemento si no hay suficientes elementos disponibles.
