### Actividad 8 - CC232

#### Estudiante

- Nombre: Santiago Alejandro Ramirez Aguilar

### Bloque 1

### Tabla: compilación completa de la carpeta
 
| Comando ejecutado | Resultado | Error | Interpretación |
|---|---|---|---|
| `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` | Configuración generada (Ninja, GNU 15.2.0) | Ninguno | El proyecto configura sin problemas |
| `cmake --build build-debug` | 28/28 targets compilados | Ninguno | Todo el código (Semana 8 y lo demás en la misma configuración) compila sin errores |
| `ctest --test-dir build-debug -R semana8 --output-on-failure` | 6/6 pruebas pasaron en 1.45 s | Ninguno | Todas las pruebas de Semana 8 pasan, incluida la comparación contra STL |
 
### Archivos revisados primero
 
* `README.md`: para entender el propósito de la semana y cómo se conecta con Semana5, Semana6 y Semana7.
* `CMakeLists.txt`: para ver qué targets y pruebas están registrados y cómo se agrupan.
* `Capitulo9.h`: para confirmar qué headers forman el núcleo agregador de la semana.
 
### 1. Qué targets de demostración aparecen para Semana 8
 
`sem8_demo_chained`, `sem8_demo_linear`, `sem8_demo_hashtable_oa`, `sem8_demo_aplicaciones`, `sem8_demo_collision_strategies`, `sem8_demo_hash_functions`, `sem8_demo_tombstones`, `sem8_demo_benchmark_load_factor`.
 
### 2. Qué pruebas públicas e internas aparecen
 
Pública: `sem8_test_public` (de `pruebas_publicas/`). Internas: `sem8_test_internal`, `sem8_test_tombstones`, `sem8_test_collision_patterns`, `sem8_test_rehashing`, `sem8_test_randomized_against_stl` (todas de `pruebas_internas/`).
 
### 3. Qué archivos incluye Capitulo9.h
 
`Applications.h`, `ArrayStack.h`, `Bitmap.h`, `ChainedHashTable.h`, `Dictionary.h`, `DoubleHashTable.h`, `Entry.h`, `HashCode.h`, `HashStats.h`, `HashtableOA.h`, `LinearHashTable.h`, `PrimeUtils.h`, `QuadraticHashTable.h`, `RehashPolicy.h`, `RobinHoodHashTable.h`, `UniversalHash.h`, `array.h`. Es el header agregador que reúne todo el contenido de la semana en un solo include.
 
### 4. Qué relación conceptual hay entre Semana 5, Semana 6, Semana 7 y Semana 8
 
Según el `README.md`: Semana5 introduce árboles binarios, BST y búsqueda ordenada básica. Semana6 refuerza priority queues, heaps y comparación experimental. Semana7 estudia AVL y Red-Black Tree, con garantía de altura logarítmica. Semana8 contrasta esas estructuras ordenadas con tablas hash, que buscan eficiencia esperada constante bajo buena dispersión, cerrando el bloque con el contraste entre eficiencia garantizada (semanas 5-7) y eficiencia esperada (semana 8).
 
### 5. Por qué no es correcto decir que una tabla hash siempre tiene costo O(1) garantizado
 
Porque ese O(1) depende de que la función hash distribuya bien las claves y de que el factor de carga se mantenga controlado mediante rehashing; en el peor caso (muchas colisiones, mala función hash, o carga sin controlar) el costo real puede degradarse a O(n), como se demostró en bloques anteriores con buckets sobrecargados y con `x % m` sin mezcla. Es un costo esperado bajo buenas condiciones, no una garantía matemática como la de un árbol balanceado.
 
### 6. Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada
 
La ejecución de `ctest --test-dir build-debug -R semana8 --output-on-failure` mostró que las 6 pruebas filtradas (`semana8_public`, `semana8_internal`, `semana8_tombstones`, `semana8_collision_patterns`, `semana8_rehashing`, `semana8_randomized_against_stl`) pasan sin fallos, y que la compilación completa (`[28/28]`) terminó sin errores de compilación ni de enlazado.
 
### 7. Qué diferencia práctica hay entre compilar todo el proyecto y compilar solo los targets de Semana 8
 
Compilar todo el proyecto (`cmake --build build-debug` sin `--target`) construye los 28 targets registrados, incluyendo posibles ejecutables de otras semanas si comparten la misma configuración de CMake, lo cual tarda más y usa más recursos. Compilar solo los targets de Semana 8 (pasando `--target sem8_demo_chained sem8_demo_linear ...` como se muestra en el `README.md` para Windows) construye únicamente los demos y pruebas de esa semana, acelerando el ciclo de compilación cuando solo se está trabajando en esa carpeta.
 
### Conclusión inicial
 
El proyecto compila sin errores y las 6 pruebas de Semana 8 pasan en menos de 1.5 segundos, lo cual indica que la base de código (interfaz, funciones hash, tablas de colisión, políticas de rehash y aplicaciones) está en un estado estable antes de cualquier modificación. La organización declarada en `README.md` y `CMakeLists.txt` coincide: los targets de demo y prueba listados en el README aparecen exactamente en el `CMakeLists.txt`, y `Capitulo9.h` agrupa todos los headers de la semana sin faltantes. Con esta base verificada, cualquier cambio posterior puede evaluarse comparando contra esta evidencia inicial de referencia.

### Bloque 2

### 1. Diccionario abstracto
 
Un diccionario abstracto (ADT Dictionary) es una estructura que asocia claves únicas (K) con valores (V), definiendo únicamente el contrato de operaciones put, get, remove y size, sin especificar cómo se implementan internamente (arreglo, lista, árbol, hash, etc). En el código, esto corresponde exactamente a la interfaz Dictionary<K,V>, una clase abstracta pura con métodos virtuales.
 
### 2. Diferencia entre diccionario, mapa, conjunto y tabla hash
 
Diccionario es el concepto abstracto (interfaz) de asociación clave valor.
 
Mapa (map) es prácticamente sinónimo de diccionario; es el nombre que suelen usar las bibliotecas concretas, por ejemplo std::map o std::unordered_map.
 
Conjunto (set) es un caso particular donde solo importan las claves, sin valor asociado; V es vacío o irrelevante.
 
Tabla hash es una implementación concreta del diccionario que usa una función hash para ubicar las claves en un arreglo, logrando operaciones en tiempo esperado O(1).
 
En resumen, diccionario, mapa y conjunto son conceptos (qué se hace), mientras que tabla hash es una técnica (cómo se hace).
 
### 3. Entry<K,V>
 
Representa un par clave valor individual almacenado dentro de la estructura. Es la unidad mínima de dato que guarda una tabla hash o cualquier diccionario: contiene la clave (key) usada para buscar y el valor (value) asociado que se recupera.
 
### 4. Función hash
 
Una función hash toma una clave, de cualquier tipo como int o std::string, y produce un número entero llamado código hash de forma determinística. Ese número se usa para calcular un índice dentro del arreglo interno de la tabla, permitiendo ubicar o insertar el elemento en tiempo aproximadamente constante. En HashCode.h, la función hashCode cumple este rol, y mix64 revuelve los bits del resultado para dispersarlo mejor.
 
### 5. Por qué pueden existir colisiones aunque el hash sea razonable
 
Porque el dominio de claves posibles es mucho mayor que la capacidad del arreglo, según el principio del palomar. Con una capacidad finita, siempre habrá múltiples claves distintas cuyo hash módulo capacity coincide, sin importar qué tan buena sea la dispersión de la función. Una buena función hash minimiza las colisiones, pero no puede eliminarlas por completo.
 
### 6. Factor de carga
 
Es la razón entre la cantidad de elementos almacenados y la capacidad del arreglo interno, es decir elementos dividido capacidad. Indica qué tan llena está la tabla. Un factor de carga alto aumenta las colisiones y degrada el rendimiento. En RehashPolicy.h, maxLoad y minLoad son los umbrales que controlan este balance.
 
