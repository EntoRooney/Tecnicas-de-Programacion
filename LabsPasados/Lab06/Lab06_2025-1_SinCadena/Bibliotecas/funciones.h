//
// Created by USUARIO on 26/10/2025.
//

#ifndef LAB06_25_1_FUNCIONES_H
#define LAB06_25_1_FUNCIONES_H

void llenarArrInfraccion(int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantCodigos);

void abrirArchivoIfstream(const char *nombArch, ifstream &archCod);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

void eliminarTexto(ifstream &archCod);

void inserOrdenado(int cod, double multa, int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantCodigos);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirReportePrueba(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantCodigos);

void llenarArrInfraCometidas(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantCodigos,
                             int *arrDni, int *arrMasMultaAntigua, int *arrUltimaMulta,
                             double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int &cantDni);

int buscarBinaria(int codigo, int *arrCodigoInfraccion, int cantCodigos);

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void actualizarDni(int &arrMasMultaAntigua, int &arrUltimaMulta, double &arrTotalMultas,
                   double &arrTotalPagadas, double &arrTotalPendientes, int fechaCometida, int fechaPago,
                   double arrMultasInfraccion);

void insertarDni(int *arrDni, int *arrMasMultaAntigua, int *arrUltimaMulta, double *arrTotalMultas,
                 double *arrTotalPagadas,
                 double *arrTotalPendientes, int &cantDni, int dni, int fechaCometida, int fechaPago,
                 double arrMultasInfraccion);

void imprimirReporte(int *arrDni, int *arrMasMultaAntigua, int *arrUltimaMulta, double *arrTotalMultas,
                     double *arrTotalPagadas,
                     double *arrTotalPendientes, int cantDni);

void imprimirEncabezado(ofstream &archReporte);
void imprimirFecha(ofstream &archReporte,int  arrUltimaMulta);
#endif //LAB06_25_1_FUNCIONES_H
