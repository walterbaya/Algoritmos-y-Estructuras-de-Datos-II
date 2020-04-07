cmake_minimum_required(VERSION 3.5)
project(solucion)

set(CMAKE_CXX_STANDARD 11)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++11 -ggdb3 -g")

# Leemos todos los archivos fuentes en ./src
# file(GLOB SOURCE_FILES src/*.cpp src/*.h)

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

# Creamos el ejecutable para correr los tests
add_executable(ej1 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej2 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej3 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej4 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej5 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej6 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej7 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(ej8 tests/test_fecha.cpp ${SOURCE_FILES})
add_executable(horario_gtest tests/test_horario.cpp ${SOURCE_FILES})
add_executable(horario_main tests/test_horario_main.cpp ${SOURCE_FILES})

# Definiciones por target
target_compile_definitions(ej1 PUBLIC EJ=1)
target_compile_definitions(ej2 PUBLIC EJ=2)
target_compile_definitions(ej3 PUBLIC EJ=3)
target_compile_definitions(ej4 PUBLIC EJ=4)
target_compile_definitions(ej5 PUBLIC EJ=5)
target_compile_definitions(ej6 PUBLIC EJ=6)
target_compile_definitions(ej7 PUBLIC EJ=7)
target_compile_definitions(ej8 PUBLIC EJ=8)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(ej1 gtest gtest_main)
target_link_libraries(ej2 gtest gtest_main)
target_link_libraries(ej3 gtest gtest_main)
target_link_libraries(ej4 gtest gtest_main)
target_link_libraries(ej5 gtest gtest_main)
target_link_libraries(ej6 gtest gtest_main)
target_link_libraries(ej7 gtest gtest_main)
target_link_libraries(ej8 gtest gtest_main)
target_link_libraries(horario_gtest gtest gtest_main)
target_link_libraries(horario_main gtest gtest_main)
