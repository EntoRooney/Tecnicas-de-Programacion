#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 28/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void leerPlatos(ifstream &archPlatos, int *arrCodigo, double *arrPrecio, int &cantPlatos) {
    int i = 0;

    while (true) {
        archPlatos >> arrCodigo[i];
        if (archPlatos.eof()) break;
        eliminarTexto(archPlatos);
        archPlatos >> arrPrecio[i];
        eliminarTexto(archPlatos);
        i++;
    }
    cantPlatos = i;
}

void eliminarTexto(ifstream &archPlatos) {
    char c;
    archPlatos >> ws;
    while (true) {
        c = archPlatos.get();
        if (c == ' ' or c == '\n')break;
    }
}

void imprimirReporte(ifstream &archRepartidores, ifstream &archRepartos, ofstream &archReporte, int *arrCodigo,
                     double *arrPrecio, int cantPlatos) {
    int dni, distrito, numRepartidor = 1;
    char vehi;
    imprimirEncabezado(archReporte);
    while (true) {
        archRepartidores >> dni;
        if (archRepartidores.eof()) break;
        imprimirEncabezadoClientes(archReporte, numRepartidor);
        leerTexto(archRepartidores, archReporte, ' ', 40, false, vehi);
        archReporte<<dni<<setw(5)<<' ';
        leerTexto(archRepartidores, archReporte, ' ', 20, true, vehi);
        archRepartidores >> distrito;
        archReporte<<distrito<<setw(3)<<' ';
        leerTexto(archRepartidores, archReporte, '\n', 20, false, vehi);
        archReporte << endl;
    }
}

void leerTexto(ifstream &archRepartidores, ofstream &archReporte, char fin, int ancho, bool guardarPrimera,
               char &primera) {
    archRepartidores >> ws;
    char c;
    int contador = 0;
    bool primeraGuardada = false;

    while (true) {
        c = archRepartidores.get();

        if (c == fin or c == '\n') break;

        if (guardarPrimera and not primeraGuardada) {
            primera = c;
            primeraGuardada = true;
        }
        contador++;

        if (c == '/' or c == '-') c = ' ';
        if (c >= 'a' and c <= 'z') c = c - 'a' + 'A';

        archReporte.put(c);
    }
    archReporte << setw(ancho - contador) << ' ';
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(40) << ' ' << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    archReporte << setw(20) << ' ' << "ENTREGAS QUE DEBEN REALIZAR LOS REPARTIDORES" << endl;
}

void imprimirEncabezadoClientes(ofstream &archReporte, int &numRepartidor) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte<<setfill('0')<<setw(2)<<numRepartidor <<setfill(' ')<<" REPARTIDOR:"<<endl;
    archReporte<<setw(4)<<' '<<"NOMBRE"<<setw(34)<<' '<<"DNI"<<setw(11)<<' '<<"VEHICULO"
    <<setw(11)<<' '<<"DISTRIO A ATENDER"<<endl;
    archReporte<<setw(4)<<' ';
    numRepartidor++;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}
