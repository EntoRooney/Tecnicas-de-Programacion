//
// Created by entol on 22/09/2025.
//

#ifndef LAB03_25_1_FUNCIONES_H
#define LAB03_25_1_FUNCIONES_H
void imprimirReporte(ifstream &archEmpresas,ifstream &archInfracciones,ifstream &archTabla,ofstream &archReporte);
void imprimirEncabezado(ofstream &archReporte);
void leerNombre(ifstream &archEmpresas,ofstream &archReporte,int dni,int numCompania) ;
void imprimirLinea(ofstream &archReporte,int cant,char c);
void leerDistrito(ifstream &archEmpresas,ofstream &archReporte) ;
void leerDistrito(ifstream &archEmpresas,ofstream &archReporte);
void imprimirPlacas(ifstream &archInfracciones, ifstream &archTabla, ofstream &archReporte, char carTipoVehi,
int num1, int num2, int nroPlaca,int &cantLeves,double &multaLeves,int &cantGraves,double &multaGraves,
int &cantMuyGraves,double &multaMuyGraves);
void imprimirEncabezadoPlacas(ofstream &archReporte,int nroPlaca,char carTipoVehi,int num1,int num2) ;
void imprimirTipo(ofstream &archReporte,char carTipoVehi);
void imprimirDatos(ifstream &archTabla, ofstream &archReporte, int dd, int mes, int anhio, char codInfra,
                   int numInfra, int nroInfraccion, int &cantLeves, double &multaLeves, int &cantGraves,
                   double &multaGraves, int &cantMuyGraves, double &multaMuyGraves);
void imprimirEncabezadoDatos(ofstream &archReporte);
void imprimirFecha(ofstream &archReporte,int dd,int mes,int anhio) ;
void  imprimirGravedad(ofstream &archReporte,char codInfra);
void imprimirMulta(ifstream &archTabla, ofstream &archReporte, char codInfra, int numInfra, int &cantLeves,
                   double &multaLeves, int &cantGraves, double &multaGraves, int &cantMuyGraves,
                   double &multaMuyGraves) ;
void imprimirDescripcion(ifstream &archTabla,ofstream &archReporte);
void calcularCantidad(char codInfra,double multa,int &cantLeves,double &multaLeves,int &cantGraves,double &multaGraves,
    int &cantMuyGraves,double &multaMuyGraves);
void imprimirEstadisticas(ofstream &archReporte, int cantLeves, double multaLeves, int cantGraves, double multaGraves,
                          int cantMuyGraves, double multaMuyGraves,int &cantTotales, double &multaTotales);
void imprimirEstadisticasFinales(ofstream &archReporte,int cantTotal,double multaFinal,double multaMayor,int dniMayor,
    double multaMenor,int dniMenor);
void calcularMayorMenor(int dni,double multaTotales,double &multaMayor,int &dniMayor,double &multaMenor,
    int &dniMenor);

#endif //LAB03_25_1_FUNCIONES_H