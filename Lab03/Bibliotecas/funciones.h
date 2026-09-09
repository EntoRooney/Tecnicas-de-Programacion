//
// Created by aml on 22/09/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimirReporte(ifstream &archCanales, ifstream &archEtiquetas, ifstream &archRepro, ofstream &archReporte);

void imprimirEncabezado(ofstream &archReporte, double &tarifaDuracion);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void leerNombre(ifstream &archCanales, ofstream &archReporte, int dd, int mes, int anhio, char codCanal,
                int numCanal, int nroCanal);

void imprimirEncabezadoCanal(ofstream &archReporte, int nroCanal);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void imprimirEtiquetas(ifstream &archEtiquetas, ifstream &archRepro, ofstream &archReporte, int etiqueta
                       , char codCanal, int numCanal, int &nroEtiqueta,int &duracionSegunTotales);

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int etiqueta);

void imprimirDescripcion(ifstream &archEtiquetas, ofstream &archReporte, int etiqueta,int cantRepro,
    int &duracionSegunTotales);

void leerDescripcion(ifstream &archEtiquetas, ofstream &archReporte, int &hhD, int &minD,int cantRepro,
    int &duracionSegunTotales);

void imprimirEncabezadoEtiquetas(ofstream &archReporte);

void calcularHora(int duracionReproSegundos, int &hhFinal, int &minFinal, int &ssFinal);

void imprimirHora(ofstream &archReporte, int hhFinal, int minFinal, int ssFinal);

void imprimirEstadisticas(ofstream &archReporte,int duracionSegunTotales,int rating,double tarifaDuracion);
void imprimirRating(ofstream &archReporte, int rating,double &porcentaje) ;
#endif //FUNCIONES_H
