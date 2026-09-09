//
// Created by USUARIO on 12/10/2025.
//

#ifndef TALLEREX1_P2_FUNCIONES_H
#define TALLEREX1_P2_FUNCIONES_H

void leerArrLibros(int *arrCodLibro, double *arrPrecLibro, int &cantLibros);

void abrirArchIfstream(const char *nombArch, ifstream &archLibros);

void eliminarTexto(ifstream &arch, bool comerPrimera, char delim);

void ordenarArrLibros(int *arrCodLibro, double *arrPrecLibro, int cantLibros);

void cambiarInt(int &arrIntX, int &arrIntJ);

void cambiarDouble(double &arrIntX, double &arrIntJ);

void imprimirReporte(int *arrCodLibro, double *arrPrecLibro, int cantLibros);

void abrirArchOfstream(const char *nombArch, ofstream &archReporte);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void leerArrVentas(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                   double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti, int *arrDniUlti,
                   int cantLibros);

int buscarIdLibro(int codLibro, int *arrCodLibro, int cantLibros);

void calcularFecha(int dd, int mes, int anhio, int &fechaConvertida);

void imprimiReporte(const char *nomArch,int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                         double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                         int *arrDniUlti, int cantLibros);

void imprimirFecha(ofstream &archReporte, int arrFechaPrime);

void imprimirEncabezado(ofstream &archReporte);

void ordenarFinal(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                  double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                  int *arrDniUlti, int cantLibros);

void eliminarArr(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                 double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                 int *arrDniUlti, int &cantLibros);

void eliminarArrLibro(int i, int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                      double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                      int *arrDniUlti, int &cantLibros);

#endif //TALLEREX1_P2_FUNCIONES_H
