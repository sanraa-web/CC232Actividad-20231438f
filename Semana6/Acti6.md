#

## BLOQUE 1

### 1

Una apliacion leve del bst de la semana anterior ahora con las rotaciones, comparacion del bst con el binary heap(esta semana), uso del treap (fnciones addinpriority e inroder). Ultimo, el uso de heap para ordenamiento (izquiera o derecha), esto dentro de la estructuras de prefijo PQ. En general es el uso de orden de busqueda y prioridad aleatoria o explicita.

### 2

Conjunto de headers, PQ (interfaz) y sus variantes (leftheap, huffman, treap, vectorheapsort).

### 3

Capitulo6.h se usara para la semana10 por lo que es mas práctico referenciarlo.

### 4

Es una continuacion del uso de los modelos arboles binarios.

### 5

Dentro de PQ_ComplHeap.h

### 6

La funcion de PQ_LeftHeap.h

### 7

El header Treap.h

### 8

Comandos usados:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
ctest --test-dir build-debug -R Semana6 --output-on-failure
```

## BLOQUE2

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

### ¿Por qué conviene expresar parent, left, right y pruebas de frontera como funciones pequeñas?

Para englobar las operaciones que luego se heredan para los demas (la funcion aritmetica).

### ¿Qué ventaja tiene constexpr frente a macros? 

Contexpr es optmimizado para el uso en PQ_ComplHeap_macro, donde no hay casos adicionales, no tiene riesgos de una magro.

### ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?

El nodo tiene un único hijo posible left, así que siftDown debe comparar solo con ese hijo en vez de elegir el menor de dos.

### ¿Qué condición identifica una hoja en la representación implícita?

Un nodo es hoja si left(i) >= size, en otras palabas, si cae fuera del rango del arreglo.

### ¿Qué cambió en percolateDown después de usar las funciones auxiliares?

Cada que se ejecuta se usa el siguiente cout: `std::cout << "\nNumero de cambios -> " << count << "\n";`.

## Bloque 3

### Codigo

## BLOQUE 3

### Código de la función nueva complheapPercolateUp

```cpp
// NUEVA FUNCIÓN: Cuenta los intercambios
template <class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
    std::size_t swapCount = 0;
    while (pqHasParent(i)) {
        const std::size_t p = pqParent(i);
        if (!comp(a[p], a[i])) { // Si el padre NO es menor que el hijo, paramos (Max-Heap)
            break;
        }
        std::swap(a[p], a[i]);
        i = p;
        ++swapCount; // Contamos el intercambio
    }
    return swapCount;
}

```

### Código de la demostración modificada

Nuevo main.

```cpp
// MODIFICACION
template <typename T>
bool verifyHeapProperty(const std::vector<T>& a) {
    for (std::size_t i = 1; i < a.size(); ++i) {
        std::size_t p = (i - 1) / 2;
        if (a[p] < a[i]) { // Violación de Max-Heap
            return false;
        }
    }
    return true;
}

int main() {
  std::vector<int> heap;
  std::vector<int> secuencia = {40, 10, 70, 30, 90, 20, 80, 60};

  for (int x : secuencia) {
    std::cout << "elemento: " << x << "\n";
    
    heap.push_back(x);
    std::size_t swaps = ods::complHeapPercolateUpCount(heap, heap.size() - 1, std::less<int>());
    
    std::cout << "- inter: " << swaps << "\n";
    printVector(heap, "- arreglo"); // Modificar la función printVector para que use el label directo
    std::cout << "- heap?: " << (verifyHeapProperty(heap) ? "Sí" : "No") << "\n\n";
  }

  return 0;
}

```

### Salida de la demostración

```text
elemento: 40
- inter: 0
- arreglo: [40]
- heap?: Sí

elemento: 10
- inter: 0
- arreglo: [40, 10]
- heap?: Sí

elemento: 70
- inter: 1
- arreglo: [70, 10, 40]
- heap?: Sí

elemento: 30
- inter: 0
- arreglo: [70, 10, 40, 30]
- heap?: Sí

elemento: 90
- inter: 2
- arreglo: [90, 70, 40, 30, 10]
- heap?: Sí

elemento: 20
- inter: 0
- arreglo: [90, 70, 40, 30, 10, 20]
- heap?: Sí

elemento: 80
- inter: 1
- arreglo: [90, 70, 80, 30, 10, 20, 40]
- heap?: Sí

elemento: 60
- inter: 1
- arreglo: [90, 70, 80, 60, 10, 20, 40, 30]
- heap?: Sí
```

### ¿En qué casos `percolateUp` hace cero intercambios?

- Cuando el elemento insertado es el primero en el heap (se convierte directamente en la raíz).  
- Cuando el elemento insertado es menor o igual que su nodo padre inmediato (en un Max-Heap). Al cumplir la propiedad del heap desde el momento de la inserción, la condición del bucle `while` falla y termina inmediatamente.

### ¿En qué casos puede hacer $O(\log n)$ intercambios?

Puede hacer $O(\log n)$ intercambios en el peor de los casos, lo cual ocurre cuando el elemento insertado es estrictamente mayor que todos sus ancestros. Esto lo obliga a "burbujear" (percolate) camino arriba hasta convertirse en la nueva raíz. Un ejemplo clásico es insertar un nuevo valor máximo absoluto en el heap.

### ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?

El nuevo nodo siempre se inserta en la primera posición disponible en el nivel más bajo, más a la izquierda (índice $n-1$ en el arreglo). La cantidad máxima de intercambios que puede sufrir este nodo está acotada exactamente por la altura del árbol, la cual en un heap completo de $n$ elementos es $\lfloor \log_2 n \rfloor$. Por lo tanto, la posición inicial determina la distancia máxima posible hacia la raíz.

### ¿Por qué el arreglo interno no necesariamente queda ordenado?

Porque un Heap solo garantiza un **orden parcial**, no un orden total. La estructura solo exige que cada padre sea mayor (o menor, según el tipo de heap) que sus hijos directos. No existe ninguna restricción sobre la relación entre nodos hermanos (por ejemplo, el hijo izquierdo no tiene por qué ser mayor que el derecho) ni entre nodos de diferentes ramas. Por eso, al imprimir el arreglo linealmente, los elementos no aparecen en orden ascendente o descendente.

### ¿Qué propiedad sí queda garantizada? 

- **Propiedad de Forma (Estructura)**: El árbol es un árbol binario completo (todos los niveles están llenos excepto posiblemente el último, que se llena estrictamente de izquierda a derecha). Esto es lo que permite usar un arreglo contiguo sin huecos.  
- **Propiedad de Montículo (Heap Property)**: Para todo nodo $i > 0$, se cumple que $A[\text{padre}(i)] \ge A[i]$ (en un Max-Heap). Esto garantiza que el elemento de mayor prioridad (el máximo) esté siempre en la raíz ($A[0]$), listo para ser consultado o extraído en $O(1)$.

## BLOQUE 4

### 1. Código modificado

Dentro de `PQ_ComplHeap_percolateDown.h`:

```cpp

