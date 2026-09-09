#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {

    ifstream archClientes("lab3_RepartosRealizados.txt",ios::in);
    if (not archClientes.is_open()) {
        cout<<"ERROR, el archivo lab3_RepartosRealizados.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archPlatos("lab3_PlatosOfrecidos.txt",ios::in);
    if (not archPlatos.is_open()) {
        cout<<"ERROR, el archivo lab3_PlatosOfrecidos.txt no se pudo abrir correctamente";
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"ERROR, el archivo Reporte.txt no se pudo abrir correctamente";
        exit(1);
    }

    imprimirReporte(archClientes,archPlatos,archReporte);
    return 0;
}