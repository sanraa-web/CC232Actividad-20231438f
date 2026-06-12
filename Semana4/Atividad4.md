#

## BLOQUE 1

1. Principalmente, la diferencia cae en el orden de como se organizan los elementos que entran y salen. En FIFO se basa en el principio de equidad, este metodo está asciado con las filas. En cambio, en LIFO, se basa en el principio de proximidad temporal, este metodo es usado para pilas.

2. Porque los Stacks usan la forma de organizacion LIFO, que maneja el ultimo elemento.

3. Porque los Queue usan la estructura FIFO, donde el priemro que llega es el que tiene mayor prioridad.

4. Reemplazar la recursión implícita por una estructura explícita significa gestionar manualmente la información que normalmente almacena la pila de llamadas del sistema.

5. Debe guardarse únicamente la información necesaria para describir la decisión actual y permitir el retroceso si la solución falla.

6. Ambas versiones realizan el mismo cálculo. La diferencia es que la recursiva utiliza la pila de llamadas, mientras que la iterativa administra una pila de forma explícita.

7. Porque cada cierre debe verificarse contra la apertura pendiente más reciente, información que una pila mantiene naturalmente.

8. Porque operandos y operadores tienen funciones diferentes y requieren reglas de procesamiento distintas, por lo que conviene almacenarlos por separado.

9. Tanto el problema de las N-Reinas como el del Laberinto son ejemplos naturales de backtracking porque ambos se basan en una exploración de "ensayo y error" dentro de un espacio de búsqueda que se puede visualizar como un árbol de decisiones.

10. Porque una fila bancaria sigue el principio FIFO, mientras que una pila sigue LIFO y alteraría el orden real de atención.

11. La estructura auxiliar conserva el estado parcial del algoritmo; si este estado se almacena incorrectamente, la solución también será incorrecta.

12. Resolver un problema busca una respuesta final específica, mientras que simular un proceso busca representar la evolución de un sistema a través del tiempo.

## BLOQUE 2

1. La salida stack.top(), refiriendose al tope de pila y queue.front(), refiriendose al frente de cola.

2. En ods::toBaseRecursive que usa convertRecursive, mientras que en ods::toBaseIterative se usa convertIterative.

3. Es una serie de pasos para garantizar rpn, primero con parenIterative chequea el orden de los parantesis y si esta bien estructurado, luego con evaluated.rpn usa   de ExpressionEvaluator.h para hacer el cambio y de evaluated.value sale el resultado de la operacion.

4. `solutions` y `checks` en N-Reinas; `solutions` cuenta solo las configuraciones válidas finales encontradas (éxitos), mientras que `checks` cuenta cada validación de conflicto realizada durante la búsqueda (éxitos y fracasos). No miden lo mismo porque `checks` refleja el esfuerzo computacional real del backtracking, no solo el resultado final.

5. Recae en la secuencia de coordenadas en el laberinto, muestra la ruta exacta paso a paso desde la celda de inicio hasta la de destino, demostrando que el algoritmo conectó exitosamente una secuencia continua de celdas libres sin chocar con paredes.

6. Las listas impresas en cada instante `t` en el banco, representan el estado de las colas de cada ventanilla en ese momento exacto, mostrando el tiempo de atención restante de cada cliente que está en espera.

7. La secuencia completa que imprime el tope de la pila, el frente de la cola, la conversión de base, el balanceo de paréntesis, el valor RPN, las soluciones de N-Reinas, la longitud del camino y las estadísticas del banco. Esto demuestra cómo las estructuras base (pilas y colas) se aplican transversalmente a problemas matemáticos, de búsqueda y de simulación en una misma ejecución.

## Bloque 3

1. ¿Qué operaciones mínimas valida la prueba pública para Stack?
   Valida `empty()`, `push()`, `top()` y `pop()`, verificando el comportamiento LIFO (el último en entrar es el primero en salir).

2. ¿Qué operaciones mínimas valida la prueba pública para Queue?
   Valida `empty()`, `enqueue()`, `front()` y `dequeue()`, verificando el comportamiento FIFO (el primero en entrar es el primero en salir).

3. ¿Qué valida la prueba pública sobre conversión de base?
   Que tanto el método recursivo como el iterativo convierten correctamente el número 12345 a base 8, produciendo la cadena `"30071"`.

4. ¿Qué valida la prueba pública sobre paréntesis balanceados?
   Que acepta anidamientos correctos de distintos tipos (`()`, `[]`, `{}`) y rechaza cruces inválidos como `"([)]"`.

5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?
   Que una expresión compleja con factoriales y potencias se evalúa al valor numérico correcto (`2012.0`) y genera la cadena de Notación Polaca Inversa (RPN) esperada.

