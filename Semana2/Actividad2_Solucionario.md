### Bloque 1

1. Almacenamiento de datos que esta guardando consecutivamente y esta marcado con un index cada uno.

2. Para calcular la ubicacion de memoria A[i], solo se opera "base + i * sizeof(T)" para encontrarlo.

3. Capacity es el espacio fisico que puede almacenar memoria sin hacer un reajuste, Size es el espacio de los elementos almacenados, no necesariamente ambos son iguales.

4. Porque en la ubicacion fisica de la memoria donde se alamacena tú bloque no te garantiza que el espacio contiguo este libre.

5. La redimencion es de costo 2n en realidad, pero debido a que se distribuye en n insercciones es que la complejidad es amortizada a O(1).

6. En similitudes, ambos tienen crecimiento dinámico, poseen el Resize y comparten operaciones básicas. En sus diferencias, algunas son: el almacenacmiento (wrapper vs puntero), inicializacion (capacity= 1 vs capacity=3), Shrink (factor x3 vs factor x4), entre otros.

7. La mejora es de como este reorganiza espacio, tanto en las funciones d resize(), add() y remove(), en particular por el uso de std::copy y std::copy_backward.

8. Es el uso de bloques i2b(int i), grow() y shrink() en su estructura.

9. Ya que es porgresiva (1, 2, 3) la suma de tamaño de los bloques es cuadratica,

---

### BLOQUE 2

1. En demo_array_basico.cpp, queda claro que un arreglo tiene tamaño fijo, los elementos están en memoria contigua y la asignación se hace normalmente por índice (a[i] = valor).
2. En demo_arraystack_explicado.cpp, la operación que mejor muestra el costo por desplazamientos es insertar o eliminar al inicio/medio, porque obliga a mover muchos elementos del arreglo.
3. En demo_fastarraystack.cpp, cambia la implementación porque se usa una estrategia más eficiente de redimensionamiento/copiado (normalmente crecimiento dinámico), aunque las operaciones principales sigan teniendo la misma complejidad asintótica.
4. En demo_rootisharraystack_explicado.cpp, el mejor ejemplo del mapeo índice lógico → bloque + offset es cuando convierten un índice global i en: número de bloque posición dentro del bloque porque ahí se entiende la fórmula característica del RootishArrayStack.
5. En demo_deng_vector.cpp, lo observable para defender el crecimiento de capacity es que la capacidad aumenta por saltos (por ejemplo duplicándose), evitando realocar memoria en cada push_back.
6. En demo_stl_vector_contraste.cpp, la similitud conceptual con DengVector es que ambos usan: memoria contigua, size y capacity, crecimiento dinámico amortizado.
7. La mejor demo para defender amortización: demo_deng_vector.cpp, porque muestra claramente el crecimiento de capacity y las realocaciones ocasionales. La mejor demo para defender uso de espacio: demo_rootisharraystack_explicado.cpp, porque RootishArrayStack está diseñado justamente para reducir desperdicio de memoria.

---

### BLOQUE3

1. ArrayStack: valida add(x), add(i,x), size(), get(i), remove(i) y el mantenimiento del orden tras inserciones y eliminaciones.
2. FastArrayStack: valida add(i,x) (incluyendo append con size()), size(), get(i), remove(i) y el correcto desplazamiento al eliminar (especialmente en índice 0).
3. RootishArrayStack: valida add(i,x), size(), get(i), set(i,x), remove(i) y acceso/modificación en posiciones internas.
4. Una prueba pública sí demuestra que las operaciones básicas funcionan correctamente en casos simples y que la interfaz está bien implementada.
5. Una prueba pública no demuestra complejidad temporal, manejo de memoria, invariantes internos ni comportamiento en casos extremos. resize_stress_week2.cpp estresa crecimiento, reducción y estabilidad tras múltiples inserciones y eliminaciones (incluyendo patrones adversos como eliminar desde el inicio y volver a crecer).
6. Pasar pruebas no reemplaza explicar invariantes y complejidad porque las pruebas son finitas, mientras que los invariantes garantizan corrección general y la complejidad asegura eficiencia en todos los casos.

---

### BLOQUE 4

