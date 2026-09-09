#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by entol on 22/09/2025.
//

#include "funciones.h"
#define TAM_MAX 160

void imprimirReporte(ifstream &archCitas, ifstream &archMedicos, ofstream &archReporte) {
    imprimirEncabezado(archReporte);
    int dd, mes, anhio, dni, hhI, minI, ssI, hhF, minF, ssF, codMedico, dniMax, dniMin;
    double descuento, montoMedi, pagoFinal, pagoTotal = 0, pagoMin = 100000, pagoMax = 1;
    char c, SN;

    while (true) {
        archCitas >> dd;
        if (archCitas.eof()) break;
        archCitas >> c >> mes >> c >> anhio >> dni >> descuento >> hhI >> c >> minI >> c >> ssI >> hhF >> c >> minF >> c
                >> ssF >> codMedico >> ws;
        archCitas >> SN;
        if (SN == 'S') {
            archCitas >> montoMedi;
        } else {
            montoMedi = 0;
        }
        imprimirDatos(archMedicos, archReporte, dd, mes, anhio, dni, descuento, hhI, minI, ssI, hhF, minF, ssF,
                      codMedico, montoMedi, pagoFinal);
        calcularMayorMenor(dni, pagoFinal, dniMax, dniMin, pagoMax, pagoMin);
        pagoTotal += pagoFinal;
    }
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "Total de ingresos: " << pagoTotal << endl;
    imprimirLinea(archReporte, 60, '*');
    archReporte << "Paciente que mas gasto en una cita medica:" << setw(5) << ' ' << dniMax << endl;
    archReporte << "Monto gastado: " << setw(40) << pagoMax << endl;
    imprimirLinea(archReporte, 60, '*');
    archReporte << "Paciente que menos gasto en una cita medica:" << setw(3) << ' ' << dniMin << endl;
    archReporte << "Monto gastado: " << setw(40) << pagoMin << endl;
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(40) << ' ' << "EMPRESA DE SALUD S.A." << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(39) << ' ' << "REGISTRO DE CITAS MEDICAS" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "Fecha" << setw(10) << ' ' << "Paciente" << setw(4) << ' ' << "Inicio" << setw(7) << ' ' << "Fin" <<
            setw(7) << ' '
            << "Duracion" << setw(2) << ' ' << "% por Seguro" << setw(7) << ' ' << "Medico" << setw(27) << ' '
            << "Especialidad" << setw(5) << ' ' << "Pago (cita+medicinas)" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << fixed << setprecision(2);
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirDatos(ifstream &archMedicos, ofstream &archReporte, int dd, int mes, int anhio, int dni, double descuento,
                   int hhI, int minI, int ssI, int hhF, int minF, int ssF, int codMedico, double montoMedi,
                   double &pagoFinal) {
    int hh, min, ss, segundosTotales;
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(4) << ' ' << dni << setw(4) << ' ';
    imprimirHora(archReporte, hhI, minI, ssI);
    archReporte << setw(4) << ' ';
    imprimirHora(archReporte, hhF, minF, ssF);
    calcularDuracion(hhI, minI, ssI, hhF, minF, ssF, hh, min, ss, segundosTotales);
    archReporte << setw(4) << ' ';
    imprimirHora(archReporte, hh, min, ss);
    archReporte << right << setw(4) << ' ' << setw(5) << descuento << "%" << setw(4) << ' ';
    imprimirMedicos(archMedicos, archReporte, descuento, codMedico, montoMedi, segundosTotales, pagoFinal);
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void imprimirHora(ofstream &archReporte, int hh, int min, int ss) {
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void calcularDuracion(int hhI, int minI, int ssI, int hhF, int minF, int ssF, int &hh, int &min, int &ss,
                      int &segundosTotales) {
    int segundosIni = hhI * 3600 + minI * 60 + ssI;
    int segundosFin = hhF * 3600 + minF * 60 + ssF;
    segundosTotales = segundosFin - segundosIni;
    hh = segundosTotales / 3600;
    min = (segundosTotales % 3600) / 60;
    ss = segundosTotales % 60;
}

void imprimirMedicos(ifstream &archMedicos, ofstream &archReporte, double descuento, int codMedico,
                     double montoMedi, int segundosTotales, double &pagoFinal) {
    archMedicos.clear();
    archMedicos.seekg(0, ios::beg);
    int codMedicoArch;
    double tarifaHora;
    while (true) {
        archMedicos >> codMedicoArch;
        if (archMedicos.eof()) break;
        if (codMedicoArch == codMedico) {
            imprimirNombre(archMedicos, archReporte);
            archMedicos >> tarifaHora;
            calcularPago(segundosTotales, tarifaHora, descuento, montoMedi, pagoFinal);
            archReporte << setw(7) << pagoFinal << endl;
        } else {
            while (true) {
                if (archMedicos.get() == '\n') break;
            }
        }
    }
}

void imprimirNombre(ifstream &archMedicos, ofstream &archReporte) {
    bool mayus = true;
    int contador = 0;
    char c;
    archMedicos >> ws;
    while (true) {
        c = archMedicos.get();
        if (c == ' ')break;
        contador++;
        if (c == '_') {
            c = ' ';
            mayus = true;
        } else {
            if (mayus) {
                if (c >= 'a' and c <= 'z') {
                    c = c - 'a' + 'A';
                }
                mayus = false;
            } else {
                if (c >= 'A' and c <= 'Z') {
                    c = c - 'A' + 'a';
                }
            }
        }
        archReporte.put(c);
    }
    archReporte << setw(40 - contador) << ' ';
    imprimirEspecialidad(archMedicos, archReporte);
}

void imprimirEspecialidad(ifstream &archMedicos, ofstream &archReporte) {
    int contador = 0;
    char c;
    archMedicos >> ws;

    while (true) {
        c = archMedicos.get();
        if (c == ' ')break;
        contador++;
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        archReporte.put(c);
    }
    archReporte << setw(25 - contador) << ' ';
}

void calcularPago(int segundosTotales, double tarifaHora, double descuento, double montoMedi, double &pagoFinal) {
    double hh = (double) segundosTotales / 3600;
    double costoConsulta = hh * tarifaHora;

    double descuentoAplicado = (costoConsulta * (descuento / 100)) + (montoMedi * (descuento / 200));

    pagoFinal = costoConsulta + montoMedi - descuentoAplicado;
}

void calcularMayorMenor(int dni, double pagoFinal, int &dniMax, int &dniMin, double &pagoMax, double &pagoMin) {
    if (pagoFinal > pagoMax) {
        pagoMax = pagoFinal;
        dniMax = dni;
    }

    if (pagoFinal < pagoMin) {
        pagoMin = pagoFinal;
        dniMin = dni;
    }
}
