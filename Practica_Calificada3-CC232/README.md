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

## Estructura Usada

La estructura elegida fue un Treap con soporte para orden estadístico. Se trata de un árbol binario de búsqueda aleatorizado donde cada nodo almacena, además de su clave y prioridad, el tamaño de su subárbol.

## Relacion con Semana4-6

La estructura Treap, en la semana 6 desarrollada, no es sino una combinación de los conceptos abordados en semanas previas. Con la base proporcionada sobre los árboles BST se añade la noción de las rotaciones, de cuya integración surge esta estructura de datos.

## Compilación

Dentro de `Practica_Calificada3-CC323/` se ejecuta lo siguiente.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

## Ejecución

## Pruebas

## Complejidad

| Operación | Complejidad esperada |
| --- | --- |
| `add(X)` | O(log N) |
| `kth(k)` | O(log N) |
| `remove(val)` | O(log N) |
| Operación tipo 2 completa (`kth` + `remove`) | O(log N) |

En general, la complejidad de cada operacion es O(log N), si se fuese a ejecutar Q veces y dado que $Q <= N$ sería: **$O(Q) * O(log Q) = O(Qlog(Q))$**

## Invariante

- La propiedad de árbol binario de búsqueda, donde los elementos menores se ubican a la izquierda y los mayores a la derecha.
- La propiedad de heap sobre las prioridades, utilizada para mantener un balance esperado adecuado.
- El almacenamiento correcto del tamaño de cada subárbol.

## Casos Borde

## Autoria
