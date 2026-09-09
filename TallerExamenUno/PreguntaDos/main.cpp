#include <iostream>
#include <fstream>
#include <iomanip>
#define TAM_LIBRO 275
using namespace std;
#include "Bibliotecas/funciones.h"

int main() {
    int arrCodLibro[TAM_LIBRO]{}, cantLibros = 0;
    double arrPrecLibro[TAM_LIBRO]{};
    leerArrLibros(arrCodLibro, arrPrecLibro, cantLibros);

    imprimirReporte(arrCodLibro, arrPrecLibro, cantLibros);

    int arrCantVendidas[TAM_LIBRO]{}, arrFechaPrime[TAM_LIBRO]{}, arrDniPrime[TAM_LIBRO]{},
            arrFechaUlti[TAM_LIBRO]{}, arrDniUlti[TAM_LIBRO]{};
    double arrPromCalif[TAM_LIBRO]{}, arrTotalVentas[TAM_LIBRO]{};

    leerArrVentas(arrCodLibro, arrPrecLibro, arrCantVendidas, arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                  arrFechaUlti, arrDniUlti, cantLibros);

    imprimiReporte("ArchivosDeReporte/ReporteVentasPorLibro.txt", arrCodLibro, arrPrecLibro, arrCantVendidas,
                   arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                   arrFechaUlti, arrDniUlti, cantLibros);

    ordenarFinal(arrCodLibro, arrPrecLibro, arrCantVendidas, arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                 arrFechaUlti, arrDniUlti, cantLibros);

    imprimiReporte("ArchivosDeReporte/ReporteVentasOrdenado.txt", arrCodLibro, arrPrecLibro, arrCantVendidas,
                   arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                   arrFechaUlti, arrDniUlti, cantLibros);

    eliminarArr(arrCodLibro, arrPrecLibro, arrCantVendidas, arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                arrFechaUlti, arrDniUlti, cantLibros);

    imprimiReporte("ArchivosDeReporte/ReporteVentasELIMINADO.txt", arrCodLibro, arrPrecLibro, arrCantVendidas,
                   arrPromCalif, arrTotalVentas, arrFechaPrime, arrDniPrime,
                   arrFechaUlti, arrDniUlti, cantLibros);
    return 0;
}
