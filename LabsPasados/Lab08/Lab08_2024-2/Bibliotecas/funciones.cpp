#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by entol on 17/11/2025.
//

#include "funciones.h"
#define NO_ENCONTRADO -1

void leerArrDistritos(struct Distrito *arrDistrito, int &cantDistritos) {
    ifstream archDistr;
    abrirArchivoIfstream("ArchivosDeDatos/lab8_Distritos.csv", archDistr);
    //LN3085,Ancon,NORTE
    int i = 0;
    while (true) {
        arrDistrito[i].codigo = leerCadenaExacta(archDistr, ',');
        if (archDistr.eof()) break;
        arrDistrito[i].nombre = leerCadenaExacta(archDistr, ',');
        arrDistrito[i].ubicacion = leerCadenaExacta(archDistr, '\n');
        i++;
    }
    cantDistritos = i;
}

void abrirArchivoIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchivoOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    arch << right << fixed << setprecision(2);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}


char *leerCadenaExacta(ifstream &arch, char delim) {
    arch >> ws;
    char cadena[300], *ptr;
    arch.getline(cadena, 300, delim);
    if (arch.eof()) return nullptr;
    ptr = new char [strlen(cadena) + 1];
    strcpy(ptr, cadena);
    return ptr;
}

void leerArrPlatos(struct Plato *arrPlato, int &cantPlatos) {
    ifstream archPlato;
    abrirArchivoIfstream("ArchivosDeDatos/lab8_PlatosOfrecidos.csv", archPlato);
    //AP-73428,TEQUEÑOS,19.50,APERITIVO
    int i = 0;
    while (true) {
        arrPlato[i].codigo = leerCadenaExacta(archPlato, ',');
        if (archPlato.eof()) break;
        arrPlato[i].descripcion = leerCadenaExacta(archPlato, ',');
        archPlato >> arrPlato[i].precio;
        archPlato.get();
        arrPlato[i].categoria = leerCadenaExacta(archPlato, '\n');
        i++;
    }
    cantPlatos = i;
}

void leerArrClientes(struct Cliente *arrCliente, int &cantClientes) {
    ifstream archCLientes;
    abrirArchivoIfstream("ArchivosDeDatos/lab8_Clientes.csv", archCLientes);
    //90367684,CORONEL CHUMPITAZ HELI,LS8594
    int i = 0;
    while (true) {
        archCLientes >> arrCliente[i].dni;
        if (archCLientes.eof()) break;
        archCLientes.get();
        arrCliente[i].nombre = leerCadenaExacta(archCLientes, ',');
        arrCliente[i].distrito.codigo = leerCadenaExacta(archCLientes, '\n');
        i++;
    }
    cantClientes = i;
}

