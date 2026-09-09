//
// Created by aml on 8/09/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerDatos();

void leerNombreCanal(char codigoCanal, int numCanal);

void imprimirEncabezado(int &fechaConvertidaI, int &fechaConvertidaF);

void imprimirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void imprimirLinea(int cant, char c);

void imprimirEncabezadoDeCanales(int nrCanal);

void imprimirEstadisticas(int dd, int mm, int anhio, int hh, int min, int ss, int cantReproduciones,
                          int &horaEnSegundos, int &ultimoDia, int &ultimoMes, int &ultimoAnhio,int fechaMin);

void imprimirHora(int hh, int min, int ss);

void imprimirEncabezadoEstadisticas();

void convertirHora(int hh, int min, int ss, int &horaEnSegundos);

void imprimirResumenDelCanal(int horaTotalEnSegundos);

void sacarUltimaFecha(int fechaConvertidaX, int &ultimoDia, int &ultimoMes, int &ultimoAnhio, int &fechaMin);

void imprimirResumenDelCanal(int horaTotalEnSegundos, int ultimoDia, int ultimoMes, int ultimoAnhio,
    int canTotalReproducciones,double &ingresosPublicidad);

void imprimirEstadisticasFinales(int cantStreams, int segundosTotales, double ingresosTotales,
    double ingresoMayor,char codigoCanal,int numCanal);

void calcularMayorIngreso(double ingresosTotales, char codigoCanal, int numCanal, char &codigoCanalMayor,
                          int &numCanalMayor, double &ingresoMayor, double ingresoMaximo);


#endif //FUNCIONES_H
