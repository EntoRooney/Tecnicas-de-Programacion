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

void leerArrLibros(int *arrCodLibro, double *arrPrecLibro, int &cantLibros) {
    ifstream archLibros;
    abrirArchIfstream("ArchivosDeDatos/libros.txt", archLibros);
    int i = 0;

    while (true) {
        archLibros >> arrCodLibro[i];
        if (archLibros.eof()) break;
        eliminarTexto(archLibros, true, ']');
        eliminarTexto(archLibros, true, '*');
        archLibros >> arrPrecLibro[i];
        i++;
    }
    cantLibros = i;
    ordenarArrLibros(arrCodLibro, arrPrecLibro, cantLibros);
}

void abrirArchIfstream(const char *nombArch, ifstream &archLibros) {
    archLibros.open(nombArch, ios::in);
    if (not archLibros.good()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void eliminarTexto(ifstream &arch, bool comerPrimera, char delim) {
    arch >> ws;
    char c, bsr;

    while (true) {
        if (comerPrimera) {
            bsr = arch.get();
            comerPrimera = false;
        }
        c = arch.get();
        if (c == delim) break;
    }
}

void ordenarArrLibros(int *arrCodLibro, double *arrPrecLibro, int cantLibros) {
    for (int i = 0; i < cantLibros - 1; i++) {
        for (int j = i + 1; j < cantLibros; j++) {
            if (arrPrecLibro[i] > arrPrecLibro[j]) {
                cambiarInt(arrCodLibro[i], arrCodLibro[j]);
                cambiarDouble(arrPrecLibro[i], arrPrecLibro[j]);
            }
        }
    }
}

void cambiarInt(int &arrIntX, int &arrIntJ) {
    int aux = arrIntX;
    arrIntX = arrIntJ;
    arrIntJ = aux;
}

void cambiarDouble(double &arrIntX, double &arrIntJ) {
    double aux = arrIntX;
    arrIntX = arrIntJ;
    arrIntJ = aux;
}

void imprimirReporte(int *arrCodLibro, double *arrPrecLibro, int cantLibros) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/ReporteSimple.txt", archReporte);
    archReporte << setw(1) << ' ' << "REPORTE DE VENTAS POR LIBRO" << endl;
    archReporte << setw(1) << ' ' << "#" << setw(6) << ' ' << "LIBRO" << setw(5) << ' ' << "PRECIO" << endl;
    imprimirLinea(archReporte, 40, '-');
    archReporte << right << fixed << setprecision(2);

    int j = 0;
    for (int i = 0; i < cantLibros; i++) {
        j++;
        archReporte << setfill('0') << setw(3) << j << ")" << setfill(' ') << setw(3) << ' ' << arrCodLibro[i] <<
                setw(4) << ' ' << setw(6) << arrPrecLibro[i] << endl;
    }
}

void abrirArchOfstream(const char *nombArch, ofstream &archReporte) {
    archReporte.open(nombArch, ios::out);
    if (not archReporte.good()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void leerArrVentas(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                   double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti, int *arrDniUlti,
                   int cantLibros) {
    ifstream archVentas;
    abrirArchIfstream("ArchivosDeDatos/Ventas.txt", archVentas);
    int libreria, dd, mes, anhio, codLibro, dniCli, califi, idLibro, fechaConvertida;
    char c;
    while (true) {
        archVentas >> libreria;
        if (archVentas.eof()) break;
        archVentas >> dd >> c >> mes >> c >> anhio;
        calcularFecha(dd, mes, anhio, fechaConvertida);
        while (true) {
            archVentas >> codLibro >> dniCli >> califi;
            idLibro = buscarIdLibro(codLibro, arrCodLibro, cantLibros);
            if (idLibro >= 0) {
                arrCantVendidas[idLibro]++;
                arrPromCalif[idLibro] += califi;
                arrTotalVentas[idLibro] += arrPrecLibro[idLibro];
                if (arrFechaPrime[idLibro] == 0 or fechaConvertida < arrFechaPrime[idLibro]) {
                    arrFechaPrime[idLibro] = fechaConvertida;
                    arrDniPrime[idLibro] = dniCli;
                }
                if (arrFechaUlti[idLibro] == 0 or fechaConvertida > arrFechaUlti[idLibro]) {
                    arrFechaUlti[idLibro] = fechaConvertida;
                    arrDniUlti[idLibro] = dniCli;
                }
            }
            if (archVentas.get() == '\n')break;
        }
    }
    for (int i = 0; i < cantLibros; i++) {
        if (arrCantVendidas[i] > 0) {
            arrPromCalif[i] /= arrCantVendidas[i];
        }
    }
}

int buscarIdLibro(int codLibro, int *arrCodLibro, int cantLibros) {
    for (int i = 0; i < cantLibros; i++) {
        if (arrCodLibro[i] == codLibro) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}


void calcularFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void imprimiReporte(const char *nomArch, int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas,
                    double *arrPromCalif,
                    double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                    int *arrDniUlti, int cantLibros) {
    ofstream archReporte;
    abrirArchOfstream(nomArch, archReporte);
    imprimirEncabezado(archReporte);

    int j = 0, totalCant = 0;
    double totalVendido = 0;
    for (int i = 0; i < cantLibros; i++) {
        j++;
        archReporte << setfill('0') << setw(3) << j << ")" << setfill(' ')
                << setw(3) << ' ' << arrCodLibro[i] << setw(4) << ' ' << setw(6) << arrPrecLibro[i]
                << setw(4) << ' ' << setw(6) << arrCantVendidas[i];
        if (arrCantVendidas[i] == 0) {
            archReporte << setw(18) << ' ' << setw(6) << "-"
                    << setw(10) << ' ' << setw(8) << arrTotalVentas[i] << setw(4) << ' ' << setw(6) << "-" <<
                    setw(4) << ' ' << setw(6) << "-" << setw(4) << ' ' << setw(6) << "-" << setw(4) << ' ' <<
                    setw(6) << "-" << endl;
        } else {
            archReporte << setw(18) << ' ' << setw(6) << arrPromCalif[i] << setw(10) << ' ' << setw(8) <<
                    arrTotalVentas[i] << setw(4) << ' ';
            imprimirFecha(archReporte, arrFechaPrime[i]);
            archReporte << setw(4) << ' ' << arrDniPrime[i] << setw(4) << ' ';
            imprimirFecha(archReporte, arrFechaUlti[i]);
            archReporte << setw(4) << ' ' << setw(6) << arrDniUlti[i] << endl;
        }
        totalCant += arrCantVendidas[i];
        totalVendido += arrTotalVentas[i];
    }
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << "TOTALES:" << setw(23) << ' ' << setw(3) << totalCant << setw(35) << ' ' << setw(6)
            << totalVendido << endl;
    imprimirLinea(archReporte, TAM_MAX, '=');
}

void imprimirFecha(ofstream &archReporte, int arrFechaPrime) {
    int anhio = arrFechaPrime / 10000;
    int mes = (arrFechaPrime % 10000) / 100;
    int dd = arrFechaPrime % 100;
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(34) << ' ' << "REPORTE DE VENTAS POR LIBRO" << endl;
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << setw(1) << ' ' << "#" << setw(6) << ' ' << "LIBRO" << setw(5) << ' ' << "PRECIO"
            << setw(2) << ' ' << "UNIDADES.VENDIDAS" << setw(5) << ' ' << "PROM.CALIFICACION" << setw(5) <<
            ' ' << "TOT.VENTAS" << setw(5) << ' ' << "PRIMERA. VENTA" << setw(12) << ' ' << "ULTIMA. VENTA" << endl;
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << right << fixed << setprecision(2);
}

void ordenarFinal(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                  double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                  int *arrDniUlti, int cantLibros) {
    for (int i = 0; i < cantLibros - 1; i++) {
        for (int j = i + 1; j < cantLibros; j++) {
            if ((arrCantVendidas[i] < arrCantVendidas[j]) or
                (arrCantVendidas[i] == arrCantVendidas[j] and arrPromCalif[i] > arrPromCalif[j])) {
                cambiarInt(arrCodLibro[i], arrCodLibro[j]);
                cambiarInt(arrCantVendidas[i], arrCantVendidas[j]);
                cambiarDouble(arrPromCalif[i], arrPromCalif[j]);
                cambiarDouble(arrTotalVentas[i], arrTotalVentas[j]);
                cambiarDouble(arrPrecLibro[i], arrPrecLibro[j]);
                cambiarInt(arrFechaPrime[i], arrFechaPrime[j]);
                cambiarInt(arrDniPrime[i], arrDniPrime[j]);
                cambiarInt(arrFechaUlti[i], arrFechaUlti[j]);
                cambiarInt(arrDniUlti[i], arrDniUlti[j]);
            }
        }
    }
}

void eliminarArr(int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                 double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                 int *arrDniUlti, int &cantLibros) {
    int i = 0;
    while (i < cantLibros) {
        if (arrCantVendidas[i] == 0) {
            eliminarArrLibro(i, arrCodLibro, arrPrecLibro, arrCantVendidas, arrPromCalif, arrTotalVentas, arrFechaPrime,
                             arrDniPrime, arrFechaUlti, arrDniUlti, cantLibros);
        } else {
            i++;
        }
    }
}

void eliminarArrLibro(int i, int *arrCodLibro, double *arrPrecLibro, int *arrCantVendidas, double *arrPromCalif,
                      double *arrTotalVentas, int *arrFechaPrime, int *arrDniPrime, int *arrFechaUlti,
                      int *arrDniUlti, int &cantLibros) {
    for (int z = i; z < cantLibros - 1; z++) {
        arrCodLibro[z] = arrCodLibro[z + 1];
        arrPrecLibro[z] = arrPrecLibro[z + 1];
        arrCantVendidas[z] = arrCantVendidas[z + 1];
        arrPromCalif[z] = arrPromCalif[z + 1];
        arrTotalVentas[z] = arrTotalVentas[z + 1];
        arrFechaPrime[z] = arrFechaPrime[z + 1];
        arrDniPrime[z] = arrDniPrime[z + 1];
        arrFechaUlti[z] = arrFechaUlti[z + 1];
        arrDniUlti[z] = arrDniUlti[z + 1];
    }
    cantLibros--;
}
