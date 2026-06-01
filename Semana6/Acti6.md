# BLOQUE 1
### 1.
Una apliacion leve del bst de la semana anterior ahora con las rotaciones, comparacion del bst con el binary heap(esta semana), uso del treap (fnciones addinpriority e inroder). Ultimo, el uso de heap para ordenamiento (izquiera o derecha), esto dentro de la estructuras de prefijo PQ. En general es el uso de orden de busqueda y prioridad aleatoria o explicita.
### 2.
Conjunto de headers, PQ (interfaz) y sus variantes (leftheap, huffman, treap, vectorheapsort).

### 3.
Capitulo6.h se usara para la semana10 por lo que es mas práctico referenciarlo.
### 4.
Es una continuacion del uso de los modelos arboles binarios.

### 5.
PQ_ComplHeap.h
### 6.
PQ_LeftHeap.h
### 7.
Treap.h
### 8.


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
  return (pqHasParent(i) && (pqHasLeftChild(i, n) || pqHasRightChild(i, n)));
}
```
Para las dos primera funciones: Si la supuesta ubicacion de los hijos esta por fuera del tamaño de n, entonces no existe.
Para pqisleaf es un bool donde para verificar si es una hoja no debe tener ni hijo izquierdo ni hijo derecho.

### 1.
Para englobar las operaciones que luego se heredan para los demas (la funcion aritmetica).
### 2.
Contexpr es optmimizado para el uso en PQ_ComplHeap_macro, donde no hay casos adicionales, no tiene riesgos de una magro.
### 3.
El nodo tiene un único hijo posible left, así que siftDown debe comparar solo con ese hijo en vez de elegir el menor de dos.
### 4.
Un nodo es hoja si left(i) >= size, en otras palabas, si cae fuera del rango del arreglo.
### 5.

# BLOQUE 4
Dentro de PQ_ComplHeap_percolateDown.h
```cpp
// MOD-BLOQ4: funcion con conteo de swaps
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  std::size_t count = 0;
  while (pqInHeap(pqLeftChild(i), n)) {
    std::size_t c = pqLeftChild(i);
    const std::size_t r = pqRightChild(i);
    if (pqInHeap(r, n) && comp(a[c], a[r])) {
      c = r;
    }
    if (!comp(a[i], a[c])) {
      break;
    }
    std::swap(a[i], a[c]);
    count++;
    i = c;
  }
  std::cout << "\nNumero de cambios -> " << count << "\n";
  return i;
}
```
Solamente se modifica la funcion complHeapPercolateDown() agregando la variable count que aumenta despues de cada swap(), luego se returna como un cout, ya que el header Huffman_PQ.h utiliza la variable del maximo y esto dañaria el header Capitulo6.h.

Dentro de PQ_ComplHeap_delMax.h
```cpp
...
  if (!a.empty()) {
    complHeapPercolateDownCount(a, a.size(), 0, comp);
  }
...
```
Se cambio la funcio de complHeapPercolateDown() a complHeapPercolateDownCount(). Luego se uso directamente la demo demo_pq_complheap_basico.cpp para probar los puntos que piden del bloque.

### 1.
### 2.
### 3.
### 4.
### 5.

# BLOQUE 5



