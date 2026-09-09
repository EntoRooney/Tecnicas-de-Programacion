//
// Created by USUARIO on 9/11/2025.
//

#ifndef LAB08_24_1_ALUMNO_H
#define LAB08_24_1_ALUMNO_H

#include "Facultad.h"

struct Alumno {
    int codigo;
    char nombre[50];
    int numCursos;
    double sumaPonderada;
    double numCreditos;
    double promPonderado;
    struct Facultad facultad;
};
#endif //LAB08_24_1_ALUMNO_H