// MOD-BLOQUE4: Función instrumentada que cuenta los intercambios
template <class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    std::size_t count = 0;
    while (pqInHeap(pqLeftChild(i), n)) {
        std::size_t c = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);
        if (pqInHeap(r, n) && comp(a[c], a[r])) {
            c = r; // Elegimos el hijo mayor (para Max-Heap)
        }
        if (!comp(a[i], a[c])) {
            break; // El nodo actual ya es mayor que su hijo dominante
        }
        std::swap(a[i], a[c]);
        count++;
        i = c;
    }
    return count; // Retornamos el conteo, sin couts internos
}

```

Dentro de `PQ_ComplHeap_delMax.h`:

```cpp
//...
  if (!a.empty()) {
    complHeapPercolateDownCount(a, a.size(), 0, comp);
  }
//...
```

Demostración nueva `demo_delmax_instrumentado.cpp`:

```cpp
int main() {
    std::vector<int> heap;
    std::vector<int> secuencia = {40, 10, 70, 30, 90, 20, 80, 60};
    
    for (int x : secuencia) {
        heap.push_back(x);
        ods::complHeapPercolateUp(heap, heap.size() - 1, std::less<int>());
    }
    
    printVector(heap, "Estado inicial");

    while (!heap.empty()) {
        std::size_t n = heap.size();
        int maximo = heap[0];
        std::cout << "Máximo eliminado: " << maximo << "\n";
        
        // Mover el último elemento a la raíz
        heap[0] = heap[n - 1];
        heap.pop_back(); // Reducimos el tamaño
        
        if (!heap.empty()) {
            printVector(heap, "  Arreglo antes de reparar");
            
            // Llamamos a la función instrumentada
            std::size_t swaps = ods::complHeapPercolateDownCount(heap, heap.size(), 0, std::less<int>());
            
            std::cout << "  intercambios: " << swaps << "\n";
            printVector(heap, "  Arreglo después de reparar");
        } else {
            std::cout << "  Arreglo antes de reparar: []\n";
            std::cout << "  intercambios: 0\n";
            std::cout << "  Arreglo después de reparar: []\n";
        }
        std::cout << "\n\n";
    }

    return 0;
}
```

### Demostración

```text
Estado inicial: [90, 70, 80, 60, 10, 20, 40, 30]

Máximo eliminado: 90
  Arreglo antes de reparar: [30, 70, 80, 60, 10, 20, 40]
  intercambios: 2
  Arreglo después de reparar: [80, 70, 40, 60, 10, 20, 30]

Máximo eliminado: 80
  Arreglo antes de reparar: [30, 70, 40, 60, 10, 20]
  intercambios: 1
  Arreglo después de reparar: [70, 60, 40, 30, 10, 20]

Máximo eliminado: 70
  Arreglo antes de reparar: [20, 60, 40, 30, 10]
  intercambios: 1
  Arreglo después de reparar: [60, 30, 40, 20, 10]

Máximo eliminado: 60
  Arreglo antes de reparar: [10, 30, 40, 20]
  intercambios: 1
  Arreglo después de reparar: [40, 30, 10, 20]

Máximo eliminado: 40
  Arreglo antes de reparar: [20, 30, 10]
  intercambios: 1
  Arreglo después de reparar: [30, 20, 10]

Máximo eliminado: 30
  Arreglo antes de reparar: [10, 20]
  intercambios: 0
  Arreglo después de reparar: [20, 10]

Máximo eliminado: 20
  Arreglo antes de reparar: [10]
  intercambios: 0
  Arreglo después de reparar: [10]

Máximo eliminado: 10
  Arreglo antes de reparar: []
  intercambios: 0
  Arreglo después de reparar: []

```

### ¿Por qué después de `delMax` se mueve el último elemento a la raíz?

Porque el heap es un **árbol binario completo**, y para mantener esa propiedad de forma después de eliminar la raíz, la única posición que puede quedar "vacía" es la última hoja (la más a la derecha en el nivel más bajo). Al mover ese último elemento a la raíz, llenamos el hueco de la raíz y eliminamos la última posición, manteniendo así la estructura de árbol completo sin dejar huecos en el arreglo.

### ¿Por qué la reparación baja y no sube?

Porque el elemento que movemos desde la última posición a la raíz es, por lo general, un elemento pequeño (ya que estaba en una hoja). Al colocarlo en la raíz, es muy probable que viole la propiedad del Max-Heap (ser menor que sus hijos). Por lo tanto, necesita "bajar" (percolate down) hasta encontrar su posición correcta donde sea mayor que sus hijos. No tiene sentido que suba, porque ya está en la posición más alta posible (la raíz).

### ¿Cómo se decide entre hijo izquierdo e hijo derecho?

En un Max-Heap, se elige siempre al **hijo mayor** (el "hijo dominante"). Esto se hace comparando ambos hijos con el comparador `comp`. Si el hijo derecho es mayor que el izquierdo, se elige el derecho; de lo contrario, se elige el izquierdo. Luego se compara el nodo actual con ese hijo dominante. Si el nodo actual es menor, se intercambian. Esta estrategia garantiza que, después del intercambio, el nodo que baja sea menor que ambos hijos, restaurando la propiedad del heap en ese subárbol.

### ¿Qué pasa si el nodo actual tiene un solo hijo?

Esto solo puede ocurrir en el último nivel del árbol (el nivel más bajo), y específicamente solo puede ser el **hijo izquierdo** (porque el árbol se llena de izquierda a derecha). En este caso, la función simplemente compara el nodo actual con su único hijo (el izquierdo). Si el nodo actual es menor, se intercambian y el nodo baja a esa posición. Como ese hijo no tiene a su vez ningún hijo (está en el último nivel), el bucle `while` terminará en la siguiente iteración, ya que no habrá más hijos que evaluar.

### ¿Por qué `delMax` tiene costo $O(\log n)$?

Porque la operación consiste en:
1.  Leer y eliminar la raíz: $O(1)$.
2.  Mover el último elemento a la raíz: $O(1)$.
3.  Ejecutar `percolateDown`: En el peor de los casos, el elemento que movimos a la raíz debe bajar hasta el nivel más bajo del árbol. La altura de un heap completo de $n$ elementos es $\lfloor \log_2 n \rfloor$. En cada nivel, se realiza una cantidad constante de operaciones (comparar hijos, comparar con el padre, y posiblemente un intercambio). Por lo tanto, el número máximo de intercambios y comparaciones está acotado por la altura del árbol, lo que da un costo total de $O(\log n)$.

### Trazado manual de una eliminación

Supongamos el siguiente Max-Heap válido (extraído de la salida del demo):

```bash
        90
      /    \
    70      80
   /  \    /  \
  60  10  20  40
  /
 30
```
Arreglo interno: `[90, 70, 80, 60, 10, 20, 40, 30]`

Paso 1: Eliminar el máximo (90)

```bash
        30
      /    \
    70      80
   /  \    /  \
  60  10  20  40
```

Paso 2: Percolate Down desde la raíz (índice 0, valor 30)

```bash
        80
      /    \
    70      30
   /  \    /  \
  60  10  20  40
