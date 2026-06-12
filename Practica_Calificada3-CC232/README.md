# PC3 - CC232

## Problema Asignado

**Link**: <https://atcoder.jp/contests/arc033/tasks/arc033_3>

**C - データ構造 (Data Structure / Estructura de Datos)**: Se solicita administrar un conjunto dinámico de números que responda $Q$ consultas de dos tipos.

1. **Inserción ($T = 1$):** Agregar el número $X$.
2. **Consulta y Eliminación ($T = 2$):** Identificar el X número más pequeño presente en el conjunto, imprimirlo y luego eliminarlo.

**Restricciones clave:**

1. $1 <= Q,X <= 200,000$ $T = 1 ó T = 2$.
2. No se pueden insertar números repetidos.

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

```bash
cd build/
./demo_sol_pc3.exe
./test_treap.exe
./bench_treap.exe
```

## Pruebas

```bash
cd build/
./test_treap.exe
```

## Complejidad

| Operación | Complejidad esperada |
| --- | --- |
| `add(X)` | $O(\log N)$ |
| `kth(k)` | $O(\log N)$ |
| `remove(val)` | $O(\log N)$ |
| Operación tipo 2 completa (`kth` + `remove`) | $O(\log N)$ |

Siendo N vale la cantidad de elementos dentro de la estructura, la complejidad de cada operacion es $O(\log N)$, si se fuese a ejecutar Q veces y se tiene $N <= Q$ sería: **$$O(Q) * O(\log N) = O(Q\log(N))$$**

## Invariante

- La propiedad de árbol binario de búsqueda, donde los elementos menores se ubican a la izquierda y los mayores a la derecha.
- La propiedad de heap sobre las prioridades, utilizada para mantener un balance esperado adecuado.
- El almacenamiento correcto del tamaño de cada subárbol.

## Casos Borde

Dentro de `test_treap.cpp` se evalua el header, no el `src` ya que la implementación es en realidad muy directa (solo llamar funciones con un if).

- test_vacio_frontera ->      árbol con 0 elementos
- test_duplicados ->          insertar el mismo valor mas de una vez
- test_extremo_manual ->      kth(1) y kth(size()) simultáneamente
- test_invariante_subtreesize ->      borrar raiz (5), mínimo (1) y máximo (9)

## Benchmark

En `benchmark/bench_treap.cpp` se verifica experimentalmente que las funciones de `treap.h` tienen complejidad temporal $O(\log N)$. Para ello, se definió $T(N)$:

$$
T(N)=\frac{t_{\text{ejecución}}}{N}.
$$

Posteriormente, se analiza el cociente:

$$
\frac{T(N)}{\log_2(N)}.
$$

Si el cociente se mantiene aproximadamente constante para cualquier valor de $N$, se corrobora dicha complejidad. Se utilizan logaritmos en base 2 porque, en un BST, la altura del árbol es proporcional al logaritmo mencionado. Además, la notación Big-O sigue siendo la misma, ya que las distintas bases difieren únicamente en una constante multiplicativa ($\log_2(N)=c,\log(N)$). Por lo tanto, asintóticamente, la expresión $O(\log N)$ es correcta.

## Autoria

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.
