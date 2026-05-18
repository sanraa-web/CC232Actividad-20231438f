**Alumno:** Santiago Alejandro Ramirez Aguilar
**VERSION C**

# Problema 1
### a.
    - El ADT es *IndexedBag*, 
### b.
### c.
### d.
### e.
## Problema 2
### a.
orden de llamadas: 
sumRec(A,4) -> sumRec(A,3) -> sumRec(A,2) -> sumRec(A,1) -> sumRec(A,0)
orden de retornos:
0 + 2 = 2 -> 2 + 4 = 6 -> 6 + 6 = 12 -> 12 + 8 = 20
### b.
- Tenemos el caso base: n == 0 -> return 0
- La hipotesis inductica es para sumRec(A, n-1) retorna: A[0] + A[1] + ... + A[n-2]
- Entonces para sumRec(A, n) = sumRec(A, n-1) + A[n-1] = (A[0] + ... + A[n-2]) + A[n-1] = A[0] + ... + A[n-1]. Lo que comprueba la correctitud.
### c. 
- El tiempo de la funsion sería, sea T(n) la funcion para int n: T(n) = T(n-1) + O(1) = O(n)
- Espacio del arreglo es O(n) ya que A[] se pasa por referencia y no se copia.
- Para la pila de llamadas es O(n) por las recursiones que se hacen.
### d.
Definiendo la funsion como sumIterativa:
```bash
int sumIterativa(const int A[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += A[i];
    return s;
    }
```
Donde la invariante es *s* como la sumatoria desde A[0] hasta A[i-1] (s == A[0]+...+A[i-1]).
### e.
Asegura que la sumRec() no modifique el arreglo, indicando que aquel es solo A es solo una entrada para lectura, mejorando la correctitud para la función.
### f.
- Caso donde n = 0, debe retornar 0, probar **assert(sumRec(A, 0) == 0)**
- Caso borde n = 1, debe retornar A[0], probar **assert(sumRec(A, 1) == A[0])**
- Caso borde n = 0 y A[] vacio, debe retornar 0, probar **assert(sumRec(A, 0) == 0)**
## Problema 3
### a.
- Bloque 0: [ 0 ]
- Bloque 1: [ 1 | 2 ]
- Bloque 2: [ 3 | 4 | 5 ]
- Bloque 3: [ 6 | 7 | 8 | 9 ]
- Bloque 4: [10 |11 |12 |13 |14]
### b.
Usando la formula b = ⌈(−3 + raiz(9+8i))/2⌉, j = i − b(b+1)/2
| i  | b | j |
|----|---|---|
| 0  | 0 | 0 |
| 1  | 1 | 0 |
| 2  | 1 | 1 |
| 5  | 2 | 2 |
| 9  | 3 | 3 |
| 14 | 4 | 4 |
### c.
La razon es por los bloques de la estructura tienen tamaños distitntos. No hay una división simple para encontrar el bloque, se necesita invertir la fórmula triangular b(b+1)/2 <= i, lo que requiere resolver la ecuación cuadrática.
### d.
La capacidad total es  r(r+1)/2 >= n, el espacio desperdiciado es máximo al tamaño del último bloque vacío o parcialmente vacio.
### e.
- Lo que se conserva: O(1) por acceso (get/set).
- Costo adicional: un cálculo aritmético extra para encontrar el bloque, versus un simple acceso directo a[i] en ArrayStack.
### f. 
- grow(): agrega un nuevo bloque de tamaño r+1 al final del ArrayStack de bloques, es costo O(1) amortizado.
- shrink(): elimina bloques del final mientras la capacidad con r−2 bloques sea suficiente para n elementos. Libera memoria con delete[].
## Problema 4
### a.
Sigue: si i < front.size() -> front.get(front.size()-i-1), sino -> back.get(i - front.size())
| i | front/back | indice | salida |
|---|---|---|---|
| 0 | front (0 < 3) | front.get(2) | 10 |
| 2 | front (2 < 3) | front.get(0) | 30 |
| 3 | back (3 ≥ 3) | back.get(0) | 40 |
| 6 | back (6 ≥ 3) | back.get(3) | 70 |
### b.
Para add(1, 15): i=1 < front.size()=3 -> inserta en front en posición front.size()-1 = 2
- front: [30,20,15,10] (lógicamente [10,15,20,30,...])
- back sin cambio: [40,50,60,70]
- balance: front.size()=4, back.size()=4 asi que no rebalancea
- Secuencia: [10,15,20,30,40,50,60,70]