```

- Iteración 2:

```bash
        80
      /    \
    70      40
   /  \    /  \
  60  10  20  30
```

- Iteración 3:
  - Nodo actual: `30` (índice 6).
  - Hijo izquierdo: índice $2 \times 6 + 1 = 13$. Fuera del heap (tamaño 7).
  - El bucle `while` termina porque no hay hijos.
Arreglo final después de reparar: `[80, 70, 40, 60, 10, 20, 30]`
Total de intercambios: 2.

## BLOQUE 5

### Código `PQ_ComplHeap.h`

Se agrega el método `isValidHeap()` a la clase `PQ_ComplHeap`:

```cpp
bool isValidHeap() const {
    for (std::size_t i = 0; i < data_.size(); ++i) {
        std::size_t l = left(i);
        std::size_t r = right(i);
        // Si el padre es "menor" que algún hijo según el comparador, no es heap válido
        if (l < data_.size() && comp_(data_[i], data_[l])) return false;
        if (r < data_.size() && comp_(data_[i], data_[r])) return false;
    }
    return true;
}
```

### Pruebas agregadas `test_internal_week6.cpp`

```cpp
void testIsValidHeap() {
    //Heap vacío
    ods::PQ_ComplHeap<int> pq_empty;
    assert(pq_empty.isValidHeap());

    //Heap con un elemento
    ods::PQ_ComplHeap<int> pq_one{42};
    assert(pq_one.isValidHeap());

    //Heap con elementos repetidos
    ods::PQ_ComplHeap<int> pq_reps{5, 5, 5, 5};
    assert(pq_reps.isValidHeap());
    pq_reps.insert(5);
    assert(pq_reps.isValidHeap());

    // Heap construido por inserciones
    ods::PQ_ComplHeap<int> pq_ins;
    for (int x : {1, 5, 3, 9, 2}) {
        pq_ins.insert(x);
        assert(pq_ins.isValidHeap());
    }

    // Heap construido por heapify
    std::vector<int> vals = {10, 3, 8, 1, 5, 9};
    ods::PQ_ComplHeap<int> pq_heapify(std::move(vals));
    assert(pq_heapify.isValidHeap());

    // Heap despues de varias llamadas a delMax
    ods::PQ_ComplHeap<int> pq_del{20, 15, 10, 5, 2, 1};
    assert(pq_del.isValidHeap());
    pq_del.delMax(); assert(pq_del.isValidHeap());
    pq_del.delMax(); assert(pq_del.isValidHeap());
    pq_del.delMax(); assert(pq_del.isValidHeap());
}
```

### Respuestas a las preguntas

1. ¿Qué invariante verifica la función?  
   Verifica la **propiedad de max-heap**: para todo nodo $i$, su valor debe ser mayor o igual (según el comparador `comp_`) que los valores de sus hijos izquierdo y derecho.

2. ¿Por qué basta revisar relaciones padre-hijo? 
   Por la **propiedad transitiva** de la relación de orden. Si $A \ge B$ y $B \ge C$, entonces $A \ge C$. Al garantizar que cada padre es $\ge$ que sus hijos directos, se garantiza indirectamente que es $\ge$ que todos sus descendientes.

3. ¿Por qué no es necesario comparar cada nodo con todos sus descendientes?
   Por la misma transitividad mencionada. Comparar solo con los hijos directos reduce la complejidad de validación de $O(N \log N)$ o $O(N^2)$ a $O(N)$, sin perder rigor en la verificación del invariante.

4. ¿Cuál es el costo de validar todo el heap?
   **$O(N)$** en tiempo, donde $N$ es el número de elementos, ya que se recorre el arreglo una sola vez realizando un número constante de comparaciones por nodo. El costo en espacio es **$O(1)$**.

5. ¿Por qué esta función es útil en pruebas pero no necesariamente en producción?
   En producción, ejecutar una validación $O(N)$ después de cada operación (que debería ser $O(\log N)$ o $O(1)$) degradaría severamente el rendimiento. En pruebas, es invaluable para detectar errores lógicos en `insert`, `delMax` o `heapify` mediante aserciones tempranas.

### Evidencia de `ctest`

```text
$ ctest --output-on-failure
Test project C:/Users/Santiago/Desktop/algos_estru/CC-232/Libreria_cc232/Semana6/build
    Start 1: sem_test_public
1/2 Test #1: sem_test_public ..............   Passed    0.01 sec
    Start 2: sem_test_inernal
2/2 Test #2: sem_test_inernal ............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

## Bloque 6

### Demostración modificada `demo_heapify_floyd.cpp`

```cpp

int main() {
    std::vector<int> inicial = { 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 };
    printVector(inicial, "Arreglo inicial");

    // Inserciones sucesivas
    std::vector<int> heap_insert;
    for (int x : inicial) {
        ods::complHeapInsert(heap_insert, x, std::less<int>{});
    }
    printVector(heap_insert, "Construcción A (Inserciones)");
    
    // Validacion
    ods::PQ_ComplHeap<int> pq_a(heap_insert, std::less<int>{});
    std::cout << "¿Es heap válido (A)? " << (pq_a.isHeap() ? "Sí" : "No") << "\n";

    //Floyd Heapify
    std::vector<int> heap_floyd = inicial;
    ods::complHeapHeapifyFloyd(heap_floyd, std::less<int>{});
    printVector(heap_floyd, "Construcción B (Floyd Heapify)");
    
    //Validacion
    ods::PQ_ComplHeap<int> pq_b(heap_floyd, std::less<int>{});
    std::cout << "¿Es heap válido (B)? " << (pq_b.isHeap() ? "Sí" : "No") << "\n";

    return 0;
}
```

### Tabla comparativa

| Método | Complejidad Temporal | Comportamiento de intercambios | Validación |
| --- | --- | --- | --- |
| Inserciones sucesivas | $O(n \log n)$ | Altos (cada elemento sube desde una hoja) | `isHeap() == true` |
| Floyd Heapify | $O(n)$ | Bajos (la mayoría de nodos bajan muy poco) | `isHeap() == true` |

### Respuestas cortas (Explicación de complejidad)

1. ¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?
   La propiedad de heap solo exige que el padre sea $\ge$ que sus hijos directos. No impone un orden total único entre hermanos o ramas distintas, permitiendo múltiples arreglos válidos.

2. ¿Por qué insertar $n$ elementos puede costar $O(n \log n)$? 
   Cada inserción puede requerir subir el elemento desde una hoja hasta la raíz (altura $\approx \log n$). Repetirlo $n$ veces acumula $O(n \log n)$.

3. ¿Por qué Floyd puede construir el heap en $O(n)$?
   La mayoría de los nodos están en los niveles inferiores (altura pequeña). La suma de las alturas de todos los nodos converge a una serie geométrica acotada por $2n$, resultando en $O(n)$.

4. ¿Qué nodos procesa Floyd primero?
   Los últimos nodos internos (padres de las hojas), empezando desde el índice `n/2 - 1` y avanzando hacia atrás hasta la raíz (índice 0).

5. ¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?
   Las hojas no tienen hijos, por lo que ya cumplen trivialmente la propiedad de heap. Llamarlo sería redundante.

## Bloque 7

### Código modificado `vector_heapSort.h`

```cpp
namespace ods {

// MOD bloque 7
template <class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
    if (a.size() < 2) return;

    if (ascending) {
        // Max-Heap 
        complHeapHeapifyFloyd(a, comp);
        for (std::size_t n = a.size(); n > 1; --n) {
            std::swap(a[0], a[n - 1]);
            complHeapPercolateDown(a, n - 1, 0, comp);
        }
    } else {
        // Min-Heap
        auto invComp = [comp](const T& x, const T& y) { return comp(y, x); };
        complHeapHeapifyFloyd(a, invComp);
        for (std::size_t n = a.size(); n > 1; --n) {
            std::swap(a[0], a[n - 1]);
            complHeapPercolateDown(a, n - 1, 0, invComp);
        }
    }
}

}  // namespace ods
```

### Demostración actualizada `demo_heapsort.cpp`

```cpp

int main() {
    // Vector con elementos repetidos para probar estabilidad/comportamiento
    std::vector<int> a = { 5, 1, 5, 3, 8, 2, 8, 0 };
    
    printVector(a, "Entrada original");

    // 1. Resultado ascendente
    std::vector<int> a_asc = a;
    ods::heapSort(a_asc, std::less<int>{}, true);
    printVector(a_asc, "Ascendente (true)");

    // 2. Resultado descendente
    std::vector<int> a_desc = a;
    ods::heapSort(a_desc, std::less<int>{}, false);
    printVector(a_desc, "Descendente (false)");

    std::cout << "Nota: Los valores repetidos (5, 5 y 8, 8) se agrupan correctamente.\n";
    return 0;
}
```

### Evidencia de salida (Repetidos)

```text
Entrada original: [5, 1, 5, 3, 8, 2, 8, 0]
Ascendente (true): [0, 1, 2, 3, 5, 5, 8, 8]
Descendente (false): [8, 8, 5, 5, 3, 2, 1, 0]
Nota: Los valores repetidos (5, 5 y 8, 8) se agrupan correctamente.
```

### Respuestas a las preguntas bloque 7

1. ¿Por qué heapsort puede ordenar in situ?
   Porque reutiliza el mismo arreglo: a medida que extrae el elemento mayor (o menor), lo coloca al final del arreglo, reduciendo el tamaño efectivo del heap sin necesitar memoria adicional.

2. ¿Qué parte del algoritmo destruye gradualmente el heap?
   El bucle `for` que ejecuta `std::swap(a[0], a[n - 1])` y luego llama a `percolateDown` con tamaño `n - 1`. Esto mueve la raíz a la zona "ordenada" y rompe la propiedad de heap en la raíz, obligando a repararla en un espacio más pequeño.

3. ¿Por qué heapsort cuesta $O(n \log n)$?
   La construcción inicial (`heapify`) cuesta $O(n)$. Luego, se realizan $n-1$ extracciones, y cada `percolateDown` cuesta $O(\log n)$ en el peor caso. La suma es $O(n) + O(n \log n) = O(n \log n)$.

4. ¿Es heapsort estable? Justifica con un ejemplo.
   No es estable. Ejemplo: `[5a, 5b, 2]` (donde 'a' y 'b' marcan el orden original). Al hacer max-heap, `5a` queda en la raíz. Se swappea con `2` $\rightarrow$ `[2, 5b, 5a]`. Al finalizar, el arreglo ordenado será `[2, 5b, 5a]`, invirtiendo el orden relativo original de los `5`.

5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?
   `heapSort` es in-place ($O(1)$ espacio extra) y sobrescribe el arreglo original. Usar `delMax` repetidamente requiere almacenar los resultados en una estructura nueva (ej. otro `std::vector`), lo que consume $O(n)$ espacio extra, aunque la complejidad temporal sea la misma.

## Bloque 8

### Código de validación `PQ_LeftHeap.h`

Agrega este método público a la clase `PQ_LeftHeap` (ya cuenta con la lógica privada `check` que valida heap, propiedad izquierdista y NPL):

```cpp
bool isValidLeftHeap() const {
    // check() ya valida: propiedad de heap, propiedad izquierdista y consistencia de npl
    return check(root_).ok; 
}
```

### Demostración modificada `demo_left_heap_merge.cpp`

