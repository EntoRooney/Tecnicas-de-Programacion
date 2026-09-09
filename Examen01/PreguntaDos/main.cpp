// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "Bibliotecas/funciones.h"
#define TAM_STREAM 120
//programa lo mismo de la pregunta 1 pero son arrelos estaticos
int main() {
    int arrCodStream[TAM_STREAM]{}, arrDuracion[TAM_STREAM]{}, arrIdioma[TAM_STREAM]{}, arrNumCate[TAM_STREAM]{},
            cantStreams = 0;
    char arrCodCate[TAM_STREAM]{};

    leerArrStreams(arrCodStream, arrDuracion, arrIdioma, arrCodCate, arrNumCate, cantStreams);
    imprimirReporteSimple(arrCodStream, arrDuracion, arrIdioma, arrCodCate, arrNumCate, cantStreams);

    int arrFechaPrime[TAM_STREAM]{}, arrFechaUlti[TAM_STREAM]{}, arrCantRepro[TAM_STREAM]{}, arrTotalRepro[TAM_STREAM]
            {};
    double arrPromRati[TAM_STREAM]{}, arrPromTasa[TAM_STREAM]{};
    actualizarArr(arrCodStream, arrDuracion, arrIdioma, arrCodCate, arrNumCate, cantStreams,
                  arrFechaPrime, arrFechaUlti, arrPromRati, arrPromTasa, arrCantRepro, arrTotalRepro);

    imprimirReporte(arrCodStream, arrDuracion, arrIdioma, arrCodCate, arrNumCate, cantStreams,
                  arrFechaPrime, arrFechaUlti, arrPromRati, arrPromTasa, arrCantRepro, arrTotalRepro);
    return 0;
}
