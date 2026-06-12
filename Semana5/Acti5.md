#

## Bloque 1

### 1. Árbol enlazado vs árbol en arreglo

En el árbol enlazado, mediante punteros `parent`, `left` y `right`, conectados se encuentran los nodos. En el implícito, por el contrario, inexistentes son los punteros y de la posición en el arreglo dependen las relaciones. Mayor flexibilidad ofrece el primero; mayor compacidad, el segundo.

### 2. Qué guarda un BinNode

El valor almacenado representa `data`; al padre apunta `parent`; a los subárboles izquierdo y derecho apuntan `left` y `right`; la altura del subárbol correspondiente conserva `height`.

### 3. Por qué parent permite succ(), pred() y actualización ascendente

Posible hace `parent` el movimiento hacia los ancestros. Gracias a ello pueden `succ()` y `pred()` encontrar nodos vecinos, y actualizar alturas hacia la raíz puede `updateHeightAbove()` sin reiniciar el recorrido desde arriba.

### 4. Responsabilidad de BinTree frente a BinNode

Del nodo individual se ocupa `BinNode`; del árbol completo, `BinTree`. Navegación local implementa el primero, mientras que inserciones, eliminaciones y mantenimiento global controla el segundo.

### 5. Qué agrega BinaryTree sobre BinTree

Funciones de consulta y recorrido añade `BinaryTree`. Entre ellas se encuentran profundidad, tamaño de subárbol, iteradores y representaciones visuales del árbol.

### 6. Propiedad que convierte un árbol binario en BST

Menores que el nodo actual deben ser todos los valores del subárbol izquierdo; mayores, todos los del derecho. De esa condición surge la propiedad fundamental del BST.

### 7. Propiedad que convierte un arreglo en heap mínimo

Para cada posición, menor o igual que sus hijos debe ser el elemento almacenado. Como consecuencia, en la raíz siempre se encuentra el mínimo.

### 8. Orden en BST vs prioridad en heap

Entre subárboles establece relaciones el BST; entre padres e hijos, el heap. Búsquedas eficientes permite el primero, mientras que acceso rápido al mínimo garantiza el segundo.

### 9. Por qué inorden de BST produce secuencia ordenada

Izquierda, raíz y derecha visita el recorrido inorden. Como menores quedan a la izquierda y mayores a la derecha, ordenada resulta la secuencia obtenida.

### 10. Por qué un heap no permite recorrer en orden sin destruirlo

Entre ramas distintas ninguna relación de orden garantiza un heap. Para obtener los elementos ordenados, repetidamente extraer el mínimo necesario resulta.

## Bloque 2 — Navegación, altura, profundidad y tamaño

### 1. Predicados de BinNode

- `hasLeft()`: existe hijo izquierdo.
- `hasRight()`: existe hijo derecho.
- `isRoot()`: padre no posee.
- `isLeaf()`: hijos no posee.
- `isLeftChild()`: hijo izquierdo del padre es.
- `isRightChild()`: hijo derecho del padre es.

### 2. succ() caso bajada

Si subárbol derecho existe, el sucesor será el nodo más a la izquierda dentro de dicho subárbol.

### 3. succ() caso subida

Cuando subárbol derecho no existe, por los ancestros se asciende hasta encontrar aquel del cual hijo izquierdo sea el nodo actual.

### 4. pred() simétrico

De forma análoga actúa `pred()`: busca el más a la derecha del subárbol izquierdo o asciende hasta hallar el ancestro adecuado.

### 5. Árbol de 7 nodos con sucesor y predecesor

Para el árbol dado, ordenada es la secuencia inorden:

5, 10, 15, 20, 25, 30, 35.

De ella se deduce que:

- De 10, predecesor es 5 y sucesor es 15.
- De 20, predecesor es 15 y sucesor es 25.
- De 30, predecesor es 25 y sucesor es 35.

### 6. depth(u)

Contando los enlaces desde el nodo hasta la raíz se obtiene la profundidad. Posible lo hace el puntero al padre.

### 7. height(u)

La longitud del camino más largo desde el nodo hasta una hoja representa la altura. De los descendientes depende su cálculo.

### 8. subtreeSize(u)

Todos los nodos contenidos en el subárbol enraizado en `u`, incluido el propio nodo, contabiliza esta función.

### 9. Demostración de depth(u) + height(u) <= height(T)

Desde la raíz hasta una hoja describe `depth(u) + height(u)` un camino válido. Mayor que el camino máximo del árbol no puede ser, y precisamente ese máximo corresponde a `height(T)`.

### 10. Condición para la igualdad

Cuando por el nodo pasa el camino más largo del árbol, la igualdad se cumple. Siempre la satisface la raíz, pues profundidad cero posee.

