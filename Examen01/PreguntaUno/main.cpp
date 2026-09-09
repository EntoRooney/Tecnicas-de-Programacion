
// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "Bibliotecas/funciones.h"


int main() {
    //este programa busca desde los streams que canales lo han reproducido, calculando su duracion y los promedios de las
    //tarifas , por ultimo hacemos un resumen de los tasaDrops menores y mayores para ponerlo como estadisticas
    ifstream archCanales,archCategorias,archIdiomas,archStreams;
    ofstream archReporte;
    abrirArchIfstream("ArchivosDeDatos/Canales.txt",archCanales);
    abrirArchIfstream("ArchivosDeDatos/Categorias.txt",archCategorias);
    abrirArchIfstream("ArchivosDeDatos/Idiomas.txt",archIdiomas);
    abrirArchIfstream("ArchivosDeDatos/Streams.txt",archStreams);
    abrirArchOfstream("ArchivosDeReporte/Reporte.txt",archReporte);

    imprimirReporte(archCanales,archCategorias,archIdiomas,archStreams,archReporte);

    return 0;
}