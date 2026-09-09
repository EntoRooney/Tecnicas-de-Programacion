#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 21/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte(ifstream &archClientes, ifstream &archPlatos, ofstream &archReporte) {
    int codigoPlato,cantFinal=0;
    double precio,montoFinal=0;
    int cantMayor=1,cantMenor=1000000,codigoPlatoMax,codigoPlatoMin,codigoPlatoCantMax, codigoPlatoCantMin;
    double montoMayor=1,montoMenor=1000000;
    imprimirEncabezado(archReporte);
    while (true) {
        archPlatos >> codigoPlato;
        if (archPlatos.eof()) break;
        leerNombre(archPlatos, archReporte, codigoPlato, precio);
        imprimirRepartidores(archClientes, archReporte, codigoPlato, precio,montoFinal,cantFinal,
        montoMayor,cantMayor,montoMenor,cantMenor,codigoPlatoMax,codigoPlatoMin,codigoPlatoCantMax, codigoPlatoCantMin);
    }
    imprimirLinea(archReporte,TAM_MAX,'=');
    archReporte<<"TOTAL RECAUDADO"<<setw(17)<<' '<<cantFinal<<setw(6)<<' '<<setw(10)<<montoFinal<<endl;
    imprimirLinea(archReporte,50,'+');
    archReporte<<"Maximo:"<<endl;
    archReporte<<"Cantidad"<<setw(20)<<' '<<cantMayor<<setw(6)<<' '<<setw(10)<<codigoPlatoCantMax<<endl;
    archReporte<<"Monto"<<setw(20)<<' '<<montoMayor<<setw(5)<<' '<<setw(10)<<codigoPlatoMax<<endl;
    archReporte<<"Minimo:"<<endl;
    archReporte<<"Cantidad"<<setw(22)<<' '<<cantMenor<<setw(6)<<' '<<setw(10)<<codigoPlatoCantMin<<endl;
    archReporte<<"Monto"<<setw(21)<<' '<<montoMenor<<setw(6)<<' '<<setw(10)<<codigoPlatoMin<<endl;
    imprimirLinea(archReporte,50,'+');
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(20) << ' ' << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    archReporte << fixed << setprecision(2);
}

void leerNombre(ifstream &archPlatos, ofstream &archReporte, int codigoPlato, double &precio) {
    char c;
    int contador = 0;
    bool mayuscula = true;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "CODIGO: " << codigoPlato << setw(6) << ' ' << "DESCRIPCION: ";
    archPlatos >> ws;
    while (true) {
        c = archPlatos.get();
        if (c == ' ') break;
        contador++;
        if (c == '_' or c == '-') {
            c = ' ';
            mayuscula = true;
        } else {
            if (mayuscula) {
                if (c >= 'a' and c <= 'z') {
                    c = c - 'a' + 'A';
                }
                mayuscula = false;
            } else {
                if (c >= 'A' and c <= 'Z') {
                    c = c - 'A' + 'a';
                }
            }
        }
        archReporte.put(c);
    }
    archPlatos >> precio;
    archReporte << right << setw(44 - contador) << ' ' << "PRECIO: " << setw(6) << precio << setw(5) << ' ' << "TIPO: ";
    leerTipo(archPlatos, archReporte);
}


