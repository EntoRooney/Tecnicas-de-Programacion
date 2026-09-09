//
// Created by aml on 10/11/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerCategorias(const char *nombArch, struct Categoria *arrCategorias, int &cantidadCategorias);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

void imprimirReportePrueba(const char *nombrArch, struct Categoria *arrCategorias, int cantidadCategorias,
                           bool reporteDos);

void imprimirLinea(ofstream &arch, int cant, char c);

void leerStreams(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias);

void convertirDuracion(int hh, int mm, int ss, int &duracion);

int buscarCategoria(struct Categoria *arrCategorias, int cantidadCategorias, const char *codCate);

void imprimirDuracion(ofstream &archReporte, int duracion);

void calcularPromedios(struct Categoria *arrCategorias, int cantidadCategorias);

void imprimirReporte(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias);

#endif //FUNCIONES_H
