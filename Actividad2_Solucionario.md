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