#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by entol on 22/09/2025.
//

#include "funciones.h"
#define TAM_MAX 220

void imprimirReporte(ifstream &archEmpresas, ifstream &archInfracciones, ifstream &archTabla, ofstream &archReporte) {
    imprimirEncabezado(archReporte);
    int dni, numCompania = 0, num1, num2, cantTotal = 0, dniMayor, dniMenor;
    double multaMayor = 1, multaMenor = 1000000, multaFinal = 0;
    char c, carTipoVehi;
    while (true) {
        int nroPlaca = 0, cantLeves = 0, cantGraves = 0, cantMuyGraves = 0, cantTotales;
        double multaLeves = 0, multaGraves = 0, multaMuyGraves = 0, multaTotales;
        archEmpresas >> dni;
        if (archEmpresas.eof()) break;
        numCompania++;
        leerNombre(archEmpresas, archReporte, dni, numCompania);
        while (true) {
            archEmpresas >> carTipoVehi >> num1 >> c >> num2;
            nroPlaca++;
            imprimirPlacas(archInfracciones, archTabla, archReporte, carTipoVehi, num1, num2, nroPlaca,
                           cantLeves, multaLeves, cantGraves, multaGraves, cantMuyGraves, multaMuyGraves);
            if (archEmpresas.get() == '\n') break;
        }
        imprimirEstadisticas(archReporte, cantLeves, multaLeves, cantGraves, multaGraves, cantMuyGraves,
                             multaMuyGraves, cantTotales, multaTotales);
        calcularMayorMenor(dni, multaTotales, multaMayor, dniMayor, multaMenor, dniMenor);
        cantTotal += cantTotales;
        multaFinal += multaTotales;
    }
    imprimirEstadisticasFinales(archReporte, cantTotal, multaFinal, multaMayor, dniMayor, multaMenor, dniMenor);
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(40) << ' ' << "MINISTERIO DE TRANSPORTE" << endl;
    archReporte << setw(37) << ' ' << "MULTAS IMPUESTAS A LAS COMPANIAS" << endl;
    archReporte << fixed << setprecision(2);
}