void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void leerTipo(ifstream &archPlatos, ofstream &archReporte) {
    char c;
    int contador = 0;
    bool mayuscula = true;
    archPlatos >> ws;
    while (true) {
        c = archPlatos.get();
        if (c == '\n') break;
        contador++;
        if (c == '_') {
            c = ' ';
            mayuscula = true;
        } else {
            if (mayuscula) {
                if (c >= 'a' and c <= 'z') {
                    c = c - 'a' + 'A';
                }
                mayuscula = false;
            } else {
                if (c >= 'A' and c <= 'Z') {
                    c = c - 'A' + 'a';
                }
            }
        }
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirRepartidores(ifstream &archClientes, ofstream &archReporte, int codigoPlato, double precio,
                          double &montoFinal,
                          int &cantFinal, double &montoMayor, int &cantMayor, double &montoMenor, int &cantMenor,
                          int &codigoPlatoMax, int &codigoPlatoMin,
                          int &codigoPlatoCantMax, int &codigoPlatoCantMin) {
    archClientes.clear();
    archClientes.seekg(0, ios::beg);
    int codRepartidor, hh, min, ss, cant, codigoPlatoArch, cantTotal = 0;
    double monto, montoTotal = 0;
    char c;
    imprimirEncabezadoRepartidores(archReporte);
    while (true) {
        archClientes >> codRepartidor;
        if (archClientes.eof()) break;
        eliminarNombre(archClientes);
        archClientes >> hh >> c >> min >> c >> ss;

        while (true) {
            archClientes >> cant >> codigoPlatoArch;
            if (codigoPlato == codigoPlatoArch) {
                imprimirDatos(archReporte, codRepartidor, hh, min, ss, cant, precio, monto,
                              cantTotal, montoTotal);

            }
            if (archClientes.get() == '\n') break;
        }
    }
    montoFinal+=montoTotal;
    cantFinal+=cantTotal;
    calcularMayorMenor(montoTotal,cantTotal,montoMayor,cantMayor,montoMenor,
                    cantMenor,codigoPlato,
                    codigoPlatoMax,codigoPlatoMin,codigoPlatoCantMax,
                    codigoPlatoCantMin);
    imprimirTotales(archReporte, montoTotal, cantTotal);

}

void eliminarNombre(ifstream &archClientes) {
    char c;
    archClientes >> ws;

    while (true) {
        archClientes.get(c);
        if (c == ' ')break;
    }
}

void imprimirDatos(ofstream &archReporte, int codRepartidor, int hh, int min, int ss, int cant, double precio,
                   double &monto, int &cantTotal, double &montoTotal) {
    monto = cant * precio;
    cantTotal += cant;
    montoTotal += monto;
    archReporte << codRepartidor << setw(10) << ' ';
    imprimirHora(archReporte, hh, min, ss);
    archReporte << setw(8) << ' ' << setw(2) << cant << setw(9) << ' ' << setw(6) << monto << endl;
}

void imprimirEncabezadoRepartidores(ofstream &archReporte) {
    archReporte << "REPARTOS REALIZADOS" << endl;
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << "REPARTIDOR" << setw(5) << ' ' << "HORA DE PARTIDA" << setw(2) << ' ' << "CANTIDAD" << setw(3) << ' '
            <<
            "TOTAL PAGADO" << endl;
}

void imprimirHora(ofstream &archReporte, int hh, int min, int ss) {
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void imprimirTotales(ofstream &archReporte, double montoTotal, int cantTotal) {
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << "TOTAL:" << setw(27) << ' ' << setw(3) << cantTotal << setw(8) << ' ' << setw(7) << montoTotal <<
            endl;
}

void  calcularMayorMenor(double montoTotal,int cantTotal,double &montoMayor,int &cantMayor,double &montoMenor,int &cantMenor,int codigoPlato,
                    int &codigoPlatoMax,int &codigoPlatoMin,int &codigoPlatoCantMax, int &codigoPlatoCantMin) {

    if (montoTotal<montoMenor) {
        montoMenor = montoTotal;
        codigoPlatoMin = codigoPlato;
    }

    if (montoTotal>montoMayor) {
        montoMayor = montoTotal;
        codigoPlatoMax = codigoPlato;
    }

    if (cantTotal<cantMenor) {
        cantMenor = cantTotal;
        codigoPlatoCantMin = codigoPlato;
    }

    if (cantTotal>cantMayor) {
        cantMayor = cantTotal;
        codigoPlatoCantMax = codigoPlato;
    }
}