En add(6, 55): i=6 ≥ front.size()=4 -> inserta en back en posición 6-4=2
- back: [40,50,55,60,70]
- Secuencia: [10,15,20,30,40,50,55,60,70]
### c.
Se guarda invertido para que las operaciones add y remove en el indice 0 se hagan al final de front, donde ArrayStack puede insertar y eliminar en tiempo amortizado O(1).
En caso contrario, insertar al inicio obligaría a mover todos los demás elementos, costando O(n).
### d.
Si (3·front.size() < back.size() o 3·back.size() < front.size())
- Se redistribuir todos los n elementos dejando nf = n/2 en front (en orden inverso) y nb = n nf en back (en orden normal), reconstruyendose los dos arreglos.
### e.
El rebalanceo cuesta O(n), pero solo ocurre cuando un lado tiene más de 3× el otro. Para ello se necesitan al menos n operaciones, distribuyendo el costo O(n) del rebalanceo entre las n operaciones previas, el costo amortizado por operación es O(1).
## Problema 5
### a.
- DDList: su estructura de nodo tiene un puntero *prev* y *next*, ademas de un elemento dummy.
- SEList: combina una estructura similar a DDList pero usa arreglos dentro de los bloques.
### b.
Todo bloque interno (no extremos) debe cumplir: b-1 ≤ size ≤ b+1. Los bloques en los extremos pueden tener menos. Esto garantiza que ningún bloque este ni casi vacío ni excesivamente lleno.
### c.
- Buscar espacio: se recorre hacia adelante hasta b bloques buscando uno con size ≤ b.
- Si se encuentra: se desplazan elementos entre bloques (el último del bloque anterior pasa al inicio del siguiente) hasta liberar espacio en el bloque destino → spread no necesario.
- Si no se encuentra en b pasos: se llama a spread(), que inserta un nuevo bloque vacío y redistribuye elementos entre b+1 bloques.
- Luego se inserta el elemento en la posición correcta.
### d.
SEList es significativamente mejor para este caso, solo desplaza elementos dentro de un bloque (O(b)) más mover a través de O(n/b) bloques. ArrayDeque desplaza la mitad del arreglo completo.
| | SEList | ArrayDeque |
|---|---|---|
|Inserción en centro | O(b + n/b) | O(b + n/b) |
|Con b = raiz(n) | O(raiz(n)) | O(n) |
### e.
Hacia el exterior funciona como una lista normal, con operaciones get(i), set(i,x), add(i,x) y remove(i) usando índices lógicos continuos.
El usuario no interactúa con bloques internos, ya que getLocation(i) se encarga de convertir automáticamente el índice lógico en la posición real (nodo, offset).
La organización en bloques es solo un detalle interno de implementación.
### f.
```bash
SEList<int> s(3);
int N = 1000;
// insertar N elementos
for (int i = 0; i < N; i++) s.add(i, i);
assert(s.size() == N);

// verificar o no perdida
for (int i = 0; i < N; i++) assert(s.get(i) == i);

// eliminar todos desde el centro alternando
for (int i = 0; i < N/2; i++) s.remove(s.size()/2);
assert(s.size() == N - N/2);

// verificar tamaño logico == elementos contables
auto v = s.to_vector();
assert((int)v.size() == s.size());
```
Detecta: size() desincronizado con elementos reales, elementos perdidos o duplicados tras rebalanceo de bloques.
## Problema 6
### a.
**Prueba 1** eliminación cuando el arreglo está "partido" (j > 0):
- Insertar 5 elementos, luego hacer pop_front() 3 veces (mueve j al índice 3). Ahora el arreglo está partido: datos en posiciones [3,4,0,1]. Eliminar índice 1 → debe manejar módulo correctamente. Verificar que los elementos restantes sean los correctos.

