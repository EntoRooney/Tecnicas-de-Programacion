#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by entol on 15/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte(ifstream &archInfracciones, ifstream &archDatosMultas, ofstream &archReporte) {
    int dni, num1, num2, dd, mes, anhio, codigoInfra, numCompania = 0, cantTotalLeves = 0, cantTotalGraves = 0,
            cantTotalMuyGraves = 0,dniMax,dniMin;
    double pagoTotal, multaTotalLeves = 0, multaTotalGraves = 0, multaTotalMuyGraves = 0,pagoMax=1,pagoMin=1000;
    char c, tipoVehi;
    imprimirEncabezado(archReporte);
    while (true) {
        int cantLeves = 0, cantGraves = 0, cantMuyGraves = 0;
        double multaLeves = 0, multaGraves = 0, multaMuyGraves = 0;
        archInfracciones >> dni;
        if (archInfracciones.eof()) break;
        numCompania++;
        leerNombre(archInfracciones, archReporte, dni, numCompania);
        imprimirEncabezadoMultas(archReporte);
        while (true) {
            archInfracciones >> tipoVehi >> num1 >> c >> num2 >> dd >> c >> mes >> c >> anhio >> codigoInfra;
            imprimirVehiculosInfraccionados(archDatosMultas, archReporte, tipoVehi, num1, num2, dd, mes, anhio,
                                            codigoInfra, cantLeves, cantGraves, cantMuyGraves,
                                            multaLeves, multaGraves, multaMuyGraves);
            archReporte << endl;
            if (archInfracciones.get() == '\n') break;
        }
        imprimirResumen(archReporte, cantLeves, cantGraves, cantMuyGraves, multaLeves, multaGraves,
                        multaMuyGraves, pagoTotal);
        calcularMayorMenor(pagoTotal,dni,pagoMax,dniMax,pagoMin,dniMin);
        cantTotalLeves += cantLeves;
        cantTotalGraves += cantGraves;
        cantTotalMuyGraves += cantMuyGraves;
        multaTotalLeves += multaLeves;
        multaTotalGraves += multaGraves;
        multaTotalMuyGraves += multaMuyGraves;
    }
    imprimirResumenFinal(archReporte, cantTotalLeves, cantTotalGraves, cantTotalMuyGraves, multaTotalLeves,
                         multaTotalGraves,multaTotalMuyGraves);
    imprimirEstadisticas(archReporte,pagoMax,dniMax,pagoMin,dniMin);
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(35) << " " << "MINISTERIO DE TRANSPORTE" << endl;
    archReporte << setw(32) << " " << "MULTAS IMPUESTAS A LAS COMPANIAS" << endl;
}

void leerNombre(ifstream &archInfracciones, ofstream &archReporte, int dni, int numCompania) {
    int contador = 0;
    char c;
    bool mayuscula = true;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << fixed << setprecision(2);
    archReporte << "COMPANIA No. " << numCompania << endl;
    archReporte << "REPRESENTANTE LEGAL: ";
    archInfracciones >> ws;
    while (true) {
        c = archInfracciones.get();
        if (c == ' ') break;
        contador++;
        if (c == '/' or c == '-') {
            c = ' ';
            mayuscula = true;
        } else {
            if (mayuscula) {
                if (c >= 'a' and c <= 'z') c = c - 'a' + 'A';
                mayuscula = false;
            } else {
                if (c >= 'A' and c <= 'Z') c = c - 'A' + 'a';
            }
        }
        archReporte.put(c);
    }
    archReporte << setw(40 - contador) << " " << "DNI: " << dni << endl;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte << c;
    }
    archReporte << endl;
}

void imprimirVehiculosInfraccionados(ifstream &archDatosMultas, ofstream &archReporte, char tipoVehi, int num1,
                                     int num2, int dd, int mes, int anhio, int codigoInfra,
                                     int &cantLeves, int &cantGraves, int &cantMuyGraves,
                                     double &multaLeves, double &multaGraves, double &multaMuyGraves) {
    archDatosMultas.clear();
    archDatosMultas.seekg(0, ios::beg);
    int codigoVerificacion;
    double multa;
    char gravedad;
    archReporte << "- " << num1 << num2 << tipoVehi << setw(5) << " ";
    imprimirTipoVehi(archReporte, tipoVehi);
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(5) << " ";
    while (true) {
        archDatosMultas >> gravedad;
        if (archDatosMultas.eof()) break;
        archDatosMultas >> codigoVerificacion;
        if (codigoVerificacion == codigoInfra) {
            archDatosMultas >> multa;
            imprimirInfraccion(archDatosMultas, archReporte, codigoInfra, gravedad, multa);
            calcularCantFaltas(gravedad, multa, cantLeves, cantGraves, cantMuyGraves,
                               multaLeves, multaGraves, multaMuyGraves);
        } else {
            while (true) {
                if (archDatosMultas.get() == '\n') break;
            }
        }
    }
}

void imprimirTipoVehi(ofstream &archReporte, char tipoVehi) {
    if (tipoVehi == 'P') {
        archReporte << "PEQUENO" << setw(5) << " ";
    } else if (tipoVehi == 'M') {
        archReporte << "MEDIANO" << setw(5) << " ";
    } else {
        archReporte << "GRANDE" << setw(6) << " ";
    }
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio
            << setfill(' ');
}