### 7. Rehashing
 
Es el proceso de redimensionar el arreglo interno, normalmente duplicándolo o reduciéndolo, y reinsertar todos los elementos en la nueva estructura, cuando el factor de carga sale de un rango aceptable. Sirve para mantener el rendimiento O(1) esperado a medida que la tabla crece o se vacía. Los métodos grownCapacity y shrunkCapacity en RehashPolicy.h calculan la nueva capacidad.
 
### 8. Qué mide HashStats
 
Recoge métricas de desempeño y comportamiento interno de la tabla hash: número de inserciones, búsquedas exitosas y fallidas, remociones, colisiones, probes totales y máximos (para medir el clustering), rehashes realizados y tombstones (marcas de borrado) activos. Sirve para diagnosticar la calidad de la función hash y de la política de resolución de colisiones.
 
### 9. Qué decide RehashPolicy
 
Define cuándo y cuánto debe crecer o achicarse la tabla: los umbrales de carga (maxLoad, minLoad, maxOccupiedLoad, este último considerando también los tombstones), la capacidad mínima y los factores de crecimiento y reducción. Sus métodos shouldGrow, shouldShrink y shouldCleanOrGrow encapsulan la lógica de decisión, separándola de la implementación de la tabla en sí.

### 10. Costo esperado (hash) frente al costo garantizado de AVL y Red Black Tree

| Aspecto | Tabla hash | AVL / Red Black |
|---|---|---|
| Costo típico | O(1) esperado (amortizado) | O(log n) garantizado |
| Peor caso | O(n) si hay muchas colisiones | O(log n) siempre |
| Orden de claves | No se preserva | Se preserva (recorrido in order) |
| Predictibilidad | Depende de la función hash y del factor de carga | Determinístico, no depende de los datos |

La tabla hash gana en el caso promedio, pero no ofrece garantías en el peor caso. Los árboles balanceados sacrifican algo de velocidad promedio a cambio de una cota superior estricta y de mantener el orden de las claves.

### Tabla conceptual

| Concepto | Definición | Archivo relacionado | Ejemplo |
|---|---|---|---|
| Diccionario abstracto | Interfaz que asocia claves con valores (put, get, remove, size) | Dictionary.h | dict.put("Peru", 1) |
| Entry | Par clave valor almacenado | Entry.h | Entry<string,int>{"Peru", 1} |
| Función hash | Convierte una clave en un entero disperso | HashCode.h | hashCode("Peru") |
| Mezcla de bits (mix64) | Dispersa los bits del hash para reducir patrones | HashCode.h | mix64(x) |
| Factor de carga | Elementos activos dividido capacidad | RehashPolicy.h | active=70, capacity=100, resultado 0.70 |
| Rehashing | Redimensionar y reinsertar elementos | RehashPolicy.h | grownCapacity(100) da 201 |
| Tombstone | Marca de un elemento borrado (borrado perezoso) | HashStats.h | tombstones aumenta tras un remove |
| Estadísticas de hash | Métricas de uso y rendimiento de la tabla | HashStats.h | stats.collisions, stats.maxProbeLength |

### Por qué el hashing no reemplaza a los árboles balanceados

El hashing suele ofrecer búsquedas muy rápidas en promedio, pero puede degradarse hasta O(n) si ocurren muchas colisiones o la tabla no se redimensiona adecuadamente. Además, no mantiene las claves ordenadas. En cambio, los árboles AVL y Red-Black garantizan operaciones en O(log n) y conservan el orden de las claves, facilitando recorridos ordenados y consultas por rango. Por ello, se usa hashing cuando se prioriza la velocidad promedio y árboles balanceados cuando se requiere orden o garantías de rendimiento.

### Bloque 3

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


### Bloque 4

### Codigo nuevo

```cpp
// findCollidingKeys.h
#include <cstddef>
#include <vector>
#include "HashCode.h"

std::vector<int> findCollidingKeys(std::size_t capacity,
                                    std::size_t targetBucket,
                                    std::size_t needed) {
    std::vector<int> found;
    for (int x = 0; static_cast<std::size_t>(found.size()) < needed; ++x) {
        if (ods::hashCode(x) % capacity == targetBucket) {
            found.push_back(x);
        }
    }
    return found;
}
```

```cpp
// demo_hash_functions.cpp
#include "findCollidingKeys.h"

for (std::size_t cap : {std::size_t(8), std::size_t(16)}) {
    auto keys = findCollidingKeys(cap, /*targetBucket=*/0, /*needed=*/4);
    std::cout << "capacity=" << cap << " -> ";
    for (int k : keys) {
        std::cout << k << " (hash%cap=" << ods::hashCode(k) % cap << ") ";
    }
    std::cout << "\n";
}
```

Claves encontradas (bucket objetivo 0)
* Capacidad 8: 6, 29, 33, 38
* Capacidad 16: 6, 29, 38, 103

### Tabla clave, hash y bucket

| Capacidad | Clave | hashCode(x) (64 bits) | hash mod capacidad |
|---|---|---|---|
| 8 | 6 | 13647215125184110592 | 0 |
| 8 | 29 | 13509472508297990000 | 0 |
| 8 | 33 | 3174492301114349736 | 0 |
| 8 | 38 | 16934044424796929712 | 0 |
| 16 | 6 | 13647215125184110592 | 0 |
| 16 | 29 | 13509472508297990000 | 0 |
| 16 | 38 | 16934044424796929712 | 0 |
| 16 | 103 | 1866550240620900528 | 0 |

### Evidencia de colisión real

Ejecución compilada del código de arriba:

```
capacity=8 -> 6 (hash%cap=0) 29 (hash%cap=0) 33 (hash%cap=0) 38 (hash%cap=0)
capacity=16 -> 6 (hash%cap=0) 29 (hash%cap=0) 38 (hash%cap=0) 103 (hash%cap=0)
```

Y la comprobación de que 0, 8, 16, 24 no colisionan bajo el hash real (solo bajo `x mod m` puro):

```
0,8,16,24 mod8 reales: 7 6 7 4
```

### 1. Por qué 0, 8, 16, 24 solo garantiza colisión si h(x) = x mod m

Esos cuatro números son múltiplos de 8, así que si la función efectiva de bucket fuera literalmente `x mod m` con m=8, los cuatro darían resto 0 y colisionarían por construcción. Es una propiedad de la aritmética modular sobre esos números, no del hashing en sí.

### 2. Qué ocurre si antes se aplica una mezcla como hashCode(x)

Esa garantía desaparece. `mix64` revuelve los bits de x antes de calcular el módulo, así que valores con relación aritmética simple (como ser todos múltiplos de 8) ya no producen el mismo resultado. La prueba de arriba lo confirma: 0, 8, 16 y 24 terminan en buckets 7, 6, 7 y 4 respectivamente, no todos en el mismo.

### 3. Que claves encontré para un mismo bucket con capacidad 8 o 16

Con capacidad 8: 6, 29, 33, 38. Con capacidad 16: 6, 29, 38, 103. Ambas listas se obtuvieron probando enteros desde 0 hacia arriba y quedándose con los que caen en el bucket 0 tras aplicar `hashCode(x) % capacity`.

### 4. Como cambia el experimento si se usan cadenas en lugar de enteros

El bucle de búsqueda ya no puede recorrer "el siguiente entero", porque el espacio de cadenas no tiene un orden natural simple para enumerar. Se necesitaría generar cadenas de alguna forma sistemática (por ejemplo por longitud creciente y combinaciones de caracteres) y aplicar `hashCode(const std::string&)`, que usa una variante FNV antes del mix64. La lógica de comparar `hash % capacity == targetBucket` es la misma, pero la generación de candidatos es mucho más cara porque el universo de cadenas crece exponencialmente con la longitud.

