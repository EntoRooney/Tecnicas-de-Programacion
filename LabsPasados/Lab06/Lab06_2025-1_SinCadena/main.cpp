#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"
#define TAM_MAX_COD 140

int main() {
    int arrCodigoInfraccion[TAM_MAX_COD]{}, cantCodigos = 0;
    double arrMultasInfraccion[TAM_MAX_COD]{};
    llenarArrInfraccion(arrCodigoInfraccion, arrMultasInfraccion, cantCodigos);
    imprimirReportePrueba(arrCodigoInfraccion, arrMultasInfraccion, cantCodigos);

    int arrDni[TAM_MAX_COD]{}, arrMasMultaAntigua[TAM_MAX_COD]{}, arrUltimaMulta[TAM_MAX_COD]{}, cantDni = 0;
    double arrTotalMultas[TAM_MAX_COD]{}, arrTotalPagadas[TAM_MAX_COD]{}, arrTotalPendientes[TAM_MAX_COD]{};
    llenarArrInfraCometidas(arrCodigoInfraccion, arrMultasInfraccion, cantCodigos,
                            arrDni, arrMasMultaAntigua, arrUltimaMulta, arrTotalMultas, arrTotalPagadas,
                            arrTotalPendientes, cantDni);
    imprimirReporte(arrDni, arrMasMultaAntigua, arrUltimaMulta, arrTotalMultas, arrTotalPagadas,
                                arrTotalPendientes, cantDni);
    return 0;
}
