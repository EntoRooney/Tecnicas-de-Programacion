//
// Created by aml on 15/09/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimirReporte(ifstream &archDatos, ofstream &archReporte);

void imprimirEncabezadoInicial(ofstream &archReporte, int &fechaInicial, int &fechaFinal, double &tarifaRepro,
                               double &tarifaStream);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void leerNombre(ifstream &archDatos, ofstream &archReporte, int ddC, int mesC, int anhioC, char codCanal,
                int numCanal, int numCompania, double &engagemente);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirEncabezadoCanales(ofstream &archReporte);

void imprimirEncabezadoDatos(ofstream &archReporte);

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int hh, int min, int ss,
                   double tarifaStream, int cantRepro, double &ingresosPorDuracion, int &horaEnSegundos);

void imprimirHora(ofstream &archReporte, int hh, int min, int ss);

void convertirHoraMinutos(int hh, int min, int ss, double &horaEnMinutos, int &horaEnSegundos);

void imprimirResumenCanal(ofstream &archReporte, int totalSegundos, double totalIngresosDuracion, int totalCantRepro,
                          double tarifaRepro, double &ingresosPorPublicidad, double engagemente);

void imprimirResumenFinal(ofstream &archReporte, int cantStreams, int duracionFinal, double ingresosFinalesDuracion,
                          double ingresosFinalesPublicidad);
#endif //FUNCIONES_H
