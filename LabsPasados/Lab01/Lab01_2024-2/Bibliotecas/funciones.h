//
// Created by USUARIO on 28/08/2025.
//

#ifndef LAB12024_1_FUNCIONES_H
#define LAB12024_1_FUNCIONES_H

void imprimirReporte();

void imprimirEncabezado();

void imprimirLinea(int cant, char c);

void imprimirFechayDni(int dia, int mes, int anhio, int dni);

void imprimirHora(int hh, int mm, int ss, int &duracion);

void calcularDuracion(int duracionI, int duracionF, double &duracionH);

void imprimirEspecialidad(char especialidad);

void imprimirPagoCM(double tarifaxHora, double monto, double duracionH, double &montoTotal);

void impresionEstadisticas(int pacientesSiMed, double montoTotalMedinas, double montoMedDerma, int totalPacientes,
                           int pacientesPedri, int pacientesDerma, int pacientesFechaCardio);

void convertirfecha(int dia, int mes, int anhio, int &fechaConvertida);

void impresionEstadisticas(int pacientesSiMed, double montoTotalMedinas, double montoMedDerma, int totalPacientes,
                           int pacientesPedri, int pacientesDerma, int pacientesFechaCardio, int pacientesNOMed);

#endif //LAB12024_1_FUNCIONES_H