### 5. Por qué este bloque es importante para defender evidencia experimental honesta

Porque muestra que las colisiones reportadas no fueron elegidas a mano ni asumidas por una fórmula ingenua como `x mod m`; se buscaron y se verificaron ejecutando el código real contra la función hash real del proyecto. Eso evita el error común de mostrar un ejemplo bonito (0, 8, 16, 24) que en realidad no colisiona una vez que se aplica el mix, y deja evidencia reproducible: cualquiera puede compilar la misma función y obtener los mismos resultados.

### Bloque 5

### Salida relevante de los demos
 
```
$ ./sem8_demo_linear.exe
LinearHashTable
size=5 capacity=8 activeLoad=0.625 occupiedLoad=0.625 tombstones=0
insertions=6, successfulSearches=1, failedSearches=6, removals=1, collisions=1, totalProbes=17, maxProbeLength=4, averageProbeLength=1.21429, rehashes=0, tombstones=0
 
$ ./sem8_demo_tombstones.exe
Linear tombstones=4 activeLoad=0.125 occupiedLoad=0.1875
HashtableOA tombstones=4 activeLoad=0.216216 occupiedLoad=0.324324
```
 
### Cómo se obtuvieron esos numeros (demo_linear.cpp)
 
Con capacidad 8 (mascara m-1=7), los hashes reales de las claves usadas dan estas posiciones iniciales:
 
7 mod 8 = 7, 15 mod 8 = 5, 23 mod 8 = 6, 31 mod 8 = 2, 39 mod 8 = 4, 47 mod 8 = 5.
 
Un detalle importante del código: cada `add(x)` primero llama a `contains(x)` para verificar que la clave no exista, y esa verificación ya cuenta como una búsqueda (fallida, normalmente) con su propio sondeo. Luego el propio `add` hace su sondeo de inserción, que se cuenta aparte. Por eso, aunque solo hay 6 inserciones, `totalProbes` acumula el costo de ambas fases en cada operación.
 
### Tabla
 
Secuencia de sondeo = posiciones visitadas durante la inserción. No incluye el sondeo interno de la verificación previa `contains(x)` dentro de `add`, que se explica en la nota debajo de la tabla.
 
| Operación | Clave | Posición hash inicial | Secuencia de sondeo | Estado final de la celda | size | occupied | loadFactor() | occupiedFactor() | tombstoneCount() |
|---|---|---|---|---|---|---|---|---|---|
| add | 7 | 7 | [7] | Filled | 1 | 1 | 0.125 | 0.125 | 0 |
| add | 15 | 5 | [5] | Filled | 2 | 2 | 0.250 | 0.250 | 0 |
| add | 23 | 6 | [6] | Filled | 3 | 3 | 0.375 | 0.375 | 0 |
| add | 31 | 2 | [2] | Filled | 4 | 4 | 0.500 | 0.500 | 0 |
| add | 39 | 4 | [4] | Filled | 5 | 5 | 0.625 | 0.625 | 0 |
| remove | 23 | 6 | [6] (encontrada de una) | Deleted | 4 | 5 | 0.500 | 0.625 | 1 |
| add | 47 | 5 | [5, 6] (celda 6 estaba Deleted, se reutiliza) | Filled | 5 | 5 | 0.625 | 0.625 | 0 |
 
Nota sobre las cuentas globales: si se suman también los sondeos de las verificaciones `contains(x)` dentro de cada `add` (todas de longitud 1, salvo la de la clave 47 que recorre 4 posiciones porque tiene que pasar por encima de la celda Deleted en 6 antes de llegar a una Empty en 0), el total de probes queda en 17, con probe máximo 4, tal como reporta `stats()`.
 
### Trazado manual de una búsqueda exitosa y una fallida
 
Búsqueda exitosa: `remove(23)` internamente llama a `findIndex(23)`. La posición inicial es 6 (23 mod 8). La celda 6 está Filled con el valor 23, así que la comparación coincide en el primer intento: 1 sondeo, búsqueda exitosa.
 
Búsqueda fallida: la verificación `contains(47)` dentro de `add(47)` llama a `findIndex(47)`. Posición inicial 5 (47 mod 8). La celda 5 está Filled con 15 (no coincide), avanza a la celda 6, que está Deleted (no es Empty, así que el bucle sigue probando), avanza a la celda 7, Filled con 7 (no coincide), avanza a la celda 0, que está Empty, y ahí se detiene: 4 sondeos, búsqueda fallida.
 
### 1. Qué representan los estados Empty, Filled y Deleted
 
Empty es una celda que nunca ha tenido un elemento, o que fue vaciada por un rehash completo. Filled es una celda que contiene actualmente un elemento activo. Deleted (tombstone) es una celda que tuvo un elemento pero fue removido; se marca así en lugar de vaciarla directamente.
 
### 2. Por qué Deleted no puede tratarse igual que Empty
 
Porque en open addressing la búsqueda de una clave depende de seguir la secuencia de sondeo hasta encontrar una celda Empty; si Deleted se tratara como Empty, la búsqueda cortaría ahí mismo y no seguiría probando las siguientes posiciones, perdiendo claves que en realidad siguen más adelante en la secuencia. Por eso findIndex sigue avanzando mientras el estado no sea Empty, aunque sea Deleted.
 
### 3. Diferencia entre size y occupied
 
size cuenta solo los elementos activos (Filled). occupied cuenta los elementos activos más las celdas marcadas como Deleted. La diferencia entre ambos es justamente tombstoneCount().
 
### 4. Por qué loadFactor() y occupiedFactor() pueden divergir después de muchas eliminaciones
 
loadFactor() usa size (elementos realmente presentes) mientras que occupiedFactor() usa occupied (activos más tombstones). Cada remove() baja size pero no baja occupied, así que después de varias eliminaciones sin limpieza, occupied queda mucho más alto que size, y los dos factores se separan.
 
### 5. Qué problema aparece si se acumulan demasiados tombstones
 
Las búsquedas fallidas se vuelven cada vez más caras, porque el bucle de findIndex tiene que atravesar todas las celdas Deleted que encuentre en el camino antes de llegar a una Empty o a la clave buscada. Aunque size sea bajo, occupied puede estar cerca de la capacidad, y en ese caso casi cualquier búsqueda termina recorriendo casi toda la tabla.
 
### 6. Cuándo debe hacerse rehashing por carga ocupada aunque haya pocos elementos activos
 
Cuando occupiedFactor() (activos más tombstones dividido capacidad) supera el umbral maxOccupiedLoad, aunque loadFactor() esté bajo. Ese es justo el chequeo shouldCleanOrGrow: sirve para limpiar los tombstones acumulados antes de que degraden las búsquedas, incluso si en ese momento hay pocos elementos realmente activos.
 
### 7. Qué costo tiene una búsqueda fallida cuando hay clustering
 
El costo deja de ser O(1) esperado y se acerca a recorrer todo el cluster de celdas ocupadas (Filled o Deleted) consecutivas hasta encontrar la primera Empty. Con mucho clustering ese recorrido puede acercarse a O(n) en el peor caso, como se ve en el ejemplo de la clave 47, que tuvo que pasar por tres celdas ocupadas antes de confirmar que no estaba.
 
### Por qué open addressing necesita una política cuidadosa de eliminación

En chaining, eliminar un elemento solo implica retirarlo de la lista asociada. En open addressing, no se puede marcar la celda como vacía porque esto rompería la secuencia de sondeo y podría hacer inaccesibles otras claves. Por ello se usa el estado Deleted (tombstone). Como estos marcadores se acumulan y afectan el rendimiento, es necesario realizar rehashes periódicos para eliminarlos.

### Bloque 6

Capacidad inicial: `nextPrime(max(minCapacity=8, 11)) = 11`. Los hashes reales (hashCode + mix64) de las tres claves dan:
 
