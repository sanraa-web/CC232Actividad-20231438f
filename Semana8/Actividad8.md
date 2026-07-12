### Actividad 8 - CC232

#### Estudiante

- Nombre: Santiago Alejandro Ramirez Aguilar

### Bloque 1

### Salida relevante de demo_chained.cpp
 
```
ChainedHashTable
size=6 capacity=17 load=0.352941 longestBucket=2
contains(26)=1 contains(99)=0
insertions=6, successfulSearches=1, failedSearches=1, removals=0, collisions=4, totalProbes=14, maxProbeLength=3, averageProbeLength=1.75, rehashes=1, tombstones=0
```
 
Esta salida se obtiene insertando 10, 18, 26, 34, 42 y 50 en una tabla que arranca con 8 buckets. Al llegar al sexto elemento (50) el factor de carga supera 0.70 y ocurre un rehash hacia 17 buckets, justo antes de calcular en qué bucket va el 50.
 
### Tabla
 
Se calculó el hash real de cada entero (hashCode + mix64) y se aplicó modulo 8 mientras la tabla tuvo 8 buckets, y modulo 17 después del rehash.
 
| Operación | Clave | Bucket calculado | Tamaño bucket antes | Tamaño bucket después | Colisión observada | loadFactor() | longestBucket() |
|---|---|---|---|---|---|---|---|
| add | 10 | 2 (mod 8) | 0 | 1 | no | 0.125 | 1 |
| add | 18 | 2 (mod 8) | 1 | 2 | si | 0.250 | 2 |
| add | 26 | 2 (mod 8) | 2 | 3 | si | 0.375 | 3 |
| add | 34 | 5 (mod 8) | 0 | 1 | no | 0.500 | 3 |
| add | 42 | 5 (mod 8) | 1 | 2 | si | 0.625 | 3 |
| rehash | (interno) | capacidad 8 a 17 | size=5 reinsertado | size=5 | no aplica | 0.294 (tras rehash) | 1 |
| add | 50 | 8 (mod 17) | 1 | 2 | si | 0.352941 | 2 |
| contains | 26 | 8 (mod 17) | 2 | 2 | no aplica, busqueda exitosa | 0.352941 | 2 |
| contains | 99 | 10 (mod 17) | 1 | 1 | no aplica, busqueda fallida | 0.352941 | 2 |
 
Notas sobre la traza:
 
Antes del rehash, las claves 10, 18 y 26 caen las tres en el mismo bucket (indice 2 modulo 8), por eso ese bucket llega a tener 3 elementos y explica el maxProbeLength=3 del resultado final. Las claves 34 y 42 también chocan entre si en el bucket 5.
 
El rehash ocurre justo al llegar a la sexta insercion (50), porque antes de insertarla la política evalúa (size actual + 1) dividido capacidad, es decir 6 dividido 8 igual 0.75, que supera el maxLoad de 0.70. Ahí se recalculan los buckets de los 5 elementos ya insertados usando la nueva capacidad de 17, y luego recién se calcula el bucket de 50.
 
Después del rehash, 26 y 50 vuelven a coincidir en el mismo bucket (indice 8 modulo 17), lo que explica por qué longestBucket termina en 2 y por qué collisions llega a 4 en total (18, 26, 42 y 50 generaron colision al momento de insertarse).
 
contains(99) también cae en un bucket no vacío (el mismo que la clave 10), así que aunque no encuentra la clave, sí recorre un elemento antes de reportar fallo, lo cual suma un probe extra a las estadísticas.
 
### 1. Diferencia entre el arreglo principal y los buckets
 
El arreglo principal (table_) es un arreglo de tamaño fijo (la capacidad de la tabla) cuya única función es servir de indice: cada posición corresponde a un valor de hash modulo capacidad. Un bucket es lo que vive dentro de cada posición de ese arreglo, en este caso una lista (ArrayStack) que puede contener cero, una o varias claves. El arreglo principal decide donde buscar, y el bucket es donde realmente están guardados los datos.
 
### 2. Por qué chaining puede almacenar más elementos que posiciones tiene el arreglo principal
 
Porque cada posición del arreglo principal no guarda un solo elemento, sino una lista que puede crecer sin límite. Si dos o más claves distintas producen el mismo índice, todas se agregan a la misma lista en esa posición. Por eso una tabla con 8 buckets perfectamente puede contener 20 o 30 elementos, aunque a costa de que las búsquedas dentro de esos buckets sean más lentas.
 
### 3. Qué significa que un bucket crezca demasiado
 
Significa que muchas claves distintas están cayendo en el mismo índice, ya sea por mala suerte, por una función hash poco uniforme, o porque la tabla necesita más buckets (factor de carga alto). Cuando un bucket crece, cada operación sobre ese bucket (buscar, insertar, borrar) deja de comportarse como si fuera O(1) y empieza a acercarse a un recorrido lineal sobre esa lista.
 
### 4. Por qué longestBucket() es una métrica importante
 
Porque el promedio (loadFactor) puede verse bien aunque existan buckets muy desbalanceados. Por ejemplo, con 6 elementos y 17 buckets el factor de carga es bajo (0.35), pero eso no dice si todos los elementos están repartidos parejo o si dos cayeron juntos en el mismo bucket. longestBucket() muestra el peor caso real que va a enfrentar una búsqueda, y es la señal más directa de que la función hash o el tamaño de la tabla no están funcionando bien.
 
### 5. Cuándo la búsqueda en chaining deja de parecerse a O(1) esperado
 
Cuando la distribución de claves deja de ser uniforme, ya sea porque la función hash tiene sesgos, porque las claves reales del problema tienen patrones (por ejemplo todas múltiplos de 8), o porque la tabla no se redimensiona a tiempo y el factor de carga sube demasiado. En esos casos varios buckets concentran muchos elementos y buscar en ellos se acerca a recorrer una lista completa, es decir O(n) en el peor caso.
 
### 6. Costo de recorrer un bucket de longitud k
 
Recorrer un bucket de longitud k cuesta O(k), porque hay que comparar la clave buscada contra cada elemento de la lista uno por uno hasta encontrarla o llegar al final. Si k es pequeño (como en una tabla bien balanceada) el costo es prácticamente constante; si k crece mucho, el costo se vuelve lineal en esa cadena.
 
### 7. Qué parte del costo depende de la función hash y qué parte de la distribución de claves
 
La función hash determina qué tan dispersos quedan los índices calculados: una función hash de mala calidad puede agrupar claves distintas en los mismos buckets incluso si las claves originales están bien distribuidas. La distribución de claves depende de los datos reales que llegan a la tabla: aunque la función hash sea excelente, si las claves de entrada tienen patrones (por ejemplo todas pares, o todas múltiplos de un mismo número), pueden terminar cayendo en menos buckets de los esperados. En la práctica el costo final depende de ambas cosas actuando juntas: una buena función hash minimiza el riesgo, pero no puede compensar por completo una entrada de datos adversarial o muy patrón.
 
### Costo esperado y peor caso
 
En promedio, con una función hash razonable y un factor de carga controlado por la política de rehash, insertar, buscar y borrar en una tabla encadenada cuesta O(1) esperado, porque los elementos quedan repartidos en buckets cortos. En el peor caso, si todas las claves colisionan en el mismo bucket (por mala suerte, mala función hash, o ataque deliberado a la función hash), el costo se degrada a O(n), porque en ese caso toda la tabla se comporta como una sola lista enlazada.

### Bloque 2

### Bloque 3

### Bloque 4


### Bloque 5


### Bloque 6


### Bloque 7

### Bloque 8


### Bloque 9


### Bloque 10


### Bloque 11


### Bloque 12



