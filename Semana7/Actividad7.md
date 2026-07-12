### Actividad 7 - CC232

#### Estudiante

- Nombre: Santiago Alejandro Ramirez Aguilar

#### Bloque 1 - Diagnóstico inicial

[Tabla de comandos, resultados e interpretación]

#### Bloque 2 - BST como punto de partida

### 1. Propiedad BST

Un árbol binario cumple la propiedad BST si, para todo nodo, las claves de su subárbol izquierdo son menores que su clave y las claves de su subárbol derecho son mayores. Es una propiedad global: cada nodo debe respetar los límites heredados de todos sus ancestros, no solo compararse con su padre inmediato.

### 2. Por qué el inorder produce una secuencia ordenada

El recorrido inorder visita primero el subárbol izquierdo, luego el nodo, luego el subárbol derecho. Como todo lo que está a la izquierda de un nodo es menor y todo lo que está a la derecha es mayor, aplicar esta regla en cada nivel produce, por inducción, la secuencia completa ordenada.

### 3. Por qué insertar claves ordenadas degenera el árbol

La inserción simple no reequilibra nada: cada clave nueva desciende comparando hasta encontrar un lugar vacío. Si las claves llegan ya ordenadas, cada nueva clave es siempre mayor que todas las anteriores, así que siempre desciende por el mismo lado. El árbol termina pareciendo una lista enlazada.

### 4. Construcción manual con las claves 10, 20, 30, 40, 50, 60, 70

Cada clave se inserta como hijo derecho de la anterior, formando una cadena hacia la derecha:

```text
10
  20
    30
      40
        50
          60
            70
```

### 5. Altura del árbol sin balanceo

Con 7 nodos en cadena la altura es 6 (n menos 1). La altura mínima posible para 7 nodos sería 2, si el árbol estuviera perfectamente balanceado.

### 6. Por qué la búsqueda puede costar O(n)

La búsqueda recorre un solo camino desde la raíz hasta encontrar la clave, y su costo depende de la altura, no del número de nodos. Cuando la altura es lineal, como en este árbol degenerado, buscar el último elemento obliga a recorrer todos los nodos, es decir O(n), igual que en una lista enlazada.

### 7. Qué problema resuelve AVL

AVL evita que la altura crezca de forma lineal. Exige que en cada nodo la diferencia de alturas entre subárbol izquierdo y derecho sea a lo más 1, y usa rotaciones para restaurar esa condición tras cada inserción o eliminación. Esto garantiza altura logarítmica en el peor caso, sin importar el orden de llegada de las claves.

### 8. Qué problema resuelve Red Black Tree

Busca la misma meta que AVL, evitar la degeneración, pero usando colores en lugar de alturas. Mantiene que todo camino desde la raíz tenga el mismo número de nodos negros y que no haya dos nodos rojos seguidos. Esto acota la altura en el peor caso y suele requerir menos rotaciones amortizadas que AVL, aunque su altura máxima permitida es algo mayor.

### Dibujo del BST degenerado

```text
10
  20
    30
      40
        50
          60
            70
```

### Explicación breve del costo

La altura es 6 en vez de un valor cercano a 3, que sería lo esperado con balance. Buscar, insertar o eliminar en el peor caso cuesta O(n) en lugar de O(log n).

### Relación con Semana 5

Este es el mismo escenario que motiva pasar de Semana 5 a Semana 7: un BST simple, sin ningún invariante de balance, puede degradarse a O(n) con entradas ordenadas. AVL y Red Black Tree agregan invariantes de altura o de color para que ese mismo patrón de inserción nunca produzca una cadena, sino un árbol con altura logarítmica garantizada.

#### Bloque 3 - AVL

### 1. Nodo balanceado en AVL
 
Un nodo esta balanceado cuando la diferencia entre la altura de su subarbol izquierdo y la de su subarbol derecho es menos 1, 0 o 1.
 
### 2. Calculo del factor de balance
 
Altura del hijo izquierdo menos altura del hijo derecho. Si un hijo no existe, su altura vale menos 1.
 
### 3. Informacion de altura tras insertar o eliminar
 
