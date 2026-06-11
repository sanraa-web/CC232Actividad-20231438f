### ACTIVIDAD 1 - CC232 
Santiago Alejandro Ramirez Aguilar

### BLOQUE1:
. Problema: Es un enunciado que describe una tarea a resolver sin decir cómo resolverla.
Ejemplo: "Dada una lista de n números, devolver la misma lista ordenada de menor a mayor."	

. Algoritmo: Es un procedimiento para resolver un problema. Es independiente del lenguaje de programación concreto.

. ADT: describe qué hace la estructura: operaciones + semántica

. implementación: Es la traducción del algoritmo o del ADT a código

1.2
La función bubbleSortOptimized demuestra dicha propiedad.

1.3
La version de power, usando el algoritmo de exponentiation by squaring,  logra una complejidad O(log n), haciéndolo idóneo para n grandes.

1.4
Es una mala elección práctica porque recalcula subproblemas repetidamente, resultando en complejidad exponencial O(2^n) y de tiempo impráctico.

1.5
La razon es que se mide el numero entero (n) según su representación binaria (en este caso 32 bits).

1.6
La razon es que el contrato ya esta definido sin especificar la implementación, esto permite la modularidad, reutilización y optimizaciones sin afectar el código cliente.

### BLOQUE2:

| Archivo | Salida u observable importante | Idea algorítmica | Argumento de costo |
|---------|-------------------------------|------------------|-------------------|
| `demo_countones.cpp` | Resultados idénticos de countOnes1 y countOnes2; representación binaria de x | Contar bits en 1 eliminando el último 1 vs agrupando por bloques | O(k) (k = número de 1s) vs O(1) para ancho fijo |
| `demo_power.cpp` | Resultados idénticos de powerBF y power para 3^5 | Potenciación por multiplicación repetida vs exponentiation by squaring | O(n) vs O(log n), logarítmico más eficiente |
| `demo_fibonacci.cpp` | Valores idénticos de fibI, fib y fib con prev para n=10 | Fibonacci iterativo vs recursivo ingenuo vs con acumulación | O(n) vs O(2^n), exponencial impráctica para n grande |
| `demo_bubblesort.cpp` | Estadísticas (comparisons, swaps, lastSwapIndex); invariante del sufijo ordenado | Bubble sort optimizado con parada temprana | Reduce intercambios innecesarios, O(n²) peor caso pero mejor en práctica |

2.1
Las estadísticas de salida (comparisons, swaps, lastSwapIndex) defienden el costo del algoritmo al cuantificar el trabajo realizado (comparaciones e intercambios), adicional del resultado final. El invariante sobre el sufijo ordenado refuerza por qué el algoritmo termina temprano.

2.2
La comparación entre powerBF(base, exp) y power(base, exp) muestra una mejora algorítmica, pero ambos dan el mismo resultado. La unica diferencia es la complejidad temporal, siendo power mas rápido.

2.3
El crecimiento lineal O(n) de fibI y la clase Fib se vuelve defendible para n grande, a diferencia del crecimiento exponencial O(2^n) de fib recursiva ingenua, que es impráctica para n muy grandes (10 < n).

2.4
El ejemplo de x = 0b101101001u (valor 361) con representación binaria de 9 bits ayuda a distinguir: el valor numérico es pequeño, pero el tamaño en bits determina la complejidad.


### BLOQUE3:
3.1
Verifica la funcionabilidad básica de los algoritmos, controla los casos limite y verifica resultados.

3.2
Valida ejemplos representativos y la interacción básica.

3.3
No prueba toda la amplitud del comportamiento posible, dando un riesgo de que no evalué un caso donde no funcione correctamente.

3.4
Problema 16: Significa que sigue funcionando bien cuando las cosas no van perfectas. No se rompe de forma inesperada.
Lograrlo combina buen diseño (contratos, invariantes), validación, manejo de errores, y pruebas exhaustivas.

3.5
comprensión conceptual: Se entiende la noción de los conceptos pero falta profundidad.
sustentación de correctitud: En proceso, sigue sin ser comodo o acostumbrado al uso de los conceptos.
análisis de eficiencia: No logrado, se necesita mucho tiempo para poder analizar.

### BLOQUE4:
4.1
lectura no alteran nada, modificación crea la alteración del original y deja el original igual pero produce un nuevo vector con el elemento añadido.

4.2
La diferencia recae en el crecimiento del vector, haciéndolo mas predecible y rápido o sino mas lento.

4.3
Es debido a como trabajan el desplazamiento de memoria de manera distinta.

4.4.
Mejor localidad suele ser mucho más importante que la estructura que usa.


### BLOQUE5:

5.1
. primero se debe elegir bien el algoritmo
. luego verifique que el programa sea correcto 
.después medir rendimiento

5.2
reserve: resuelve el problema de fragmentación y copias innecesarias . Se obtienen menos llamadas al sistema y copia de memoria 

nth_element: Resuelve la búsqueda de mediana

partial_sort: Resuelve rankings o top-k.  Reduce drásticamente las comparaciones innecesarias 

lower_bound: Resuelve las consultas frecuentes en datos estáticos. Cambia la búsqueda lineal a algorítmica

5.3
genera una evidencia técnica completa de los experimentos de optimización y calidad de código

5.4
menciona que, si trabajas en Windows (especialmente usando Git Bash o MSYS2), podrías enfrentar problemas con herramientas avanzadas.

### BLOQUE 6:
Afirmación de especificación: Ahora no solo definimos qué hace el programa, sino bajo qué condiciones exactas debe responder

Afirmación de corrección: Pasamos de creer que el código está bien a usar sanitizers y pruebas de cobertura para garantizar que no existan errores ocultos de memoria o caminos del código que nunca se probaron

Afirmación de costo: 
 Aquí descubrimos que un algoritmo teóricamente rápido puede ser lento si no aprovecha bien la memoria caché del procesador

Afirmación de representación o memoria:
 Evaluamos cómo el uso de estructuras evita el desperdicio de recursos y reduce el tamaño del ejecutable, optimizando el espacio físico que ocupa el programa

Advertencia metodológica: Ten cuidado con las mediciones en entornos inestables. Si tu computadora está realizando otras tareas mientras mides, los tiempos de ejecución serán erróneos y no evidencia real
