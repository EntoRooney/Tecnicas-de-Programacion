//
// Created by aml on 29/09/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerCanales(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int &cantCanales);

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void eliminarTexto(ifstream &archCanales);

void leerEtiquetas(int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int &cantEtiquetas);

void emitirReporteCanales(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int cantCanales);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirFecha(int fecha, ofstream &archReporte);

void emitirReporteEtiquetas(int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int cantEtiquetas);

void emitirReporte(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int cantCanales,
                   int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int cantEtiquetas,
                   int *arrNumRepro,int *arrSegundosTotales);

int buscarIdCanal( char codCanalArch, int numCanalArch, char *arrCodigo,
                  int *arrNumCod, int cantCanales);

void imprimirEncabezado(ofstream &archReporte, double &tarifa);

void imprimirCanales(ofstream &archReporte, char *arrCodigo, int *arrNumCod, int *arrFecha, double *arrRating,int *arrNumRepro,
                     int *arrSegundosTotales,int cantCanales);

int buscarIdEtiqueta(int *arrEtiquetas,int etiqueta,int  cantEtiquetas);

void convertirSegundos(int arrDuracionMin, int arrDuracionSeg, int &duracionSeg);

void imprimirHora(int horaSeg, ofstream &archReporte);

void imprimirRating(double arrRating,ofstream &archReporte,double &rating);
#endif //FUNCIONES_H
