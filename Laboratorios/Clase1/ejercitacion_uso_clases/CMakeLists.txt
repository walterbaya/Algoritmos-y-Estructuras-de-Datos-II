cmake_minimum_required(VERSION 3.4)
project(uso_clases)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/)
include_directories(tests/)

file(GLOB SOURCE_FILES src/algobot.h src/algobot.cpp)

add_executable(tests_algobot tests/tests_algobot.cpp ${SOURCE_FILES})
add_executable(tests_ejercitacion tests/tests_funciones.cpp ${SOURCE_FILES})
