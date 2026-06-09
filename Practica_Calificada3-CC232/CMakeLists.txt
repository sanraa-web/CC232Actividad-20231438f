cmake_minimum_required(VERSION 3.10)
project(Practica_Calificada3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorios
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ejecutable principal (Solucion)
add_executable(demo_sol_ingenua demos/demo_sol_ingenua.cpp)

# Ejecutable demo
add_executable(demo_sol_pc3 demos/demo_sol_pc3.cpp)

# Registrar como tests
enable_testing()
add_test(NAME demo_pc3 COMMAND demo_sol_pc3)
