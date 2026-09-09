#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define TAM_MAX 150

//
// Created by USUARIO on 11/10/2025.
//

#include "funciones.h"

void imprimirReporte() {
    ifstream archPlatos, archClientes, archRepartos, archRepartidores;
    ofstream archReporte;
    abrirArchivos(archPlatos, archClientes, archRepartos, archRepartidores, archReporte);
    int dniCli, distrito;
    double descuentoCli, descuentoVehi, pagosTotalesPlatos = 0, pagosTotalesRepati;
    char vehi, siNo, c;
    while (true) {
        double pagoCliente = 0, pagoRepartidor = 0;
        archClientes >> dniCli;
        if (archClientes.eof()) break;
        imprimirDni(archReporte, dniCli);
        imprimirTexto(archClientes, archReporte, ']', 40, false, vehi);
        archReporte << "DISTRITO: ";
        archClientes >> distrito;
        imprimirTexto(archClientes, archReporte, ' ', 27, false, vehi);
        archClientes >> ws >> vehi >> ws >> siNo;
        if (siNo == 'S') {
            archClientes >> descuentoCli >> c;
        } else descuentoCli = 0;

        imprimirTipoVehi(archReporte, vehi, descuentoCli, descuentoVehi);
        imprimirRepartos(archRepartos, archPlatos, archReporte, dniCli, descuentoCli, descuentoVehi,
                         pagoCliente, pagoRepartidor);
        imprimirRepartidor(archRepartidores, archReporte, distrito, vehi, pagoCliente, pagoRepartidor);
        pagosTotalesPlatos += pagoCliente;
        pagosTotalesRepati += pagoRepartidor;
    }
    imprimirEstadisticaFinal(archReporte, pagosTotalesPlatos, pagosTotalesRepati);
}