void leerNombre(ifstream &archEmpresas, ofstream &archReporte, int dni, int numCompania) {
    char c;
    int contador = 0;
    bool mayus = true;

    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "COMPANIA No. " << numCompania << endl;
    archReporte << "REPRESENTANTE LEGAL: ";
    archEmpresas >> ws;

    while (true) {
        c = archEmpresas.get();
        if (c == ' ')break;
        contador++;
        if (c == '/' or c == '-') {
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
    archReporte << setw(40 - contador) << ' ' << "DNI: " << dni << setw(10) << ' ' << "DISTRITO: ";
    leerDistrito(archEmpresas, archReporte);
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void leerDistrito(ifstream &archEmpresas, ofstream &archReporte) {
    char c;
    int contador = 0;
    bool mayus = true;
    archEmpresas >> ws;
    while (true) {
        c = archEmpresas.get();
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
    archReporte << endl;
    archEmpresas >> ws;
}

void imprimirPlacas(ifstream &archInfracciones, ifstream &archTabla, ofstream &archReporte, char carTipoVehi,
                    int num1, int num2, int nroPlaca, int &cantLeves, double &multaLeves, int &cantGraves,
                    double &multaGraves,
                    int &cantMuyGraves, double &multaMuyGraves) {
    archInfracciones.clear();
    archInfracciones.seekg(0, ios::beg);
    imprimirEncabezadoPlacas(archReporte, nroPlaca, carTipoVehi, num1, num2);
    imprimirTipo(archReporte, carTipoVehi);
    int dd, mes, anhio, num1Arch, num2Arch, numInfra, nroInfraccion = 0;
    char c, carTipoVehiArch, codInfra;
    imprimirEncabezadoDatos(archReporte);
    while (true) {
        archInfracciones >> dd;
        if (archInfracciones.eof()) break;
        archInfracciones >> c >> mes >> c >> anhio >> ws;
        archInfracciones >> carTipoVehiArch >> num1Arch >> c >> num2Arch >> ws;
        if (carTipoVehi == carTipoVehiArch and num1 == num1Arch and num2 == num2Arch) {
            archInfracciones >> codInfra >> numInfra;
            nroInfraccion++;
            imprimirDatos(archTabla, archReporte, dd, mes, anhio, codInfra, numInfra, nroInfraccion,
                          cantLeves, multaLeves, cantGraves, multaGraves, cantMuyGraves, multaMuyGraves);
        } else {
            while (true) {
                if (archInfracciones.get() == '\n') break;
            }
        }
    }
    if (nroInfraccion == 0) {
        archReporte << setw(20) << "---------------NO HAY INFRACCIONES----------------" << setw(20) << endl;
    }
}

void imprimirEncabezadoPlacas(ofstream &archReporte, int nroPlaca, char carTipoVehi, int num1, int num2) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "VEHICULOS INFRACCIONADOS:" << endl;
    archReporte << setw(2) << ' ' << setfill('0') << setw(2) << nroPlaca << setfill(' ') << ")" << setw(3) <<
            ' ' << "PLACA: " << carTipoVehi << num1 << "-" << num2 << setw(5) << ' ' << "TIPO: ";
}

void imprimirTipo(ofstream &archReporte, char carTipoVehi) {
    if (carTipoVehi == 'P') {
        archReporte << "PEQUENO";
    } else if (carTipoVehi == 'M') {
        archReporte << "MEDIANO";
    } else {
        archReporte << "GRANDE";
    }
    archReporte << endl;
}

void imprimirDatos(ifstream &archTabla, ofstream &archReporte, int dd, int mes, int anhio, char codInfra,
                   int numInfra, int nroInfraccion, int &cantLeves, double &multaLeves, int &cantGraves,
                   double &multaGraves, int &cantMuyGraves, double &multaMuyGraves) {
    archReporte << setw(5) << ' ' << setfill('0') << setw(2) << nroInfraccion << setfill(' ') << ")" <<
            setw(5) << ' ';
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(7) << ' ' << numInfra << setw(8) << ' ';
    imprimirGravedad(archReporte, codInfra);
    imprimirMulta(archTabla, archReporte, codInfra, numInfra, cantLeves, multaLeves, cantGraves, multaGraves,
                  cantMuyGraves, multaMuyGraves);
    archReporte << endl;
}

void imprimirEncabezadoDatos(ofstream &archReporte) {
    archReporte << setw(5) << ' ' << "No." << setw(5) << ' ' << "FECHA" << setw(9) << ' ' << "INFRACCION" << setw(4)
            << ' ' << "GRAVEDAD" << setw(6) << ' ' << "MULTA" << setw(5) << ' ' << "DESCRIPCIÓN" << endl;
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void imprimirGravedad(ofstream &archReporte, char codInfra) {
    if (codInfra == 'L') {
        archReporte << "LEVE" << setw(8) << ' ';
    } else if (codInfra == 'G') {
        archReporte << "GRAVE" << setw(7) << ' ';
    } else {
        archReporte << "MUY GRAVE" << setw(3) << ' ';
    }
}

void imprimirMulta(ifstream &archTabla, ofstream &archReporte, char codInfra, int numInfra, int &cantLeves,
                   double &multaLeves, int &cantGraves, double &multaGraves, int &cantMuyGraves,
                   double &multaMuyGraves) {
    archTabla.clear();
    archTabla.seekg(0, ios::beg);
    bool encontrado = false;
    char codInfraArch;
    double multa;
    int numInfraArch;
    while (true) {
        archTabla >> codInfraArch;
        if (archTabla.eof()) break;
        archTabla >> numInfraArch >> multa >> ws;
        if (codInfra == codInfraArch and numInfraArch == numInfra) {
            archReporte << right << setw(7) << multa << setw(5) << ' ';
            imprimirDescripcion(archTabla, archReporte);
            encontrado = true;
            calcularCantidad(codInfra, multa, cantLeves, multaLeves, cantGraves, multaGraves, cantMuyGraves,
                             multaMuyGraves);
        } else {
            while (true) {
                if (archTabla.get() == '\n') break;
            }
        }
    }
    if (!encontrado) {
        archReporte << "---------No hay multa--------------" << endl;
    }
}

void imprimirDescripcion(ifstream &archTabla, ofstream &archReporte) {
    char c;

    archTabla >> ws;

    while (true) {
        c = archTabla.get();
        if (c == '\n')break;
        archReporte.put(c);
    }
}

void calcularCantidad(char codInfra, double multa, int &cantLeves, double &multaLeves, int &cantGraves,
                      double &multaGraves,
                      int &cantMuyGraves, double &multaMuyGraves) {
    if (codInfra == 'L') {
        cantLeves++;
        multaLeves += multa;
    } else if (codInfra == 'G') {
        cantGraves++;
        multaGraves += multa;
    } else {
        cantMuyGraves++;
        multaMuyGraves += multa;
    }
}

void imprimirEstadisticas(ofstream &archReporte, int cantLeves, double multaLeves, int cantGraves, double multaGraves,
                          int cantMuyGraves, double multaMuyGraves, int &cantTotales, double &multaTotales) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    cantTotales = cantLeves + cantGraves + cantMuyGraves;
    multaTotales = multaLeves + multaGraves + multaMuyGraves;
    archReporte << setw(21) << ' ' << "CANTIDAD" << setw(8) << ' ' << "MONTO PAGADO" << endl;
    archReporte << "FALTA LEVES:" << setw(14) << cantLeves << setw(20) << multaLeves << endl;
    archReporte << "FALTA GRAVES:" << setw(13) << cantGraves << setw(20) << multaGraves << endl;
    archReporte << "FALTA MUY GRAVES:" << setw(9) << cantMuyGraves << setw(20) << multaMuyGraves << endl;
    imprimirLinea(archReporte, 50, '-');
    archReporte << "TOTAL:" << setw(20) << cantTotales << setw(20) << multaTotales << endl;
}

void imprimirEstadisticasFinales(ofstream &archReporte, int cantTotal, double multaFinal, double multaMayor,
                                 int dniMayor,
                                 double multaMenor, int dniMenor) {
    imprimirLinea(archReporte, 60, '*');
    archReporte << "CANTIDADES TOTALES:" << setw(7) << cantTotal << setw(20) << multaFinal << endl;
    imprimirLinea(archReporte, 60, '*');
    imprimirLinea(archReporte, 45, '+');
    archReporte << "+ COMPANIA CON MAYOR PAGO POR INFRACCIONES: +" << endl;
    archReporte << "+ DNI:" << setw(29) << dniMayor << setw(10) << "+" << endl;
    archReporte << "+ TOTAL PAGADO:" << setw(20) << multaMayor << setw(10) << "+" << endl;
    imprimirLinea(archReporte, 45, '+');
    archReporte << "+ COMPANIA CON MENOR PAGO POR INFRACCIONES: +" << endl;
    archReporte << "+ DNI:" << setw(29) << dniMenor << setw(10) << "+" << endl;
    archReporte << "+ TOTAL PAGADO:" << setw(20) << multaMenor << setw(10) << "+" << endl;
    imprimirLinea(archReporte, 45, '+');
}

void calcularMayorMenor(int dni, double multaTotales, double &multaMayor, int &dniMayor, double &multaMenor,
                        int &dniMenor) {
    if (multaTotales > multaMayor) {
        multaMayor = multaTotales;
        dniMayor = dni;
    }

    if (multaTotales < multaMenor) {
        multaMenor = multaTotales;
        dniMenor = dni;
    }
}
