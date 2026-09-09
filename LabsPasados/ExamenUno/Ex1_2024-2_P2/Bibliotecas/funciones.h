//
// Created by USUARIO on 12/10/2025.
//

#ifndef EX1_24_2_P2_FUNCIONES_H
#define EX1_24_2_P2_FUNCIONES_H

void leerArrPlatos(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato, int &cantPlatos);

void abrirArchIfstream(const char *nomArch, ifstream &arch);

void eliminarTexto(ifstream &arch, char deli);

void leerArrCliente(int *arrDniCliente, double *arrDescCliente, int &cantCliente);

void imprimirReporteSimple(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                           int cantPlatos,
                           int *arrDniCliente, double *arrDescCliente, int cantCliente);

void abrirArchOfstream(const char *nomArch, ofstream &arch);

void llenarArrFinales(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato, int cantPlatos,
                      int *arrDniCliente, double *arrDescCliente, int cantCliente,
                      int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                      double *arrMontoRecibido);

int buscarIdCliente(int dniCliArch, int *arrDniCliente, int cantCliente);

int buscarIdPlato(int codPlato, int *arrCodPlato, int cantPlatos);

void ordenarCantPlatos(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                       int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                       double *arrMontoRecibido, int cantPlatos);

void cambiarInt(int &arrI, int &arrJ);

void cambiarDou(double &arrI, double &arrJ);

void imprimirReporte(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                     int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                     double *arrMontoRecibido, int cantPlatos);

void imprimirLinea(ofstream &arch, int can, char c);

void eliminarArr(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                 int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                 double *arrMontoRecibido, int &cantPlatos);

void eliminarElemento(int n, int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                      int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                      double *arrMontoRecibido, int &cantPlatos);
void  imprimirReporteEliminado(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                     int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                     double *arrMontoRecibido, int cantPlatos);
#endif //EX1_24_2_P2_FUNCIONES_H
