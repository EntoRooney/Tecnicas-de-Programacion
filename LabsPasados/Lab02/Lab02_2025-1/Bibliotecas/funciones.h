//
// Created by entol on 15/09/2025.
//

#ifndef LAB02_25_1_FUNCIONES_H
#define LAB02_25_1_FUNCIONES_H

void imprimirReporte(ifstream &archInfracciones, ifstream &archDatosMultas, ofstream &archReporte);

void imprimirEncabezado(ofstream &archReporte);

void leerNombre(ifstream &archInfracciones, ofstream &archReporte, int dni, int numCompania);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirVehiculosInfraccionados(ifstream &archDatosMultas, ofstream &archReporte, char tipoVehi, int num1,
                                     int num2, int dd, int mes, int anhio, int codigoInfra,
                                     int &cantLeves, int &cantGraves, int &cantMuyGraves,
                                     double &multaLeves, double &multaGraves, double &multaMuyGraves);

void imprimirTipoVehi(ofstream &archReporte, char tipoVehi);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void imprimirInfraccion(ifstream &archDatosMultas, ofstream &archReporte, int codigoInfra, char gravedad,
                        double multa);

void imprimirGravedad(ofstream &archReporte, char gravedad);

void imprimirDescripcion(ifstream &archDatosMultas, ofstream &archReporte);

void imprimirEncabezadoMultas(ofstream &archReporte);

void calcularCantFaltas(char gravedad, double multa, int &cantLeves, int &cantGraves, int &cantMuyGraves,
                        double &multaLeves, double &multaGraves, double &multaMuyGraves);

void imprimirResumen(ofstream &archReporte, int cantLeves, int cantGraves, int cantMuyGraves,
                     double multaLeves, double multaGraves, double multaMuyGraves, double &pagoTotal);

void imprimirResumenFinal(ofstream &archReporte, int cantTotalLeves, int cantTotalGraves, int cantTotalMuyGraves,
                          double multaTotalLeves, double multaTotalGraves, double multaTotalMuyGraves);

void calcularMayorMenor(double pagoTotal, int dni, double &pagoMax, int &dniMax, double &pagoMin, int &dniMin);

void imprimirEstadisticas(ofstream &archReporte, double pagoMax, int dniMax, double pagoMin, int dniMin);

#endif //LAB02_25_1_FUNCIONES_H