"hash" mod 11 = 4, "tree" mod 11 = 9, "graph" mod 11 = 4.
 
"hash" y "graph" colisionan en el mismo bucket (4), lo que explica exactamente el `collisions=1` del resultado.
 
| Operación | Clave / valor | Resultado esperado | Posición | Sondeo | Evidencia observada |
|---|---|---|---|---|---|
| put | "hash", 1 | true (insertada) | 4 | 1 sondeo (bucket vacío) | insertions pasa a 1 |
| put | "tree", 2 | true (insertada) | 9 | 1 sondeo (bucket vacío) | insertions pasa a 2 |
| put | "graph", 3 | true (insertada) | bucket 4 ocupado, se reubica en 5 | 2 sondeos, colisión | insertions pasa a 3, collisions=1 |
| get | "hash" | optional con valor 1 | 4 | 1 sondeo (coincide de una) | successfulSearches=1, imprime "hash -> 1" |
| remove | "tree" | true (removida) | 9 | 1 sondeo (coincide de una) | removals=1, tombstoneCount=1 |
 
Con esto, `size=2` (quedan "hash" y "graph"), `capacity=11`, `load=2/11=0.181818`, `occupied=(2+1)/11=0.272727`, `tombstones=1`. Sumando todos los sondeos (1+1+1+1+2+2+1+1=10) se llega a `totalProbes=10`, `maxProbeLength=2` y `averageProbeLength=10/5=2`, exactamente lo que reporta la ejecución real.
 
### Ejemplo string a int para conteo de frecuencias
 
Usando `frequencyCount` de `Applications.h` sobre esta lista de palabras:
 
```
["the", "quick", "brown", "fox", "the", "fox", "the"]
```
 
El resultado esperado, aplicando `normalizeToken` y `put`/`get`/`remove` para actualizar cada contador, es:
 
| Clave | Valor (frecuencia) |
|---|---|
| the | 3 |
| quick | 1 |
| brown | 1 |
| fox | 2 |
 
`frequencyCount` funciona así: por cada palabra normalizada llama `get(s)`; si ya existe, hace `remove(s)` seguido de `put(s, valor+1)` (porque esta implementación de `put` no actualiza claves existentes, ver pregunta 6); si no existe, simplemente hace `put(s, 1)`.
 
### 1. Diferencia entre tabla usada como conjunto y como diccionario
 
Como conjunto, solo importa si una clave está presente o no (por ejemplo `ChainedHashTable<int>` en `hasDuplicates`, donde el "valor" es la propia clave). Como diccionario, cada clave tiene asociado un valor independiente que se puede consultar y actualizar (`HashtableOA<K,V>`), como en `frequencyCount` donde la clave es la palabra y el valor es su conteo.
 
### 2. Qué representa una clave
 
Es el dato que identifica de forma única una entrada dentro de la tabla, y es lo que se usa para calcular el hash y encontrar la posición donde buscar, insertar o borrar.
 
### 3. Qué representa un valor
 
Es el dato asociado a una clave, el que realmente interesa recuperar. La clave sirve para ubicar, el valor es lo que se quiere obtener o modificar (por ejemplo el contador en `frequencyCount`, o el índice en `twoSum`).
 
### 4. Qué debe devolver get(k) si la clave existe
 
Debe devolver el valor asociado envuelto en `std::optional<V>` con contenido válido, tal como hace `HashtableOA::get`, que retorna `table_[hit.index]->value` cuando `probe4Hit` encuentra coincidencia.
 
### 5. Qué debe ocurrir con remove(k) si la clave no existe
 
Debe devolver `false` sin modificar el estado de la tabla. En el código, si `probe4Hit` no encuentra la clave, `remove` incrementa `failedSearches` y retorna `false` sin tocar `size_`, `removed_` ni disparar ningún rehash.
 
### 6. Que política usa la implementación cuando se intenta insertar una clave repetida
 
`put` no sobrescribe: si `probe4Hit` encuentra la clave ya presente, incrementa `failedSearches` y retorna `false` sin modificar el valor existente. Por eso `frequencyCount` tiene que hacer `remove` seguido de `put` para simular una actualización, en vez de llamar `put` directamente sobre una clave existente.
 
### 7. Por qué una interfaz put, get, remove permite separar el uso del diccionario de su implementación interna
 
Porque el código que usa el diccionario (como las funciones de `Applications.h`) solo depende del contrato definido en `Dictionary<K,V>`, sin conocer si por debajo hay direccionamiento abierto, encadenamiento, o cualquier otra estrategia. Esto permite cambiar `HashtableOA` por `ChainedHashTable` u otra implementación sin tocar el código que la usa, siempre que se respete la misma interfaz.
 
### Como cambia el diseño si put debe actualizar una clave existente

Actualmente, `put` rechaza una inserción si la clave ya existe. Para permitir actualizaciones, cuando `probe4Hit` encuentre la clave (`hit.found == true`), bastaría con reemplazar el valor almacenado y devolver un resultado que indique éxito. Esto evitaría tener que hacer `remove` seguido de `put` para actualizar una clave, reduciendo sondeos innecesarios y la creación de tombstones adicionales.

### Bloque 7

### Salida demo
 
```
chained:   load=0.56338 longestBucket=2 stats={insertions=40, successfulSearches=0, failedSearches=0, removals=0, collisions=15, totalProbes=58, maxProbeLength=4, averageProbeLength=1.45, rehashes=3, tombstones=0}
linear:    load=0.3125 occupied=0.3125 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=13, totalProbes=116, maxProbeLength=4, averageProbeLength=1.45, rehashes=2, tombstones=0}
quadratic: load=0.412371 occupied=0.412371 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=16, totalProbes=126, maxProbeLength=4, averageProbeLength=1.575, rehashes=3, tombstones=0}
double:    load=0.412371 occupied=0.412371 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=22, totalProbes=156, maxProbeLength=6, averageProbeLength=1.95, rehashes=3, tombstones=0}
robinhood: load=0.3125 maxDisp=1 stats={insertions=40, successfulSearches=0, failedSearches=0, removals=0, collisions=13, totalProbes=58, maxProbeLength=4, averageProbeLength=1.45, rehashes=2, tombstones=0}
```
 
### Tabla comparativa
 
| Estrategia | Representación interna | Cómo resuelve colisiones | Métrica más sensible | Ventaja | Debilidad | Costo esperado | Peor caso |
|---|---|---|---|---|---|---|---|
| Chaining | Arreglo de buckets, cada uno una lista | Agrega la clave a la lista del bucket correspondiente | longestBucket | Simple, degrada suave, tolera factor de carga alto | Cada bucket es una estructura aparte, más memoria por lista | O(1 + factor de carga) | O(n) si un bucket concentra todo |
| Linear probing | Un solo arreglo de slots | Si el slot está ocupado, prueba el siguiente slot consecutivo | occupiedFactor / clustering | Buena localidad de memoria (cache friendly) | Forma bloques contiguos (clustering primario) que crecen con el uso | O(1) esperado con carga baja | O(n) con clustering severo |
| Quadratic probing | Un solo arreglo de slots | Prueba slots separados por pasos cuadráticos (i²) | maxProbeLength | Rompe el clustering primario de linear probing | Puede no cubrir todos los slots libres si la tabla no es prima o el tamaño no ayuda; clustering secundario | O(1) esperado, algo peor que linear en promedio aquí | O(n) si el patrón cuadrático no encuentra hueco rápido |
| Double hashing | Un solo arreglo de slots | El salto entre intentos depende de un segundo hash h2(x) | collisions / maxProbeLength | Distribuye mejor los saltos, evita clustering secundario | Más caro de calcular (dos hashes por operación), sensible a mala elección de h2 | O(1) esperado, el mejor en distribución teórica | O(n) si ambos hashes coinciden mal |
| Robin Hood hashing | Un solo arreglo de slots, cada uno con su distancia al hogar | Reordena: el elemento que está más lejos de su posición ideal se queda, el más cercano cede el lugar | maxDisplacement | Empareja la varianza del costo de búsqueda entre elementos, búsquedas más predecibles | Inserciones más costosas por los intercambios, remove necesita desplazamiento hacia atrás | O(1) esperado con varianza baja | O(n) en teoría, pero mucho más raro que en linear/quadratic |
 
