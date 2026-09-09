#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define TAM_REPARTIDOR 80
#define TAM_PLATO 140
#include "Bibliotecas/funciones.h"

int main() {
    int arrDniRepartidor[TAM_REPARTIDOR]{}, arrCodDistRepartidor[TAM_REPARTIDOR]{}, cantRepartidores = 0;
    char *arrNombreRepartidor[TAM_REPARTIDOR]{}, *arrVehiRepartidor[TAM_REPARTIDOR]{},
            *arrDistritoRepartidor[TAM_REPARTIDOR]{};
    leerArrRepartidores(arrDniRepartidor, arrNombreRepartidor, arrVehiRepartidor, arrCodDistRepartidor,
                        arrDistritoRepartidor,
                        cantRepartidores);

    int arrCodPlato[TAM_PLATO]{}, cantPlatos = 0;
    char *arrNombrePlato[TAM_PLATO]{}, *arrCategoriaPlato[TAM_PLATO]{};
    double arrPrecioPlato[TAM_PLATO]{}, arrDescPlato[TAM_PLATO]{};
    leerArrPlatos(arrCodPlato, arrNombrePlato, arrPrecioPlato, arrCategoriaPlato, arrDescPlato, cantPlatos);

    imrprimirReportePrueba(arrCodPlato, arrNombrePlato, arrPrecioPlato, arrCategoriaPlato, arrDescPlato, cantPlatos,
                           arrDniRepartidor, arrNombreRepartidor, arrVehiRepartidor, arrCodDistRepartidor,
                           arrDistritoRepartidor, cantRepartidores);
    return 0;
}