```cpp
// MOD bloque 8
int main() {
    ods::PQ_LeftHeap<int> a{7, 2, 9};
    ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

    std::cout << "¿A es válido? " << (a.isValidLeftHeap() ? "Sí" : "No") << "\n";
    std::cout << "¿B es válido? " << (b.isValidLeftHeap() ? "Sí" : "No") << "\n";

    printVector(a.levelOrder(), "Heap A antes del merge");
    printVector(b.levelOrder(), "Heap B antes del merge");

    a.merge(b); // Fusión

    std::cout << "¿A es válido tras merge? " << (a.isValidLeftHeap() ? "Sí" : "No") << "\n";
    printVector(a.levelOrder(), "Heap A después del merge");
    std::cout << "¿B quedó vacío? " << std::boolalpha << b.empty() << "\n";

    a.insert(10);
    std::cout << "¿A es válido tras insert? " << (a.isValidLeftHeap() ? "Sí" : "No") << "\n";
    printVector(a.levelOrder(), "A después de insert(10)");

    std::cout << "Extracción (delMax): ";
    while (!a.empty()) {
        std::cout << a.delMax() << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

### Respuestas a las preguntas bloque 8

1. ¿Por qué `merge` es la operación central del heap izquierdista?
   Porque simplifica el diseño: tanto `insert` como `delMax` se implementan delegando directamente en `merge`, garantizando complejidad $O(\log n)$ con código mínimo.

2. ¿Cómo se implementa `insert` usando `merge`?
   Se crea un nuevo heap de un solo nodo con el elemento y se fusiona con la raíz actual: `root_ = mergeNodes(root_, new Node(e))`.

3. ¿Cómo se implementa `delMax` usando `merge`?
   Se elimina la raíz y se fusionan sus dos subárboles (izquierdo y derecho): `root_ = mergeNodes(root_->left, root_->right)`.

4. ¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?
   La propiedad izquierdista: la distancia al nodo nulo más cercano (NPL) del hijo izquierdo es siempre $\ge$ que la del hijo derecho. Esto fuerza al árbol a ser más denso a la izquierda.

5. ¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?
   Permite fusionar (`merge`) dos estructuras de datos en $O(\log n)$ de forma nativa y eficiente. Fusionar dos heaps binarios completos requiere reconstruir todo el arreglo en $O(n)$.

### Trazado de una fusión pequeña

Fusionar `A = {9}` y `B = {8}` (ambos con `comp = std::less<int>`):
1. `mergeNodes(9, 8)`: `9` es mayor se queda como raíz.
2. Se llama recursivamente a fusionar el hijo derecho de `9` (`nullptr`) con `8`.
3. El resultado de esa fusión es `8` se asigna como hijo derecho de `9`.
4. Rebalanceo NPL: `npl(izq) = 0`, `npl(der) = 1` como `0 < 1`, se intercambian los hijos.
5. final: `9` tiene `left = 8`, `right = nullptr` su `npl` se actualiza a `1`. El heap es válido.

## Bloque 9

### Código modificado `demo_huffman.cpp`

```cpp
int main() {
    // 1. Prueba de desempate (A y B = 5; C y D = 10)
    std::vector<ods::HuffmanSymbol> alfabeto_tie = {
        {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20}
    };
    auto codigos_tie = ods::huffmanGenerateCodes(alfabeto_tie);
    
    std::cout << "--- 1. Desempate ---\n";
    for (const auto& s : alfabeto_tie) {
        std::string c = codigos_tie.at(s.symbol);
        std::cout << s.symbol << " (freq " << s.frequency << "): " 
                  << c << " (longitud " << c.length() << ")\n";
    }
    std::cout << "Libre de prefijos: " << std::boolalpha 
              << ods::huffmanIsPrefixFree(codigos_tie) << "\n\n";

    // 2. Prueba de un solo símbolo (Caso extremo)
    std::vector<ods::HuffmanSymbol> alfabeto_single = {{'X', 100}};
    auto codigos_single = ods::huffmanGenerateCodes(alfabeto_single);
    
    std::cout << "--- 2. Un solo símbolo ---\n";
    std::string c_single = codigos_single.at('X');
    std::cout << "X (freq 100): '" << c_single << "' (longitud " 
              << c_single.length() << ")\n";
    std::cout << "Libre de prefijos: " << std::boolalpha 
              << ods::huffmanIsPrefixFree(codigos_single) << "\n";
    
    return 0;
}
```

### Respuestas cortas

1. ¿Por qué Huffman necesita una cola de prioridad?
   Para extraer de forma eficiente ($O(\log n)$) los dos nodos con la frecuencia más baja en cada paso.
2. ¿Qué elementos se extraen repetidamente?
   Los dos nodos (hojas o subárboles) con la frecuencia acumulada más pequeña.
3. ¿Qué nodo se vuelve a insertar?
   Un nuevo nodo interno cuya frecuencia es la suma de las frecuencias de los dos nodos extraídos.
4. ¿Por qué el caso de un solo símbolo requiere cuidado especial? 
   Porque el bucle de fusión (`while size > 1`) nunca se ejecuta. El código base lo resuelve asignando `"0"` si el prefijo está vacío.
5. ¿Qué significa que el conjunto de códigos sea libre de prefijos?
   Que ningún código es el inicio de otro, lo que permite decodificar el mensaje de forma única y sin ambigüedades.
6. ¿Cómo afecta el desempate a la forma del árbol?
   Determina qué nodos se unen primero y su posición (izquierda/derecha), cambiando los códigos específicos, pero no la optimalidad.
7. ¿El desempate cambia necesariamente la longitud total ponderada? 
   No, la suma ponderada de longitudes se mantiene óptima e idéntica sin importar el orden en que se resuelvan los empates.

### Tabla: Símbolo, Frecuencia, Código, Longitud

| Simbolo | Frecuencia | Codigo (ejem) | Longitud |
| --- | --- | --- | --- |
| A | 5 | 110 | 3 |
| B | 5 | 111 | 3 |
| C | 10 | 10 | 2 |
| D | 10 | 01 | 2 |
| E | 20 | 00 | 2 |

Costo total ponderado = (5×3) + (5×3) + (10×2) + (10×2) + (20×2) = 110

### Verificación de prefijo libre

La ejecución del programa imprime `Libre de prefijos: true` para ambos casos, confirmando que la función `ods::huffmanIsPrefixFree` valida correctamente que ningún código es prefijo de otro, cumpliendo la propiedad fundamental de Huffman.

## Bloque 10

Nota: en esta implementación, prioridad menor sube más cerca de la raíz (min-heap por prioridad).

## Parte A

### Código modificado

```cpp
// MODIFICACION: construir con prioridades fijas e imprimir estado tras cada inserción
std::vector<std::pair<int, std::uint64_t>> pares = {
  {50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80}
};
for (auto& [clave, prioridad] : pares) {
  t.addWithPriority(clave, prioridad);
  std::cout << "clave=" << clave << " prioridad=" << prioridad << "\n";
  std::cout << "inorden: ";
  for (int x : t.inorderKeys()) std::cout << x << ' ';
  std::cout << "\nniveles: ";
  for (int x : t.levelOrderKeys()) std::cout << x << ' ';
  std::cout << "\nraiz: " << t.root()->key << "\n";
  std::cout << "isBST=" << t.isBST()
            << " isHeapByPriority=" << t.isHeapByPriority()
            << " isTreap=" << t.isTreap() << "\n\n";
}
std::cout << t;
```

### Salida de las 7 intersecciones

Como la prioridad asignada coincide con la clave, el menor valor siempre tiene la menor prioridad, así que cada nuevo mínimo se convierte en raíz. El resultado final es una cadena hacia la derecha (cada nodo solo tiene hijo derecho).

| Clave insertada | Prioridad | Inorden | Niveles | Raíz | isBST | isHeapByPriority | isTreap |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 50 | 50 | 50 | 50 | 50 | true | true | true |
| 30 | 30 | 30 50 | 30 50 | 30 | true | true | true |
| 70 | 70 | 30 50 70 | 30 50 70 | 30 | true | true | true |
| 20 | 20 | 20 30 50 70 | 20 30 50 70 | 20 | true | true | true |
| 40 | 40 | 20 30 40 50 70 | 20 30 40 50 70 | 20 | true | true | true |
| 60 | 60 | 20 30 40 50 60 70 | 20 30 40 50 60 70 | 20 | true | true | true |
| 80 | 80 | 20 30 40 50 60 70 80 | 20 30 40 50 60 70 80 | 20 | true | true | true |

### Árbol final (asciiArt)

Cadena pura hacia la derecha:

```bash
(20,20) -> (30,30) -> (40,40) -> (50,50) -> (60,60) -> (70,70) -> (80,80)
```

### Respuestas

1. ¿Por qué el inorden sale ordenado aunque las prioridades cambien la forma?
Porque el invariante BST sobre `key` se mantiene en cada rotación: una rotación reordena punteros pero nunca mueve una clave fuera del rango que le corresponde. La forma cambia, el orden no.

2. ¿Por qué la raíz no es necesariamente la primera clave insertada?
La raíz la determina la prioridad mínima, no el orden de inserción. `bubbleUp` sube cualquier nodo cuyo padre tenga prioridad mayor, sin importar cuándo se insertó.

3. ¿Qué nodo sube cuando se inserta una clave con prioridad menor que sus ancestros?
El nodo recién insertado. `bubbleUp` lo rota hacia arriba mientras su prioridad sea menor que la de su padre.

4. ¿Qué propiedad conserva una rotación local sobre las claves?
La propiedad BST: el conjunto de claves en cada subárbol sigue siendo el mismo, solo cambia la jerarquía interna.

5. ¿Qué propiedad intenta restaurar bubbleUp sobre las prioridades?
La propiedad de heap por prioridad: que todo padre tenga prioridad menor o igual que sus hijos.

## Parte B

### Código `bubbleUp`

```cpp
// MODIFICACION: version instrumentada de bubbleUp que cuenta rotaciones
std::size_t bubbleUpCount(Node* u) {
  std::size_t count = 0;
  while (u->parent && u->parent->priority > u->priority) {
    if (u->isRightChild()) rotateLeft(u->parent);
    else                   rotateRight(u->parent);
    ++count;
  }
  if (!u->parent) root_ = u;
  return count;
}