En esta ejecución concreta: `chained` tiene el promedio de sondeo más bajo (1.45) junto con `robinhood`, pero `robinhood` logra ese mismo promedio con un `maxDisplacement=1`, es decir ningún elemento quedó lejos de su posición ideal. `double` es la que más sondeos totales acumula (156) y el `maxProbeLength` más alto (6), reflejando que sus saltos, aunque teóricamente buenos, en esta muestra concreta tardaron más en encontrar hueco libre.
 
### 1. Qué es clustering primario
 
Es la formación de bloques contiguos de slots ocupados en linear probing, donde una vez que varias claves caen cerca unas de otras, cualquier nueva clave que aterrice dentro de ese bloque tiene que recorrerlo entero antes de encontrar un slot libre, lo que hace crecer el bloque aún más.
 
### 2. Por qué linear probing tiende a formar bloques contiguos
 
Porque cada colisión se resuelve avanzando al slot inmediatamente siguiente. Eso hace que dos claves que colisionan terminen adyacentes, y cualquier tercera clave que caiga en ese rango también se sume al mismo bloque, generando un efecto de bola de nieve.
 
### 3. Qué intenta mejorar quadratic probing
 
Evitar el clustering primario de linear probing, separando los intentos sucesivos por pasos cuadráticos (i²) en vez de pasos consecutivos, para que las claves que colisionan no queden pegadas unas a otras.
 
### 4. Qué intenta mejorar double hashing
 
Evitar el clustering secundario que puede aparecer con quadratic probing (donde claves con el mismo hash inicial siguen la misma secuencia de saltos). Al usar un segundo hash para definir el salto, dos claves que colisionan en el mismo slot inicial suelen seguir secuencias de sondeo distintas.
 
### 5. Qué intenta equilibrar Robin Hood hashing
 
Equilibra la distancia de cada elemento respecto a su posición ideal (home), haciendo que ningún elemento quede mucho más lejos que otro de su bucket de origen. Esto reduce la varianza del costo de búsqueda entre distintas claves, en vez de solo minimizar el promedio.
 
### 6. Por qué chaining y open addressing no tienen el mismo comportamiento ante carga alta
 
Porque en chaining un factor de carga mayor a 1 sigue siendo manejable (cada bucket simplemente tiene una lista más larga), mientras que en open addressing el factor de carga no puede pasar de 1 (no hay más slots que capacidad), y a medida que se acerca a 1 el costo de encontrar un slot libre se dispara, porque cada vez hay menos huecos disponibles para sondear.
 
### 7. Qué estrategia elegirías para una tabla pequeña de laboratorio
 
Chaining, por ser la más simple de implementar y depurar, y porque su comportamiento es fácil de razonar sin preocuparse por clustering ni por elegir un buen segundo hash.
 
### 8. Qué estrategia elegirías para una carga alta con muchas búsquedas
 
Robin Hood hashing, porque mantiene el costo de búsqueda más parejo entre todas las claves (bajo maxDisplacement), lo cual es justamente lo que más importa cuando se hacen muchas búsquedas repetidas bajo carga alta.
 
### 9. Qué estrategia se degrada más claramente en presencia de muchas eliminaciones
 
Cualquiera de las tres basadas en direccionamiento abierto con tombstones (linear, quadratic, double), porque cada eliminación deja una celda Deleted que las búsquedas posteriores igual tienen que atravesar; sin una limpieza (rehash) frecuente, esas tres acumulan tombstones y sus búsquedas fallidas se vuelven cada vez más largas.

### conclusion

Las cinco estrategias resuelven las colisiones con distintos compromisos. Chaining tolera mejor cargas altas al no depender de espacios libres. Linear probing es simple y rápida, pero sufre de clustering primario. Quadratic probing reduce ese problema mediante saltos variables. Double hashing mejora la distribución de los sondeos usando dos funciones hash, aunque con mayor costo de cálculo. Robin Hood hashing destaca por ofrecer búsquedas más uniformes y predecibles. En esta ejecución, chaining y Robin Hood lograron el mismo promedio de sondeos (1.45), pero Robin Hood presentó una dispersión mucho menor (`maxDisplacement = 1`), mientras que double hashing obtuvo el peor rendimiento práctico de la muestra.


### Bloque 8

### Salida de la demo original
 
```
x=10 hashCode%m=10 universal1=8 universal2=9
x=20 hashCode%m=4 universal1=10 universal2=0
x=30 hashCode%m=0 universal1=16 universal2=12
x=40 hashCode%m=2 universal1=8 universal2=7
x=50 hashCode%m=8 universal1=10 universal2=15
```
 
### Tabla de distribución para los tres conjuntos de claves
 
Todos los conjuntos tienen 200 claves y se probaron sobre una tabla de capacidad `m=101` (primo), midiendo tanto con `hashCode` como con `UniversalHash(seed=12345)`:
 
| Conjunto | Cantidad de claves | Capacidad | Buckets usados | Bucket más cargado | Colisiones observadas | Comentario sobre la distribución |
|---|---|---|---|---|---|---|
| 1. Enteros consecutivos (1000..1199) | 200 | 101 | 87 (hashCode) / 88 (UniversalHash) | 6 / 6 | 113 / 112 | Distribución pareja en ambos casos, cercana a lo esperado por el principio del palomar con n=200, m=101 |
| 2. Enteros con patrón repetitivo (múltiplos de 8: 0..1592) | 200 | 101 | 91 (hashCode) / 87 (UniversalHash) | 6 / 5 | 109 / 113 | El patrón aritmético no afecta la distribución porque el mix64 rompe la relación entre las claves antes del módulo |
| 3. Strings con prefijo común ("user_0000".."user_0199") | 200 | 101 | 83 (hashCode) / 86 (UniversalHash) | 6 / 7 | 117 / 114 | El prefijo compartido no genera clustering porque hashCode(string) mezcla todos los bytes, incluido el sufijo variable |
 
Las tres distribuciones son prácticamente equivalentes entre sí (entre 83 y 91 buckets usados de 101, cargas máximas entre 5 y 7), lo cual es justamente la señal de una buena función hash: el patrón de las claves de entrada (consecutivas, repetitivas, o con prefijo común) deja de importar una vez que se aplica el mix.
 
### Caso de contraste: qué pasa sin mezcla
 
Para mostrar qué ocurriría con una función hash débil, repetí el conjunto 2 (múltiplos de 8) pero con capacidad `m=32` (potencia de 2, que comparte factor con 8) y comparé tres funciones: `x % m` sin ninguna mezcla, `hashCode` (con mix64), y `UniversalHash`:
 
| Función | Buckets usados (de 32) | Bucket más cargado |
|---|---|---|
| x % m (sin mezcla) | 4 | 50 |
| hashCode (con mix64) | 32 | 12 |
| UniversalHash(12345) | 32 | 13 |
 
Con `x % m` puro, las 200 claves (todas múltiplos de 8) caen solo en 4 de los 32 buckets posibles, con un bucket cargando 50 elementos: es el caso patológico que ilustra por qué una función hash sin mezcla es peligrosa ante datos con patrón. Tanto `hashCode` como `UniversalHash` usan los 32 buckets con cargas mucho más parejas.
 
### Comparación entre hashCode y UniversalHash
 
