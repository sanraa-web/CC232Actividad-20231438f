#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>
#include "deque.h"
#include "maxScore.h"

struct BenchmarkResult {
    int size;
    int k;
    double timeMs;
};

void runBenchmark(int size, int k, std::vector<BenchmarkResult>& results) {
    // Generar datos mixtos para la prueba
    std::vector<int> nums(size);
    for (int i = 0; i < size; ++i) {
        nums[i] = ((i % 2) == 0) ? (i % 50) + 1 : -((i % 50) + 1);
    }
    
    // mide tiempo
    auto start = std::chrono::high_resolution_clock::now();
    algorithm::maxScore(nums, k);
    auto end = std::chrono::high_resolution_clock::now();
    
    double timeMs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
    
    results.push_back({size, k, timeMs});
}

void printTable(const std::string& title, const std::vector<BenchmarkResult>& results) {
    std::cout << "\n--- " << title << " ---\n";
    std::cout << std::left << std::setw(15) << "Tamano (n)" 
              << std::setw(10) << "k" 
              << "Tiempo (ms)\n";
    std::cout << "-------------------------------------------\n";
    for (const auto& r : results) {
        std::cout << std::left << std::setw(15) << r.size 
                  << std::setw(10) << r.k 
                  << std::fixed << std::setprecision(4) << r.timeMs << " ms\n";
    }
}

int main() {
    std::vector<BenchmarkResult> scalabilityResults;
    std::vector<BenchmarkResult> kSensitivityResults;

    // 1. PRUEBA DE ESCALABILIDAD (n variable, k fijo)
    // Objetivo: crecimiento lineal O(n)
    int k_fijo = 500;
    int tamaños[] = {20000, 40000, 60000, 80000, 100000};
    
    for (int n : tamaños) {
        runBenchmark(n, k_fijo, scalabilityResults);
    }
    printTable("ESCALABILIDAD LINEAL O(n)", scalabilityResults);

    // 2. PRUEBA DE SENSIBILIDAD A K (n fijo, k variable)
    // Objetivo: Demostrar que la Deque amortiza el costo de la ventana
    int n_fijo = 100000;
    int valores_k[] = {100, 1000, 5000, 10000};
    
    for (int k : valores_k) {
        runBenchmark(n_fijo, k, kSensitivityResults);
    }
    printTable("EFICIENCIA DE LA VENTANA (DEQUE)", kSensitivityResults);
    return 0;
}