#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/funciones.h"
#define CANALES_MAX 120
#define ETIQUETAS_MAX 120
#define REPRO_MAX 120
//PONER LOS DATOS Y LO Q HACE MI PROGRAMA++
int main() {
    int arrFecha[CANALES_MAX]{}, arrNumCod[CANALES_MAX]{},cantCanales=0;
    double arrRating[CANALES_MAX]{};
    char arrCodigo[CANALES_MAX]{};

    leerCanales(arrFecha,arrCodigo,arrNumCod,arrRating,cantCanales);


    int arrEtiquetas[ETIQUETAS_MAX]{},arrDuracionMin[ETIQUETAS_MAX]{},arrDuracionSeg[ETIQUETAS_MAX]{},cantEtiquetas=0;
    leerEtiquetas(arrEtiquetas,arrDuracionMin,arrDuracionSeg,cantEtiquetas);


    emitirReporteCanales(arrFecha,arrCodigo,arrNumCod,arrRating,cantCanales);
    emitirReporteEtiquetas(arrEtiquetas,arrDuracionMin,arrDuracionSeg,cantEtiquetas);

    int arrNumRepro[REPRO_MAX]{},arrSegundosTotales[REPRO_MAX]{};
    emitirReporte(arrFecha,arrCodigo,arrNumCod,arrRating,cantCanales,arrEtiquetas,arrDuracionMin,arrDuracionSeg,
        cantEtiquetas,arrNumRepro,arrSegundosTotales);
    return 0;
}