**Prueba 2** eliminación en el extremo derecho con wrap:
- Llenar arreglo hasta capacidad, hacer add(0,x) varias veces para forzar j != 0. Eliminar el último elemento (i = size-1). Verificar que size decremente y que get(size-1) sea correcto.
### b.
**Tamaño 1:**
- add un elemento, remove(0).
- Verificar: size()==0, estructura vacía sin acceso inválido.

**Tamaño 2:**
- add dos elementos [A,B], remove(0).
- Verificar: size()==1, get(0)==B.
- Luego remove(0), verificar size()==0.
### c.
Las pruebas públicas cubren casos típicos (arreglo sin wrap, tamaños medianos). El wrap-around solo ocurre cuando j + i >= capacidad, lo cual requiere una secuencia específica de push_front/pop_front. Una implementación puede ser correcta en casos lineales y fallar solo cuando los datos "rodean" el final del arreglo.
### d.
Se revisaria la invariante explicada como: n es el número real de elementos, j es el índice lógico del primer elemento, y para todo 0 ≤ k < n: get(k) == a[(j+k) % capacidad].

En especifico, el size() debe decrementar en 1 y todos los elementos en posiciones [0, n-1] deben ser accesibles correctamente con módulo.
### e.
**ASan detecta:**
Acceso fuera de los límites del arreglo (a[índice_inválido]) — heap buffer overflow.
Use-after-free si se libera el arreglo prematuramente.
Double-free en resize mal implementado.

**ASan NO detecta:**
Errores lógicos donde el índice es válido en memoria pero incorrecto semánticamente (ej: (j+i) % cap mal calculado devuelve una posición dentro del arreglo pero con el elemento equivocado).
n desincronizado (size incorrecto pero sin acceso ilegal).
## Problema 7
### a.
- apply(x):  pre: ninguna. post: agrega x al final; size++; current() == x.
- undo():    pre: size() > 0. post: elimina estado actual; size--; current() == estado anterior.
- current(): pre: size() > 0. retorna el estado más reciente sin modificar.
- size():    retorna número de estados. No modifica.
- clear():   post: size() == 0.
### b.
Basada en **ArrayStack** (arreglo dinámico):

- El tope del stack (a[n-1]) es el estado actual.
- Invariante: n ≥ 0, todos los estados en a[0..n-1] son válidos.
- apply → add(n, x) ; undo → remove(n-1) ; current → get(n-1).

Basada en **SLList** (lista enlazada):

- Se usa como stack: head es el estado actual (como un stack).
- Invariante: head apunta al tope; n refleja el número de nodos.
- apply es push(x) ; undo es remove() (pop del head) ; current es peek().
### c.
| Operación | ArrayStack | SLList |
|---|---|---|
| apply | O(1) amort. | O(1) |
| undo | O(1) amort. | O(1) |
| current | O(1) | O(1) |
| clear | O(1)* | O(n) — libera cada nodo |
*en ArrayStack: pone n=0, libera con resize.
### d.
Se debe verificar 'size() > 0' antes de llamar 'undo()'. Si 'size() == 0', lanzar excepción o retornar error. Semánticamente significa "no hay nada que deshacer". En ArrayStack: 'if (n == 0) throw underflow'. En SLList: 'if (head == nullptr) throw underflow'.
### e.
```bash
// caso secuencia larga
for i in 1..1000: apply(i)
assert(size() == 1000, current() == 1000)

// estado repetido
apply(5); apply(5); apply(5)
undo(); assert(current() == 5)  // no confunde duplicados

// operacion invalida
clear(); try { undo(); } catch(...) { ok }  // debe lanzar excepción
```
### f.
Ambas representaciones actuales serian insuficientes en eficiencia:

- **ArrayStack:** get(i) es O(1) —> es la mejor opción. Acceso directo por índice.
- **SLList:** get(i) es O(n) -> muy costoso para acceso aleatorio.

**Reevaluación:** si se necesita get(i), la representación con ArrayStack es claramente superior. SLList queda descartada para este caso de uso. Si además se requiere muy bajo desperdicio de memoria, RootishArrayStack sería una alternativa válida manteniendo O(1) para get(i).