## BLOQUE 3

### 1. ¿Qué significa visitar un nodo en preorden?

Primero se procesa la raíz y luego sus hijos: raíz → izquierda → derecha.

### 2. ¿Qué significa visitar un nodo en inorden?

Entre ambos subárboles se procesa la raíz: izquierda → raíz → derecha. En un BST genera un recorrido en orden ascendente.

### 3. ¿Qué significa visitar un nodo en postorden?

Después de ambos hijos se procesa la raíz: izquierda → derecha → raíz. Útil para liberar memoria o resolver dependencias.

### 4. ¿Qué significa visitar un árbol por niveles?

Por profundidad se visitan los nodos: primero el nivel 0, luego el 1, después el 2, sucesivamente.

### 5. ¿Por qué los recorridos recursivos tienen tiempo O(n)?

Una sola vez se visita cada nodo y constante es el trabajo realizado en cada visita. Por ello, proporcional a n es el costo total.

### 6. ¿Por qué las versiones iterativas también tienen tiempo O(n)?

Una sola vez se inserta y se extrae cada nodo de la pila o cola. Proporcional a n sigue siendo el trabajo total.

### 7. ¿Memoria auxiliar de un recorrido recursivo en árbol balanceado?

O(log n), porque igual a la altura del árbol es la profundidad máxima de la pila de llamadas.

### 8. ¿Memoria auxiliar de un recorrido recursivo en árbol degenerado?

O(n), porque similar a una lista es el árbol y hasta n puede crecer la pila de llamadas.

### 9. ¿Diferencia entre pila explícita y pila de llamadas?

La misma información almacenan ambas, pero manualmente la controla el programador en la pila explícita, mientras que automáticamente la administra el lenguaje en la pila de llamadas.

### 10. ¿Por qué la cola de niveles crece más en árbol completo que en degenerado?

Muchos nodos puede contener un mismo nivel en un árbol completo, por lo que la cola puede alcanzar O(n) elementos. En un árbol degenerado, un solo nodo existe por nivel, por lo que la cola permanece constante.

## Bloque 4

### 1. Salida que verifica el orden de los recorridos en `demo_binary_tree.cpp`

La misma secuencia producen las cuatro versiones de inorden: `1 3 4 5 6 7 8 10 12`. Así se confirma que equivalentes son.

### 2. Parte que defiende que `succ()`/`pred()` respetan el inorden

`Sucesor de 5: 6` y `Predecesor de 5: 4`. Con el inorden `...4 5 6...` coinciden exactamente.

### 3. Evidencia que produce la representación ASCII

La forma del árbol muestra visualmente. Verificar permite qué nodo es hijo de cuál.

### 4. Observable en `demo_bst.cpp` que defiende el inorden ordenado

`BST inorden: 1 3 4 5 6 7 8 10 12`. Creciente es toda la secuencia, por lo que la propiedad BST se cumple.

### 5. Operación de búsqueda mejor distinguida en `demo_bst.cpp`

`findLast(9)`, porque devuelve `8` y no `9`. Claramente muestra que igualdad no busca.

### 6. Salida que defiende que el mínimo queda en la raíz

`Heapify: 1 3 8 7 5 10 2`. El menor elemento es `1` y en la raíz queda.

### 7. Evidencia que distingue `add()` de `heapify()`

Todo el arreglo reorganiza `heapify()`. Un solo elemento ajusta `add()`.

### 8. Comparación que resume mejor la semana en `demo_capitulo5_panorama.cpp`

Acceso directo al mínimo ofrece el heap. Orden total navegable mantiene el BST.

## Bloque 5 — Pruebas públicas, internas e invariantes

### 1. ¿Qué operaciones del BST valida la prueba pública?

Inserción, búsqueda y eliminación valida. Además, ordenado permanece el inorden.

### 2. ¿Qué casos validan que el BST no acepta duplicados?

Dos veces se inserta el mismo valor. La segunda inserción falla.

### 3. ¿Qué se verifica al comparar inorden recursivo con versiones iterativas?

La misma secuencia generan todas las versiones. Equivalentes son.

### 4. ¿Qué se espera de `findEQ(8)`?

El nodo 8 retorna si existe. `nullptr` si no existe.

### 5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?

Ambas operaciones retornan 10.

### 6. ¿Qué propiedad se valida con `isBST()`?

Menores quedan a la izquierda y mayores a la derecha.

### 7. ¿Qué se valida después de eliminar un nodo con `remove()`?

Ordenado sigue el inorden y disminuye el tamaño.

### 8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar?

Correctos siguen los punteros `parent`.

### 9. ¿Qué operaciones del heap valida la prueba pública?

`heapify()`, `add()`, `remove()`, `top()` e `isHeap()`.