Hay que actualizar la altura de cada nodo en el camino desde el punto modificado hasta la raiz. La altura de un nodo es 1 mas la altura maxima entre sus dos hijos.
 
### 4. Que representa `_hot`
 
Es el ultimo nodo valido visitado durante una busqueda, o sea el padre del punto donde se inserto o donde se buscaba una clave. Sirve como punto de partida para subir y revisar el balance de los ancestros.
 
### 5. Por que AVL puede heredar de BST
 
AVL es un BST con una regla extra de balance. No cambia el orden ni la busqueda, solo agrega revision de altura tras insertar o eliminar. Por eso reutiliza `search` de BST y solo redefine `insert` y `remove`.
 
### 6. Operacion que restaura la forma del arbol
 
La rotacion, hecha con `rotateAt` y `connect34`. Reordena tres nodos y cuatro subarboles alrededor del punto desbalanceado.
 
### 7. Por que la rotacion no rompe la propiedad BST
 
Porque conserva el mismo recorrido inorder. Solo cambia la forma vertical del arbol, no el orden de las claves.
 
### 8. Por que tras insertar suele bastar un solo ancestro
 
Al insertar una clave, la altura de un subarbol crece como maximo en un nivel. Al reparar el primer ancestro desbalanceado, su altura vuelve a ser la misma de antes de insertar, asi que los ancestros de arriba ya no ven cambio y no necesitan revision.
 
### 9. Por que tras eliminar hay que seguir revisando
 
Al eliminar, la altura de un subarbol puede disminuir. Aunque se repare un ancestro, su altura puede quedar menor que antes, y eso puede afectar el balance de los ancestros de arriba. Por eso hay que seguir subiendo hasta la raiz.
 
### Invariantes AVL
 
Un arbol AVL cumple siempre tres cosas: es un BST valido, el factor de balance de cada nodo esta entre menos 1 y 1, y la altura de cada nodo es 1 mas la altura maxima entre sus hijos.
 
### Trazado de insercion con rotacion
 
Se insertan en orden 30, 20, 10.
 
Insertar 30: queda como raiz.
 
Insertar 20: menor que 30, se coloca como hijo izquierdo.
 
Insertar 10: menor que 30 y menor que 20, se coloca como hijo izquierdo de 20. El arbol queda en cadena:
 
```text
30
20
10
```
 
El nodo 30 queda con factor de balance 2, lo cual rompe el invariante. Se identifica a 30 como el ancestro desbalanceado y se hace una rotacion con los tres nodos 30, 20 y 10. El resultado queda balanceado:
 
```text
20
10 30
```
 
El factor de balance de 20 queda en 0 y el inorder sigue siendo 10, 20, 30.
 
### Salida de demo_avl_deng_core.cpp
 
Compilacion y ejecucion real del programa:
 
```text
$ ./sem7_demo_avl_deng_core.exe
AVL inorder: 10 20 22 25 27 30 40 50
AVL level-order: 30 20 40 10 25 50 22 27
Valido AVL: si
Tras borrar 20 y 40: 10 22 25 27 30 50
Valido AVL: si
```

#### Bloque 4 - Rotaciones AVL

### Tabla de rotaciones
 
| Caso | Secuencia insertada | Nodo desbalanceado | Rotacion aplicada | Inorder antes | Inorder despues | Altura final |
|---|---|---|---|---|---|---|
| LL | 30, 20, 10 | 30 | Simple, hacia la derecha | 20 30 | 10 20 30 | 1 |
| RR | 10, 20, 30 | 10 | Simple, hacia la izquierda | 10 20 | 10 20 30 | 1 |
| LR | 30, 10, 20 | 30 | Doble, izquierda luego derecha | 10 30 | 10 20 30 | 1 |
| RL | 10, 30, 20 | 10 | Doble, derecha luego izquierda | 10 30 | 10 20 30 | 1 |
 
En los cuatro casos, tras la rotacion, el nodo 20 queda como raiz, con 10 a la izquierda y 30 a la derecha, y la altura final es 1.
 
### Caso LL
 
Antes de rotar, cadena hacia la izquierda:
 
