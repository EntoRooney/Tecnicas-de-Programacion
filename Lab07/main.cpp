#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
//Nombre: Ento Rooney Lazaro Trujillo
//Codigo: 20222032
using namespace std;
#include "Bibliotecas/funciones.h"
#include "Bibliotecas/Categoria .h"
#include "Bibliotecas/Reproduccion .h"
#define MAX_CAT 120

int main() {
    //En este codigo usaremos estructuras estaticas junto con cadenas de caracteres tambien estaticas
    //leyendo archivos .csv que nos permiten hacer un reporte de categorias
    //teniendo su codigo, nombre y los canales que han reproducido dicha categoria
    //cuyo cada canal tiene su nombre, rating y duracion
    //finalmente tenemos las estadisticas finales de promedio de rating y duracion total
    //usaremos tambien la libreai cstring para hacer busquedas

    struct Categoria arrCategorias[MAX_CAT]{};
    int cantidadCategorias = 0;

    leerCategorias("ArchivosDeDatos/Categorias.csv", arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePuebaDeCategorias.txt", arrCategorias, cantidadCategorias,
                          false);

    leerStreams("ArchivosDeDatos/Reproducciones.csv", arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", arrCategorias, cantidadCategorias,
                          true);

    calcularPromedios(arrCategorias, cantidadCategorias);
    imprimirReporte("ArchivosDeReporte/ReportePorCategorias.txt", arrCategorias, cantidadCategorias);

    return 0;
}
