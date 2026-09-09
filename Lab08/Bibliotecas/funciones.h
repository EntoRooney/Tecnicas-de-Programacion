//
// Created by aml on 17/11/2025.
//
#include "Reproduccion.h"
#include "Categoria.h"

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerArrCategorias(struct Categoria *arrCategorias, int &cantidadCategorias);

void abrirArchivoIfstream(const char *nomArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

char *leerCadenaExacta(ifstream &arch, char delim);

void imprimirReportePrueba(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias,
                           bool segundoReporte,bool tercerReporte);

void imprimirLinea(ofstream &arch, int cant, char c);

void leerStreamsRepro(struct Categoria *arrCategorias, int cantidadCategorias);

void convertirDuracion(int hh, int min, int ss, int &tiempoSeg);

int buscarCategoria(struct Categoria *arrCategorias, int cantidadCategorias, const char *codCategoria);

void imprimirDuracion(ofstream &archReporte, int duracion);

void ordenarPorNombreCat(struct Categoria *arrCategorias, int cantidadCategorias);

void leerComentariosCanal(struct Categoria *arrCategorias, int cantidadCategorias);

#endif //FUNCIONES_H
