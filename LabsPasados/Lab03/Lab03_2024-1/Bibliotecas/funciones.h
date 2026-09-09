//
// Created by entol on 22/09/2025.
//

#ifndef LAB03_24_1_FUNCIONES_H
#define LAB03_24_1_FUNCIONES_H
void imprimirReporte(ifstream &archCitas,ifstream &archMedicos,ofstream &archReporte);
void imprimirEncabezado(ofstream &archReporte);
void imprimirLinea(ofstream &archReporte, int cant, char c) ;
void imprimirDatos(ifstream &archMedicos, ofstream &archReporte, int dd, int mes, int anhio, int dni, double descuento,
                   int hhI, int minI, int ssI, int hhF, int minF, int ssF, int codMedico, double montoMedi,
                   double &pagoFinal);
void imprimirFecha(ofstream &archReporte,int dd,int mes,int anhio);
void imprimirHora(ofstream &archReporte,int hh,int min,int ss);
void  calcularDuracion(int hhI,int minI,int ssI,int hhF,int minF,int ssF,int &hh,int &min,int &ss,int &segundosTotales);
void imprimirMedicos(ifstream &archMedicos, ofstream &archReporte, double descuento, int codMedico,
                     double montoMedi, int segundosTotales,double &pagoFinal);
void imprimirNombre(ifstream &archMedicos, ofstream &archReporte);
void imprimirEspecialidad(ifstream &archMedicos, ofstream &archReporte);
void calcularPago(int segundosTotales, double tarifaHora, double descuento, double montoMedi,double &pagoFinal);
void calcularMayorMenor(int dni,double pagoFinal,int &dniMax,int &dniMin,double &pagoMax,double &pagoMin);

#endif //LAB03_24_1_FUNCIONES_H