### 10. ¿Qué demuestra extraer repetidamente hasta vaciarlo?

En orden salen todos los elementos.

### 11. ¿Qué operaciones de BinTree se validan con `attachAsRC`, `secede` y `removeSubtree`?

Conectar, separar y eliminar subárboles permiten.

### 12. ¿Qué agregan las pruebas internas?

Invariantes, rotaciones y casos especiales verifican.

### 13. ¿Qué sí demuestra pasar las pruebas públicas?

Que funcionan los casos más comunes.

### 14. ¿Qué no demuestra pasar las pruebas públicas?

Ni todos los casos borde ni la complejidad garantizan.

### 15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad?

Porque entender el funcionamiento también importa.

## Bloque 6

### 1. En BinNode, ¿qué invariantes deben mantenerse?

Un único padre válido tiene cada nodo y ciclos no existen.

### 2. ¿Por qué `insertAsLC` e `insertAsRC` rechazan si ya existe el hijo?

Evitan sobrescribir un subárbol existente.

### 3. Explica cómo `size()` de BinNode recorre el subárbol

El nodo actual y ambos hijos suma recursivamente.

### 4. Explica `leftmost()` y `rightmost()`

Hasta el extremo izquierdo o derecho avanzan.

### 5. Explica `succ()` paso a paso

Busca el siguiente nodo en inorden.

### 6. Explica `pred()` paso a paso

Busca el nodo anterior en inorden.

### 7. En BinTree, ¿qué papel cumplen `root_` y `size_`?

La raíz guarda uno y el total de nodos el otro.

### 8. ¿Qué hace `updateHeight(Node*)`?

La altura del nodo recalcula.

### 9. ¿Qué hace `updateHeightAbove` y por qué sube?

Actualiza alturas hasta llegar a la raíz.

### 10. ¿Cómo `attachAsLC/RC` transfieren un subárbol?

Lo conectan como hijo y actualizan enlaces.

### 11. ¿Diferencia entre `removeSubtree` y `secede`?

Uno destruye el subárbol y el otro lo conserva.

### 12. ¿Por qué `secede` no destruye?

Porque útil sigue siendo el subárbol.

### 13. ¿Por qué `removeSubtree` sí destruye?

Porque eliminarlo es su objetivo.

### 14. ¿Qué verifica `checkParentLinks()`?

Que correctos son los enlaces padre-hijo.

### 15. En BinaryTree, explica `firstNode`, `lastNode`, `nextNode`, `prevNode`

Primer, último, siguiente y anterior nodo obtienen.

### 16. ¿Por qué un iterador basado en `succ()` produce inorden?

Porque al siguiente nodo en inorden avanza.

### 17. ¿Qué aporta `asciiArt()` para depuración?

La forma real del arbol muestra.

## Bloque 7

### 1. Define formalmente la propiedad BST

Menores a la izquierda y mayores a la derecha.

### 2. ¿Por qué el inorden de un BST produce secuencia ordenada?

Porque entre menores y mayores visita cada nodo.

### 3. Diferencia entre `find`, `findEQ`, `lowerBound`, `upperBound`

Igualdad exacta busca `findEQ`; rangos buscan los demás.

### 4. ¿Por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no?

Porque igualdad exacta requiere `findEQ`.

### 5. Construye manualmente el BST para 7, 3, 10, 1, 5, 8, 12, 4, 6

```bash
       7
      / \
     3   10
    / \  / \
   1  5 8  12
     / \
    4   6
```

### 6. Recorridos del árbol

Inorden ordena; preorden, postorden y niveles visitan distinto.

### 7. Simula `lowerBound(9)` y `upperBound(8)`

Ambos terminan retornando 10.

### 8. Casos de eliminación en BST

Hoja, un hijo o dos hijos.

### 9. ¿Qué papel cumple `splice`?

Reemplaza un nodo por su hijo.

### 10. Después de eliminar, ¿qué invariantes deben ser ciertos?

La propiedad BST y los enlaces correctos.

### 11. ¿Por qué `remove(3)` debe conservar el inorden ordenado?

Porque válida sigue siendo la estructura BST.

### 12. ¿Qué hace `rotateLeft`?

El hijo derecho sube y el nodo baja.

### 13. ¿Qué hace `rotateRight`?

El hijo izquierdo sube y el nodo baja.

### 14. Demuestra que una rotación preserva la propiedad BST

Los valores no cambian, solo los enlaces.

### 15. ¿Para qué sirve construir desde arreglo ordenado?

Un BST balanceado permite obtener.

### 16. Compara búsqueda en BST balanceado vs degenerado

Balanceado: O(log n). Degenerado: O(n).

## Bloque 8 — Heap binario y representación implícita

### 1. ¿Por qué un heap puede almacenarse en vector sin punteros?

