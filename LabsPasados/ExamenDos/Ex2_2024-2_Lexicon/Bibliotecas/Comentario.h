//
// Created by entol on 1/12/2025.
//

#ifndef EXAMENMIMAYORTERROR_COMENTARIO_H
#define EXAMENMIMAYORTERROR_COMENTARIO_H

struct Comentario {
    char *texto;
    char *pre_procesado;
    struct Palabra palabras[20];
    int cantidad_palabras;
    int polaridad_total;
};
#endif //EXAMENMIMAYORTERROR_COMENTARIO_H