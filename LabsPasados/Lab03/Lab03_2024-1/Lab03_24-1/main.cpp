#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {

    ifstream archCitas("CitasMedicas_laboratorio3.txt",ios::in);
    if (not archCitas.is_open()) {
        cout<<"ERROR, el archivo CitasMedicas_laboratorio3.txt no se pudo abrir correctamente";
        exit(1);
    }

    ifstream archMedicos("Medicos_laboratorio3.txt",ios::in);
    if (not archMedicos.is_open()) {
        cout<<"ERROR, el archivo Medicos_laboratorio3.txt no se pudo abrir correctamente";
        exit(1);
    }

    ofstream archReporte("Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"ERROR, el archivo Reporte.txt no se pudo abrir correctamente";
        exit(1);
    }

    imprimirReporte(archCitas,archMedicos,archReporte);

    return 0;
}