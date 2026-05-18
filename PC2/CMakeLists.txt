cmake_minimum_required(VERSION 3.10)
project(MaxScore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Especificar el directorio include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Archivos fuente comunes
set(COMMON_SOURCES src/maxScore.cpp)

# Compilar todos los demos
file(GLOB DEMO_SOURCES demos/*.cpp)
foreach(demo ${DEMO_SOURCES})
    get_filename_component(demo_name ${demo} NAME_WE)
    add_executable(${demo_name} ${demo} ${COMMON_SOURCES})
endforeach()

# Compilar test
file(GLOB TEST_SOURCES tests/*.cpp)
foreach(test ${TEST_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test} ${COMMON_SOURCES})
endforeach()

# Compilar benchmarks
file(GLOB BENCHMARK_SOURCES benchmark/*.cpp)
foreach(benchmark ${BENCHMARK_SOURCES})
    get_filename_component(benchmark_name ${benchmark} NAME_WE)
    add_executable(${benchmark_name} ${benchmark} ${COMMON_SOURCES})
endforeach()

# Habilitar testing
enable_testing()
foreach(test ${TEST_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Habilitar flags de compilación
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()