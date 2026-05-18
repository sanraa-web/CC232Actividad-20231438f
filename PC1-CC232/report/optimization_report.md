# Reporte de Optimización y Builds

## Entorno
- OS: Windows (MSYS2/UCRT64)
- Compilador: g++ 15.2.0 (x86_64-w64-mingw32)
- Estándar: C++17
- Problema: Evaluate RPN (LeetCode 150)

---

## Tabla

| Build      | Flag(s)             | Tamaño (.exe) | Tiempo real | Warnings | Correctitud |
|------------|---------------------|---------------|-------------|----------|-------------|
| Debug      | `-O0 -g`            | 412 KB        | 0.347 s     | Ninguno  | ✓ (salida: 9) |
| Debug opt. | `-Og -g`            | 350 KB        | 0.206 s     | Ninguno  | ✓ (salida: 9) |
| Release    | `-O2 -DNDEBUG`      | 145 KB        | 0.195 s     | —        | ✓ (salida: 9) |
| Compacto   | `-Os`               | 146 KB        | 0.204 s     | —        | ✓ (salida: 9) |

---

### Correctitud
Todos los builds producen la salida correcta (`9` para el input `["2","1","+","3","*"]`).
No se observaron diferencias de comportamiento entre niveles de optimización.

### Tamaño del ejecutable
El salto más notable es entre `-O0` (412 KB) y `-O2` (145 KB): una reducción de ~65%.
`-Os` (146 KB) es prácticamente igual a `-O2`, lo que indica que para este programa
el compilador ya alcanza un tamaño mínimo con `-O2` y `-Os` no aporta reducción adicional.

### Tiempo de ejecución
`-O0` es el más lento (0.347 s) por la ausencia total de optimizaciones.
`-Og` mejora a 0.206 s manteniendo información de depuración.
`-O2` es el más rápido (0.195 s) y el más recomendado para producción.
`-Os` (0.204 s) es ligeramente más lento que `-O2` porque prioriza tamaño sobre velocidad.

### Warnings
Los builds con `-Wall -Wextra -Wpedantic` (`-O0` y `-Og`) no generaron ningún warning,
lo que indica que el código es limpio y sigue buenas prácticas de C++17.

### Facilidad de depuración
Los builds con `-g` (`-O0`, `-Og`) incluyen símbolos de depuración utilizables con `gdb`.
`-O0` es el más fácil de depurar porque no reordena ni elimina instrucciones.
`-O2` y `-Os` no incluyen símbolos, por lo que no son adecuados para depuración.

### Estabilidad entre corridas
Los tiempos son estables entre corridas. La variación observada es atribuible al
overhead de inicio del proceso en Windows, no al algoritmo en sí.

---

## Sanitizers (ASan / UBSan)

Se intentó compilar con `-fsanitize=address,undefined` pero MinGW en Windows (MSYS2/UCRT64)
no incluye `libasan` ni `libubsan`, produciendo el error:

```
cannot find -lasan: No such file or directory
cannot find -lubsan: No such file or directory
```

### Qué habrían detectado en este código

- **AddressSanitizer (ASan):** detectaría acceso a memoria inválida. En este código,
  un `pop()` o `top()` sobre un stack vacío sin protección produciría heap-buffer-overflow.
  Nuestro `Stack<T>` lanza `std::underflow_error` explícitamente en ambos casos,
  y `evalRPN` valida `st.size() < 2` antes de operar, por lo que ASan no reportaría errores.

- **UndefinedBehaviorSanitizer (UBSan):** detectaría desbordamiento de enteros con signo.
  Las constraints del problema garantizan tokens en `[-200, 200]` y resultados en rango
  de 32 bits, por lo que no hay riesgo de overflow en las operaciones aritméticas.

**Conclusión:** el código es defensivo por diseño. No se esperan errores bajo entradas válidas.

---

### Conclusión general

La mejora más significativa proviene del nivel de optimización del compilador (`-O0` → `-O2`),
no de microoptimizaciones en el código. Sin embargo, para este problema la diferencia
algorítmica más importante es el uso de un stack (O(n)) frente a una solución ingenua
sin estructura adecuada, como se evidencia en el benchmark separado.
