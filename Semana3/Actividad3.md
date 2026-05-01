### Bloque 1

3. Para la listas enlazadas, no se exige seguir el orden lógico de secuencias, sino se enfoca más al acceso por referencia, lo cual lo haze menos eficiente para recuperar directamente el elemento de una posición arbitraria. 

6. El nodo dummy ayuda de que la función next y prev siempre existan, trabaja como una constante que nos permite guiar hacia la cabeza o cola de la lista.
7. Porque usan la función *GetNode* con la cual hace una busqueda segun la distancia entre sus extremos.
8. La idea es central es: reducir el desperdicio de espacio y mejora la localización por bloques, pero lo hace a costa de una implementación más compleja y de un análisis amortizado más sofisticado.
9. 

---

### BLOQUE 2

1. La secuencia push (add al inicio) y luego remove al final vs add al final y remove al inicio deja ver comportamiento tipo pila (LIFO) y cola (FIFO) coexistiendo.
2. Una operación add(i, x) con i en medio de la lista.
3. Que al imprimir o recorrer (traverse) los elementos salen en orden lógico continuo aunque internamente estén en bloques.
4. Que se pueden usar operaciones típicas de lista (insertar, eliminar, acceder por índice) de forma uniforme y consistente.
5. La salida donde se aplican algoritmos (como recorridos o búsquedas) sobre la estructura adaptada sin cambiar su implementación base.
6. Almacenar valores es guardar solo datos; almacenar info adicional (como mínimo) implica mantener estructuras auxiliares o invariantes extra.
7. El adaptador que transforma una lista enlazada en pila o cola (LinkedStack o LinkedQueue).
8. Arreglos: acceso rápido por índice pero inserción costosa; listas enlazadas: inserción local eficiente pero sin acceso directo y peor localidad de memoria.

---

### BLOQUE 3

1. Las pruebas son sobre el orden de posicion de sus datos agregados y las funciones add, push, size, peek, pop, remove.
2. Similar a las pruebas de SLList, añadir datos a la estructura y comprobar las funciones add, push, size, peek, pop, remove.  
3. Para SEList, se tiene una estrucutra de tamaño predeterminado y luego se evalua su expansion al agregar mas elementos, además de comprobar las funciones de size, get, set, remove.
4.  Operaciones adicionales como inserción en posiciones arbitrarias o recorridos extendidos.
5. Que los adaptadores respetan comportamiento LIFO (stack), FIFO (queue) y doble extremo (deque).
6. Que se pueden integrar componentes sin modificar sus implementaciones internas.
7. Inserciones, eliminaciones repetidas y verificación de que size se mantiene correcto.
8. Que funciona correctamente bajo uso típico (casos esperados).
9. No garantiza eficiencia, ni cubre todos los casos límite.
10. Porque las pruebas no explican por qué funciona: no muestran invariantes, manejo de punteros ni complejidad.

--- 

### BLOQUE 4

Problemas 1 - 5 SLList
- head, tail y n:
- head apunta al primer nodo (inicio de la lista), tail al último (permite inserciones en O(1) al final) y n mantiene el tamaño lógico. Juntos definen la representación e invariantes básicos: si n=0 entonces head=tail=null, y si n>0 entonces tail->next=null.
Cambios de punteros:
- push(x): nuevo->next = head; luego head = nuevo; si la lista estaba vacía, también tail = nuevo.
- pop(): head = head->next; si la lista queda vacía, tail = null.
- add(x) (al final): tail->next = nuevo; luego tail = nuevo; si estaba vacía, head = nuevo.
- remove(x o por posición): el nodo previo cambia su next para saltar el nodo eliminado; si se elimina el último, también se actualiza tail.
- secondLast(): Recorre desde head hasta encontrar el nodo cuyo next es tail. No basta con mirar tail porque en una lista simplemente enlazada no existe enlace hacia atrás; no hay forma directa de conocer el anterior sin recorrer.
- reverse(): Se usan tres punteros: prev = null, curr = head, y en cada paso se guarda next = curr->next. Luego se invierte el enlace (curr->next = prev), se avanza (prev = curr, curr = next). Al final, head pasa a ser el antiguo tail. No requiere estructura auxiliar porque solo reorienta punteros existentes.
- checkSize(): Recorre la lista contando nodos reales y compara ese conteo con n. Verifica el invariante de tamaño; si no coincide, hay inconsistencia estructural. Es clave para defender correctitud porque detecta errores silenciosos en inserciones/eliminaciones.

Problemas 5 - 9 DLList
- getNode(i): Puede iniciar desde head o tail porque hay enlaces dobles (next y prev). Se elige el extremo más cercano a i, reduciendo el recorrido a O(min(i, n−i)).
- addBefore(w):
- Si w es el nodo de referencia, se actualizan cuatro enlaces:
nuevo->prev = w->prev, nuevo->next = w;
w->prev->next = nuevo; w->prev = nuevo.
El nodo centinela evita casos borde (inicio/fin), porque siempre existe un nodo “ficticio” que conecta todo.
- rotate(r): En lugar de mover elementos uno a uno, se reubican punteros: se identifica el nuevo inicio y fin, y se reconectan head, tail y sus vecinos. Es un cambio de “vista lógica” de la lista.
- isPalindrome(): Usa dos punteros: uno desde head y otro desde tail, comparando valores mientras avanzan hacia el centro. Esto es eficiente gracias a los enlaces dobles.