Porque la posición de cada nodo determina dónde están sus hijos y su padre. No son necesarios punteros.

### 2. Demuestra las fórmulas de navegación

En un árbol completo almacenado en vector, el hijo izquierdo está en `2i+1`, el derecho en `2i+2` y el padre en `(i-1)/2`.

### 3. Define la propiedad de min-heap

Cada padre es menor o igual que sus hijos. Por ello, el mínimo siempre queda en la raíz.

### 4. ¿Por qué `top()` devuelve el mínimo?

Porque la propiedad de heap garantiza que la raíz es menor o igual que todos sus descendientes.

### 5. Explica `bubbleUp(i)` paso a paso

El elemento recién insertado sube mientras sea menor que su padre. Se detiene cuando encuentra su posición correcta.

### 6. Explica `trickleDown(i)` paso a paso

El nodo baja intercambiándose con su hijo más pequeño hasta recuperar la propiedad de heap.

### 7. ¿Por qué `remove()` mueve el último elemento a la raíz?

Porque mantiene la forma de árbol completo. Luego `trickleDown()` restaura el orden.

### 8. ¿Qué verifica `isHeap()`?

Que cada padre sea menor o igual que sus hijos en todo el vector.

### 9. Compara insertar n elementos vs `heapify()`

Insertar uno por uno cuesta O(n log n). `heapify()` construye el heap completo en O(n).

### 10. Justifica por qué insertar n elementos cuesta O(n log n)

Cada inserción puede requerir un `bubbleUp()` de O(log n). Repetido n veces da O(n log n).

### 11. Justifica por qué `heapify()` es O(n)

La mayoría de los nodos están cerca de las hojas y descienden pocos niveles. El costo total es O(n).

### 12. Extracción completa de {7, 3, 10, 1, 5, 8, 2}

Las extracciones producen `1, 2, 3, 5, 7, 8, 10`. Esto demuestra que el mínimo siempre está en la raíz.

### 13. ¿Heap vs BST para mínimos repetidos y búsquedas ordenadas?

Para obtener el mínimo muchas veces, conviene usar un heap porque `top()` es O(1) y `remove()` es O(log n). Para búsquedas ordenadas, conviene usar un BST porque permite buscar valores en O(log n) y recorrer los elementos en orden mediante un inorden.

## Bloque 9

### ¿Qué cambia cuando pasamos de estudiar listas, pilas y colas a diseñar árboles binarios, heaps y árboles binarios de búsqueda?

En listas, pilas y colas los elementos se organizan de forma lineal, mientras que en los árboles la organización es jerárquica. Cada nodo puede tener hijos y, en muchas implementaciones, también un puntero hacia su padre. Esto permite representar relaciones más complejas que una simple secuencia de elementos.

Otra diferencia importante es la representación. Mientras que las listas suelen requerir punteros para enlazar nodos, un heap puede almacenarse completamente dentro de un vector gracias a que es un árbol binario completo. En este caso, la posición de cada elemento determina automáticamente dónde están sus hijos y su padre.

También aparecen nuevas propiedades que deben mantenerse. En un BST se exige que todos los valores del subárbol izquierdo sean menores que la raíz y los del derecho mayores. En un heap, cada padre debe ser menor o igual que sus hijos. La correctitud de la estructura depende de conservar estas propiedades después de cada operación.

Los recorridos se vuelven fundamentales. A diferencia de una lista, donde solo existe un orden natural de recorrido, un árbol puede recorrerse en preorden, inorden, postorden o por niveles. Cada recorrido muestra información distinta sobre la estructura.

Además, pasan a ser importantes conceptos como altura, profundidad y punteros `parent`. Mantener esta información permite realizar búsquedas, inserciones y modificaciones de manera más eficiente sin tener que recalcular todo el árbol.

Debido a estas propiedades, un BST permite mantener los datos ordenados y realizar búsquedas eficientes, mientras que un heap permite acceder rápidamente al elemento mínimo mediante la raíz. Cada estructura optimiza operaciones diferentes según el problema que se quiera resolver.

Finalmente, la validación ya no consiste solamente en comprobar que las operaciones producen la salida correcta. También es necesario verificar que los invariantes se conservan y que las complejidades esperadas, como O(log n) en árboles balanceados y heaps, siguen cumpliéndose.

### Autoevaluación breve

- Qué puedo defender con seguridad: diferencia entre árboles binarios, BST y heaps, operaciones y complejidad.
- Qué todavía confundo: Graficacion de un BST no es algo que lo haga con facilidad.
- Qué evidencia usaría en una sustentación: las pruebas publicas y demos, que asisten a entender los conceptos.
- Qué parte del código me parece más importante para revisar otra vez: Rotaciones de BST.