6. ¿Qué valida la prueba pública sobre NQueens?
   Que para un tablero de $N=4$, el algoritmo encuentra exactamente 2 soluciones válidas.

7. ¿Qué valida la prueba pública sobre Maze?
   Que dado un laberinto con una ruta disponible, la función `findPath` devuelve un camino no vacío que conecta el inicio con el final.

8. ¿Qué valida la prueba pública sobre `bestWindow` en la simulación bancaria?
   Que, dadas 3 ventanas con colas de clientes y tiempos de servicio específicos, el algoritmo selecciona correctamente la ventana con menor carga (índice 2).

9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?
   Casos borde y de error: conversión a base inválida (lanza excepción), laberinto sin salida (devuelve camino vacío), $N=1$ en N-Queens, expresiones con números negativos (`-3+5`) y cadenas sin paréntesis.

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?
    Las pruebas solo garantizan que el código funciona para un conjunto finito de entradas. No demuestran que el algoritmo sea eficiente (ej. $O(N \log N)$ vs $O(N^2)$) ni que mantenga la consistencia de sus estructuras de datos en estados intermedios no evaluados.

11. Ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos:
    Implementar `dequeue()` en una Cola usando un `std::vector` y haciendo `erase(begin())`. Las pruebas públicas (con 3 elementos) pasarían sin problemas, pero en producción, con miles de elementos, el costo sería $O(N)$ por operación en lugar de $O(1)$, causando un *Time Limit Exceeded* (TLE).

## Bloque 4

1. En conversión de base, el residuo (n % base) determina el dígito actual, el cociente (n / base) es el valor restante por procesar, y la pila sirve para invertir el orden de los dígitos generados.

2. Los residuos se apilan porque el algoritmo de división genera los dígitos desde el menos significativo (derecha) al más significativo ( izquiera). La pila (LIFO) los invierte para construir la cadena final en el orden de lectura correcto (izquierda a derecha).

3. Dejar que el call stack haga el trabajo (recursivo) es elegante y conciso, pero tiene overhead de llamadas a función y riesgo de desbordamiento (stack overflow). Manejar una pila explícita (iterativo) usa memoria del heap, es más rápida y evita los límites de profundidad de recursión del sistema.

4. En parenRecursive, divideParentheses intenta encontrar el punto exacto donde se cierra el primer paréntesis de apertura. Usa un contador de balance que sube con '(' y baja con ')'; cuando llega a cero, ha encontrado el límite para dividir la expresión en dos sub-problemas válidos.

5. La limitación conceptual de la versión recursiva mostrada es que está diseñada exclusivamente para paréntesis redondos (). Ignora por completo los corchetes [] y llaves {}, por lo que no puede validar anidamientos mixtos ni detectar cruces inválidos entre distintos tipos de símbolos, algo que la versión iterativa resuelve fácilmente con un switch.

6. En parenIterative, un cierre incorrecto se detecta al instante porque evalúa el tope de la pila en el momento exacto en que aparece. Si la pila está vacía o el elemento extraído no coincide con el tipo de apertura esperado, la función retorna false de inmediato, sin necesidad de leer el resto de la cadena.

7. La versión iterativa resulta más natural para el balanceo de paréntesis, ya que recorrer una cadena linealmente y emparejar con una pila es un proceso directo y eficiente. La versión recursiva resulta más expresiva para la conversión de base, pues su código refleja casi literalmente la definición matemática de la división sucesiva.

## Bloque 5

1. Almacena el valor numérico final de la expresión evaluada (`value`) y su representación equivalente en Notación Polaca Inversa (`rpn`).

2. Para simplificar el análisis léxico. Al quitar los espacios, el algoritmo no necesita ignorar caracteres en blanco al recorrer la cadena, haciendo la detección de números y operadores más directa y eficiente.

3. Se verifica si el carácter es '-', si está seguido de un dígito o punto, y si aparece al inicio de la expresión o inmediatamente después de un operador o un paréntesis de apertura '('.

4. Es unario porque actúa sobre un solo operando (el que le precede). El código impone la restricción de que este operando debe ser un número entero no negativo; de lo contrario, lanza una excepción.

5. Cada vez que el analizador lee un número completo o desempila un operador para calcularlo, llama inmediatamente a la función `appendRpn`, agregando ese token a la cadena de salida en tiempo real, no al final.

6. Define la precedencia. '<' indica que el símbolo actual tiene mayor prioridad y debe apilarse; '>' indica que el operador en el tope tiene mayor prioridad y debe evaluarse primero; '=' significa que son paréntesis coincidentes que se cancelan.

7. Porque fallar en silencio y devolver un valor arbitrario o basura puede propagar errores graves en sistemas que dependan de ese cálculo. Lanzar una excepción obliga a manejar el fallo de forma explícita y segura.

