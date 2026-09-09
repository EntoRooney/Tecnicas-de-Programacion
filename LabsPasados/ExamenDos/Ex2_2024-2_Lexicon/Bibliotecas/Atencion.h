//
// Created by entol on 1/12/2025.
//

#ifndef EXAMENMIMAYORTERROR_ATENCION_H
#define EXAMENMIMAYORTERROR_ATENCION_H

struct Atencion {
    int codigo;
    struct Plato *platos_atentidos;
    int cantidad_platos;
    double total_venta;
    int hora;
    struct Comentario *comentarios;
    int cantidad_comentarios;
};
#endif //EXAMENMIMAYORTERROR_ATENCION_H
