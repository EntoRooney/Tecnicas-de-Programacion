//
// Created by USUARIO on 2/11/2025.
//

#ifndef LAB06_25_1CONCADENA_FUNCIONES_H
#define LAB06_25_1CONCADENA_FUNCIONES_H

void leerArrCodInfra(int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantInfra);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

void eliminarTexto(ifstream &archTabla);

void insertarOrdenado(int cod, double multa, int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantInfra);

void imprimirReportePrueba(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfra);

void imprimirLinea(ofstream &arch, int cant, char c);

void leerMultasCometidas(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfra,
                         int *arrDni, int *arrMultaMasAntigua, int *arrMultaMasRecientePagada,
                         double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int &cantDni);

void convertirFecha(int dd, int mes, int anhio, int &fecha);

int busquedaBinaria(int codBuscado, int *arr, int cant);

void actualizarDni(int &arrMultaMasAntigua, int &arrMultaMasRecientePagada,
                   double &arrTotalMultas, double &arrTotalPagadas, double &arrTotalPendientes,
                   int fechaCometida, int fechaPagada, double arrMultasInfraccion);

void insertarDni(int dni, int fechaCometida, int fechaPagada, double multa, int *arrDni, int *arrMultaMasAntigua,
                 int *arrMultaMasRecientePagada, double *arrTotalMultas, double *arrTotalPagadas,
                 double *arrTotalPendientes, int &cantDni);

void imprimirReporte(int *arrDni, int *arrMultaMasAntigua, int *arrMultaMasRecientePagada,
                     double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int cantDni);

void imprimirEncabezado(ofstream &archReporte);

void imprimirFecha(ofstream &archReporte, int arrFecha);

void buscarPlacas(ifstream &archPlacas, int dniBuscado, char *listaDePlacas);

void agregarPlaca(char *listaDePlacas, const char *placaNueva);

void imprimirPlacas(ofstream &archReporte, const char *listaDePlacas, int ancho);

#endif //LAB06_25_1CONCADENA_FUNCIONES_H
