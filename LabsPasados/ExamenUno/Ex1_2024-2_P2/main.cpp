#include <iostream>
#include <fstream>
#include <iomanip>
#define TAM_PLATOS 150
#define TAM_CLI 120
using namespace std;
#include "Bibliotecas/funciones.h"

int main() {
    int arrCodPlato[TAM_PLATOS]{}, arrCantStock[TAM_PLATOS]{}, cantPlatos = 0;
    double arrPrecioPlato[TAM_PLATOS]{}, arrDescPlato[TAM_PLATOS]{};
    leerArrPlatos(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato, cantPlatos);

    int arrDniCliente[TAM_CLI]{}, cantCliente = 0;
    double arrDescCliente[TAM_CLI]{};
    leerArrCliente(arrDniCliente, arrDescCliente, cantCliente);

    imprimirReporteSimple(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato, cantPlatos,
                          arrDniCliente, arrDescCliente, cantCliente);

    int arrPlatoAtendido[TAM_PLATOS]{}, arrPlatoNoAtendido[TAM_PLATOS]{};
    double arrMontoEsperado[TAM_PLATOS]{}, arrMontoBruto[TAM_PLATOS]{}, arrMontoRecibido[TAM_PLATOS]{};

    llenarArrFinales(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato, cantPlatos,
                    arrDniCliente, arrDescCliente, cantCliente,
                    arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido);

    ordenarCantPlatos(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato,
        arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido,cantPlatos);

    imprimirReporte(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato,
        arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido,cantPlatos);

    eliminarArr(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato,
        arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido,cantPlatos);

    imprimirReporteEliminado(arrCodPlato, arrPrecioPlato, arrCantStock, arrDescPlato,
        arrPlatoAtendido, arrPlatoNoAtendido, arrMontoEsperado, arrMontoBruto, arrMontoRecibido,cantPlatos);
    return 0;
}
