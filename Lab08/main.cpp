#include <fstream>
#include <iostream>
#include <iomanip>
//Ento Rooney Lazaro Trujillo
//20222032
using namespace std;
#include "Bibliotecas/funciones.h"
#define MAX_CAT 150
//En este programa usaremos estructuras dinamicas para hallar primero de un archivo csv, el nombre
//de una categoria junto a codigo y su descripcion.
//En segundo lugar, mediante el archivo de Streams reproducidos. Hallaremos el nombre del canal cuyo
//codigo de categoria coincida para ponerlo en nuestro reporte, junto con su rating y duracion
//esto lo haremos usando la libreria cstring.
//Y por ultimo, con el ultimo archivo de comentarios, hallaremos los comentarios de cada canal
//usando nuevamente la libreia cstring junto con cadenas dinamicas.
int main() {
    struct Categoria *arrCategorias;
    arrCategorias = new struct Categoria[MAX_CAT]{};
    int cantidadCategorias = 0;

    leerArrCategorias(arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt", arrCategorias,
                          cantidadCategorias, false, false);

    leerStreamsRepro(arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", arrCategorias,
                          cantidadCategorias, true, false);

    ordenarPorNombreCat(arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePruebaOrdenado.txt", arrCategorias,
                          cantidadCategorias, true, false);

    leerComentariosCanal(arrCategorias, cantidadCategorias);
    imprimirReportePrueba("ArchivosDeReporte/ReporteDePruebaConComentarios.txt", arrCategorias,
                          cantidadCategorias, true, true);
    return 0;
}