```text
30
  20
    10
```
 
Despues de rotar:
 
```text
20
  10
  30
```
 
### Caso RR
 
Antes de rotar, cadena hacia la derecha:
 
```text
10
  20
    30
```
 
Despues de rotar:
 
```text
20
  10
  30
```
 
### Caso LR
 
Antes de rotar, 20 cuelga como hijo derecho de 10, que es hijo izquierdo de 30:
 
```text
30
  10
    20
```
 
Despues de rotar:
 
```text
20
  10
  30
```
 
### Caso RL
 
Antes de rotar, 20 cuelga como hijo izquierdo de 30, que es hijo derecho de 10:
 
```text
10
  30
    20
```
 
Despues de rotar:
 
```text
20
  10
  30
```

### 1. Diferencia entre rotacion simple y rotacion doble
 
La rotacion simple mueve un solo nivel de nodos: el hijo sube y el padre baja, en una sola operacion. La rotacion doble aplica ese mismo movimiento dos veces en direcciones distintas, primero sobre el hijo y despues sobre el nodo desbalanceado, porque el desequilibrio no esta alineado en una sola direccion.
 
### 2. Por que LL y RR se corrigen con una sola rotacion
 
En LL y RR los tres nodos ya estan alineados en la misma direccion, todos hacia la izquierda o todos hacia la derecha. Como forman una linea recta, basta con un solo giro para que el nodo del medio quede como raiz del grupo y los otros dos queden como sus hijos.
 
### 3. Por que LR y RL requieren dos pasos
 
En LR y RL los tres nodos no estan alineados, cambian de direccion a mitad de camino, por ejemplo izquierda y luego derecha. Una sola rotacion no logra poner al nodo del medio como raiz del grupo, porque el nodo intermedio queda en el lugar equivocado. Por eso primero se endereza esa mitad con una rotacion sobre el hijo, y luego se aplica la rotacion final sobre el nodo desbalanceado original.
 
### 4. Que parte del arbol cambia y que parte permanece igual
 
Cambian los enlaces entre los tres nodos involucrados y sus cuatro subarboles, es decir la forma vertical de esa zona del arbol. Lo que permanece igual es el contenido de esos subarboles y el orden de las claves, ya que los mismos cuatro subarboles se reconectan solo en otra posicion.
 
### 5. Por que el inorder debe ser el mismo antes y despues de reestructurar
 
Porque una rotacion es una transformacion equivalente: solo reorganiza los enlaces entre los nodos, sin mover claves fuera de su lugar relativo. Si el recorrido izquierda, nodo, derecha se mantiene igual en cada subarbol reconectado, la secuencia completa en orden tampoco cambia, aunque la forma del arbol sea distinta. Esto es justamente lo que confirma la tabla anterior, donde el inorder despues de cada rotacion es siempre 10 20 30.
 
### Preservacion del orden BST
 
Una rotacion no mueve claves entre subarboles, solo cambia cual nodo queda arriba y cual abajo. Los cuatro subarboles que participan, llamados T0, T1, T2 y T3 en la implementacion, se reconectan siempre respetando su posicion relativa: T0 sigue siendo el mas pequeno, T3 el mas grande, y T1 y T2 quedan entre los tres nodos centrales en el mismo orden que tenian antes. Como el inorder solo depende de esa posicion relativa entre subarboles y nodos, y no de cual nodo es padre de cual, cualquier reordenamiento de enlaces que preserve esa posicion relativa preserva tambien el recorrido inorder, y por lo tanto preserva la propiedad BST.

#### Bloque 5 - Red-Black Tree

### 1. Que propiedad BST mantiene Red Black Tree
 
La propiedad de orden normal: izquierda menor, derecha mayor en cada nodo.
 
### 2. Que propiedades de color debe cumplir
 
Cada nodo es rojo o negro. La raiz es negra. Las hojas nulas son negras. Ningun nodo rojo tiene hijo rojo. Todos los caminos hasta las hojas nulas tienen la misma cantidad de nodos negros.
 
### 3. Por que la raiz debe terminar negra
 
