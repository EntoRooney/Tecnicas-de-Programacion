#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"
#define TAM_COD 150
#define TAM_INFR 700

int main() {
    int arrCodigoInfraccion[TAM_COD]{}, cantInfra = 0;
    double arrMultasInfraccion[TAM_COD]{};
    leerArrCodInfra(arrCodigoInfraccion, arrMultasInfraccion, cantInfra);
    imprimirReportePrueba(arrCodigoInfraccion, arrMultasInfraccion, cantInfra);

    int arrDni[TAM_INFR]{}, arrMultaMasAntigua[TAM_INFR]{}, arrMultaMasRecientePagada[TAM_INFR]{}, cantDni = 0;
    double arrTotalMultas[TAM_INFR]{}, arrTotalPagadas[TAM_INFR]{}, arrTotalPendientes[TAM_INFR]{};
    leerMultasCometidas(arrCodigoInfraccion, arrMultasInfraccion, cantInfra,
                        arrDni, arrMultaMasAntigua, arrMultaMasRecientePagada,
                        arrTotalMultas, arrTotalPagadas, arrTotalPendientes, cantDni);
    imprimirReporte(arrDni, arrMultaMasAntigua, arrMultaMasRecientePagada,
                    arrTotalMultas, arrTotalPagadas, arrTotalPendientes, cantDni);
    return 0;
}
