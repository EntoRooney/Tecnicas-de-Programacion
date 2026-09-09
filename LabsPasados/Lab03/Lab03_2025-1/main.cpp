#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {

    ifstream archEmpresas("EmpresasRegistradas.txt",ios::in);
    if (not archEmpresas.is_open()) {
        cout<<"ERROR, el archivo EmpresasRegistradas.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archInfracciones("InfraccionesCometidas.txt",ios::in);
    if (not archInfracciones.is_open()) {
        cout<<"ERROR, el archivo InfraccionesCometidas.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archTabla("TablaDeInfracciones.txt",ios::in);
    if (not archTabla.is_open()) {
        cout<<"ERROR, el archivo TablaDeInfracciones.txt no se pudo abrir correctamente";
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"ERROR, el archivo Reporte.txt no se pudo abrir correctamente";
        exit(1);
    }

    imprimirReporte(archEmpresas,archInfracciones,archTabla,archReporte);

    return 0;
}