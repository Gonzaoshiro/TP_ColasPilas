cmake_minimum_required(VERSION 4.0)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 src/main.cpp
        src/dominio.cpp
        src/dominio.h
        src/cola.h
        src/pila.h
        src/util.cpp
        src/util.h
        src/menu.cpp
        src/menu.h)