En los tres conjuntos, `hashCode` y `UniversalHash` se comportan de forma casi idéntica: ambos usan una fracción similar de buckets (83-91 de 101) y tienen cargas máximas parecidas (5-7). La diferencia entre ellos no está en la calidad de la dispersión para datos comunes, sino en la garantía que ofrecen: `hashCode` es una función fija, la misma para todas las ejecuciones, mientras que `UniversalHash` elige `a` y `b` al azar (a partir de una semilla) en cada instancia, de modo que un atacante que no conozca la semilla no puede construir de antemano un conjunto de claves que fuerce colisiones, algo que sí podría hacer si conociera el código exacto de `hashCode`.
 
### 1. Qué propiedad debe tener una buena función hash
 
Debe distribuir las claves de forma aproximadamente uniforme sobre los buckets disponibles, de manera que claves con relaciones aritméticas o estructurales entre sí (consecutivas, con patrón, con prefijo común) no terminen agrupadas en los mismos buckets.
 
### 2. Por qué una función hash determinista puede ser buena para datos comunes y mala para datos adversariales
 
Porque al ser fija y conocida, alguien que conozca su fórmula exacta puede construir deliberadamente un conjunto de claves que todas produzcan el mismo bucket, degradando la tabla a O(n) a propósito. Con datos comunes (no diseñados para atacarla) esa función puede distribuir perfectamente bien, como se vio en los tres conjuntos de arriba.
 
### 3. Qué idea aporta hashing universal
 
Elegir la función hash al azar dentro de una familia de funciones válidas (en este caso, los parámetros `a` y `b` del esquema MAD), de modo que ningún conjunto de claves fijo pueda garantizar colisiones para todas las instancias: el atacante no sabe qué función se va a usar hasta que se elige la semilla en tiempo de ejecución.
 
### 4. Por qué no se debe evaluar una función hash con un solo conjunto de claves
 
Porque una función puede lucir excelente en un conjunto (por ejemplo, enteros aleatorios) y fallar catastróficamente en otro con estructura distinta (por ejemplo, múltiplos de un número que comparte factor con la capacidad), como se demostró con `x % m` sobre múltiplos de 8 y capacidad 32. Evaluar con varios conjuntos, incluyendo unos con patrón deliberado, es la única forma de detectar esos puntos débiles.
 
### 5. Qué relación existe entre dispersión y costo esperado
 
A mayor dispersión (buckets usados de forma pareja, sin buckets sobrecargados), más cerca está el costo real de las operaciones del O(1) esperado teórico. Cuando la dispersión es mala, aunque el factor de carga promedio sea bajo, algunos buckets concentran muchas claves y el costo de esas búsquedas se acerca a O(n), como se vio con el bucket de 50 elementos en el caso de `x % m`.
 
### Conclusión

La función hash es clave para lograr el rendimiento esperado de O(1) en una tabla hash. Los experimentos muestran que tanto `hashCode` como `UniversalHash` distribuyen bien distintos tipos de datos, evitando clustering significativo. En contraste, usar simplemente `x % m` puede generar concentraciones extremas y degradar el rendimiento. Esto demuestra que la eficiencia no depende solo del método de manejo de colisiones, sino también de una buena dispersión de las claves. Además, `UniversalHash` aporta mayor seguridad al usar parámetros aleatorios, dificultando la construcción intencional de colisiones.

### Bloque 9

### Tabla: capacidad, elementos, factor de carga, rehashes y máximo de sondeos
 
De `demo_benchmark_load_factor.cpp`:
 
| maxLoad configurado | Elementos insertados | Capacidad final | loadFactor() final | maxProbeLength | averageProbeLength | Tiempo (us) |
|---|---|---|---|---|---|---|
| 0.45 | 5000 | 32768 | 0.152588 | 13 | 1.32887 | 2613 |
| 0.65 | 5000 | 8192 | 0.610352 | 31 | 1.93973 | 1529 |
| 0.85 | 5000 | 8192 | 0.610352 | 69 | 2.44807 | 1513 |
 
Con maxLoad más bajo, la tabla crece antes y termina con más capacidad de la que estrictamente necesita (0.45 deja la tabla muy holgada), pero a cambio los sondeos se mantienen cortos (maxProbe=13). Con maxLoad alto (0.85), la tabla tolera mucha más ocupación antes de crecer, así que termina con la misma capacidad que con 0.65 pero con sondeos mucho más largos (maxProbe=69), porque deja que el factor de carga suba más antes de reaccionar. El tiempo total es menor con maxLoad alto porque hay menos rehashes de por medio (cada rehash cuesta recorrer todo lo insertado hasta ese momento), aunque cada búsqueda individual termine costando más sondeos.
 
### Explicación de costo amortizado
 
Cada rehash individual cuesta O(n), porque hay que recorrer y reinsertar todos los elementos que había hasta ese momento en la tabla nueva. Pero un rehash no ocurre en cada inserción: ocurre solo cuando el factor de carga cruza el umbral, y como la capacidad se multiplica (por ejemplo x2) cada vez que se crece, el número de rehashes necesarios para llegar a n elementos es aproximadamente log(n), no n. Si se reparte el costo total de todos los rehashes entre las n inserciones que los provocaron, cada inserción individual termina "pagando" solo una fracción constante de ese costo, en promedio. Por eso, aunque una inserción particular (la que dispara el rehash) sea cara, el costo promedio por inserción a lo largo de toda la secuencia sigue siendo O(1) amortizado.
 
### Interpretación de test_rehashing.cpp
 
El test inserta 1000 elementos en `ChainedHashTable`, `LinearHashTable` y `HashtableOA` (capacidades iniciales 8, 8 y 11 respectivamente) y solo verifica dos cosas: que la capacidad final sea mayor que la inicial, y que `stats().rehashes` sea mayor que cero, para las tres implementaciones.
 
Siguiendo exactamente la lógica de `RehashPolicy` (que decide crecer solo con base en la proporción elementos/capacidad, sin depender de qué claves específicas se insertan), se puede reconstruir la secuencia real de rehashes para 1000 inserciones:
 
| Tabla | Capacidad inicial | Rehashes ocurridos | Capacidad final |
|---|---|---|---|
| ChainedHashTable | 8 | 8 | 2303 |
| LinearHashTable | 8 | 4 | 2048 |
| HashtableOA | 11 | 7 | 1597 |
 
Esto confirma por qué el test pasa: en los tres casos la capacidad final es mucho mayor que la inicial y el contador de rehashes es claramente mayor que cero. También muestra una diferencia entre implementaciones: `LinearHashTable` necesita menos rehashes (4) porque cada uno prácticamente cuadriplica la capacidad (al normalizar a la siguiente potencia de 2), mientras que `ChainedHashTable` solo duplica aproximadamente en cada rehash y por eso necesita el doble de rehashes (8) para llegar a un tamaño similar.
 
### 1. Qué condición de carga provoca crecimiento
 
Que los elementos activos divididos entre la capacidad superen `maxLoad` (0.70 por defecto): `shouldGrow` devuelve true cuando `active/capacity > maxLoad`.
 
### 2. Qué condición puede provocar limpieza por tombstones
 
Que los elementos activos más los tombstones divididos entre la capacidad superen `maxOccupiedLoad` (0.82 por defecto): `shouldCleanOrGrow` devuelve true cuando `occupied/capacity > maxOccupiedLoad`, y en ese caso se hace un rehash al mismo tamaño solo para eliminar los tombstones acumulados.
 
### 3. Qué condición puede provocar contracción
 
Que los elementos activos divididos entre la capacidad caigan por debajo de `minLoad` (0.125 por defecto) y que la capacidad actual sea mayor que `minCapacity`: `shouldShrink` exige ambas condiciones a la vez.
 
### 4. Por qué rehashing cuesta O(n) en el momento en que ocurre
 
Porque hay que recorrer todos los elementos de la tabla vieja y reinsertarlos uno por uno en la tabla nueva (de distinto tamaño), y ese recorrido es lineal en la cantidad de elementos que había en ese momento.
 
### 5. Por qué aun así se habla de costo amortizado
 
