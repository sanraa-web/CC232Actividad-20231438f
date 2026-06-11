#

## 06-06-2026

Se completo el formato de los elementos necesarios para el repositorio, al leer el problema se observa la ncesidad de una estrucutra de datos mas avanzada que un vector por la operacion de tipo 2 en particular, considerando que el rango de Q es de hasta 200,000 se concluye que la complegidad temporal de mis algoritmos debe ser necesariamente menor a $Q^2$. Mas adelante tengo planeado mostrar dicha demo del caso ingenuo e iniciar la creacion de los headers que deberan tener que ven con arboles por como me sugieren en el repositorio de problemas, como tambien que son las estructuras estudiadas que a primera vista (por el costo de las operaciones) son ideales en este caso.

## 07-06-2026

Se creó la demo con la solución ingenua; dicha solución usa el formato de código común de la programación competitiva, incluyendo `ios_base::sync_with_stdio(false)` para desincronizar los streams de C++ con C, y `cin.tie(nullptr)` para evitar que los `cout` hagan *flush* antes de leer con `cin`. Como era de esperarse, ocurrió un TLE al pasarlo por el juez virtual. Esto refuerza la idea de ayer de usar una estructura de datos más potente; se pasará ahora a crear el header.

En `treap.h` es una recuperación del header `Treap.h`, pero solo utiliza como funciones públicas `add()` y `remove()`, mientras que las demás utilidades necesarias para un *treap* se movieron al ámbito privado. La implementación del `kth` se realizará más adelante, lo cual servirá como distinción necesaria entre el modelo hecho en clase y la nueva aplicación para este problema.

## 08-06-2026

El *header* mencionado ya se creó en su totalidad con la función `kth()`, y solamente se movió a su carpeta correcta. Las modificaciones que requerían su implementación no resultaron ser tan complejas: solo se creó una nueva variable que cuenta la cantidad de nodos en los subárboles; esto se agregó a la función pública junto con otras dos utilidades privadas y, finalmente, se actualizaron las demás funciones para que mantengan al día el valor de esta nueva variable.

Se creó `demo_sol_pc3.cpp`, que contiene la implementación de `treap.h` aplicada al problema y la comparación de resultados del ejemplo 2 de AtCoder en su ejecución, sirviendo como muestra directa de su correctitud. También se creó `Solucion.cpp`, que es la implementación definitiva usando `treap.h`. Más adelante se busca detallar con rigurosidad los fundamentos tanto del *header* como de la solución dentro del repositorio.

Por último, se actualizo el CMakeLists.

## 09-06-2026

Se completaron 12/20 preguntas de respuestas_obligatorias, avanzo readme y se creo test_treap.cpp que hará pruebas para el header ya que la solución es solamente un wrapper.

## 10-06-2026

Se agrego el .gitignore solo para `Practica_Calificada3-CC232`

Se observo que el test_treap fallaba ya que `kth` no tenia un caso para k fuera de rango, se hizo la corrección en `treap.h`. Se agrego `Solucion_Atcoder.cpp` como enviable al juez virtual, el cual salio **aceptable**. Se actualizo el CMAKE y la carpeta `resultados/` con las salidas.

Por ultimo, hay un avance en `bench_treap.cpp` la idea es que tener una lista de N elementos ordenados aleatoriamente y agregarlos en dicho orden al Treap, posterior a ello se ejecuta el `Treap.remove` hasta que quede vacio, luego comparar los tiempos y probar con eso que la complejidad es logarítmica.

## 11-06-2026

Se completo `benc_treap.cpp` tiene el obejtivo de demostrar la complejidad algoritmica del header. Se actualizo CMAKE, README, los archivos de `resultados/`.
