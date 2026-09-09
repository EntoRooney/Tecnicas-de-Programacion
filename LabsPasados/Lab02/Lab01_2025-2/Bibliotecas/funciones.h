//
// Created by USUARIO on 14/09/2025.
//

#ifndef LAB1CONLAB2_25_2_FUNCIONES_H
#define LAB1CONLAB2_25_2_FUNCIONES_H

void imprimirReporte(ifstream &archDatos, ofstream &archReporte);

void imprimirEncabezado(ofstream &archReporte, int &fechaInicial, int &fechaFinal);

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void leerNombreCanal(ifstream &archDatos, ofstream &archReporte, int cantCanal, int ddC, int mesC, int anhioC,
                     char codCanal,
                     int numCanal);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int hh, int min, int ss,
                   int cantRepro, int &horaTotalSegundos, int &fechaMax, int &ddUltima, int &mesUltima,
                   int &anhioUltima, int &totalReproducciones);

void imprimirEncabezadoDatos(ofstream &archReporte);

void imprimirHora(ofstream &archReporte, int hh, int min, int ss);

void convertirHora(int hh, int min, int ss, int &horaEnSegundos);

void calcularUltimaPublicacion(int fechaConvertida, int &fechaMax, int &ddUltima, int &mesUltima, int &anhioUltima);

void imprimirResumen(ofstream &archReporte, int horaTotalSegundos, int ddUltima, int mesUltima, int anhioUltima,
                     int totalReproducciones, double &ingresosPublicidad);

void imprimirResumenFinal(ofstream &archReporte, int cantTotalStreams, int horaFinalSegundos, double ingresosTotales,
                          double ingresosMaximo, char codCanalMax, int numCanalMax);

void calcularMayoresIngresos(double ingresosPublicidad, char codCanal, int numCanal, double &ingresosMaximo,
                             char &codCanalMax, int &numCanalMax);
#endif //LAB1CONLAB2_25_2_FUNCIONES_H