Porque los rehashes no ocurren en cada inserción, sino cada vez menos frecuentemente a medida que la capacidad crece geométricamente (se duplica o similar). El número total de rehashes para llegar a n elementos es del orden de log(n), así que el costo acumulado de todos los rehashes, repartido entre las n inserciones, se mantiene constante en promedio por inserción.
 
### 6. Qué relación hay entre capacidad, factor de carga y número de sondeos
 
El factor de carga es elementos activos dividido capacidad. Cuanto más alto es ese factor (o sea, cuanto menor es la capacidad relativa a los elementos), más sondeos hacen falta en promedio para encontrar un slot libre o para verificar que una clave no está, porque hay menos huecos disponibles. Esto se ve claro en la tabla de arriba: con maxLoad=0.85 el maxProbeLength llega a 69, más del doble que con maxLoad=0.45 (13), aunque la capacidad final termine siendo la misma en 0.65 y 0.85.
 
### 7. Qué evidencia muestra HashStats sobre rehashings
 
El campo `rehashes` cuenta cuántas veces se disparó un rehash durante la vida de la tabla, y sirve como evidencia directa de que la política de crecimiento (o contracción) se activó las veces esperadas. En el benchmark, comparar `rehashes` junto con `capacity` y `maxProbeLength` permite ver el compromiso entre crecer temprano (más rehashes, tabla más grande, sondeos más cortos) y crecer tarde (menos rehashes, tabla más compacta, sondeos más largos).
 
### 8. Qué riesgo hay si se permite que el factor de carga sea demasiado alto
 
Que los sondeos se vuelvan cada vez más largos porque hay pocos huecos libres, acercando el costo real de las operaciones a O(n) en vez de O(1) esperado. El propio benchmark lo muestra: con maxLoad=0.85, el máximo de sondeos (69) es más de cinco veces el de maxLoad=0.45 (13), para el mismo número de elementos insertados.

### Bloque 10

Ambas (twoSum y wordFrequencyFromText) aparecen con evidencia directa en la salida de `demo_aplicaciones.cpp`:
 
```
duplicados=1
primer repetido=7
twoSum indices=0,1
hash=2 tree=2
```
 
### Trazado manual 1: twoSum
 
Entrada: `a = {2, 7, 11, 15, 7}`, `target = 9`. Internamente usa `HashtableOA<int,int> pos`, guardando valor -> índice.
 
| Paso | a[i] | need = target - a[i] | pos.get(need) | Resultado | pos después |
|---|---|---|---|---|---|
| i=0 | 2 | 7 | no existe | se guarda: pos.put(2, 0) | {2:0} |
| i=1 | 7 | 2 | existe, valor=0 | encontrado -> retorna (0, 1) | {2:0} |
 
El bucle termina en la segunda iteración, devolviendo el par de índices (0,1), porque `a[0]=2` y `a[1]=7` suman 9. Coincide exactamente con la salida real `twoSum indices=0,1`.
 
### Trazado manual 2: wordFrequencyFromText
 
Entrada: `"Hash hash TREE, tree hashing."`. Primero se tokeniza por espacios: `["Hash", "hash", "TREE,", "tree", "hashing."]`. Luego `frequencyCount` normaliza cada token (solo alfanuméricos, minúsculas) y actualiza la tabla `HashtableOA<std::string,int>`.
 
| Token crudo | normalizeToken | f.get(s) antes | Acción | f.get(s) después |
|---|---|---|---|---|
| "Hash" | "hash" | no existe | put("hash", 1) | 1 |
| "hash" | "hash" | 1 | remove("hash"); put("hash", 2) | 2 |
| "TREE," | "tree" | no existe | put("tree", 1) | 1 |
| "tree" | "tree" | 1 | remove("tree"); put("tree", 2) | 2 |
| "hashing." | "hashing" | no existe | put("hashing", 1) | 1 |
 
Resultado final: hash=2, tree=2, hashing=1. Coincide con la salida real `hash=2 tree=2` (hashing no se imprime en el demo, pero el cálculo es consistente). Nótese que cada actualización usa `remove` seguido de `put`, porque como se vio antes, `HashtableOA::put` no sobrescribe una clave existente.
 
### twoSum
 
1. Problema de entrada: un arreglo de enteros y un valor objetivo; se busca un par de índices cuyos valores sumen el objetivo.
2. Salida esperada: un par de índices (i, j) tal que a[i] + a[j] == target, o nada si no existe tal par.
3. Qué se guarda en la tabla hash: cada valor ya visitado del arreglo como clave, y su índice como valor.
4. Operación que domina el costo: el `get` y el `put` sobre la tabla hash, uno de cada por elemento recorrido.
5. Por qué el costo esperado puede ser lineal: cada acceso a la tabla es O(1) esperado, y el arreglo se recorre una sola vez, dando O(n) esperado en total.
6. Qué caso podría degradar el rendimiento: muchas colisiones (mala distribución de hash o factor de carga alto sin rehash a tiempo), que harían que cada get/put cueste más que O(1).
7. Cómo resolverlo con AVL o Red-Black: insertar cada valor visitado en un árbol balanceado junto a su índice, y para cada elemento buscar `target - a[i]` en el árbol; cada operación cuesta O(log n) garantizado, dando O(n log n) total.
8. Qué se gana y qué se pierde con hashing: se gana velocidad promedio (O(n) frente a O(n log n)); se pierde la garantía de peor caso y la posibilidad de consultas por orden o rango sobre los valores ya vistos.

### wordFrequencyFromText
 
1. Problema de entrada: un texto del cual hay que contar cuántas veces aparece cada palabra, ignorando mayúsculas y signos de puntuación.
2. Salida esperada: una tabla palabra -> frecuencia de aparición.
3. Qué se guarda en la tabla hash: cada palabra normalizada como clave, y su contador de apariciones como valor.
4. Operación que domina el costo: calcular el hash de cada palabra (proporcional a su longitud) más el get/put/remove correspondiente en la tabla.
5. Por qué el costo esperado puede ser lineal: cada palabra cuesta O(longitud de la palabra) para el hash más O(1) esperado de acceso a la tabla; sumado sobre todas las palabras del texto da un costo esperado proporcional al total de caracteres del texto.
6. Qué caso podría degradar el rendimiento: un vocabulario con muchas colisiones entre palabras distintas, o una tabla que no se redimensiona a tiempo conforme crece el vocabulario.
7. Cómo resolverlo con AVL o Red-Black: usar un árbol balanceado de palabra -> contador; cada inserción o búsqueda de palabra cuesta O(log w) garantizado (w = número de palabras distintas), con la ventaja adicional de poder recorrer el vocabulario en orden alfabético.
8. Qué se gana y qué se pierde con hashing: se gana velocidad promedio y simplicidad de implementación; se pierde el orden alfabético natural del vocabulario y la garantía de que ninguna palabra individual sea costosa de procesar.

### Comparación de costo esperado (hash) frente a costo garantizado (árbol balanceado)
 
En estas aplicaciones, la tabla hash ofrece un costo esperado de O(1) por operación y O(n) total al recorrer la entrada una sola vez, siempre que la distribución de claves sea adecuada. Los árboles AVL y Red-Black garantizan O(log n) por operación, independientemente de los datos de entrada, y además mantienen las claves ordenadas. Por ello, para problemas como `twoSum` o conteo de frecuencias, donde no se requiere orden, las tablas hash suelen ser más eficientes; los árboles balanceados resultan más útiles cuando se necesitan recorridos ordenados o búsquedas por rango.

### Bloque 11


### Bloque 12

### Matriz
 