Problemas 10 - 12 SEList
- Location: Representa la posición física de un elemento como (bloque, índice interno). Es el resultado del mapeo desde índice lógico a estructura por bloques.
- spread() y gather():
spread(): redistribuye elementos cuando un bloque está sobrecargado, repartiéndolos entre bloques vecinos.
gather(): agrupa elementos cuando hay bloques con pocos datos, evitando desperdicio.
Ambos mantienen balance estructural.
- Tamaño de bloque b:
b grande -> menos bloques, mejor acceso (menos saltos), pero inserciones más costosas.
b pequeño -> inserciones más rápidas y flexibles, pero más overhead y peor localidad de memoria.
Es un trade-off entre tiempo de acceso, costo de actualización y uso de espacio.
--- 

### BLOQUE 5
1. LinkedStack reutiliza SLList usando push y pop sobre head, logrando comportamiento LIFO sin implementar nodos nuevos.
2. LinkedQueue reutiliza SLList usando add en tail y remove en head, logrando comportamiento FIFO.
3. LinkedDeque se construye sobre DLList porque necesita acceso eficiente a ambos extremos; SLList no tiene punteros hacia atrás.
4. En MinStack, cada entrada guarda el valor y el mínimo acumulado para poder responder min() en O(1).
5. En MinQueue, dos pilas permiten mantener FIFO (una para entrada, otra para salida) y el mínimo se obtiene combinando los mínimos de ambas.
6. En MinDeque, el rebalanceo entre front_ y back_ evita que una parte crezca demasiado y degrade el rendimiento.
7. Implementar una estructura es crearla desde cero (ej: SLList); adaptar es reutilizar otra (ej: LinkedStack sobre SLList), reduciendo código y errores.
8. Operaciones constantes: acceso a extremos, push/pop.
   Operaciones amortizadas: redimensionamiento, rebalanceos, transferencias entre pilas.

--- 

### BLOQUE 6
1. En DengList se refuerzan operaciones como acceso por índice, inserción, eliminación, recorrido, búsqueda y ordenamiento.
2. Permite usar más funcionalidades sin modificar estructuras existentes (reutilización y bajo acoplamiento).
3. to_deng convierte una estructura a DengList; assign_from_deng copia de DengList a la estructura original.
4. Porque el ordenamiento se hace sobre DengList y luego se transfiere el resultado, evitando reimplementar en cada estructura.
5. dedup_with_deng elimina duplicados; es equivalente a deduplicate() (general) o uniquify() (si está ordenada).
6. reverse_with_deng aplica un algoritmo de reversa sobre DengList y luego lo reutiliza en otras estructuras.
7. Introduce costo O(n) por conversión; vale la pena cuando se reutilizan algoritmos complejos o se evita duplicar lógica.

--- 

### BLOQUE 7
1. ArrayDeque vs LinkedDeque:
   ArrayDeque usa un arreglo circular (memoria contigua); LinkedDeque usa nodos enlazados.
   Costo: ArrayDeque -> mejor acceso y caché; LinkedDeque -> mejor en inserciones/eliminaciones en extremos sin redimensionar.

2. Localidad de memoria:
   Elementos cercanos están juntos en memoria -> mejor uso de caché -> accesos más rápidos.

3. Favorece lista enlazada:
   Inserciones y eliminaciones frecuentes en extremos o posiciones conocidas sin mover elementos.

4. Benchmark:
   Acceso aleatorio -> mejor comparar ArrayDeque.
   Operaciones en extremos -> comparar con LinkedDeque.

5. No es prueba absoluta:
   Depende de implementación, hardware, tamaño de datos y patrón de uso.

6. XorList (idea):
   Ahorrar memoria usando un solo puntero XOR en vez de dos (prev y next).

7. Desventaja de XorList:
   Código más complejo, difícil de depurar y poco práctico en lenguajes modernos.

--- 

### BLOQUE 8

1. Cambio de arquitectura: Se evoluciona de bloques de memoria juntos (arreglos) a nodos conectados por referencias; la información ya no está en un solo sitio, sino distribuida en la memoria.
2. Limitación de acceso: Mientras que en los arreglos llegas a cualquier dato al instante (O(1)), en las listas debes recorrer los nodos uno por uno (O(n)), perdiendo el acceso directo eficiente.
3. Ventaja en modificaciones: Insertar o borrar en arreglos es lento porque hay que mover elementos; en listas, estas operaciones son casi instantáneas (O(1)) porque solo necesitas cambiar hacia dónde apuntan los enlaces.
4. Variedades de listas:SLList (Simple): Rápida en los extremos, pero solo se mueve en una dirección.  DLList (Doble): Más flexible al permitir ir hacia adelante y hacia atrás mediante dos enlaces por nodo.  SEList: Un híbrido que agrupa elementos en pequeños bloques para equilibrar la velocidad de los arreglos con la flexibilidad de las listas.
5. Estructuras como adaptadores: Las listas sirven como "motor" interno para construir otras herramientas como Stacks o Queues, permitiendo crear nuevas funciones sin tener que programar la lógica base desde cero.  Contiguo vs. Enlazado: La memoria contigua es mejor para la velocidad del procesador (caché), mientras que la memoria enlazada es superior cuando necesitas modificar la estructura constantemente sin mover grandes cantidades de datos.  
