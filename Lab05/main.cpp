#include <iostream>
#include <fstream>
#include <iomanip>
//Ento Rooney Lazaro Trujillo
//20222032

using namespace std;
#include "Bibliotecas/funciones.h"
#define TAM_STREAM 150

int main() {
    //descripcion del programa
    //En este programa calculamos las duraciones de un stream, las fechas más recientes y más antiguas
    //junto a sus promedios de rating y promedios de Dropp, además de la cantidad de reproducciones usando
    //1.arreglos estaticos que lo sacamos del archivo de stream.txt usando el metodo de insertar ordenada
    //2.actualizamos los arreglos que definimos en el main usando la busqueda binaria
    //3.usamos la funcion reporte para el reporte final y despues ordenamos usando el metodo burbuja con las condiciones
    //4.reusamos la funcion reporte para el nuevo reporte ordenado
    int arrCodigoStream[TAM_STREAM]{}, arrDuracionStrem[TAM_STREAM]{}, arrIdiomaStream[TAM_STREAM]{},
            arrNumCateStream[TAM_STREAM]{}, cantStreams = 0;
    char arrCarCateStream[TAM_STREAM]{};
    leerArrStreams(arrCodigoStream, arrDuracionStrem, arrIdiomaStream, arrCarCateStream, arrNumCateStream, cantStreams);
    imprimirReportePrueba(arrCodigoStream, arrDuracionStrem, arrIdiomaStream, arrCarCateStream, arrNumCateStream,
                          cantStreams);

    int arrFechaMasAntigua[TAM_STREAM]{}, arrFechaMasReciente[TAM_STREAM]{}, arrNumRepro[TAM_STREAM]{}, arrDuracionTotal
            [TAM_STREAM]{};
    double arrPromRat[TAM_STREAM]{}, arrPromDrop[TAM_STREAM]{};
    leerArrCanales(arrCodigoStream, arrIdiomaStream, arrCarCateStream, arrNumCateStream, arrDuracionStrem,
                   arrFechaMasAntigua, arrFechaMasReciente, arrPromRat, arrPromDrop, arrNumRepro, arrDuracionTotal,
                   cantStreams);

    imprimirReporte("ArchivosDeReporte/Reproducciones_Streams.txt", true, arrCodigoStream, arrIdiomaStream,
                    arrCarCateStream, arrNumCateStream, arrDuracionStrem,
                    arrFechaMasAntigua, arrFechaMasReciente, arrPromRat, arrPromDrop, arrNumRepro, arrDuracionTotal,
                    cantStreams);

    ordenarArr(arrCodigoStream, arrIdiomaStream, arrCarCateStream, arrNumCateStream, arrDuracionStrem,
               arrFechaMasAntigua, arrFechaMasReciente, arrPromRat, arrPromDrop, arrNumRepro, arrDuracionTotal,
               cantStreams);

    imprimirReporte(
        "ArchivosDeReporte/DETALLE COMPLETO DE REPRODUCCIONES DE STREAMS ORDENADO POR IDIOMA Y TASA DROP-OFF.txt",
        false,
        arrCodigoStream, arrIdiomaStream,
        arrCarCateStream, arrNumCateStream, arrDuracionStrem,
        arrFechaMasAntigua, arrFechaMasReciente, arrPromRat, arrPromDrop, arrNumRepro, arrDuracionTotal,
        cantStreams);

    return 0;
}