Porque la altura negra se cuenta desde la raiz, y fijarla en negro da un punto de referencia estable para ese conteo.
 
### 4. Que significa no tener dos rojos consecutivos
 
Que un nodo rojo nunca tiene padre rojo ni hijo rojo. Evita caminos largos formados solo por nodos rojos.
 
### 5. Que representa la altura negra
 
La cantidad de nodos negros en el camino desde un nodo hasta sus hojas nulas descendientes. Debe ser igual en todos los caminos.
 
### 6. Por que permite un balance menos estricto que AVL
 
AVL limita la diferencia de altura entre subarboles a uno. Red Black solo exige igual cantidad de negros, dejando que los rojos hagan un camino hasta el doble de largo que otro. A cambio, necesita menos rotaciones en promedio.
 
### 7. Correcciones despues de insertar
 
El nodo nuevo entra rojo. Si el tio es rojo, se recolorea padre y tio a negro y abuelo a rojo, y se sigue revisando mas arriba. Si el tio es negro, se aplica una rotacion y la correccion termina ahi.
 
### 8. Correcciones despues de eliminar
 
Puede faltar un negro en una rama. Se revisa el hermano del nodo afectado: si es rojo se rota para volverlo negro, si es negro se recolorea o se rota segun sus hijos, hasta restaurar la altura negra o llegar a la raiz.
 
### 9. Papel de las rotaciones
 
Cambian la forma del arbol sin alterar el orden de las claves, reubicando un nodo negro cuando el recoloreo simple no basta.
 
### 10. Papel del cambio de colores
 
Corrige una violacion sin cambiar la forma del arbol. Es mas barato que rotar, y en varios casos es suficiente.
 
### Invariantes Red Black
 
BST valido. Cada nodo rojo o negro. Raiz negra. Hojas nulas negras. Sin dos rojos consecutivos. Misma altura negra en todos los caminos.
 
### Insercion con recoloreo
 
Arbol con raiz negra 10, hijos 5 y 15 rojos. Se inserta 3 como hijo izquierdo de 5, en rojo.
 
Ahora 5 es rojo con hijo rojo 3, lo cual viola la regla. El tio de 3 es 15, tambien rojo, asi que se aplica recoloreo puro: 5 y 15 pasan a negro, 10 pasa a rojo. La altura negra no cambia, solo se redistribuye.
 
Como 10 es la raiz, se fuerza de vuelta a negro y termina la correccion, sin ninguna rotacion.
 
### Evidencia de salida
 
```text
$ ./sem7_demo_redblack_morin.exe
RB inorder: 2 3 6 7 8 10 11 13 18 22 26
Valido RedBlack: si
Tras borrar 18 y 11: 2 3 6 7 8 10 13 22 26
Valido RedBlack: si
```
 
El inorder queda ordenado tras insertar en orden arbitrario, y `verifyRB` confirma las reglas de color. Tras eliminar 18 y 11, el inorder sigue ordenado sin ellas y el arbol sigue siendo valido.

#### Bloque 6 - Comparación

### Tabla
 
| Estructura | Propiedad de orden | Propiedad adicional | Operacion de reparacion | Altura esperada o garantizada | Caso donde conviene usarla |
|---|---|---|---|---|---|
| BST comun | Izquierda menor, derecha mayor | Ninguna | Ninguna | Sin garantia, puede llegar a n | Datos que ya llegan en orden aleatorio, o prototipos simples |
| Treap | Izquierda menor, derecha mayor | Heap por prioridad aleatoria | bubbleUp y trickleDown | O(log n) esperado | Cuando se acepta balance probabilistico a cambio de codigo simple |
| AVL | Izquierda menor, derecha mayor | Diferencia de altura entre hijos a lo mas 1 | Rotacion simple o doble | O(log n) garantizado, la mas ajustada | Busquedas frecuentes donde importa altura minima garantizada |
| Red Black Tree | Izquierda menor, derecha mayor | Color rojo o negro, misma altura negra en todo camino | Recoloreo y rotacion | O(log n) garantizado, hasta el doble que AVL | Muchas inserciones y eliminaciones intercaladas |
 
