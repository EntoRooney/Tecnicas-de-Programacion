#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 2/11/2025.
//
#include "funciones.h"
#define TAM_MAX 120

void leerArrRepartidores(int *arrDniRepartidor, char * *arrNombreRepartidor, char * *arrVehiRepartidor,
                         int *arrCodDistRepartidor, char * *arrDistritoRepartidor, int &cantRepartidores) {
    ifstream archRepartidores;
    abrirArchivosIfstream("ArchivosDeDatos/lab7_Repartidores.txt", archRepartidores);
    int i = 0;
    char nombre[100], vehiculo[50], distrito[50];
    //24721987      Ramirez_Astete_Karina_Estefania     Bicicleta     6092     Punta_Hermosa
    while (true) {
        archRepartidores >> arrDniRepartidor[i];
        if (archRepartidores.eof()) break;

        archRepartidores >> nombre;
        modificarTexto(nombre, false);
        arrNombreRepartidor[i] = new char [strlen(nombre) + 1];
        strcpy(arrNombreRepartidor[i], nombre);

        archRepartidores >> vehiculo;
        modificarTexto(vehiculo, true);
        arrVehiRepartidor[i] = new char [strlen(vehiculo) + 1];
        strcpy(arrVehiRepartidor[i], vehiculo);

        archRepartidores >> arrCodDistRepartidor[i];

        archRepartidores >> distrito;
        modificarTexto(distrito, false);
        arrDistritoRepartidor[i] = new char [strlen(distrito) + 1];
        strcpy(arrDistritoRepartidor[i], distrito);
        i++;
    }
    cantRepartidores = i;
}

void abrirArchivosIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchivosOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void modificarTexto(char *texto, bool pasarMayus) {
    for (int i = 0; texto[i]; i++) {
        if (texto[i] == '_') {
            texto[i] = ' ';
        }
        if (pasarMayus) {
            if (texto[i] >= 'a' and texto[i] <= 'z') {
                texto[i] -= ('a' - 'A');
            }
        }
    }
}

void leerArrPlatos(int *arrCodPlato, char **arrNombrePlato, double *arrPrecioPlato, char **arrCategoriaPlato,
                   double *arrDescPlato, int &cantPlatos) {
    ifstream archPlatos;
    abrirArchivosIfstream("ArchivosDeDatos/lab7_PlatosOfrecidos.txt", archPlatos);
    //77894    ENSALADA_SENSACION_GRANDE_CON_POLLO   32.90      ENSALADAS   5.74%
    int i = 0;
    char c, nombre[100], categoria[50];
    while (true) {
        archPlatos >> arrCodPlato[i];
        if (archPlatos.eof()) break;

        archPlatos >> nombre;
        modificarTexto(nombre, false);
        arrNombrePlato[i] = new char [strlen(nombre) + 1];
        strcpy(arrNombrePlato[i], nombre);

        archPlatos >> arrPrecioPlato[i];

        archPlatos >> categoria;
        arrCategoriaPlato[i] = new char [strlen(categoria) + 1];
        strcpy(arrCategoriaPlato[i], categoria);

        if (archPlatos.peek() != '\n') {
            archPlatos >> arrDescPlato[i] >> c;
        }
        i++;
    }
    cantPlatos = i;
}

void imrprimirReportePrueba(int *arrCodPlato, char **arrNombrePlato, double *arrPrecioPlato, char **arrCategoriaPlato,
                            double *arrDescPlato, int cantPlatos,
                            int *arrDniRepartidor, char * *arrNombreRepartidor, char * *arrVehiRepartidor,
                            int *arrCodDistRepartidor, char * *arrDistritoRepartidor, int cantRepartidores) {
    ofstream archReporte;
    abrirArchivosOfstream("ArchivosDeReporte/ReporteDePrueba.txt", archReporte);
    imprimirEncabezadoPlatos(archReporte);
    for (int i = 0; i < cantPlatos; i++) {
        archReporte << arrCodPlato[i] << setw(5) << ' ' << arrNombrePlato[i] <<
                setw(50 - strlen(arrNombrePlato[i])) << ' ' << setw(7) << arrPrecioPlato[i] <<
                setw(5) << ' ' << arrCategoriaPlato[i] << setw(26 - strlen(arrCategoriaPlato[i])) << ' ' <<
                setw(5) << arrDescPlato[i] << "%" << endl;
    }
    imprimirEncabezadoRepartidores(archReporte);
    for (int i = 0; i < cantRepartidores; i++) {
        archReporte << arrDniRepartidor[i] << setw(5) << ' ' << arrNombreRepartidor[i] <<
                setw(50 - strlen(arrNombreRepartidor[i])) << ' ' << arrVehiRepartidor[i] <<
                setw(20 - strlen(arrVehiRepartidor[i])) << ' ' << arrCodDistRepartidor[i] <<
                setw(5) << ' ' << arrDistritoRepartidor[i] << endl;
    }
}


void imprimirEncabezadoPlatos(ofstream &archReporte) {
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(41) << ' ' << "REPORTE PARA PLATOS" << endl;
    archReporte << "CODIGO" << setw(16) << ' ' << "NOMBRE" << setw(34) << ' ' << "PRECIO" << setw(5) << ' ' << "CATEGORIA"
            << setw(15) << ' ' << "DESCUENTO" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirEncabezadoRepartidores(ofstream &archReporte) {
    archReporte << endl;
    archReporte << setw(40) << ' ' << "REPORTE PARA REPARTIDORES" << endl;
    archReporte << setw(2) << ' '<< "DNI" << setw(17) << ' ' << "NOMBRE" << setw(36) << ' ' << "VEHICULO" << setw(5) << ' ' <<
            "CODIGO DISTRITO" << setw(3) << ' ' << "DISTRITO" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}
