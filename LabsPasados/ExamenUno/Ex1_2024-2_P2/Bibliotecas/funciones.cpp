#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 12/10/2025.
//

#include "funciones.h"
#define NO_ENCONTRADO -1
#define TAM_MAX 120

void leerArrPlatos(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato, int &cantPlatos) {
    ifstream archPlatos;
    abrirArchIfstream("ArchivosDeDatos/PlatosOfrecidos (1).txt", archPlatos);
    int i = 0;
    char c;
    while (true) {
        archPlatos >> arrCodPlato[i];
        if (archPlatos.eof()) break;
        eliminarTexto(archPlatos, '}');
        archPlatos >> arrPrecioPlato[i];
        archPlatos >> arrCantStock[i];
        if (archPlatos.get() != '\n') {
            archPlatos >> arrDescPlato[i] >> c;
        } else {
            arrDescPlato[i] = 0;
        }
        i++;
    }
    cantPlatos = i;
}

void abrirArchIfstream(const char *nomArch, ifstream &arch) {
    arch.open(nomArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nomArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void eliminarTexto(ifstream &arch, char deli) {
    char c;
    arch >> ws;
    while (true) {
        c = arch.get();
        if (c == deli) break;
    }
}

void leerArrCliente(int *arrDniCliente, double *arrDescCliente, int &cantCliente) {
    ifstream archCli;
    abrirArchIfstream("ArchivosDeDatos/Clientes.txt", archCli);
    int i = 0, bsr;
    char c, siNo;

    while (true) {
        archCli >> arrDniCliente[i];
        if (archCli.eof()) break;
        eliminarTexto(archCli, ']');
        archCli >> bsr;
        eliminarTexto(archCli, ' ');
        archCli >> ws >> c >> ws >> siNo;
        if (siNo == 'S') {
            archCli >> arrDescCliente[i] >> c;
        } else {
            arrDescCliente[i] = 0;
        }
        i++;
    }
    cantCliente = i;
}

void imprimirReporteSimple(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                           int cantPlatos, int *arrDniCliente, double *arrDescCliente, int cantCliente) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/ReporteSimple.txt", archReporte);
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(10) << ' ' << "REPORTE PARA PLATOS" << endl;
    archReporte << "CODIGO" << setw(4) << ' ' << "PRECIO" << setw(5) << ' ' << "CANTIDAD" << setw(2) << ' ' <<
            "DESCUENTO" << endl;
    for (int i = 0; i < cantPlatos; i++) {
        archReporte << arrCodPlato[i] << setw(5) << ' ' << setw(6) << arrPrecioPlato[i] << setw(5) << ' ' << setw(5) <<
                arrCantStock[i] << setw(6) << ' ' << setw(5) << arrDescPlato[i] << endl;
    }
    archReporte << endl;
    archReporte << setw(1) << ' ' << "REPORTE PARA CLIENTES" << endl;
    archReporte << setw(2) << ' ' << "DNI" << setw(7) << ' ' << "DESCUENTO" << endl;
    for (int i = 0; i < cantCliente; i++) {
        archReporte << arrDniCliente[i] << setw(5) << ' ' << setw(6) << arrDescCliente[i] << endl;
    }
}

void abrirArchOfstream(const char *nomArch, ofstream &arch) {
    arch.open(nomArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nomArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void llenarArrFinales(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato, int cantPlatos,
                      int *arrDniCliente, double *arrDescCliente, int cantCliente, int *arrPlatoAtendido,
                      int *arrPlatoNoAtendido,
                      double *arrMontoEsperado, double *arrMontoBruto, double *arrMontoRecibido) {
    ifstream archRepartos;
    abrirArchIfstream("ArchivosDeDatos/RepartosARealizar (1).txt", archRepartos);
    int bsr, dniCliArch, idCliente, cant, codPlato, idPlato, cantFalta = 0;
    double pagoRecibido;
    for (int i = 0; i < cantPlatos; i++) {
        arrMontoEsperado[i] = arrPrecioPlato[i] * arrCantStock[i];
    }
    while (true) {
        archRepartos >> bsr;
        if (archRepartos.eof()) break;
        archRepartos >> dniCliArch;
        idCliente = buscarIdCliente(dniCliArch, arrDniCliente, cantCliente);
        if (idCliente != NO_ENCONTRADO) {
            while (true) {
                archRepartos >> cant >> codPlato;
                idPlato = buscarIdPlato(codPlato, arrCodPlato, cantPlatos);
                if (idPlato != NO_ENCONTRADO) {
                    int cantPedida = cant;
                    int cantAtendida, cantNoAtendida;
                    if (arrPlatoAtendido[idPlato] + cant <= arrCantStock[idPlato]) {
                        cantAtendida = cantPedida;
                        cantNoAtendida = 0;
                        arrPlatoAtendido[idPlato] += cantAtendida;
                    } else {
                        cantAtendida = arrCantStock[idPlato] - arrPlatoAtendido[idPlato];
                        cantNoAtendida = cantPedida - cantAtendida;
                        arrPlatoAtendido[idPlato] += cantAtendida;
                        arrPlatoNoAtendido[idPlato] += cantNoAtendida;
                    }
                    arrMontoBruto[idPlato] += cantAtendida * arrPrecioPlato[idPlato];
                    pagoRecibido = cantAtendida * arrPrecioPlato[idPlato] * (1 - arrDescPlato[idPlato] / 100);
                    pagoRecibido *= (1 - arrDescCliente[idCliente] / 100.0);
                    arrMontoRecibido[idPlato] += pagoRecibido;
                }
                if (archRepartos.get() == '\n') break;
            }
        }
    }
}


int buscarIdCliente(int dniCliArch, int *arrDniCliente, int cantCliente) {
    for (int i = 0; i < cantCliente; i++) {
        if (arrDniCliente[i] == dniCliArch) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

int buscarIdPlato(int codPlato, int *arrCodPlato, int cantPlatos) {
    for (int i = 0; i < cantPlatos; i++) {
        if (arrCodPlato[i] == codPlato) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void ordenarCantPlatos(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                       int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                       double *arrMontoRecibido, int cantPlatos) {
    for (int i = 0; i < cantPlatos - 1; i++) {
        for (int j = i + 1; j < cantPlatos; j++) {
            if (arrCantStock[i] < arrCantStock[j]) {
                cambiarInt(arrCodPlato[i], arrCodPlato[j]);
                cambiarDou(arrPrecioPlato[i], arrPrecioPlato[j]);
                cambiarDou(arrDescPlato[i], arrDescPlato[j]);
                cambiarInt(arrCantStock[i], arrCantStock[j]);
                cambiarInt(arrPlatoAtendido[i], arrPlatoAtendido[j]);
                cambiarInt(arrPlatoNoAtendido[i], arrPlatoNoAtendido[j]);
                cambiarDou(arrMontoEsperado[i], arrMontoEsperado[j]);
                cambiarDou(arrMontoBruto[i], arrMontoBruto[j]);
                cambiarDou(arrMontoRecibido[i], arrMontoRecibido[j]);
            }
        }
    }
}

void cambiarInt(int &arrI, int &arrJ) {
    int aux = arrI;
    arrI = arrJ;
    arrJ = aux;
}

void cambiarDou(double &arrI, double &arrJ) {
    double aux = arrI;
    arrI = arrJ;
    arrJ = aux;
}

void imprimirReporte(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                     int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                     double *arrMontoRecibido, int cantPlatos) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/ReporteDeRelacionDePlatos.txt", archReporte);
    double totalEsperado = 0, totalBruto = 0, totalRecibido = 0;
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(30) << ' ' << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    archReporte << setw(34) << ' ' << "RELACION DE PLATOS VENDIDOS" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(25) << ' ' << "CANTIDAD DE PLATOS" << setw(33) << ' ' << "MONTOS RECAUDADOS" << endl;
    archReporte <<
            "CODIGO" << setw(5) << ' ' <<
            "PRECIO" << setw(2) << ' ' <<
            "PREPARADOS" << setw(2) << ' ' <<
            "ATENDIDOS" << setw(1) << ' ' <<
            "NO ATENDIDOS" << setw(1) << ' ' <<
            "DESCUENTO" << setw(5) << ' ' <<
            "ESPERADO" << setw(6) << ' ' <<
            "BRUTO" << setw(7) << ' ' <<
            "RECIBIDO" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
    for (int i = 0; i < cantPlatos; i++) {
        archReporte << arrCodPlato[i]
                << setw(5) << ' ' << setw(6) << arrPrecioPlato[i]
                << setw(3) << ' ' << setw(5) << arrCantStock[i]
                << setw(7) << ' ' << setw(5) << arrPlatoAtendido[i]
                << setw(5) << ' ' << setw(6) << arrPlatoNoAtendido[i]
                << setw(7) << ' ' << setw(6) << arrDescPlato[i]
                << setw(7) << ' ' << setw(8) << arrMontoEsperado[i]
                << setw(5) << ' ' << setw(8) << arrMontoBruto[i]
                << setw(5) << ' ' << setw(8) << arrMontoRecibido[i] << endl;
        totalEsperado += arrMontoEsperado[i];
        totalBruto += arrMontoBruto[i];
        totalRecibido += arrMontoRecibido[i];
    }
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(50) << ' ' << "TOTALES" << setw(10) << ' ' << setw(9) << totalEsperado
            << setw(3) << ' ' << setw(10) << totalBruto << setw(4) << ' ' << setw(9) << totalRecibido << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}

void imprimirLinea(ofstream &arch, int can, char c) {
    for (int i = 0; i < can; i++) {
        arch.put(c);
    }
    arch << endl;
}

void eliminarArr(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                 int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                 double *arrMontoRecibido, int &cantPlatos) {
    int n = 0;
    while (n < cantPlatos) {
        if (arrPlatoNoAtendido[n] == 0) {
            eliminarElemento(n, arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato,
                             arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido,
                             cantPlatos);
        } else {
            n++;
        }
    }
}

void eliminarElemento(int n,int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                       int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                       double *arrMontoRecibido, int &cantPlatos) {
    for (int i=n; i < cantPlatos-1; i++) {
        arrCodPlato[i]=arrCodPlato[i+1];
        arrPrecioPlato[i]=arrPrecioPlato[i+1];
        arrCantStock[i]=arrCantStock[i+1];
        arrDescPlato[i]=arrDescPlato[i+1];
        arrPlatoAtendido[i]=arrPlatoAtendido[i+1];
        arrPlatoNoAtendido[i]=arrPlatoNoAtendido[i+1];
        arrMontoEsperado[i]=arrMontoEsperado[i+1];
        arrMontoBruto[i]=arrMontoBruto[i+1];
        arrMontoRecibido[i]=arrMontoRecibido[i+1];
    }
    cantPlatos--;
}

void  imprimirReporteEliminado(int *arrCodPlato, double *arrPrecioPlato, int *arrCantStock, double *arrDescPlato,
                     int *arrPlatoAtendido, int *arrPlatoNoAtendido, double *arrMontoEsperado, double *arrMontoBruto,
                     double *arrMontoRecibido, int cantPlatos) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/ReporteDePlatosConDeficit.txt", archReporte);
    double totalEsperado = 0, totalBruto = 0, totalRecibido = 0;
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(30) << ' ' << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    archReporte << setw(34) << ' ' << "RELACION DE PLATOS VENDIDOS" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(25) << ' ' << "CANTIDAD DE PLATOS" << setw(33) << ' ' << "MONTOS RECAUDADOS" << endl;
    archReporte <<
            "CODIGO" << setw(5) << ' ' <<
            "PRECIO" << setw(2) << ' ' <<
            "PREPARADOS" << setw(2) << ' ' <<
            "ATENDIDOS" << setw(1) << ' ' <<
            "NO ATENDIDOS" << setw(1) << ' ' <<
            "DESCUENTO" << setw(5) << ' ' <<
            "ESPERADO" << setw(6) << ' ' <<
            "BRUTO" << setw(7) << ' ' <<
            "RECIBIDO" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
    for (int i = 0; i < cantPlatos; i++) {
        archReporte << arrCodPlato[i]
                << setw(5) << ' ' << setw(6) << arrPrecioPlato[i]
                << setw(3) << ' ' << setw(5) << arrCantStock[i]
                << setw(7) << ' ' << setw(5) << arrPlatoAtendido[i]
                << setw(5) << ' ' << setw(6) << arrPlatoNoAtendido[i]
                << setw(7) << ' ' << setw(6) << arrDescPlato[i]
                << setw(7) << ' ' << setw(8) << arrMontoEsperado[i]
                << setw(5) << ' ' << setw(8) << arrMontoBruto[i]
                << setw(5) << ' ' << setw(8) << arrMontoRecibido[i] << endl;
        totalEsperado += arrMontoEsperado[i];
        totalBruto += arrMontoBruto[i];
        totalRecibido += arrMontoRecibido[i];
    }
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(50) << ' ' << "TOTALES" << setw(10) << ' ' << setw(9) << totalEsperado
            << setw(3) << ' ' << setw(10) << totalBruto << setw(4) << ' ' << setw(9) << totalRecibido << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}