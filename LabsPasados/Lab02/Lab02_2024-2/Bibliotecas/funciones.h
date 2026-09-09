//
// Created by USUARIO on 7/09/2025.
//

#ifndef LAB_24_2_FUNCIONES_H
#define LAB_24_2_FUNCIONES_H
void imprimirReporte();
void leerNombre(int dni) ;
void imprimirEncabezado(int dd, int mes, int anhio) ;
void imprimirLinea(int cant, char c) ;
void imprimirFecha(int dd, int mes, int anhio);
void imprimirHora(int hh, int mm, int ss);
void imprimirResultados(int hhI, int mmI, int ssI, int hh, int mm, int ss, int grados, int minutos, int segundos,
                        double velocidad,double &distanciaAcumulada,double &xAnterior,double &yAnterior);
void convertirGrados(int grados,int minutos,int segundos,double &gradosSexa);
void calcularDistancia(int hhI,int  mmI,int  ssI,int  hh,int  mm,int  ss,double velocidad,double &distancia) ;
void calcularPuntosDistancia(double gradosSexa, double distancia, double &distanciaAcumulada,
                             double &xAnterior, double &yAnterior ,double &x,double &y);
void calcularPagoTramos(double distanciaAcumulada,double &pagoTramo);
#endif //LAB_24_2_FUNCIONES_H