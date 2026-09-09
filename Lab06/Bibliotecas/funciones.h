//
// Created by USUARIO on 9/11/2025.
//

#ifndef LAB06_25_2_FUNCIONES_H
#define LAB06_25_2_FUNCIONES_H

void generaArchivoEnlace(const char *categoria, char *nombArch, char *enlace);

void leerArrCategorias(char **arrCodCat, char **arrNombCat, int &cantCategorias);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

char *leerCadenaExacta(ifstream &arch, char delim);

void imprimirReporteCat(char **arrCodCat, char **arrNombCat, int cantCategorias);

void imprimirLinea(ofstream &arch, int cant, char c);

void leerArrStreams(int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                    double *arrTasaDOffStream, int *arrDuracion, int &cantStreams);

void convertirFecha(int dd, int mes, int anhio, int &arrFecha);

void convertirHora(int hh, int min, int ss, int &arrDuracion);

void imprimirReporteStream(int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                           double *arrTasaDOffStream, int *arrDuracion, int cantStreams);

void imprimirFecha(ofstream &arch, int fecha);

void imprimirHora(ofstream &arch, int duracion);

void imprimirReportes(char **arrCodCat, char **arrNombCat, int cantCategorias,
                      int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                      double *arrTasaDOffStream, int *arrDuracion, int cantStreams);

void imprimirEncabezado(ofstream &archReporte, const char *arrCodCat, const char *arrNombCat, const char *enlace);
void imprimirResumen(ofstream &archReporte,double sumaRat,double sumaTasaD,int cant,int duracionTotal);
#endif //LAB06_25_2_FUNCIONES_H
