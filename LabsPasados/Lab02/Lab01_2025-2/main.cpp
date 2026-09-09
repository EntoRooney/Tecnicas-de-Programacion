#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {
    ifstream archDatos("twitchdataTP.txt", ios::in);
    if (not archDatos.is_open()) {
        cout << "Error, el archivo twitchdataTP.txt no se pudo abrir correctamente" << endl;
        exit(1);
    }

    ofstream archReporte("Reporte.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "Error, el archivo Reporte.txt no se pudo abrir correctamente" << endl;
        exit(1);
    }

    imprimirReporte(archDatos,archReporte);

    return 0;
}
