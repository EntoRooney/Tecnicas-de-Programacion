//
// Created by aml on 27/10/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerArrStreams(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream,
                    char *arrCarCateStream, int *arrNumCateStream, int &cantStreams);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

void convertirDuracion(int hh, int mm, int ss, int &duracionSeg);

void insertarOrdenadoStreams(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream, char *arrCarCateStream,
                             int *arrNumCateStream, int &cantStreams, int cod, int duracionSeg, int idioma, char carCat,
                             int numCat);

void imprimirReportePrueba(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream, char *arrCarCateStream,
                           int *arrNumCateStream, int cantStreams);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirDuracion(ofstream &archReporte, int arrDuracionStrem);

void leerArrCanales(int *arrCodigoStream, int *arrIdiomaStream, char *arrCarCateStream, int *arrNumCateStream,
                    int *arrDuracionStrem, int *arrFechaMasAntigua, int *arrFechaMasReciente, double *arrPromRat,
                    double *arrPromDrop, int *arrNumRepro, int *arrDuracionTotal, int cantStreams);

void eliminarTexto(ifstream &archCanales);

int busquedaBinaria(int cod, int *arrCodigoStream, int cantStreams);

void convertirFecha(int dd, int mes, int anhio, int &fecha);

void actualiazarArr(int &arrFechaMasAntigua, int &arrFechaMasReciente, double &arrPromRat,
                    double &arrPromDrop, int &arrNumRepro, int &arrDuracionTotal, int fecha, double rating,
                    double drop, int arrDuracionStrem);

void imprimirReporte(const char *nombArch, bool imprimirResumen,
                     int *arrCodigoStream, int *arrIdiomaStream, char *arrCarCateStream, int *arrNumCateStream,
                     int *arrDuracionStrem, int *arrFechaMasAntigua, int *arrFechaMasReciente, double *arrPromRat,
                     double *arrPromDrop, int *arrNumRepro, int *arrDuracionTotal, int cantStreams);

void imprimirEncabezado(ofstream &archReporte);

void imprimirFecha(ofstream &archReporte, int arrFechaMasReciente);

void calcularResumen(int arrCodigoStream, int arrDuracionTotal, int &menorDuracion, int &codMenor,
                     int &mayorDuracion, int &codMayor);

void imprimirDatosResumen(ofstream &archReporte, int menorDuracion, int codMenor, int mayorDuracion, int codMayor);

void ordenarArr(int *arrCodigoStream, int *arrIdiomaStream,
                char *arrCarCateStream, int *arrNumCateStream, int *arrDuracionStrem, int *arrFechaMasAntigua,
                int *arrFechaMasReciente, double *arrPromRat, double *arrPromDrop, int *arrNumRepro,
                int *arrDuracionTotal,
                int cantStreams);

void intercambiarInt(int &datoI, int &datoJ);

void intercambiarChar(char &datoI, char &datoJ);

void intercambiarDouble(double &datoI, double &datoJ);

#endif //FUNCIONES_H
