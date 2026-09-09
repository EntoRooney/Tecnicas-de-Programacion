//
// Created by aml on 10/11/2025.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H
#include "Reproduccion .h"
#define MAX_REPRO 15

struct Categoria {
    char codigo[100];
    char nombre[100];
    struct Reproduccion reproducciones[MAX_REPRO]{};
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};

#endif //CATEGORIA_H