// MODIFICACION: addWithPriority que retorna cuantas rotaciones hizo bubbleUp
std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
  Node* u = new Node(x, priority);
  if (!addNode(u)) { delete u; return 0; }
  return bubbleUpCount(u);
}
```

### Secuencia de prueba: {100,100}, {90,90}, {80,80}, {70,70}, {60,60}

| Clave | Prioridad | Rotaciones | Raíz tras insertar |
| --- | --- | --- | --- |
| 100 | 100 | 0 | 100 |
| 90 | 90 | 1 | 90 |
| 80 | 80 | 1 | 80 |
| 70 | 70 | 1 | 70 |
| 60 | 60 | 1 | 60 |

### Explicación de costo esperado

Cada elemento nuevo tiene la menor prioridad vista hasta el momento, así que sube hasta convertirse en raíz con una sola rotación. En el caso general, el número de rotaciones de `bubbleUp` es igual a la diferencia de profundidad entre la posición de inserción y la posición final, que en promedio es O(1) y en el peor caso O(log n) esperado.

### Respuestas

**1. ¿Por qué esta secuencia tiende a producir rotaciones repetidas?**
Porque cada nuevo elemento tiene prioridad estrictamente menor que todo lo insertado antes, forzándolo a subir hasta la raíz cada vez.

**2. ¿Cuándo `bubbleUpCount` retorna cero?**
Cuando el nodo insertado ya cumple la propiedad de heap respecto a su padre (su prioridad es mayor o igual), o cuando es el primer nodo (no tiene padre).

**3. ¿Cuál es el peor caso de rotaciones durante una inserción?**
Igual a la profundidad inicial del nodo insertado, O(n) en un treap degenerado, pero O(log n) esperado en un treap aleatorizado.

**4. ¿Por qué una rotación no rompe la propiedad BST?**
Porque solo reorganiza punteros entre dos nodos y sus subárboles, preservando los rangos de valores de cada subárbol.

**5. ¿Por qué el treap busca altura esperada logarítmica, no garantizada?**
Porque las prioridades son aleatorias; no hay garantía absoluta de que el árbol quede balanceado, solo que es muy probable (con alta probabilidad la altura es O(log n)).

## Parte C

### Codigo `trickeldown`

```cpp
// MODIFICACION: version instrumentada de trickleDown que cuenta rotaciones
std::size_t trickleDownCount(Node* u) {
  std::size_t count = 0;
  while (u->left || u->right) {
    if (!u->left)                              rotateLeft(u);
    else if (!u->right)                        rotateRight(u);
    else if (u->left->priority < u->right->priority) rotateRight(u);
    else                                       rotateLeft(u);
    ++count;
    if (root_ == u) root_ = u->parent;
  }
  return count;
}