1. _size es la cantidad de elementos actuales, _capacity es el tamaño del arreglo reservado y _elem es el puntero al arreglo dinámico donde se almacenan los datos.
2. expand() debe ejecutarse cuando _size == _capacity, es decir, cuando ya no hay espacio para insertar nuevos elementos.
3. insert(r, e) necesita desplazar elementos porque debe abrir espacio en la posición r, moviendo todos los elementos desde r hacia la derecha.
4. remove(r) elimina un solo elemento en la posición r, mientras que remove(lo, hi) elimina un rango de elementos en el intervalo [lo, hi).
5. La evidencia de copia profunda en la demo aparece cuando al copiar un vector, modificar uno no afecta al otro (cada uno tiene su propio arreglo _elem).
6. traverse() es una buena interfaz didáctica porque permite aplicar una operación a todos los elementos sin exponer la implementación interna del vector.
7. Implementar un vector propio permite entender la gestión de memoria, redimensionamiento e invariantes antes de usar abstracciones como std::vector.

--- 

### BLOQUE 5

1. Los elementos se distribuyen en bloques de tamaño creciente: el primero tiene 1 elemento, el segundo 2, el tercero 3, y así sucesivamente. Esto permite un crecimiento progresivo sin necesidad de redimensionar todo el arreglo como en estructuras clásicas.
2. La capacidad total con r bloques es r(r+1)/2 porque corresponde a la suma de los primeros r números naturales (1+2+…+r). Es una propiedad matemática que modela exactamente cómo crecen los bloques.
3. i2b(i) resuelve el problema de ubicar rápidamente en qué bloque se encuentra un elemento dado su índice global, evitando recorrer toda la estructura. Es clave para mantener eficiencia en el acceso.
4. locate(i) devuelve la ubicación exacta del elemento: no solo el bloque, sino también la posición interna dentro de ese bloque, permitiendo acceder directamente al dato.
5. Se gana eficiencia en el uso de memoria frente a ArrayStack, ya que no se necesita duplicar el tamaño del arreglo completo al crecer, sino que el crecimiento es gradual y más controlado.
6. Se mantiene la misma interfaz abstracta (operaciones como get, set, add, remove), por lo que desde el punto de vista del usuario la estructura se comporta igual que otras listas.
7. La parte más difícil de defender suele ser el mapeo, porque implica entender y explicar la relación matemática entre el índice global y su ubicación en bloques.

---

### BLOQUE 6

1. operator[] aporta acceso directo por índice, haciendo que la estructura se sienta como un arreglo tradicional y facilitando su uso.
2. find(e) supone que los elementos pueden compararse mediante igualdad, lo cual implica que existe un criterio claro para determinar si dos elementos son iguales.
3. traverse() muestra cómo recorrer todos los elementos de forma secuencial, evidenciando el comportamiento lineal de la estructura.
4. Esta lectura refuerza naturalmente el concepto de vector (como DengVector), ya que trabaja con ideas fundamentales como acceso indexado, recorrido y búsqueda, aunque no sea el foco principal.

---

### BLOQUE 7

1. De contenedor fijo a abstracción activa: Diseñar una estructura dinámica significa dejar de ver el arreglo como algo estático para tratarlo como una base flexible que nosotros controlamos y hacemos crecer según la necesidad.
2. Mapeo y Representación: La estructura separa la vista lógica (lo que ve el usuario) de la física (cómo se guarda); esto permite usar uno o varios arreglos para representar una sola lista de datos.
3. Invariantes y Correctitud: Mantener el orden y evitar huecos entre elementos es fundamental; la validez de la estructura depende de que cada operación de inserción o borrado deje el sistema en un estado consistente.
4. Costo Amortizado: Aunque algunas operaciones son costosas (como redimensionar), se garantiza un costo promedio de $O(1)$, asegurando que el rendimiento sea eficiente a largo plazo.
5. Eficiencia en el espacio: Se busca reducir el desperdicio de memoria; mientras un arreglo común puede sobrar en un 50%, estructuras avanzadas como RootishArrayStack minimizan ese exceso de forma más inteligente.
6. Diferencias clave:
   - ArrayStack: Es el más simple; crece duplicando su tamaño y es rápido, pero puede desperdiciar mucha memoria.
   - FastArrayStack: Mantiene la lógica del anterior, pero usa funciones de copia más rápidas para mejorar el rendimiento real.
   - RootishArrayStack: Utiliza múltiples bloques de memoria para ahorrar espacio, aunque su acceso es un poco más complejo matemáticamente. 
