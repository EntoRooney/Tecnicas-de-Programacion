//
// Created by USUARIO on 21/09/2025.
//

#ifndef LAB3_2024_2_FUNCIONES_H
#define LAB3_2024_2_FUNCIONES_H
void imprimirReporte(ifstream &archClientes,ifstream &archPlatos,ofstream &archReporte);
void imprimirEncabezado(ofstream &archReporte);
void leerNombre(ifstream &archPlatos,ofstream &archReporte,int codigoPlato,double &precio);
void imprimirLinea(ofstream &archReporte,int cant,char c);
void leerTipo(ifstream &archPlatos,ofstream &archReporte);
void imprimirRepartidores(ifstream &archClientes, ofstream &archReporte, int codigoPlato, double precio,
                          double &montoFinal,
                          int &cantFinal, double &montoMayor, int &cantMayor, double &montoMenor, int &cantMenor,
                          int &codigoPlatoMax, int &codigoPlatoMin,
                          int &codigoPlatoCantMax, int &codigoPlatoCantMin);
void eliminarNombre(ifstream &archClientes) ;
void imprimirDatos(ofstream &archReporte, int codRepartidor, int hh, int min, int ss, int cant, double precio,
                   double &monto, int &cantTotal, double &montoTotal);
void imprimirEncabezadoRepartidores(ofstream &archReporte) ;
void imprimirHora(ofstream &archReporte,int hh,int min,int ss);
void imprimirTotales(ofstream &archReporte,double montoTotal,int cantTotal);
void  calcularMayorMenor(double montoTotal,int cantTotal,double &montoMayor,int &cantMayor,double &montoMenor,int &cantMenor,int codigoPlato,
                    int &codigoPlatoMax,int &codigoPlatoMin,int &codigoPlatoCantMax, int &codigoPlatoCantMin) ;
#endif //LAB3_2024_2_FUNCIONES_H