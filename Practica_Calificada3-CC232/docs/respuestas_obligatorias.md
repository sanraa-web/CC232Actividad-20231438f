# Preguntas

## 1. ¿Cuál es el problema exacto asignado?

Como objetivo se tiene mantener un conjunto dinámico de enteros sobre el cual puedan ejecutarse dos operaciones distintas.

- **Tipo 1:** insertar un valor X dentro del conjunto.
- **Tipo 2:** obtener el X elemento más pequeño según el orden ascendente y, una vez encontrado, eliminarlo de la estructura.

## 2. ¿Qué recibe la entrada y qué produce la salida?

La entrada está formada inicialmente por un entero Q, correspondiente al número total de operaciones. A continuación aparecen Q pares de valores `T` y `X`, donde `T` identifica el tipo de operación y `X` representa el parámetro asociado.

Como salida, por cada operación de tipo 2 se imprime el valor encontrado en la posición X del orden ascendente. Después de ser reportado, dicho valor deja de pertenecer al conjunto.

## 3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?

El principal inconveniente se encuentra en que la cantidad de operaciones puede alcanzar las 200 000. Bajo esas condiciones, una estrategia basada únicamente en arreglos termina siendo demasiado costosa, ya que las inserciones y eliminaciones obligan a desplazar numerosos elementos. Como consecuencia, el tiempo total puede crecer cuadráticamente y exceder los límites permitidos.

## 4. ¿Cuál sería la solución ingenua y cuál es su complejidad?

Una implementación elemental podría utilizar un `std::vector<int>` para almacenar todos los elementos.

La inserción tendría costo constante mediante `push_back()`. Sin embargo, cuando se requiera responder una consulta de tipo 2, sería necesario ordenar los elementos y posteriormente eliminar el seleccionado. Aunque la búsqueda del elemento deseado resulta sencilla una vez ordenado el arreglo, el desplazamiento provocado por la eliminación mantiene el costo lineal.

En el peor escenario, donde se realizan numerosas consultas de extracción, el tiempo acumulado alcanza O(Q²), lo que la vuelve inapropiada para los límites establecidos.

## 5. ¿Qué estructura de datos elegiste?

La estructura elegida fue un Treap con soporte para orden estadístico. Se trata de un árbol binario de búsqueda aleatorizado donde cada nodo almacena, además de su clave y prioridad, el tamaño de su subárbol. Gracias a esta información adicional es posible determinar el k elemento en tiempo logarítmico esperado.

## 6. ¿Qué estructura de la librería `cc232` se parece más?

La implementación utilizada se corresponde con el `Treap.h` encontrado en Semana 6, se recupero utilidades y funciones para el nuevo header `treap.h`.

## 7. ¿Qué operación domina el tiempo?

La mayor parte del tiempo de ejecución se concentra en las operaciones `kth(k)` y `remove()`. Ambas requieren recorrer una trayectoria desde la raíz hasta algún nodo del árbol. Debido a que la altura esperada del Treap es logarítmica, estas operaciones mantienen una complejidad esperada de O(log N).

## 8. ¿Qué invariante mantiene tu estructura?

El correcto funcionamiento de la estructura depende de tres propiedades que deben conservarse permanentemente:

- La propiedad de árbol binario de búsqueda, donde los elementos menores se ubican a la izquierda y los mayores a la derecha.
- La propiedad de heap sobre las prioridades, utilizada para mantener un balance esperado adecuado.
- El almacenamiento correcto del tamaño de cada subárbol.

Estas condiciones deben seguir siendo válidas después de cualquier inserción, eliminación o rotación.

## 9. ¿Dónde se actualiza ese invariante en el código?

La actualización del tamaño de los subárboles se realiza mediante la función `updateSize(Node* u)` definida en `treap.h`.

```cpp
static void updateSize(Node* u) noexcept {
    if (u) u->subtreeSize = 1 + sz(u->left) + sz(u->right);
}
```

Dicha función es invocada después de cada rotación y también tras inserciones o eliminaciones. De esta forma, los tamaños se propagan correctamente desde el nodo afectado hacia todos sus ancestros.

## 10. ¿Qué caso borde puede romper una solución superficial?

Un escenario problemático aparece cuando se solicita el k elemento utilizando un valor de X superior a la cantidad de nodos existentes. En esa situación la búsqueda podría finalizar sin encontrar un resultado válido. Para evitar comportamientos indefinidos, antes de llamar a `kth()` se verifica que se cumpla la condición `X <= treap.size()`.

## 11. ¿Cómo manejas duplicados, empates o elementos obsoletos?

Los elementos repetidos no son admitidos dentro de la estructura. Durante la inserción se compara el valor a insertar con el nodo correspondiente; si ambos resultan equivalentes según el comparador utilizado, la operación retorna `false` y el nuevo nodo no se incorpora al árbol.

## 12. ¿Cuál es la complejidad temporal por operación?

| Operación | Complejidad esperada |
| --- | --- |
| `add(X)` | O(log N) |
| `kth(k)` | O(log N) |
| `remove(val)` | O(log N) |
| Operación tipo 2 completa (`kth` + `remove`) | O(log N) |

Estas cotas se sostienen porque la aleatorización de prioridades permite que la altura del Treap permanezca logarítmica en expectativa.

## R1. ¿Cómo se encuentra el k-ésimo usando tamaños de subárbol?

Se compara el parametro `subtreeSize`, cuenta la cantidad de elementos que tienen sus subarboles adicional a contarse a si mismo.

## R2. ¿Dónde se actualiza size?

Se utiliza la utilidad `updateSize`, las funciones que la requieren son `addNote`, `splice` y `rotateLeft / rotateRight`. La función `updateSize` es la suma del tamaño del size en el hijo izquierdo, el derecho y 1.

## R3. ¿Qué pasa si el árbol se vuelve degenerado?

Si el árbol se degenera, es decir, cuando el tamaño de los subárboles no está correctamente balanceado y el árbol adopta la forma de una lista enlazada, la altura deja de cumplir la complejidad esperada $O(\log N)$. En consecuencia, las operaciones pasan a tener un costo $O(N)$, elevando la complejidad temporal del problema a $O(Q \cdot N)$, con el riesgo de producir TLE.
