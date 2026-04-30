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

| Archivo | Salida | Idea estructural | Argumento costo/epacio |
| ------- | ------ | ---------------- | ---------------------- |
| demo_array_basico.cpp | array.length = 5
contenido: 10 20 30 40 50
antes de la asignacion, b[0] = -1
despues de b = a, b.length = 5
b: 10 20 30 40 50 | agregar datos, indexar y elminar | O(n) |
| demo_arraystack.cpp | size = 3
10 15 20
remove(1) = 15 | añadir elementos a la cola | O(n) |
| demo_fastarraystack.cpp | size = 7
0 1 2 99 3 4 5 | aumetar longitud del array | O(n) |
| demo_arraystack_explicado.cpp | Operacion 1-4 probando size y capacity | usar add(i,x) y remove(i) | O(n-i) |
| demo_rootisharraystack.cpp | size = 8
0 10 20 30 40 50 60 70
remove(3) = 30 | Comparar size luego de añadir y eliminar elementos. | O(n) |
| demo_rootisharraystack_explicado.cpp | operaciones add y remove para explicacion |  | O(n) |
| demo_deng_vector.cpp | - | - | - |
| demo_stl_vector_contraste.cpp | - | - | - |
| demo_stl_vector_contraste.cpp
 | - | - | - |
| demo_array_basico.cpp | - | - | - |
