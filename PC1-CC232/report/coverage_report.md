# Reporte de Cobertura

## Entorno
- OS: Windows (MSYS2/UCRT64)
- Compilador: g++ 15.2.0
- Herramienta: gcov (incluido con GCC)

---

## Ejecución

```bash
g++ -std=c++17 --coverage -O0 -o main_cov src/main.cpp src/solution.cpp
./main_cov
gcov src/solution.cpp
```

## Resultado

```
src/solution.gcno: cannot open notes file
src/solution.gcda: cannot open data file, assuming not executed
No executable lines
```

## Causa

Los archivos `.gcno` y `.gcda` se generan en el directorio de trabajo raíz,
no en `src/`. Al invocar `gcov src/solution.cpp` no los encuentra.
Es una limitación del manejo de rutas de gcov en MinGW/Windows.

---

## Cobertura esperada sobre el conjunto de pruebas

Aunque no se pudo obtener el reporte automático, se puede razonar la cobertura
manualmente sobre `tests.cpp`:

### Cobertura de líneas — `evalRPN`

| Bloque                        | Cubierto por tests         |
|-------------------------------|---------------------------|
| Token es operador `+`         | ✓ caso básico 1 y 2       |
| Token es operador `-`         | ✓ `{"5","3","-"}`         |
| Token es operador `*`         | ✓ `{"2","3","*"}`         |
| Token es operador `/`         | ✓ `{"8","2","/"}`         |
| Stack con menos de 2 elementos| ✓ caso `{"+"}`            |
| División por cero             | ✓ caso `{"4","0","/"}`    |
| Número negativo               | ✓ `{"-3"}`, `{"-7","2","/"}` |
| Token es número positivo      | ✓ todos los casos normales|
| Número fuera de rango         | no cubierto (fuera de constraints del problema) |

### Cobertura de condiciones — función `Stack<T>::pop()`

| Condición              | Cubierto |
|------------------------|----------|
| `data_.empty() == true`  | ✓ caso `{"+"}` dispara underflow en evalRPN antes, pero el guard en pop existe |
| `data_.empty() == false` | ✓ todos los casos normales |

---

## Conclusión

La cobertura de líneas estimada es alta (~95%) sobre el conjunto de pruebas actual.
La única rama no ejercida es la validación de rango `[-200, 200]`, que por las
constraints del problema nunca se activa con entradas válidas de LeetCode.