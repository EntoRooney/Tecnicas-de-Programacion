cmake_minimum_required(VERSION 4.0)
project(Lab08_24_22)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab08_24_22 main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/Distrito.h
        Bibliotecas/Plato.h
        Bibliotecas/PlatoPedido.h
        Bibliotecas/Cliente.h)
