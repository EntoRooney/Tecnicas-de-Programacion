#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"
#define TAM_PLATOS 120

int main() {
    ifstream archPlatos("ArchivosDeDatos/lab4_PlatosOfrecidos.txt", ios::in);
    if (not archPlatos.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/lab4_PlatosOfrecidos.txt no se pudo abrir correctamente";
        exit(1);
    }

    int arrCodigo[TAM_PLATOS]{},cantPlatos=0;
    double arrPrecio[TAM_PLATOS]{};

    leerPlatos(archPlatos, arrCodigo, arrPrecio,cantPlatos);

    ifstream archRepartos("ArchivosDeDatos/lab4_RepartosARealizar.txt", ios::in);
    if (not archRepartos.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/lab4_RepartosARealizar.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archRepartidores("ArchivosDeDatos/lab4_Repartidores.txt", ios::in);
    if (not archRepartidores.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/lab4_Repartidores.txt no se pudo abrir correctamente";
        exit(1);
    }

    ofstream archReporte("ArchivosDeReporte/Reporte.txt", ios::out);

    imprimirReporte(archRepartidores,archRepartos,archReporte,arrCodigo,arrPrecio,cantPlatos);

    return 0;
}
