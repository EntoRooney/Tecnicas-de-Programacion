#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"
#include "Bibliotecas/Facultad.h"
#include "Bibliotecas/Alumno.h"


int main() {
    struct Alumno arrAlumnos[100]{};
    int cantAlumnos = 0;

    procesarCalificaciones("ArchivosDeDatos/Calificaciones.txt", arrAlumnos, cantAlumnos);

    completarAlumnos("ArchivosDeDatos/alumnos.csv", arrAlumnos, cantAlumnos);

    leerFacultades("ArchivosDeDatos/facultades.txt",arrAlumnos, cantAlumnos);

    imprimirReporte("ArchivosDeReporte/ReporteDePagoPorAlumno.txt",arrAlumnos, cantAlumnos);

    return 0;
}
