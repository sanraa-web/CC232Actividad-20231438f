# Benchmark: maxScore O(n)

## Prueba 1: Escalabilidad Lineal

**Objetivo**: Verificar que tiempo crece con n

Se ejecuto 10 veces el programa y se saco el tiempo promedio, comparando con el tiempo teorico (lineal).

| n | Tiempo Medio (ms) | Tiempo Esperado (ms) |
|---|---|---|
| 20,000 | 2.759 | 2.759 |
| 40,000 | 5.406 | 5.518 |
| 60,000 | 8.019 | 8.277 |
| 80,000 | 10.707 | 11.036 |
| 100,000 | 13.325 | 13.795 |

**Resultado**: Se observa que la diferencia entre el valor obtenido de pruebas y el teorico son muy cercanos por lo que se puede confirmar que su complejidad temporal es  **O(n)**

---

## Prueba 2: Variable k

**Objetivo**: Verificar que k NO afecta el tiempo

| k | Tiempo (ms) |
|---|---|
| 100 | 14.574 |
| 1,000 | 14.446 |
| 5,000 | 13.557 |
| 10,000 | 14.448 |

**Resultado**: aqune k aumenta 100x el tiempo igual (varia 1ms) se demuestra que **Deque es O(1) amortizado**

---

## Conclusion

- **Complejidad O(n) comprobada**
- Tiempo escala linealmente con n
- Parametro k no afecta rendimiento
- **El algoritmo es óptimo**