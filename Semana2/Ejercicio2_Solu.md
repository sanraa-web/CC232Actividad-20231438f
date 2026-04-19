### Ejercicio 1 Semana 2 (Yo)

1. El tiempo promedio es que en la ejecucion de las operaciones, es la estimacion el tiempo medio considerando las distribucion sobre las entradas posibles; mientras que el tiempo amortizado, al considerar una secuencia larga de actualizaciones, es el tiempo medio de las operaciones por actualizaicon.

2. Para `DengVector`, la función `insert`, al agregar un dato al inicio del vector, requeriría recorrer toda su longitud para desplazar los *n* elementos. En otras palabras, la complejidad sería O(n). Ejemplo: `vec.insert(0, 999)`. Esto es muy diferente a agregarlo al final del array, donde el costo se amortiza a O(1). 

En el caso de `ArrayStack`, ocurre algo similar: si usamos la función `remove` para eliminar el primer elemento de la lista, será necesario reubicar el resto de los elementos del vector, lo que incrementa el costo a O(n). Ejemplo: `stack.remove(0)`.
  

3. 

4. 

5. 
