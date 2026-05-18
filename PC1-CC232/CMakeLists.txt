cmake_minimum_required(VERSION 3.10)
project(PC1-CC232)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio src para headers
include_directories(src)

# Ejecutable principal
add_executable(main src/main.cpp src/solution.cpp)

# Ejecutable de pruebas
add_executable(tests test/tests.cpp src/solution.cpp)

# Ejecutable de benchmark
add_executable(benchmark bench/benchmark.cpp src/solution.cpp)

enable_testing()
add_test(NAME tests COMMAND tests)