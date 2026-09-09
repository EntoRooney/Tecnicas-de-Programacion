//
// Created by USUARIO on 12/10/2025.
//

#ifndef TALLEREX1_P1_FUNCIONES_H
#define TALLEREX1_P1_FUNCIONES_H

void imprimirReporte();

void aperturaArchivos(ifstream &archLibros, ifstream &archClientes, ifstream &archVentas, ofstream &archReporte);

void abrirArchIfstream(const char *nombArch, ifstream &arch);

void abrirArchOfstream(const char *nombArch, ofstream &arch);

void leerTexto(ifstream &arch, ofstream &archReporte, bool enMayus, bool quitarPrimerC, int cant, char deli);

void imprimirEncabezado(ofstream &archReporte, int &fechaI, int &fechaF);

void calcularFecha(int dd, int mes, int anhio, int &fechaConvertida);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void imprimirVentas(ifstream &archVentas, ifstream &archClientes, ofstream &archReporte, int fechaI, int fechaF,
                    int codLibro, int &cantVendidas, int &sumaCalificacion, int &peorCali, int &dniPeor, int &mejorCali,
                    int &dniMejor);

void imprimirEncabezadoLibros(ofstream &archReporte);

void leerCliente(ifstream &archClientes, ofstream &archReporte, int codLibreria, int dniCliente, int dd, int mes,
                 int anhio, int califacion, int &cantVendidas, int &sumaCalificacion,
                 int &peorCali, int &dniPeor, int &mejorCali, int &dniMejor);

void imprimirCantTotal(ofstream &archReporte, int cantVendidas, double precioLibro, double &totalVentas);

void imprimirEstadisticias(ofstream &archReporte, int cantVendidas, int sumaCalificacion, int peorCali, int dniPeor,
                           int mejorCali, int dniMejor);

void calcularMejorPeorCali(int califacion, int dniCliente, int &peorCali, int &dniPeor, int &mejorCali, int &dniMejor);

void imprimirResumen(ofstream &archReporte,int cantTotal,double ventasTotales);

#endif //TALLEREX1_P1_FUNCIONES_H
