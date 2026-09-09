//
// Created by entol on 17/11/2025.
//

#ifndef LAB08_24_22_CLIENTE_H
#define LAB08_24_22_CLIENTE_H

struct Cliente {
    int dni;
    char *nombre;
    struct Distrito distrito;
    struct PlatoPedido pedidos[30];
    int cantidadDePedidos;
    double montoTotal;
};

#endif //LAB08_24_22_CLIENTE_H