| Estructura | Mantiene orden | Búsqueda promedio | Búsqueda peor caso | Inserción | Eliminación | Memoria adicional | Ventaja principal | Riesgo principal | Caso de uso recomendado |
|---|---|---|---|---|---|---|---|---|---|
| BST simple | Sí | O(log n) | O(n) | O(log n) promedio, O(n) peor caso | O(log n) promedio, O(n) peor caso | Punteros left/right/parent por nodo | Simple de implementar y entender | Se puede degradar a lista enlazada con entradas ordenadas o adversariales | Prototipos, datos ya aleatorizados, enseñanza |
| Treap | Sí | O(log n) esperado | O(n), pero extremadamente improbable | O(log n) esperado (rotaciones por prioridad) | O(log n) esperado | Punteros + una prioridad aleatoria por nodo | Balance probabilístico sin lógica de rebalanceo compleja | Depende de la calidad del generador aleatorio de prioridades | Cuando se quiere orden y balance simple sin implementar rotaciones AVL/RB completas |
| AVL | Sí | O(log n) garantizado | O(log n) garantizado | O(log n), con rotaciones para reequilibrar | O(log n), con rotaciones para reequilibrar | Punteros + altura o factor de balance por nodo | Árbol más estrictamente balanceado, búsquedas muy predecibles | Rebalanceo más frecuente que Red-Black, algo más lento en inserciones/eliminaciones intensivas | Lecturas muy frecuentes con pocas modificaciones |
| Red-Black Tree | Sí | O(log n) garantizado | O(log n) garantizado | O(log n), con menos rotaciones que AVL | O(log n), con menos rotaciones que AVL | Punteros + 1 bit de color por nodo | Buen equilibrio entre costo de balanceo y altura, estándar en bibliotecas | Implementación de los casos de fixup más intrincada de programar correctamente | Cargas mixtas de lectura y escritura (ej. std::map) |
| ChainedHashTable | No | O(1) esperado | O(n) si un bucket concentra todo | O(1) esperado, amortizado por rehash | O(1) esperado | Un arreglo de listas (buckets) | Tolera factor de carga alto sin degradarse abruptamente | Un bucket muy cargado hace lenta esa clave en particular | Conjuntos o mapas donde no importa el orden y se prioriza velocidad promedio |
| LinearHashTable | No | O(1) esperado | O(n) con clustering severo | O(1) esperado, amortizado por rehash | O(1) esperado, pero deja tombstones | Un solo arreglo con sondeo lineal | Buena localidad de memoria (cache friendly) | Clustering primario: bloques contiguos que crecen con el uso | Cuando la velocidad de acceso a memoria contigua importa más que la simplicidad conceptual |
| HashtableOA | No | O(1) esperado | O(n) con clustering severo | O(1) esperado, amortizado por rehash | O(1) esperado, pero deja tombstones | Un arreglo + un Bitmap de posiciones borradas | Diccionario clave-valor genérico con la misma filosofía de sondeo abierto | Acumulación de tombstones si no se limpia a tiempo (shouldCleanOrGrow) | Diccionarios (K,V) de propósito general sin necesidad de orden |
 
### 1. Cuándo elegirías una tabla hash
 
Cuando solo importa buscar, insertar o borrar por clave exacta, sin necesitar orden ni consultas por rango, y se prioriza la velocidad promedio sobre la garantía de peor caso.
 
### 2. Cuándo elegirías AVL
 
Cuando las búsquedas son mucho más frecuentes que las inserciones o eliminaciones, y conviene que el árbol quede lo más bajo posible para minimizar el costo de cada búsqueda, aceptando rebalanceos algo más costosos.
 
### 3. Cuándo elegirías Red-Black Tree
 
Cuando hay una mezcla equilibrada de inserciones, eliminaciones y búsquedas, y se prefiere un balanceo un poco más relajado que el de AVL a cambio de menos rotaciones por operación (es la elección típica de bibliotecas de propósito general).
 
### 4. Cuándo elegirías Treap
 
Cuando se quiere mantener orden y un balance razonable sin implementar la lógica completa de rotaciones deterministas de AVL o Red-Black, aceptando que la garantía de balance es probabilística en vez de estricta.
 
### 5. Por qué una tabla hash no sirve directamente para consultas por rango
 
Porque la función hash dispersa las claves deliberadamente para evitar patrones, así que dos claves cercanas en valor pueden terminar en posiciones completamente distintas y sin relación en el arreglo interno; no hay forma de recorrer "todas las claves entre X y Y" sin revisar toda la tabla.
 
### 6. Por qué un árbol balanceado sí permite recorrer claves en orden
 
Porque la propiedad de BST garantiza que todo lo que está a la izquierda de un nodo es menor y todo lo que está a la derecha es mayor, así que un recorrido in-order visita las claves en orden ascendente de forma natural, y las operaciones lowerBound/upperBound pueden navegar el árbol descartando la mitad del espacio de búsqueda en cada paso.
 
### 7. Qué significa que una estructura tenga costo esperado y otra tenga costo garantizado
 
Costo esperado significa que, en promedio (sobre muchas operaciones o asumiendo buena distribución de los datos), el costo es bajo, pero puede haber casos particulares donde una operación individual sea mucho más lenta. Costo garantizado significa que toda operación individual respeta esa cota, sin importar los datos de entrada ni la mala suerte.
 
### 8. Qué estructura preferirías para un índice de palabras sin orden
 
ChainedHashTable o HashtableOA, porque un índice invertido solo necesita consultar rápido si una palabra existe y a qué documentos apunta, sin necesitar recorrerlas en orden alfabético.
 
### 9. Qué estructura preferirías para un ranking ordenado por clave
 
Un Red-Black Tree o un AVL, porque un ranking necesita mantener las entradas ordenadas por su clave (por ejemplo puntaje) y poder recorrerlas o consultar posiciones relativas de forma eficiente y garantizada.
 
### 10. Qué estructura preferirías si necesitas lowerBound y upperBound
 
Cualquiera de los árboles balanceados (AVL, Red-Black, o Treap), ya que estas operaciones dependen de la propiedad de orden del árbol; una tabla hash no puede implementarlas de forma eficiente porque no conserva ninguna relación de orden entre las claves.
 
### Ejemplo concreto donde hashing gana
 
Un sistema de autocompletado de nombres de usuario que solo necesita responder "¿este nombre de usuario ya existe?" al momento de registrar una cuenta nueva. No importa el orden de los nombres, solo la verificación de existencia lo más rápido posible; una tabla hash (como HashtableOA<string,bool>) responde en O(1) esperado, mientras que un árbol balanceado gastaría O(log n) sin necesidad, ya que nunca se pide recorrer los nombres en orden ni buscar rangos.
 
### Ejemplo concreto donde AVL o Red-Black Tree gana
 
Un sistema de reservas que necesita encontrar, dado un horario deseado, el primer espacio disponible igual o posterior a esa hora (`lowerBound`), y también poder listar todos los espacios disponibles entre dos horas dadas. Una tabla hash no puede resolver ninguna de las dos consultas de forma eficiente porque no preserva el orden de los horarios; un AVL o Red-Black Tree las resuelve en O(log n) garantizado, navegando el árbol y aprovechando la propiedad de orden para descartar subárboles enteros en cada paso.
 
### Conclusión final
 
La elección entre árboles balanceados y tablas hash depende de si se necesita mantener orden. Si solo se realizan búsquedas por clave exacta, una tabla hash ofrece el mejor rendimiento promedio y una implementación sencilla. En cambio, si se requieren recorridos ordenados, búsquedas por rango o encontrar valores cercanos, los árboles balanceados son la opción adecuada. Entre ellos, AVL destaca cuando predominan las búsquedas, Red-Black Tree ofrece un buen equilibrio para cargas mixtas y Treap es más simple de implementar. Entre las tablas hash, ChainedHashTable tolera mejor factores de carga altos, mientras que las variantes de sondeo abierto aprovechan mejor la memoria, aunque requieren gestionar los tombstones. En definitiva, la elección depende de si el problema prioriza velocidad promedio o mantenimiento del orden con garantías de peor caso.

