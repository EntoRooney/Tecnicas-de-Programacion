//
// Created by entol on 17/11/2025.
//

#include "Distrito.h"
#include "Plato.h"
#include "PlatoPedido.h"
#include "Cliente.h"

#ifndef LAB08_24_22_FUNCIONES_H
#define LAB08_24_22_FUNCIONES_H

void leerArrDistritos(struct Distrito *arrDistrito, int &cantDistritos);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

char *leerCadenaExacta(ifstream &arch, char delim);

void leerArrPlatos(struct Plato *arrPlato, int &cantPlatos);

void leerArrClientes(struct Cliente *arrCliente, int &cantClientes);

void imprimirReportesPrueba(struct Distrito *arrDistrito, int cantDistritos,
                            struct Plato *arrPlato, int cantPlatos,
                            struct Cliente *arrCliente, int cantClientes);

void imprimirLinea(ofstream &arch, int cant, char c);

void imprimirEncabezadoDis(ofstream &arch);

void imprimirEncabezadoPlatos(ofstream &arch);

void imprimirEncabezadoCli(ofstream &arch);

void llenarArrTotales(struct Distrito *arrDistrito, int cantDistritos,
                      struct Plato *arrPlato, int cantPlatos,
                      struct Cliente *arrCliente, int cantClientes);

int buscarCliente(struct Cliente *arrCliente, int cantClientes, int dniCli);

int buscarPlato(struct Plato *arrPlato, int cantPlatos, const char *codPlato);

void ordenarClientes(struct Cliente *arrCliente, int cantClientes);

void cambiarStructs(struct Cliente &arrI, struct Cliente &arrJ);

void ordenarTodosLosPedidos(struct Cliente *arrCliente, int cantClientes);

void ordenarPedidosClientes(struct Cliente &cli);

void intercambiarPedidos(struct PlatoPedido &a, struct PlatoPedido &b);
void imprimirReporteFinal(struct Cliente *arrCliente, int cantClientes);
void imprimirTitulo(ofstream &arch);
void imprimirCliente(ofstream &arch, const Cliente &cli);
void imprimirPedidosCliente(ofstream &arch, const Cliente &cli);
void imprimirTotalesCliente(ofstream &arch, const Cliente &cli);
#endif //LAB08_24_22_FUNCIONES_H
