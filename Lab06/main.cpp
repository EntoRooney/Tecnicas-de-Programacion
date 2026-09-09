#include <iostream>
#include <fstream>
#include <iomanip>
#define TAM_CAT 120
#define  TAM_STR 450

using namespace std;
#include "Bibliotecas/funciones.h"

int main() {
    //Definimos los arreglos
    //Para categorias
    int cantCategorias = 0;
    char *arrCodCat[TAM_CAT]{}, *arrNombCat[TAM_CAT]{};
    leerArrCategorias(arrCodCat, arrNombCat, cantCategorias);
    imprimirReporteCat(arrCodCat, arrNombCat, cantCategorias);

    //Para streams
    int arrFecha[TAM_STR]{}, arrDuracion[TAM_STR]{}, cantStreams = 0;
    double arrRatingStream[TAM_STR]{}, arrTasaDOffStream[TAM_STR]{};
    char *arrNombCanal[TAM_STR]{}, *arrCodCate[TAM_STR]{};
    leerArrStreams(arrFecha, arrNombCanal, arrCodCate, arrRatingStream, arrTasaDOffStream, arrDuracion, cantStreams);
    imprimirReporteStream(arrFecha, arrNombCanal, arrCodCate, arrRatingStream, arrTasaDOffStream, arrDuracion,
                          cantStreams);

    imprimirReportes(arrCodCat, arrNombCat, cantCategorias,
                     arrFecha, arrNombCanal, arrCodCate, arrRatingStream, arrTasaDOffStream, arrDuracion, cantStreams);

    return 0;
}
