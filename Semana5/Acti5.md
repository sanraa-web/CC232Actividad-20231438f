
## Bloque 1 — Núcleo conceptual

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
| recorrido | ver revisada | estruc auxiliar usada | sec producida en el arbol de prueba |
|--- | --- | --- | --- |


### 1. 
Significa que visita el root_ y luego a sus hijos.
### 2.
### 3.
visita los hijos antes de la raiz.