void imprimirReportesPrueba(struct Distrito *arrDistrito, int cantDistritos,
                            struct Plato *arrPlato, int cantPlatos,
                            struct Cliente *arrCliente, int cantClientes) {
    ofstream archReporteDis;
    abrirArchivoOfstream("ArchivosDeReporte/ReportePruebaDistritos.txt", archReporteDis);
    imprimirEncabezadoDis(archReporteDis);
    for (int i = 0; i < cantDistritos; i++) {
        archReporteDis << arrDistrito[i].codigo << setw(5) << ' ' << arrDistrito[i].nombre <<
                setw(30 - strlen(arrDistrito[i].nombre)) << ' ' << arrDistrito[i].ubicacion << endl;
    }

    ofstream archPlatos;
    abrirArchivoOfstream("ArchivosDeReporte/ReportePruebaPlatos.txt", archPlatos);
    imprimirEncabezadoPlatos(archPlatos);
    for (int i = 0; i < cantPlatos; i++) {
        archPlatos << arrPlato[i].codigo << setw(5) << ' ' << arrPlato[i].descripcion <<
                setw(50 - strlen(arrPlato[i].descripcion)) << ' ' << setw(7) << arrPlato[i].precio << setw(5) << ' ' <<
                arrPlato[i].categoria << endl;
    }

    ofstream archReporteCli;
    abrirArchivoOfstream("ArchivosDeReporte/ReportePruebaCliente.txt", archReporteCli);
    imprimirEncabezadoCli(archReporteCli);
    for (int i = 0; i < cantClientes; i++) {
        archReporteCli << arrCliente[i].dni << setw(5) << ' ' << arrCliente[i].nombre <<
                setw(50 - strlen(arrCliente[i].nombre)) << ' ' << arrCliente[i].distrito.codigo << endl;
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch.put('\n');
}

void imprimirEncabezadoDis(ofstream &arch) {
    arch << setw(12) << ' ' << "REPORTE PRUEBA PARA DISTRITOS" << endl;
    arch << "CODIGO" << setw(5) << ' ' << "NOMBRE" << setw(23) << ' ' << "UBICACION" << endl;
    imprimirLinea(arch, 56, '=');
}

void imprimirEncabezadoPlatos(ofstream &arch) {
    arch << setw(27) << ' ' << "REPORTE PRUEBA PARA PLATOS" << endl;
    arch << "CODIGO" << setw(7) << ' ' << "DESCRIPCION" << setw(40) << ' ' << "PRECIO" << setw(5) << ' ' <<
            "CATEGORIA" << endl;
    imprimirLinea(arch, 86, '=');
}

void imprimirEncabezadoCli(ofstream &arch) {
    arch << setw(20) << ' ' << "REPORTE PRUEBA PARA CLIENTES" << endl;
    arch << "DNI" << setw(18) << ' ' << "NOMBRE" << setw(32) << ' ' << "CODIGO DISTRITO" << endl;
    imprimirLinea(arch, 76, '=');
}

void llenarArrTotales(struct Distrito *arrDistrito, int cantDistritos,
                      struct Plato *arrPlato, int cantPlatos,
                      struct Cliente *arrCliente, int cantClientes) {
    ifstream archPedidos;
    abrirArchivoIfstream("ArchivosDeDatos/lab8_PedidosRealizados.txt", archPedidos);
    //117660      68114999        AP-73428       3
    int codPedido, dniCli, cantPedido;
    char codPlato[9];

    while (true) {
        archPedidos >> codPedido;
        if (archPedidos.eof()) break;
        archPedidos >> dniCli >> ws >> codPlato >> cantPedido;
        int idCliente = buscarCliente(arrCliente, cantClientes, dniCli);
        int idPlato = buscarPlato(arrPlato, cantPlatos, codPlato);
        if (idPlato != NO_ENCONTRADO and idCliente != NO_ENCONTRADO) {
            int pos = arrCliente[idCliente].cantidadDePedidos;

            arrCliente[idCliente].pedidos[pos].codigoPedido = codPedido;

            arrCliente[idCliente].pedidos[pos].codigoPlato = new char[strlen(codPlato) + 1];
            strcpy(arrCliente[idCliente].pedidos[pos].codigoPlato, codPlato);

            arrCliente[idCliente].pedidos[pos].descripcion = new char[strlen(arrPlato[idPlato].descripcion) + 1];
            strcpy(arrCliente[idCliente].pedidos[pos].descripcion, arrPlato[idPlato].descripcion);

            arrCliente[idCliente].pedidos[pos].cantidad = cantPedido;
            arrCliente[idCliente].pedidos[pos].precio = arrPlato[idPlato].precio;

            arrCliente[idCliente].pedidos[pos].subtotal = cantPedido * arrPlato[idPlato].precio;

            arrCliente[idCliente].montoTotal += arrCliente[idCliente].pedidos[pos].subtotal;
            arrCliente[idCliente].cantidadDePedidos++;
        }
    }
}

int buscarCliente(struct Cliente *arrCliente, int cantClientes, int dniCli) {
    for (int i = 0; i < cantClientes; i++) {
        if (arrCliente[i].dni == dniCli) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

int buscarPlato(struct Plato *arrPlato, int cantPlatos, const char *codPlato) {
    for (int i = 0; i < cantPlatos; i++) {
        if (strcmp(arrPlato[i].codigo, codPlato) == 0) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}


void ordenarClientes(struct Cliente *arrCliente, int cantClientes) {
    for (int i = 0; i < cantClientes - 1; i++) {
        for (int j = i + 1; j < cantClientes; j++) {
            if (strcmp(arrCliente[i].nombre, arrCliente[j].nombre) > 0) {
                cambiarStructs(arrCliente[i], arrCliente[j]);
            }
        }
    }
}

void cambiarStructs(struct Cliente &arrI, struct Cliente &arrJ) {
    struct Cliente aux = arrI;
    arrI = arrJ;
    arrJ = aux;
}


void ordenarTodosLosPedidos(struct Cliente *arrCliente, int cantClientes) {
    for (int i = 0; i < cantClientes; i++) {
        ordenarPedidosClientes(arrCliente[i]);
    }
}

void ordenarPedidosClientes(struct Cliente &cli) {
    for (int i = 0; i < cli.cantidadDePedidos - 1; i++) {
        for (int j = i + 1; j < cli.cantidadDePedidos; j++) {
            bool debeIntercambiar = false;

            if (cli.pedidos[i].codigoPedido > cli.pedidos[j].codigoPedido) {
                debeIntercambiar = true;
            } else if (cli.pedidos[i].codigoPedido == cli.pedidos[j].codigoPedido and
                       strcmp(cli.pedidos[i].codigoPlato, cli.pedidos[j].codigoPlato) < 0) {
                debeIntercambiar = true;
            }

            if (debeIntercambiar) {
                intercambiarPedidos(cli.pedidos[i], cli.pedidos[j]);
            }
        }
    }
}

void intercambiarPedidos(struct PlatoPedido &a, struct PlatoPedido &b) {
    struct PlatoPedido aux = a;
    a = b;
    b = aux;
}

void imprimirReporteFinal(struct Cliente *arrCliente, int cantClientes) {
    ofstream arch;
    abrirArchivoOfstream("ArchivosDeReporte/ReporteFinal.txt", arch);

    imprimirTitulo(arch);

    for (int i = 0; i < cantClientes; i++) {
        imprimirCliente(arch, arrCliente[i]);
        imprimirPedidosCliente(arch, arrCliente[i]);
        imprimirTotalesCliente(arch, arrCliente[i]);
        imprimirLinea(arch, 80, '=');
    }
}

void imprimirTitulo(ofstream &arch) {
    arch << setw(25) << ' ' << "REPORTE FINAL DE CLIENTES" << endl;
    imprimirLinea(arch, 80, '=');
}

void imprimirCliente(ofstream &arch, const Cliente &cli) {
    arch << "DNI: " << cli.dni << endl;
    arch << "Nombre: " << cli.nombre << endl;
    arch << "Distrito: " << cli.distrito.codigo << endl;
    imprimirLinea(arch, 80, '-');
}

void imprimirPedidosCliente(ofstream &arch, const Cliente &cli) {
    arch << "PEDIDOS REALIZADOS:" << endl;

    arch << left
            << setw(12) << "CodPedido"
            << setw(15) << "CodPlato"
            << setw(35) << "Descripcion"
            << setw(10) << "Cant"
            << setw(10) << "Precio"
            << "Subtotal" << endl;

    imprimirLinea(arch, 80, '-');

    for (int i = 0; i < cli.cantidadDePedidos; i++) {
        const PlatoPedido &p = cli.pedidos[i];

        arch << left
                << setw(12) << p.codigoPedido
                << setw(15) << p.codigoPlato
                << setw(75) << p.descripcion
                << setw(10) << p.cantidad
                << setw(10) << p.precio
                << p.subtotal << endl;
    }

    arch << endl;
}

void imprimirTotalesCliente(ofstream &arch, const Cliente &cli) {
    imprimirLinea(arch, 80, '-');
    arch << "Cantidad total de pedidos: " << cli.cantidadDePedidos << endl;
    arch << "Monto total: " << cli.montoTotal << endl;
}
