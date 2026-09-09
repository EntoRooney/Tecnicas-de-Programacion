//
// Created by USUARIO on 28/09/2025.
//

#ifndef LAB04_24_2_FUNCIONES_H
#define LAB04_24_2_FUNCIONES_H
void leerPlatos(ifstream &archPlatos, int *arrCodigo, double *arrPrecio, int &cantPlatos);
void eliminarTexto(ifstream &archPlatos) ;
void imprimirReporte(ifstream &archRepartidores, ifstream &archRepartos, ofstream &archReporte, int *arrCodigo,
                     double *arrPrecio, int cantPlatos);
void leerTexto(ifstream &archRepartidores, ofstream &archReporte, char fin, int ancho, bool guardarPrimera,
               char &primera) ;
void imprimirEncabezado(ofstream &archReporte);
void imprimirEncabezadoClientes(ofstream &archReporte,int &numRepartidor);
void imprimirLinea(ofstream &archReporte, int cant, char c) ;
#endif //LAB04_24_2_FUNCIONES_H