#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {

    ifstream archInfracciones("InfraccionesCometidas.txt",ios::in);
    if (not archInfracciones.is_open()) {
        cout << "Error al abrir el archivo InfraccionesCometidas.txt" << endl;
        exit(1);
    }

    ifstream archDatosMultas("InfraccionesDeTransito.txt",ios::in);
    if (not archDatosMultas.is_open()) {
        cout << "Error al abrir el archivo InfraccionesDeTransito.txt" << endl;
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo Reporte.txt" << endl;
        exit(1);
    }

    imprimirReporte(archInfracciones,archDatosMultas,archReporte);

    return 0;
}