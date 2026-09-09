//
// Created by USUARIO on 11/10/2025.
//

#ifndef EX1_24_2_FUNCIONES_H
#define EX1_24_2_FUNCIONES_H

void imprimirReporte();

void abrirArchIfstream(const char *nomArch, ifstream &arch);

void abrirArchOfstream(const char *nomArch, ofstream &arch);

void abrirArchivos(ifstream &archPlatos, ifstream &archClientes, ifstream &archRepartos, ifstream &archRepartidores,
                   ofstream &archReporte);

void imprimirEncabezado(ofstream &archReporte);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirTexto(ifstream &archClientes, ofstream &archReporte, char deli, int cantEspa, bool primerGuar, char &vehi);

void imprimirDni(ofstream &archReporte, int dniCli);

void imprimirTipoVehi(ofstream &archReporte, char vehi, double descuento, double &descuentoVehi);

void imprimirRepartos(ifstream &archRepartos, ifstream &archPlatos, ofstream &archReporte, int dniCli,
                      double descuentoCli, double descuentoVehi, double &pagoCliente, double &pagoRepartidor);

void imprimirEncabezadoRepartos(ofstream &archReporte);

void imprimirPedido(ofstream &archReporte, int nroPedido, int pedido);

void imprimirPlatos(ifstream &archPlatos, ofstream &archReporte, int cant, int nroPlato, int v, double &subTotal
                    , double &descuento);

void imprimirResumen(ofstream &archReporte, double totalPedidoSinDes, double descuentoPorPlatos,
                     double descuentoDelCliente, double totalPagoCliente, double totalPagoReparti);

void imprimirRepartidor(ifstream &archRepartidores,ofstream &archReporte,int distrito,char vehi,
    double pagoCliente,double pagoRepartidor);

void imprimirEstadisticaFinal(ofstream &archReporte,double pagosTotalesPlatos,double pagosTotalesRepati);
#endif //EX1_24_2_FUNCIONES_H