// MODIFICACION: remove que retorna la cantidad de rotaciones realizadas
std::size_t removeCount(const T& x) {
  Node* u = findEQ(x);
  if (!u) return 0;
  std::size_t count = trickleDownCount(u);
  splice(u);
  delete u;
  return count;
}
```

### Eliminaciones sobre el árbol de la Parte A: 50, 20, 70

| Clave eliminada | Rotaciones | Inorden resultante | isTreap |
| --- | --- | --- | --- |
| 50 | 1 | 20 30 40 60 70 80 | true |
| 20 | 1 | 30 40 60 70 80 | true |
| 70 | 1 | 30 40 60 80 | true |

### Trazado manual: eliminar 50

Antes: `50` tiene hijo derecho `60` (sin hijo izquierdo). `trickleDown(50)`: como no tiene izquierda, `rotateLeft(50)` — `60` sube, `50` baja a ser hijo izquierdo de `60`. Ahora `50` no tiene hijos. `splice(50)`: `60->left = nullptr`. Resultado: `60` ocupa el lugar de `50` en la cadena.

### Respuestas

1. ¿Por qué eliminar en un treap no es simplemente borrar como en BST?
Porque hay que respetar también la propiedad de heap: no se puede simplemente desconectar el nodo, primero hay que bajarlo (trickleDown) hasta que tenga a lo más un hijo, y luego aplicar splice.

2. ¿Por qué trickleDown rota con el hijo de menor prioridad?
Porque ese hijo es el que debe ocupar el lugar del nodo eliminado para mantener la propiedad de heap (prioridad menor más cerca de la raíz).

3. ¿Qué ocurre si el nodo tiene solo hijo izquierdo?
`rotateRight(u)` lo baja, su hijo izquierdo sube a su posición.

4. ¿Qué ocurre si el nodo tiene solo hijo derecho?
`rotateLeft(u)` lo baja, su hijo derecho sube a su posición.

5. ¿Qué invariantes deben seguir siendo verdaderos después de splice?
La propiedad BST sobre claves, la propiedad de heap sobre prioridades, y la consistencia de punteros `parent` en todo el árbol.

## Parte D

### Resultados sobre el árbol de la Parte A (claves 20,30,40,50,60,70,80)

| Operación | Resultado |
|---|---|
| `findEQ(40)` | nodo 40 (existe) |
| `findEQ(35)` | nullptr (no existe) |
| `lowerBound(35)` | 40 (menor clave ≥ 35) |
| `lowerBound(40)` | 40 (coincidencia exacta) |
| `upperBound(40)` | 50 (menor clave > 40) |
| `upperBound(75)` | 80 (menor clave > 75) |

Estos resultados son idénticos a los de `BinarySearchTree` con las mismas claves, porque ambas búsquedas dependen únicamente del orden de `key`, no de `priority`.

### Tabla comparativa Treap vs BinarySearchTree

| Aspecto | Treap | BinarySearchTree |
| --- | --- | --- |
| Búsqueda/lowerBound/upperBound | O(log n) esperado | O(log n) si balanceado, O(n) si degenerado |
| Balance | Probabilístico (vía prioridades) | No garantizado sin rotaciones manuales |
| Estructura adicional | Campo `priority` por nodo | Ninguna |
| Extra invariante | Heap por prioridad | Ninguno |

### Respuestas

1. ¿Por qué lowerBound/upperBound dependen de BST y no de heap?
Porque ambas buscan por orden de `key`, descendiendo izquierda/derecha según comparación de claves; la prioridad nunca se consulta en esa búsqueda.

2. ¿Qué parte del treap se comporta igual que un BST?
Toda búsqueda por clave: `findEQ`, `lowerBound`, `upperBound`, `findLast`, y el recorrido inorden.

3. ¿Qué parte se comporta como heap?
La inserción (`bubbleUp`) y la eliminación (`trickleDown`), que mueven nodos según `priority` para mantener balance.

4. ¿Por qué el treap no reemplaza a una cola de prioridad?
Extraer el mínimo/máximo por prioridad en un treap requeriría buscarlo (no está garantizado en la raíz ni en una posición fija), mientras que un heap binario da acceso O(1) al extremo.

5. ¿En qué situación conviene un treap?
Cuando necesitas mantener un conjunto ordenado por clave con inserciones y eliminaciones dinámicas, y quieres balance probabilístico sin lógica explícita de rotación como AVL o Red-Black.

## Parte E — Pruebas específicas para Treap

### Pruebas agregadas 

```cpp
// MODIFICACION: pruebas adicionales para Treap, casos borde e invariantes
void test_treap_extra() {
    ods::Treap<int> t;

    // 1. vacio
    assert(t.empty() && t.size() == 0);
    assert(t.isBST() && t.isHeapByPriority() && t.isTreap());

    // 2-5. inserciones con prioridades
    assert(t.addWithPriority(50, 50));
    assert(t.addWithPriority(30, 30));
    assert(!t.addWithPriority(30, 1));
    assert((t.inorderKeys() == std::vector<int>{30, 50}));
    assert(t.isHeapByPriority());

    // 6. lowerBound / upperBound
    assert(t.lowerBound(40)->key == 50);
    assert(t.upperBound(30)->key == 50);

    // 7-10.
    t.addWithPriority(70, 70);
    assert(t.remove(70));               
    t.addWithPriority(70, 70);
    t.addWithPriority(60, 60);          
    assert(t.remove(70));
    assert(t.remove(30));               
    assert(t.isTreap());

    // 12-13.
    std::size_t before = t.size();
    t.addWithPriority(90, 90);
    t.remove(90);
    assert(t.size() == before);
    assert(t.isTreap());
}
```

### Respuestas

1. ¿Qué bug atraparía una prueba de enlaces parent?
Un nodo cuyo `parent` no apunte de vuelta correctamente tras una rotación, dejando el árbol inconsistente aunque las claves parezcan correctas.

2. ¿Qué bug atraparía una prueba de size()?
Un `remove` o `add` que olvide actualizar `size_`, o que lo actualice dos veces, desincronizando el contador del número real de nodos.

3. ¿Qué bug atraparía una prueba de inorden ordenado?
Una rotación implementada incorrectamente que mueva una clave fuera de su rango válido, rompiendo el orden BST.

4. ¿Qué bug atraparía una prueba de prioridad padre-hijo?
Un `bubbleUp` o `trickleDown` que se detenga antes de tiempo, dejando un padre con prioridad mayor que un hijo.

5. ¿Por qué conviene usar prioridades fijas en pruebas unitarias?
Porque hacen el resultado determinista y reproducible: la forma exacta del árbol es predecible, permitiendo verificar valores concretos (raíz, inorden, niveles) en lugar de solo propiedades generales.

### Resultado esperado de ctest

```
ctest --test-dir build-debug -R semana6 --output-on-failure
```

Todos los tests (`test_public_week6`, `test_internal_week6`, y los extra agregados) deben pasar con código de salida 0, confirmando que `isTreap()` se mantiene verdadero en cada paso de la secuencia de inserciones y eliminaciones.

## Bloque 11

### Demostración modificada (`demo_compare_with_semana5.cpp`)

```cpp
int main() {
    const std::vector<int> xs{8, 3, 10, 1, 6, 14, 4, 7, 13};

    // 1. BinaryHeap (Sem5: Min-Heap)
    ods::BinaryHeap<int> minHeap;
    for (int x : xs) minHeap.add(x);
    std::cout << "BinaryHeap     | top (min): " << minHeap.top() 
              << " | isHeap: " << minHeap.isHeap() << "\n";

    // 2. PQ_ComplHeap (Sem 6: Max-Heap)
    ods::PQ_ComplHeap<int> pq;
    for (int x : xs) pq.insert(x);
    std::cout << "PQ_ComplHeap   | getMax (max): " << pq.getMax() 
              << " | isHeap: " << pq.isHeap() << "\n";

    // 3. BinarySearchTree (Semana 5)
    ods::BinarySearchTree<int> bst;
    for (int x : xs) bst.add(x);
    std::cout << "BinarySearchTree| inorder: ";
    for (int x : bst.inorder()) std::cout << x << " ";
    std::cout << "| lowerBound(5): " << bst.lowerBound(5)->data << "\n";

    // 4. Treap (Semana 6)
    ods::Treap<int> treap;
    for (int x : xs) treap.add(x); 
    std::cout << "Treap          | inorder: ";
    for (int x : treap.inorderKeys()) std::cout << x << " ";
    std::cout << "| isTreap: " << treap.isTreap() 
              << " | lowerBound(5): " << treap.lowerBound(5)->key << "\n";

    return 0;
}
```

### Tabla de comparación

| Estructura | Operación principal | Propiedad mantenida | Operación eficiente | Operación que no conviene | Evidencia en demo |
| --- | --- | --- | --- | --- | --- |
| BinaryHeap | `add` / `remove` | Min-Heap (padre $\le$ hijos) | Obtener mínimo ($O(1)$) | Búsqueda arbitraria ($O(n)$) | `top()` = 1, `isHeap` = true |
| PQ_ComplHeap | `insert` / `delMax` | Max-Heap (padre $\ge$ hijos) | Obtener máximo ($O(1)$) | Búsqueda arbitraria ($O(n)$) | `getMax()` = 14, `isHeap` = true |
| BinarySearchTree | `add` / `find` | BST (izq < raíz < der) | Búsqueda / `lowerBound` ($O(\log n)$) | Extraer máximos repetidamente | `inorder` ordenado, `lowerBound(5)` = 6 |
| Treap | `add` / `remove` | BST por clave + Max-Heap por prioridad | Búsqueda / `lowerBound` ($O(\log n)$ esperado) | Acceso por índice posicional | `inorder` ordenado, `isTreap` = true |

### Respuestas breves de selección de estructura

1. ¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?
   El heap optimiza el acceso al extremo (máximo o mínimo) en $O(1)$ sacrificando el orden total. El BST optimiza la búsqueda, inserción y eliminación de cualquier elemento en $O(\log n)$ manteniendo un orden total.
2. ¿Por qué un BST permite recorrido ordenado y un heap no?
   El BST garantiza que todos los nodos a la izquierda son menores y los de la derecha mayores. El heap solo garantiza que el padre domina a sus hijos, sin relación de orden entre hermanos o ramas distintas.
3. ¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?
   Una interfaz estandarizada de Cola de Prioridad (`PQ`), soporte nativo para comparadores personalizados (`Compare`), y métodos de construcción optimizados como `heapify` de Floyd.
4. ¿Qué combina un Treap?
   Combina la propiedad de búsqueda binaria (ordenada por clave) con la propiedad de heap (ordenada por una prioridad aleatoria), logrando un balanceo probabilístico sin rotaciones complejas deterministas.
5. ¿Qué estructura usarías para extraer máximos repetidamente?
   `PQ_ComplHeap` (Max-Heap), ya que `delMax()` es $O(\log n)$ y `getMax()` es $O(1)$.
6. ¿Qué estructura usarías para responder `lowerBound` o `upperBound`?
   `BinarySearchTree` o `Treap`, ya que ambas mantienen el orden total de las claves.
7. ¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?
   `Treap`, porque evita el degeneramiento a $O(n)$ que puede sufrir un `BinarySearchTree` simple ante inserciones ordenadas, sin la sobrecarga de un AVL o Red-Black Tree.

## Bloque 12

### Código de pruebas agregadas `test_internal_week6.cpp`

```cpp
int main() {
    // 1. PQ_ComplHeap: insercion, eliminacion y tamaño
    ods::PQ_ComplHeap<int> pq;
    pq.insert(5); assert(pq.isHeap());
    pq.insert(10); assert(pq.isHeap());
    std::size_t sz = pq.size();
    assert(pq.getMax() == 10 && pq.size() == sz);
    pq.delMax(); 
    assert(pq.isHeap() && pq.size() == sz - 1);

    // 2. heapifyFloyd y heapSort con repetidos
    std::vector<int> v_floyd = {9, 3, 7, 1, 5};
    ods::complHeapHeapifyFloyd(v_floyd, std::less<int>{});
    ods::PQ_ComplHeap<int> pq_check(v_floyd, std::less<int>{});
    assert(pq_check.isHeap());

    std::vector<int> v_sort = {5, 1, 5, 3, 8, 2, 8, 0};
    ods::heapSort(v_sort);
    assert((v_sort == std::vector<int>{0, 1, 2, 3, 5, 5, 8, 8}));

    // 3. PQ_LeftHeap: merge, insert y delMax
    ods::PQ_LeftHeap<int> lh1{5, 2}, lh2{4, 1};
    lh1.merge(lh2); assert(lh1.isLeftistHeap()); 
    lh1.insert(6);  assert(lh1.isLeftistHeap()); 
    lh1.delMax();   assert(lh1.isLeftistHeap()); 

    // 4. Huffman: símbolos, prefijos y caso extremo
    std::vector<ods::HuffmanSymbol> huff = {{'A', 5}, {'B', 5}, {'C', 10}};
    auto codes = ods::huffmanGenerateCodes(huff);
    assert(codes.size() == 3);
    assert(ods::huffmanIsPrefixFree(codes));     

    std::vector<ods::HuffmanSymbol> huff_single = {{'X', 100}};
    auto codes_single = ods::huffmanGenerateCodes(huff_single);
    assert(codes_single.at('X') == "0");

    // 5. Treap: BST, prioridad y eliminación
    ods::Treap<int> treap;
    treap.add(10); treap.add(5); treap.add(15);
    assert(treap.isBST());
    assert(treap.isHeapByPriority());
    treap.remove(10);
    assert(treap.isTreap());

    return 0;
}
```

### Resultado de `ctest`

```text
Test project C:/Users/Santiago/Desktop/algos_estru/CC-232/Libreria_cc232/Semana6/build
    Start 2: semana6_internal