### 1. Que tienen en comun

Las cuatro son BST: mantienen la propiedad de orden izquierda menor, derecha mayor. Esa propiedad es la unica que comparten todas sin excepcion.

### 2. Diferencia entre prioridad, altura y color

La prioridad en Treap es un numero aleatorio ajeno a la clave, usado solo para decidir la forma del arbol via una regla de heap. La altura en AVL es una medida exacta y determinista de cada nodo, recalculada tras cada cambio. El color en Red Black Tree es una etiqueta discreta, rojo o negro, que no mide altura directamente pero acota la altura negra. Prioridad decide forma por azar, altura decide forma por medicion exacta, color decide forma por una regla combinatoria mas laxa.

### 3. Por que Treap depende de prioridades

Porque sin prioridades un Treap seria un BST comun, sujeto a degenerarse con entradas ordenadas. La prioridad aleatoria simula un orden de insercion aleatorio independientemente del orden real de llegada de las claves, dando balance esperado sin reglas deterministas.

### 4. Por que AVL suele ser mas estricto en altura

Porque su invariante limita la diferencia de altura entre hijos a uno en cada nodo, la cota mas ajustada de las cuatro. Eso produce una altura muy cercana al minimo teorico, a cambio de rotaciones mas frecuentes en cada insercion o eliminacion.

### 5. Por que Red Black puede ser preferible con muchas inserciones y eliminaciones

Porque su invariante es mas laxo, permite mas desbalance antes de exigir una correccion estructural, y buena parte de las correcciones se resuelven con recoloreo, mas barato que una rotacion. Con cargas de trabajo dominadas por muchas actualizaciones, esto suele significar menos reestructuracion total.

### 6. Estructura para defender busqueda ordenada con balance fuerte

AVL, porque garantiza la altura mas ajustada de las cuatro y por tanto el mejor peor caso para busquedas.

### 7. Estructura para explicar balance probabilistico

Treap, porque su balance depende directamente de prioridades aleatorias y de la propiedad de heap, siendo el ejemplo mas directo de balance esperado en vez de garantizado.

### Conexion con Sem 5 y 6

Semana 5 aporta el BST comun, sin ninguna proteccion contra degeneracion, como lo confirma la evidencia real: al insertar 50,30,70,20,40,60,80 el `BinarySearchTree1` de Semana 5 y el `AVL` de Semana 7 producen el mismo inorder ordenado, 20 30 40 50 60 70 80, pero solo AVL garantiza que ese orden se mantenga con altura acotada sin importar como lleguen las claves.
Semana 6 aporta el Treap, que resuelve el mismo problema de degeneracion que Semana 5 no resuelve, pero usando prioridades aleatorias en vez de invariantes deterministas.
Semana 7 cierra la progresion con AVL y Red Black Tree, que garantizan balance en el peor caso, no solo en promedio. La evidencia real con insercion ordenada 1 a 12 lo muestra: AVL Deng, AVL compacto y RedBlack LLRB terminan con altura 3, y RedBlack Morin con altura 4, todas validas, mientras que un BST comun con esa misma entrada ordenada habria quedado con altura 11, es decir, una cadena.

#### Bloque 7 - Pruebas e invariantes

### Tabla
 
| Archivo | Estructuras probadas | Que valida | Resultado ctest |
|---|---|---|---|
| test_public_week7.cpp | AVL, RedBlackTree1, AVLTreeCompact, RedBlackTreeLLRB | Insercion basica, un remove puntual, inorder, invariante propio de cada estructura, altura o tamano en un caso pequeno | Passed |
| test_internal_week7.cpp | BST, BinarySearchTree1, AVL, RedBlackTree1, AVLTreeCompact, RedBlackTreeLLRB | 250 inserciones y 120 eliminaciones aleatorias con semilla fija, comparadas contra std::set como oraculo, invariantes verificados tras cada operacion | Passed |
 
### 1. Operaciones que valida la prueba publica para AVL

Insercion de varias claves, calculo de altura, `remove` de una clave puntual, `inorder` resultante y `isAVLValid` tras insertar y tras eliminar.

