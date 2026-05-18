# Informe de Verificación y Testing - PC2

## 1. Resumen de Ejecución
Se ha implementado una batería completa de pruebas unitarias para validar el algoritmo `maxScore` del problema LeetCode 1696 (Jump Game VI). El algoritmo utiliza **Dynamic Programming** optimizado con una **Deque** personalizada (`ods::Deque`). La ejecución del archivo `CasosBorde.cpp` completó **100% de éxito** en todas las pruebas.

> **Resultado final:** `No hubo errores en las pruebas`

## 2. Metodología de Testing
Se diseñó una batería de pruebas clasificada por categorías críticas:

- **Casos Base y Frontera:** Vectores vacíos, $k=0$, arreglos unitarios. Verifican retorno de valores neutrales (0) y valores únicos.
- **Análisis de Signos:** Secuencias estrictamente positivas, negativas y mixtas. Valida la robustez de la acumulación de puntajes.
- **Valores Extremos:** Magnitudes de $10^6$, valores muy negativos ($-10000$). Verifica ausencia de desbordamiento en el rango de `int`.
- **Validación de Deque:** Patrones con distintos valores de $k$ que fuerzan `removeFront()` y `removeBack()`. Confirma que la ventana deslizante mantiene el máximo óptimo.
- **Secuencias Largas:** Generadas mediante bucles (hasta 15 elementos). Verifican que el algoritmo escale correctamente.

## 3. Cumplimiento de Requerimientos
De acuerdo con las indicaciones del curso CC-232, el testing realizado satisface los siguientes puntos:

| Requerimiento | Estado | Detalle |
| :--- | :--- | :--- |
| **Validación funcional** | Hecho | Se verificaron resultados contra cálculos manuales y patrones esperados |
| **Uso de `assert`** | Hecho | Se empleó `<cassert>` para garantizar que cualquier fallo detenga la ejecución |
| **Cobertura de casos críticos** | Hecho | Arreglos ordenados, inversos, con repeticiones, vacíos y con valores extremos |
| **Integración con `ods::Deque`** | Hecho | Confirmada la correctitud de la estructura de datos personalizada |

## 4. Análisis Técnico
La solución implementa la recurrencia:

$$dp[i] = nums[i] + \max_{i-k \le j < i} dp[j]$$

La `ods::Deque` mantiene índices en orden **decreciente de sus valores `dp`**, permitiendo:
- Consulta $O(1)$ del máximo en la ventana $[i-k, i-1]$
- Actualización amortizada $O(1)$ mediante `removeFront()` y `removeBack()`
- Complejidad total: **O(n) tiempo, O(n) espacio**

## 5. Conclusión
La batería de pruebas valida exitosamente que la implementación maneja correctamente:
- Acumulación de puntajes con ventanas deslizantes
- Mantenimiento eficiente de máximos mediante la deque
- Casos extremos sin pérdida de precisión

El código está verificado y listo para evaluación.