void abrirArchIfstream(const char *nomArch, ifstream &arch) {
    arch.open(nomArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nomArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchOfstream(const char *nomArch, ofstream &arch) {
    arch.open(nomArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nomArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchivos(ifstream &archPlatos, ifstream &archClientes, ifstream &archRepartos, ifstream &archRepartidores,
                   ofstream &archReporte) {
    abrirArchIfstream("ArchivosDeDatos/PlatosOfrecidos (1).txt", archPlatos);
    abrirArchIfstream("ArchivosDeDatos/Clientes.txt ", archClientes);
    abrirArchIfstream("ArchivosDeDatos/RepartosARealizar (1).txt", archRepartos);
    abrirArchIfstream("ArchivosDeDatos/Repartidores.txt", archRepartidores);
    abrirArchOfstream("ArchivosDeReporte/Reporte.txt", archReporte);
    imprimirEncabezado(archReporte);
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(30) << ' ' << "EMPRESA DE REPARTOS A DOMILICIO TP S.A." << endl;
    archReporte << setw(40) << ' ' << "CLIENTES POR ATENDER" << endl;
    archReporte << right << fixed << setprecision(2);
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirTexto(ifstream &archClientes, ofstream &archReporte, char deli, int cantEspa, bool primerGuar,
                   char &vehi) {
    archClientes >> ws;
    int contador = 0;
    char c;

    while (true) {
        archClientes.get(c);
        if (primerGuar) {
            vehi = c;
        }
        if (c == deli) break;
        if (c == '_') {
            c = ' ';
        }
        contador++;
        archReporte.put(c);
    }
    archReporte << setw(cantEspa - contador) << ' ';
}

void imprimirDni(ofstream &archReporte, int dniCli) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "CLIENTE: " << dniCli << " - ";
}

void imprimirTipoVehi(ofstream &archReporte, char vehi, double descuento, double &descuentoVehi) {
    archReporte << "TIPO DE VEHICULO: ";
    if (vehi == 'M') {
        archReporte << "Motocicleta" << setw(5) << ' ';
        descuentoVehi = 10 / 100.0;
    } else {
        archReporte << "Bicibleta" << setw(7) << ' ';
        descuentoVehi = 5 / 100.0;
    }
    archReporte << "DESCUENTO: " << setw(5) << descuento << "%" << endl;
}

void imprimirRepartos(ifstream &archRepartos, ifstream &archPlatos, ofstream &archReporte, int dniCli,
                      double descuentoCli, double descuentoVehi, double &pagoCliente, double &pagoRepartidor) {
    archRepartos.clear();
    archRepartos.seekg(0, ios::beg);
    imprimirEncabezadoRepartos(archReporte);
    int nroPedido, dniCliArch, cant, nroPlato, pedido = 0;
    double subTotal, descuento, totalPedidoSinDes = 0, descuentoPorPlatos = 0, descuentoDelCliente, totalPagoCliente,
            totalPagoReparti;
    while (true) {
        archRepartos >> nroPedido;
        if (archRepartos.eof()) break;
        archRepartos >> dniCliArch;
        if (dniCliArch == dniCli) {
            int v = 0;
            pedido++;
            imprimirPedido(archReporte, nroPedido, pedido);
            while (true) {
                archRepartos >> cant >> nroPlato;
                v++;
                imprimirPlatos(archPlatos, archReporte, cant, nroPlato, v, subTotal, descuento);
                totalPedidoSinDes += subTotal;
                descuentoPorPlatos += descuento;
                if (archRepartos.get() == '\n') break;
            }
            descuentoDelCliente = totalPedidoSinDes * (descuentoCli / 100.0);
            totalPagoCliente = totalPedidoSinDes - descuentoDelCliente - descuentoPorPlatos;
            totalPagoReparti = totalPedidoSinDes * descuentoVehi;
            pagoCliente += totalPagoCliente;
            pagoRepartidor += totalPagoReparti;
            imprimirResumen(archReporte, totalPedidoSinDes, descuentoPorPlatos, descuentoDelCliente, totalPagoCliente,
                            totalPagoReparti);
        } else {
            while (true) {
                if (archRepartos.get() == '\n') break;
            }
        }
    }
}

void imprimirEncabezadoRepartos(ofstream &archReporte) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "REPARTOS:" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}

void imprimirPedido(ofstream &archReporte, int nroPedido, int pedido) {
    archReporte << setfill('0') << setw(2) << pedido << ")" << setfill(' ') << setw(3) << ' ' << "PEDIDO: " << nroPedido
            << endl;
    archReporte << setw(18) << ' ' << "PLATO" << setw(42) << ' ' << "CANTIDAD" << setw(5) << ' ' << "PRECIO"
            << setw(5) << ' ' << "SUBTOTAL" << setw(11) << ' ' << "DESCUENTO" << endl;
}

void imprimirPlatos(ifstream &archPlatos, ofstream &archReporte, int cant, int nroPlato, int v, double &subTotal
                    , double &descuento) {
    archPlatos.clear();
    archPlatos.seekg(0, ios::beg);
    int nroPlatoArch, bsr;
    double precio, descPlato;
    char vehi, c;

    while (true) {
        archPlatos >> nroPlatoArch;
        if (archPlatos.eof()) break;
        if (nroPlatoArch == nroPlato) {
            archReporte << setw(6) << ' ' << setfill('0') << setw(2) << v << ") " << setfill(' ') << nroPlatoArch <<
                    "-";
            imprimirTexto(archPlatos, archReporte, '}', 50, false, vehi);
            archPlatos >> precio >> bsr;
            if (archPlatos.get() != '\n') {
                archPlatos >> descPlato >> c;
            } else {
                descPlato = 0;
            }
            subTotal = cant * precio;
            descuento = (descPlato / 100.0) * subTotal;
            archReporte << setw(3) << cant << setw(10) << ' ' << setw(5) << precio << setw(5) << ' ' << setw(6) <<
                    subTotal << setw(10) << ' ' << setw(5) << descPlato << "%" << " - " << setw(5) << descuento << endl;
        } else {
            while (true) {
                if (archPlatos.get() == '\n') break;
            }
        }
    }
}

void imprimirResumen(ofstream &archReporte, double totalPedidoSinDes, double descuentoPorPlatos,
                     double descuentoDelCliente, double totalPagoCliente, double totalPagoReparti) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(6) << ' ' << "TOTAL PEDIDO SIN DESCUENTOS:" << setw(13) << ' ' << setw(6) << totalPedidoSinDes
            << endl;
    archReporte << setw(6) << ' ' << "DESCUENTO POR TOTAL POR PLATOS:" << setw(10) << ' ' << setw(6) <<
            descuentoPorPlatos << endl;
    archReporte << setw(6) << ' ' << "DESCUENTO DEL CLIENTE:" << setw(19) << ' ' << setw(6) << descuentoDelCliente <<
            endl;
    archReporte << setw(6) << ' ' << "TOTAL PAGADO POR EL CLIENTE:" << setw(13) << ' ' << setw(6) << totalPagoCliente <<
            endl;
    archReporte << setw(6) << ' ' << "PAGO AL REPARTIDOR:" << setw(22) << ' ' << setw(6) << totalPagoReparti
            << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}

void imprimirRepartidor(ifstream &archRepartidores, ofstream &archReporte, int distrito, char vehi, double pagoCliente,
                        double pagoRepartidor) {
    archRepartidores.clear();
    archRepartidores.seekg(0, ios::beg);
    int dniRep, distriRep;
    char c;
    archReporte << "MONTO TOTAL PAGADO POR EL CLIENTE" << setw(10) << ' ' << setw(6) << pagoCliente << endl;
    while (true) {
        archRepartidores >> dniRep;
        if (archRepartidores.eof()) break;
        archRepartidores >> ws >> c;
        while (true) {
            if (archRepartidores.get() == ' ') break;
        }
        archRepartidores >> distriRep;
        if (c == vehi and distriRep == distrito) {
            archReporte << "REPARTIDOR: " << dniRep << " - ";
            imprimirTexto(archRepartidores, archReporte, '\n', 30, false, vehi);
            archReporte << "PAGO TOTAL:" << setw(6) << ' ' << setw(6) << pagoRepartidor << endl;
        } else {
            while (true) {
                if (archRepartidores.get() == '\n') break;
            }
        }
    }
}

void imprimirEstadisticaFinal(ofstream &archReporte, double pagosTotalesPlatos, double pagosTotalesRepati) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "TOTAL RECAUDADO POR LOS PEDIDOS SOLICITADOS" << setw(5) << ' ' << setw(13) << pagosTotalesPlatos <<
            endl;
    archReporte << "TOTAL A PAGAR A LOS REPARTIDORES" << setw(17) << ' ' << setw(12) << pagosTotalesRepati << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}