### 2. Operaciones que valida la prueba publica para Red Black Tree

`add` de varias claves con verificacion de retorno, rechazo de un `add` duplicado, `remove` de una clave, y `verifyRB` antes y despues de eliminar.

### 3. Casos adicionales que cubre la prueba interna

Insercion y eliminacion sobre `BST` y `BinarySearchTree1` con `lowerBound` y `upperBound`, y una prueba cruzada con 250 inserciones y 120 eliminaciones aleatorias sobre las cuatro estructuras balanceadas a la vez, comparando su `inorder` contra un `std::set` oraculo y verificando el invariante propio de cada una despues de cada operacion.

### 4. Que significa que una prueba valide el inorder
 
Que la propiedad BST se mantiene: la secuencia de claves en orden creciente coincide con la esperada, sin huecos ni duplicados ni desorden, sin importar la forma interna del arbol.
 
### 5. Que significa que una prueba valide alturas o factores de balance
 
Que el invariante estructural de la estrategia de balance, diferencia de altura acotada en AVL, se cumple en todos los nodos, no solo que el arbol funcione por fuera.

### 6. Que significa que una prueba valide colores

Que las reglas de Red Black, raiz negra, sin dos rojos seguidos, misma altura negra en todo camino, se cumplen realmente en la estructura interna, y no solo que las operaciones no fallen.

### 7. Que no demuestra pasar solo las pruebas publicas

No demuestra que la estructura resista muchas operaciones intercaladas ni entradas aleatorias grandes, porque la prueba publica usa pocas claves y casos fijos. Tampoco demuestra que los invariantes se mantengan tras eliminaciones repetidas, ya que solo hay un remove por estructura.

### 8. Evidencia a usar en una sustentacion

Las cuatro combinadas, pero con distinto peso: el argumento de complejidad explica por que deberia funcionar, el trazado muestra un caso concreto paso a paso, la prueba automatizada confirma que se cumple en muchos casos incluidos los aleatorios, y la demostracion en vivo conecta todo con una ejecucion real visible. La prueba interna con 250 insersiones y 120 eliminaciones aleatorias es la evidencia mas fuerte, porque no depende de casos elegidos a mano.

### 9. Invariante a revisar primero si falla AVL

El factor de balance de cada nodo, es decir, si `isAVLValid` sigue fallando incluso despues de que `isBSTValid` pase, el problema esta en la logica de rotacion o en el calculo de altura, no en el orden de las claves.

### 10. Invariante a revisar primero si falla Red Black Tree

La raiz negra y la ausencia de dos rojos consecutivos, revisando primero `verifyRB`. Si la raiz aparece roja o hay un rojo con hijo rojo, el problema esta en `addFixup` o `removeFixup`. Si eso pasa pero la altura negra no coincide entre ramas, el problema esta en el recoloreo, no en las rotaciones.

### Lista de invariantes que defenderia

Para AVL: propiedad BST, factor de balance entre menos uno y uno en cada nodo, altura almacenada consistente con la de los hijos.

Para Red Black Tree: propiedad BST, cada nodo rojo o negro, raiz negra, hojas nulas negras, ningun rojo con hijo rojo, misma altura negra en todo camino desde cada nodo.

### Evidencia de ejecucion de ctest

```text
$ ctest --test-dir build-debug -R semana7 --output-on-failure
Test project C:/Users/Santiago/Desktop/algos_estru/CC-232/Libreria_cc232/Semana7/build-debug
    Start 1: semana7_public
1/2 Test #1: semana7_public ...................   Passed    0.03 sec
    Start 2: semana7_internal
2/2 Test #2: semana7_internal .................   Passed    0.03 sec
100% tests passed, 0 tests failed out of 2
Total Test time (real) =   0.08 sec
```

#### Bloque 8 - Ejercicios de codificación

[Código, evidencias, pruebas e interpretación]

#### Bloque 9 - Cierre comparativo

[Respuesta final]

#### Autoevaluación breve

- Qué puedo defender con seguridad: 
- Qué todavía confundo: 
- Qué evidencia usaría en una sustentación: 
- Qué parte del código debo revisar otra vez: 
