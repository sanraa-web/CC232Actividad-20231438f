# BLOQUE 1
## 1.
Una apliacion leve del bst de la semana anterior ahora con las rotaciones, comparacion del bst con el binary heap(esta semana), uso del treap (fnciones addinpriority e inroder). Ultimo, el uso de heap para ordenamiento (izquiera o derecha), esto dentro de la estructuras de prefijo PQ. En general es el uso de orden de busqueda y prioridad aleatoria o explicita.
## 2.
Conjunto de headers, PQ (interfaz) y sus variantes (leftheap, huffman, treap, vectorheapsort).

## 3.
Capitulo6.h se usara para la semana10 por lo que es mas práctico referenciarlo.
## 4.
Es una continuacion del uso de los modelos arboles binarios.

## 5.
PQ_ComplHeap.h
## 6.
PQ_LeftHeap.h
## 7.
Treap.h
## 8.

Comandos usados
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
ctest --test-dir build-debug -R Semana6 --output-on-failure

# BLOQUE2
Dentro de PQ_ComplHeap_macro.h
```cpp
//MOD-A6-B2: Funciones auxiliares
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept { return n > 2 * i + 1; }
inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept { return n > 2 * i + 2; }
inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
  return (!pqHasLeftChild(i, n) && !pqHasRightChild(i, n));
}
inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
  return ((pqHasLeftChild(i, n) || pqHasRightChild(i, n)));
}
```
Para las dos primera funciones: Si la supuesta ubicacion de los hijos esta por fuera del tamaño de n, entonces no existe.
Para pqisleaf es un bool donde para verificar si es una hoja no debe tener ni hijo izquierdo ni hijo derecho.
Para pqisinternal 

## 1.
Para la 
## 2.
Estaría mas optimizado para las funciones que no tiene excepciones, haciendolo mas rapido al compilar
## 3.


