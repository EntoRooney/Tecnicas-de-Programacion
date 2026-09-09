#include <iostream>
#include <fstream>
#include <iomanip>

// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032

using namespace std;
#include "Bibliotecas/funciones.h"
//
//este programa genera una boleta a base de datos de streams y sus estadisticas usando
//la biblioteca fstream y además unicamente va a procesar datos dentro de una fecha limite
//la cual el usuario va a insertar manualmente junto con las tarifas dadas en la rubrica del laboratorio
//
int main() {
//abrimos los archivos
    ifstream archDatos("twitchdataTP.txt",ios::in);
    if (not archDatos.is_open()) {
        cout<<"ERROR, al abrir el archivo twitchdataTP.txt";
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"ERROR, al abrir el archivo Reporte.txt";
        exit(1);
    }
//invocamos los archivos para trabajarlos en el cpp
    imprimirReporte(archDatos,archReporte);

    return 0;
}