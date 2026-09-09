//
// Created by USUARIO on 3/09/2025.
//

#ifndef LAB25_1_FUNCIONES_H
#define LAB25_1_FUNCIONES_H

void imprimirReporte();

void imprimirNombre(int dni, int nroCompania);

void imprimirEncabezado(int ddI, int mmI, int anhioI, int ddF, int mmF, int anhioF);

void imprimirFecha(int dd, int mes, int anhio);

void imprimirLinea(int cant, char c);

void imprimirDatos(char tipoVehi, int num1, int num2, int dd, int mm, int anhio, int hh, int min, int ss,
                   char gravedad, int ddI, int mmI, int anhioI, int ddF, int mmF, int anhioF, double &multa,
                   double &porTipo, double &porFecha, double &porHora, double &montoTotal);

void imprimirTipoVehiculo(char tipoVehi, double &incrementoPorTipo);

void imprimirPlaca(char tipoVehi, int num1, int num2);

void imprimirHora(int hh, int min, int ss);

void imprimirGravedad(char gravedad, double &multa);

void imprimirEncabezadoVehi();

void incrementoFechas(int dd, int mm, int anhio, int ddI, int mmI, int anhioI, int ddF, int mmF,
                      int anhioF, double &incrementoPorFecha);

void convertidorDeFechas(int dd, int mm, int anhio, int &fechaConvertida);

void incrementoHoras(int hh, int min, int ss, double &incrementoPorhoras);

void montosTotales(double multa, double porTipo, double porFecha, double porHora, double monto, double &montoFinal,
                   double &multaTotales, double &porTipoTotal, double &porFechaTotal, double &porHoratotal);

void imprimirEstadisticasFinales(double multaTotales, double porTipoTotal, double porFechaTotal, double porHoratotal,
                                 double montoFinal);

void calcularEstadisticas(int dni, double montoFinal, double &totalRecaudado, int &dniMayor, double &montoMayor,
                          int &dniMenor, double &montoMenor,double &montoMinimo,double &montoMaximo);

void imprimirEstadisticas(double totalRecaudado, int dniMayor, double montoMayor, int dniMenor, double montoMenor);

#endif //LAB25_1_FUNCIONES_H