void imprimirInfraccion(ifstream &archDatosMultas, ofstream &archReporte, int codigoInfra, char gravedad,
                        double multa) {
    archReporte << codigoInfra << setw(5) << " ";;
    imprimirGravedad(archReporte, gravedad);
    archReporte << right << setw(8) << multa << setw(5) << " ";
    imprimirDescripcion(archDatosMultas, archReporte);
}

void imprimirGravedad(ofstream &archReporte, char gravedad) {
    if (gravedad == 'L') {
        archReporte << "LEVE" << setw(7) << " ";
    } else if (gravedad == 'G') {
        archReporte << "GRAVE" << setw(6) << " ";
    } else {
        archReporte << "MUY GRAVE" << setw(2) << " ";
    }
}

void imprimirDescripcion(ifstream &archDatosMultas, ofstream &archReporte) {
    char c;
    archDatosMultas >> ws;
    while (true) {
        c = archDatosMultas.get();
        if (c == '\n') break;
        archReporte.put(c);
    }
}

void imprimirEncabezadoMultas(ofstream &archReporte) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "VEHICULOS INFRACCIONADOS:" << endl;
    archReporte << setw(1) << " " << "PLACA" << setw(8) << " " << "TIPO" << setw(10) << " " << "FECHA"
            << setw(4) << " " << "INFRACCION" << setw(2) << " " << "GRAVEDAD" << setw(6) << " " << "MULTA"
            << setw(6) << " " << "DESCRIPCION" << endl;
}

void calcularCantFaltas(char gravedad, double multa, int &cantLeves, int &cantGraves, int &cantMuyGraves,
                        double &multaLeves, double &multaGraves, double &multaMuyGraves) {
    if (gravedad == 'L') {
        cantLeves++;
        multaLeves += multa;
    } else if (gravedad == 'G') {
        cantGraves++;
        multaGraves += multa;
    } else {
        cantMuyGraves++;
        multaMuyGraves += multa;
    }
}

void imprimirResumen(ofstream &archReporte, int cantLeves, int cantGraves, int cantMuyGraves,
                     double multaLeves, double multaGraves, double multaMuyGraves, double &pagoTotal) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(19) << " " << "CANTIDAD" << setw(7) << " " << "MONTO PAGADO" << endl;
    archReporte << "FALTAS LEVES:" << setw(10) << " " << cantLeves << setw(10) << " " << setw(8) << multaLeves << endl;
    archReporte << "FALTAS GRAVES:" << setw(9) << " " << cantGraves << setw(10) << " " << setw(8) << multaGraves <<
            endl;
    archReporte << "FALTAS MUY GRAVES:" << setw(5) << " " << cantMuyGraves << setw(10) << " " << setw(8)
            << multaMuyGraves << endl;
    imprimirLinea(archReporte,48, '-');
    pagoTotal = multaLeves + multaGraves + multaMuyGraves;
    archReporte << "PAGO TOTAL :" << setw(22) << " " << setw(8) << pagoTotal << endl;
}

void imprimirResumenFinal(ofstream &archReporte, int cantTotalLeves, int cantTotalGraves, int cantTotalMuyGraves,
                          double multaTotalLeves, double multaTotalGraves, double multaTotalMuyGraves) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "TOTAL RECAUDADO POR INFRACCIONES" << endl;
    archReporte << setw(19) << " " << "CANTIDAD" << setw(7) << " " << "MONTO PAGADO" << endl;
    archReporte << "FALTAS LEVES:" << setw(11) << " " << cantTotalLeves << setw(10) << " " << setw(9) << multaTotalLeves
            << endl;
    archReporte << "FALTAS GRAVES:" << setw(9) << " " << cantTotalGraves << setw(10) << " " << setw(9) <<
            multaTotalGraves <<
            endl;
    archReporte << "FALTAS MUY GRAVES:" << setw(5) << " " << cantTotalMuyGraves << setw(10) << " " << setw(9)
            << multaTotalMuyGraves << endl;
    double pagoTotal = multaTotalLeves + multaTotalGraves + multaTotalMuyGraves;
    archReporte << "PAGO TOTAL :" << setw(24) << " " << setw(8) << pagoTotal << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}

void calcularMayorMenor(double pagoTotal,int dni,double &pagoMax,int &dniMax,double &pagoMin,int &dniMin) {

    if (pagoTotal<pagoMin) {
        pagoMin=pagoTotal;
        dniMin=dni;
    }

    if (pagoTotal>pagoMax) {
        pagoMax=pagoTotal;
        dniMax=dni;
    }
}

void imprimirEstadisticas(ofstream &archReporte,double pagoMax,int dniMax,double pagoMin,int dniMin) {
    imprimirLinea(archReporte,45, '/');
    archReporte<<"//COMPANIA CON MAYOR PAGO POR INFRACCIONES:"<<setw(2)<<"//"<<endl;
    archReporte<<"//DNI: "<<setw(11)<<" "<<dniMax<<setw(19)<<"//"<<endl;
    archReporte<<"//TOTAL PAGADO: "<<setw(10)<<pagoMax<<setw(19)<<"/"<<endl;
    archReporte<<"//COMPANIA CON MENOR PAGO POR INFRACCIONES:"<<setw(2)<<"//"<<endl;
    archReporte<<"//DNI: "<<setw(11)<<" "<<dniMin<<setw(19)<<"//"<<endl;
    archReporte<<"//TOTAL PAGADO: "<<setw(10)<<pagoMin<<setw(19)<<"//"<<endl;
    imprimirLinea(archReporte,45, '/');
}