8. Permite depurar y validar el proceso. La RPN actúa como una representación intermedia explícita y libre de ambigüedades, demostrando exactamente cómo el evaluador interpretó la jerarquía de operadores antes de calcular el resultado final.

## Bloque 6

1. Significa que comparten la misma fila, la misma columna o alguna de las dos diagonales (principal o secundaria).

2. Representa la configuración parcial actual del tablero, almacenando las reinas que ya han sido colocadas exitosamente en las filas precedentes.

3. Avanzar en columna significa probar la siguiente posición horizontal en la fila actual para colocar una reina. Toca retroceder cuando se agotan las columnas disponibles en esa fila sin encontrar una posición válida, o cuando ya se completó una solución y se buscan alternativas.

4. Porque cuantifica el esfuerzo computacional real (número de comparaciones de conflicto), permitiendo medir y comparar la eficiencia del algoritmo y la efectividad de las podas.

5. El algoritmo solo incrementa el contador de soluciones encontradas, pero no guarda en memoria las coordenadas de cada configuración, lo que ahorra espacio y tiempo de ejecución.

6. `AVAILABLE` es una celda libre por explorar, `ROUTE` es parte del camino activo actual, `BACKTRACKED` es una celda ya visitada que no condujo a la salida, y `WALL` es un obstáculo intransitable.

7. `incoming` indica la dirección desde la cual se llegó a la celda actual, y `outgoing` indica la dirección hacia la que se intentará avanzar en el siguiente paso.

8. Para evitar ciclos infinitos y recordar qué caminos ya fueron explorados sin éxito, garantizando que el retroceso (backtracking) funcione correctamente y no vuelva a visitar celdas muertas.

9. Ambos comparten el uso de backtracking con una pila para explorar un espacio de estados y retroceder ante callejones sin salida. Cambia que N-Reinas representa el estado como coordenadas abstractas en un espacio vacío, mientras que el laberinto usa una cuadrícula física con celdas que tienen estados explícitos y conexiones restringidas.

## Bloque 7

1. Representa la fila de espera independiente de los clientes asignados a una ventanilla de atención específica.

2. Evalúa el tamaño de cada cola (`size()`). En caso de empate, selecciona la primera ventanilla que encontró con ese tamaño mínimo (el índice más bajo), ya que la condición de comparación es estrictamente menor (`<`).

3. Garantiza que la generación de números aleatorios (llegadas y tiempos de servicio) sea determinista, permitiendo reproducir exactamente la misma secuencia de eventos para pruebas y depuración.

4. `totalArrivals >= totalServed`, porque es físicamente imposible atender a más clientes de los que han llegado al banco durante el periodo de simulación.

5. Es un registro histórico paso a paso que guarda el estado de todas las colas (los tiempos de servicio restantes de cada cliente) en cada instante de tiempo de la simulación.

6. Porque los clientes deben ser atendidos estrictamente en su orden de llegada (FIFO). Usar una pila (LIFO) significaría atender al último en llegar primero, lo cual es ilógico e injusto en este contexto.

7. Asume que los clientes nunca abandonan la fila por impaciencia y que cada ventanilla gestiona su propia cola independiente, en lugar de usar una sola cola general para todas las ventanillas disponibles.

8. Solo sería necesario reescribir la lógica interna de la función `bestWindow` (por ejemplo, para elegir la ventanilla con menor tiempo acumulado de atención o usar un turno rotativo round-robin), sin necesidad de modificar el motor principal de la simulación.

## Bloque 8

Pasar de usar pilas y colas como simples contenedores a usarlas para controlar el flujo de un programa cambia todo. La pila usa LIFO para deshacer pasos, mientras que la cola usa FIFO para guardar el orden de llegada. Esto se ve claro al comparar problemas: en la conversión de base y el balanceo de paréntesis, la pila organiza los datos. Podemos usar la recursión implícita del sistema o crear una pila explícita; la primera es más corta, pero la explícita evita que el programa colapse y nos da control total.

En la evaluación de expresiones, las pilas deciden qué operador resolver primero según su prioridad. Para problemas como las N-Reinas o el laberinto, la pila es el motor del backtracking, guardando el camino para retroceder cuando nos equivocamos. En cambio, en la simulación bancaria, la cola es obligatoria para modelar la realidad, asegurando que los clientes se atiendan justo en el orden en que llegan.

Finalmente, la correctitud experimental es clave. No basta con que el código compile; debemos probar con casos borde para asegurar que nuestras pilas y colas mantienen sus invariantes. Así demostramos que la estructura elegida resuelve el problema de forma rápida y sin errores, ya sea para invertir dígitos, explorar un mapa o atender clientes.
