cmake_minimum_required(VERSION 4.0)
project(ExamenMiMayorTerror)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExamenMiMayorTerror main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/Palabra.h
        Bibliotecas/Comentario.h
        Bibliotecas/Plato.h
        Bibliotecas/Atencion.h)
