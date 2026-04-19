### Ejercicio 1 Semana 2 (Yo)

1. El tiempo promedio es que en la ejecucion de las operaciones, es la estimacion el tiempo medio considerando las distribucion sobre las entradas posibles; mientras que el tiempo amortizado, al considerar una secuencia larga de actualizaciones, es el tiempo medio de las operaciones por actualizaicon.

2. Para `DengVector.h`, la función `insert()`, al agregar un dato al inicio del vector. Ejemplo: **vec.insert(0, 999)**. En el caso de `ArrayStack.h`, ocurre algo similar: si usamos la función `remove()` para eliminar el primer elemento de la lista. Ejemplo: **stack.remove(0)**. En ambos la complejidad de la función aumenta a O(n).
  

3. Como se explico en la respuesta *1.* la complejidad amortizada es el promedio sobre m operaciones, no garantía individual. El costo puntual puede ser O(n), pero se "diluye" en las operaciones baratas.

4. La duplicacion es necesária para la amortización del `expand`, ya que se generan log(n) resizes, totalizando ~2n copias. Sin ella, habría O(n) de costo por operación.

5. Si fuese una expansion fija del tipo Capacidad += K, el costo escala a O(n²), igualmente sería amortizado a O(n), pero es claro que en este caso el metodo de duplicado es superior.
