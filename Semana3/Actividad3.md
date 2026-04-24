### Bloque 1

3. Para la listas enlazadas, no se exige seguir el orden lógico de secuencias, sino se enfoca más al acceso por referencia, lo cual lo haze menos eficiente para recuperar directamente el elemento de una posición arbitraria. 

6. El nodo dummy ayuda de que la función next y prev siempre existan, trabaja como una constante que nos permite guiar hacia la cabeza o cola de la lista.
7. Porque usan la función *GetNode* con la cual hace una busqueda segun la distancia entre sus extremos.
8. La idea es central es: reducir el desperdicio de espacio y mejora la localización por bloques, pero lo hace a costa de una implementación más compleja y de un análisis amortizado más sofisticado.
9. 

---

### BLOQUE 2

| Archivo | Salida | Idea estructural | Argumento costo/epacio |
| ------- | ------ | ---------------- | ---------------------- |
|demo_sllist.cpp | size = 3, peek = 5, pop = 5, remove = 10 | a | na |
| demo_dllist.cpp | DLList: 10 20 30 | a | a |
| demo_selist.cpp | SEList: 0 10 20 30 40 50 60 70 80 90 | na | na |
| demo_deng_list.cpp | a | a | a |
| demo_morin_deng_bridge.cpp | a | a | a |
| demo_capitulo3_panorama.cpp | SLList size = 3, peek = 0 DLList: 10 20 30 SEList: 8 6 7 LinkedStack top = 200 LinkedQueue front = 11 LinkedDeque front/back = 5/9 ArrayDeque first/last = 4/6 | a | a |
| demo_min_structures.cpp | MinStack min=3 top=7 MinQueue min=2 front=4 MinDeque min=1 front=3 back=1 | a | a | a |
| demo_xor_list.cpp | a | a | a |
| demo_linked_adapters.cpp | a | a | a |
| demo_contiguous_vs_linked.cpp | a | a | a |


---

### BLOQUE 3

1. Las pruebas son sobre el orden de posicion de sus datos agregados y las funciones add, push, size, peek, pop, remove.
2. Similar a las pruebas de SLList, añadir datos a la estructura y comprobar las funciones add, push, size, peek, pop, remove.  
3. Para SEList, se tiene una estrucutra de tamaño predeterminado y luego se evalua su expansion al agregar mas elementos, además de comprobar las funciones de size, get, set, remove.
4.  
