#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/funciones.h"
#define MAX 500

int main() {

    struct Distrito *arrDistrito;
    arrDistrito = new struct Distrito[MAX]{};
    int cantDistritos = 0;

    struct Plato  *arrPlato;
    arrPlato = new struct Plato[MAX]{};
    int cantPlatos = 0;

    struct Cliente  *arrCliente;
    arrCliente = new struct Cliente[MAX]{};
    int cantClientes = 0;

    leerArrDistritos(arrDistrito,cantDistritos);
    leerArrPlatos(arrPlato,cantPlatos);
    leerArrClientes(arrCliente,cantClientes);

    imprimirReportesPrueba(arrDistrito,cantDistritos,arrPlato,cantPlatos,arrCliente,cantClientes);

    llenarArrTotales(arrDistrito,cantDistritos,arrPlato,cantPlatos,arrCliente,cantClientes);

    ordenarClientes(arrCliente,cantClientes);

    ordenarTodosLosPedidos(arrCliente,cantClientes);
    imprimirReporteFinal(arrCliente, cantClientes);

    return 0;
}