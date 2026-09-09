//
// Created by aml on 17/11/2025.
//
#define MAX 15
#ifndef CATEGORIA_H
#define CATEGORIA_H

struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    struct Reproduccion *reproducciones;
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};
#endif //CATEGORIA_H