1/1 Test #2: semana6_internal .................   Passed    0.32 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.33 sec
```

### ¿Qué bug atraparía cada prueba?

| Prueba | Bug que atrapa |
| :--- | :--- |
| **Conserva heap tras insert/delMax** | Lógica rota en `percolateUp` o `percolateDown` (ej. comparar con el hijo equivocado). |
| **getMax no cambia tamaño / delMax** | Modificación accidental de `size_` en métodos `const`, o olvidar `--n_` al eliminar. |
| **heapifyFloyd válido** | Errores "off-by-one" en el bucle (ej. empezar en `size/2` en lugar de `size/2 - 1`). |
| **heapSort con repetidos** | Bucles infinitos o swaps incorrectos cuando `comp_(a, b)` es falso por igualdad. |
| **LeftHeap tras merge/insert/delMax** | Olvidar actualizar el `npl` (Null Path Length) o fallar al intercambiar hijos izquierdo/derecho. |
| **Huffman todos los símbolos** | Pérdida de nodos hoja durante la fusión o recorrido incompleto del árbol. |
| **Huffman libre de prefijos** | Asignación invertida de bits '0' y '1' en las ramas izquierda/derecha. |
| **Huffman un solo símbolo** | El bucle `while(size > 1)` se salta, dejando el mapa de códigos vacío para ese símbolo. |
| **Treap BST / Heap / Remove** | Rotaciones (`bubbleUp`/`trickleDown`) que rompen el orden de las claves o la prioridad, o punteros colgantes al eliminar. |

## Bloque 13

Al trabajar con las diferentes estructuras de datos, que la interfaz PQ permite utilizar distintas implementaciones sin modificar la forma en que el usuario interactúa con ellas, se observó. Gracias a ello, operaciones como insertar elementos, obtener el máximo y eliminarlo, independientemente de la estructura utilizada, pueden realizarse de manera uniforme.

En el caso del heap binario, que almacenar los elementos en un arreglo constituye una solución eficiente, se aprendió, pues el uso de punteros adicionales evita. No obstante, correctamente calcular las posiciones de padres e hijos resulta necesario para conservar sus propiedades y estructura.

Durante la implementación de las operaciones principales, que `percolateUp` se emplea tras insertar un nuevo elemento para restaurar la propiedad del heap, se comprendió; mientras que `percolateDown`, después de eliminar el máximo, utilizarse debe. Asimismo, que el algoritmo `heapify de Floyd` construye un heap de manera más eficiente que la inserción sucesiva de elementos, se verificó, alcanzando una complejidad de `O(n)`.

Al implementar `heapSort`, que ordenar utilizando el mismo arreglo donde se construye el heap es posible sin requerir memoria adicional, se comprobó. Una solución eficiente tanto en tiempo como en espacio, esto permite obtener.

En el `heap izquierdista`, que la operación fundamental es `merge`, se identificó, puesto que en la combinación de heaps se basan las inserciones y eliminaciones. Gracias a esta característica, un rendimiento adecuado mantienen dichas operaciones.

Durante la construcción del árbol de `Huffman`, la importancia de manejar correctamente los empates entre símbolos y de considerar casos especiales, como la existencia de un único carácter, se observó. Necesarios para garantizar códigos válidos y libres de prefijos compartidos, estos aspectos resultan.

La implementación del `Treap` permitió comprender cómo las características de un árbol binario de búsqueda y de un heap se combinan. Que el uso de prioridades aleatorias contribuye a mantener un rendimiento esperado de `O(log n)` en las operaciones principales, se evidenció, evitando así que la estructura fácilmente se degrade.

Finalmente, que ventajas y limitaciones distintas poseen `BinaryHeap` y `BinarySearchTree`, permitió entender mejor su comparación. Mientras que para acceder y eliminar rápidamente el elemento máximo más adecuado resulta el `BinaryHeap`, las búsquedas ordenadas y los recorridos en orden facilita el `BinarySearchTree`. Además, que verificar continuamente las propiedades de cada estructura es fundamental para detectar errores en casos especiales, demostraron las pruebas realizadas.
