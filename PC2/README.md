## PC2 - CC232

### Estudiante
- Nombre: Santiago Alejandro Ramirez Aguilar
- Código: 20231438F
- Problema asignado: LeetCode 1696 - Jump Game VI
- Enlace: https://leetcode.com/problems/jump-game-vi/description/

## Problema asignado
**https://leetcode.com/problems/jump-game-vi/**

### Tema principal
- Semana: 3
- Estructura o técnica principal: Deque

### Resumen de la solución
Se utiliza programación dinámica con una deque de máximos decreciente. `dp[i]` almacena la máxima puntuación hasta la posición `i`. Para cada posición, se consulta el máximo de `dp` en el rango `[i-k, i-1]` usando una deque que mantiene los índices ordenados por valor de forma decreciente.

### Complejidad
- Tiempo: O(n)
- Espacio: O(n)

### Invariante o idea clave
La deque mantiene índices en orden decreciente de sus valores `dp`. Al procesar cada posición `i`, se remove el índice más antiguo si está fuera del rango válido `[i-k, i-1]`, y se añade el nuevo índice manteniendo la propiedad decreciente.

### Archivos relevantes
- include/deque.h ; maxScore.h
- src/maxScore.cpp
- tests/CasosBorde.cpp
- demos/demo_maxScore.cpp
- benchmak/benchmark.cpp

### Compilación
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Ejecución
```bash
./build/demo_maxScore.exe
./build/pruebas.exe
./build/benchmark.exe
```

### Casos de prueba
Describe al menos 3 casos:
1. `[]` con k=1: Caso donde el array esta vacio, devuelve el resultado de 0 automáticamente.
2. `[10000,10000,10000]` con k=2: Valores extremos grandes para verificar precisión. Resultado: 30000
3. `[1,2,3,4,5,6,7,8]` con k=2: Secuencia creciente que verifica correctamente el deque. Resultado: 36

### Historial de commits
- Commit 1: Agrego README.md, CMakelist y Actividad1
- Commit 2: implemento header deque.h
- Commit 3: modifico deque.h y CMakelist, adicionalmente se agrego la demo temprana Solution.cpp
- Commit 4: Reorganizo las ubicaciones del repo; Solution.cpp se separo en maxScore.h + maxScore.cpp (algoritmo) y demo_maxScore.cpp (demo); modifico los demas archivos
- Commit 5: Se agrego CasosBorde.cpp que es el test
- Commit 6: Se renombro CasosBorde a pruebas.cpp ; se agrego benchmark.cpp ; se agrego la documentacion para ambos y se hizo ajustes en maxScore, CMakelist
- Commit 7: Caso reto agregado y commit 8 solo se cambio la vercion de c++11 a c++17

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
