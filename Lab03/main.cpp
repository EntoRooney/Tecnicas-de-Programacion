#include <iostream>
#include <fstream>
#include <iomanip>
//Ento Lazaro
//20222032
using namespace std;
#include "Bibliotecas/funciones.h"
int main() {
    //ESTE PROGRAMA CALCULA LAS ETIQUETAS DE UN CANAL Y ADEMÁS CALCULAR LOS TIEMPOS DE REPRODUCCION Y LOS COSTOS
    //MEDIANTE C++ Y FULL FSTREAM 
    ifstream archCanales("Canales.txt",ios::in);
    if (not archCanales.is_open()) {
        cout<<"ERROR, el archivo Canales.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archEtiquetas("Etiquetas.txt",ios::in);
    if (not archEtiquetas.is_open()) {
        cout<<"ERROR, el archivo Etiquetas.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archRepro("ReproduccionesDeEtiquetas.txt",ios::in);
    if (not archRepro.is_open()) {
        cout<<"ERROR, el archivo ReproduccionesDeEtiquetas.txt no se pudo abrir correctamente";
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"ERROR, el archivo Reporte.txt no se pudo abrir correctamente";
        exit(1);
    }

    imprimirReporte(archCanales,archEtiquetas,archRepro,archReporte);

    return 0;
}