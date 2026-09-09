#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 12/10/2025.
//

#include "funciones.h"
#define TAM_MAX 130

void imprimirReporte() {
    ifstream archLibros, archClientes, archVentas;
    ofstream archReporte;
    aperturaArchivos(archLibros, archClientes, archVentas, archReporte);
    int codLibro, fechaI, fechaF, dniPeor, dniMejor,cantTotal=0;
    double precioLibro, totalVentas,ventasTotales=0;
    imprimirEncabezado(archReporte, fechaI, fechaF);
    while (true) {
        int cantVendidas = 0, sumaCalificacion = 0,peorCali = 101, mejorCali = -1;
        archLibros >> codLibro;
        if (archLibros.eof())break;
        imprimirLinea(archReporte,TAM_MAX, '=');
        archReporte << "LIBRO: ";
        leerTexto(archLibros, archReporte, true, true, 60, ']');
        archReporte << "AUTOR: ";
        leerTexto(archLibros, archReporte, false, true, 30, '*');
        archLibros >> precioLibro;
        archReporte << "PRECIO S/." << setw(4) << ' ' << setw(6) << precioLibro << endl;
        imprimirEncabezadoLibros(archReporte);
        imprimirVentas(archVentas, archClientes, archReporte, fechaI, fechaF, codLibro, cantVendidas,
                       sumaCalificacion, peorCali, dniPeor, mejorCali, dniMejor);
        imprimirCantTotal(archReporte, cantVendidas, precioLibro, totalVentas);
        if (cantVendidas > 0) {
            imprimirEstadisticias(archReporte, cantVendidas, sumaCalificacion, peorCali, dniPeor, mejorCali, dniMejor);
        }
        cantTotal+=cantVendidas;
        ventasTotales+=totalVentas;
    }
    imprimirResumen(archReporte,cantTotal,ventasTotales);
}

void aperturaArchivos(ifstream &archLibros, ifstream &archClientes, ifstream &archVentas, ofstream &archReporte) {
    abrirArchIfstream("ArchivosDeDatos/libros.txt", archLibros);
    abrirArchIfstream("ArchivosDeDatos/Clientes.txt", archClientes);
    abrirArchIfstream("ArchivosDeDatos/Ventas.txt", archVentas);
    abrirArchOfstream("ArchivosDeReporte/Reporte.txt", archReporte);
}

void abrirArchIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, archivo " << nombArch << "  no se pudo abrir";
        exit(1);
    }
}

void abrirArchOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, archivo " << nombArch << "  no se pudo abrir";
        exit(1);
    }
}

void leerTexto(ifstream &arch, ofstream &archReporte, bool enMayus, bool quitarPrimerC, int cant, char deli) {
    arch >> ws;
    int contador = 0;
    char c, carBsr;
    while (true) {
        if (quitarPrimerC) {
            arch >> carBsr;
            quitarPrimerC = false;
        }
        c = arch.get();
        if (c == deli)break;
        contador++;
        if (enMayus) {
            if ('a' <= c and c <= 'z') {
                c = c - 'a' + 'A';
            }
        }
        archReporte.put(c);
    }
    archReporte << setw(cant - contador) << ' ';
}

void imprimirEncabezado(ofstream &archReporte, int &fechaI, int &fechaF) {
    int ddI, ddF, mesI, mesF, anhioI, anhioF;
    archReporte << right << fixed << setprecision(2);

    cout<<"INGRESE LA FECHA INICIAL"<<endl;
    cin>>ddI>>mesI>>anhioI;
    cout<<"INGRESE LA FECHA INICIAL"<<endl;
    cin>>ddF>>mesF>>anhioF;

    calcularFecha(ddI, mesI, anhioI, fechaI);
    calcularFecha(ddF, mesF, anhioF, fechaF);
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(45) << ' ' << "REPORTE POR VENTAS POR LIBROS" << endl;
    archReporte << setw(40) << ' ' << "DESDE: ";
    imprimirFecha(archReporte, ddI, mesI, anhioI);
    archReporte << setw(5) << ' ' << "HASTA: ";
    imprimirFecha(archReporte, ddF, mesF, anhioF);
    archReporte << endl;
}

void calcularFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(2) << anhio << setfill(' ');
}

void imprimirVentas(ifstream &archVentas, ifstream &archClientes, ofstream &archReporte, int fechaI, int fechaF,
                    int codLibro, int &cantVendidas, int &sumaCalificacion,
                    int &peorCali, int &dniPeor, int &mejorCali, int &dniMejor) {
    archVentas.clear();
    archVentas.seekg(0, ios::beg);
    int codLibreria, dd, mes, anhio, codLibroArch, dniCliente, califacion, fechaConvertida;

    char c;
    while (true) {
        archVentas >> codLibreria;
        if (archVentas.eof()) break;
        archVentas >> dd >> c >> mes >> c >> anhio;
        calcularFecha(dd, mes, anhio, fechaConvertida);
        if (fechaConvertida >= fechaI and fechaConvertida <= fechaF) {
            while (true) {
                archVentas >> codLibroArch >> dniCliente >> califacion;
                if (codLibroArch == codLibro) {
                    leerCliente(archClientes, archReporte, codLibreria, dniCliente, dd, mes, anhio, califacion,
                                cantVendidas, sumaCalificacion, peorCali, dniPeor, mejorCali, dniMejor);
                }
                if (archVentas.get() == '\n') break;
            }
        } else {
            while (true) {
                if (archVentas.get() == '\n') break;
            }
        }
    }
}

void imprimirEncabezadoLibros(ofstream &archReporte) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "LIBRERIA" << setw(17) << ' ' << "CLIENTE" << setw(29) << ' ' << "TIPO" << setw(7) << ' '
            << "FECHA DE VENTA" << setw(8) << ' ' << "CALIFICACION" << endl;
}


void leerCliente(ifstream &archClientes, ofstream &archReporte, int codLibreria, int dniCliente, int dd, int mes,
                 int anhio, int califacion, int &cantVendidas, int &sumaCalificacion,
                 int &peorCali, int &dniPeor, int &mejorCali, int &dniMejor) {
    archClientes.clear();
    archClientes.seekg(0, ios::beg);
    int dniClienteArch;
    char tipoCli;
    while (true) {
        archClientes >> dniClienteArch;
        if (archClientes.eof()) break;
        if (dniCliente == dniClienteArch) {
            archClientes >> ws >> tipoCli;
            cantVendidas++;
            sumaCalificacion += califacion;
            archReporte << setw(1) << ' ' << codLibreria << setw(5) << ' ' << dniCliente << " - ";
            leerTexto(archClientes, archReporte, false, false, 40, '\n');
            archReporte << tipoCli << setw(11) << ' ';
            imprimirFecha(archReporte, dd, mes, anhio);
            archReporte << setw(14) << ' ' << setw(2) << califacion << endl;
            calcularMejorPeorCali(califacion, dniCliente, peorCali, dniPeor, mejorCali, dniMejor);
        } else {
            while (true) {
                if (archClientes.get() == '\n') break;
            }
        }
    }
}

void imprimirCantTotal(ofstream &archReporte, int cantVendidas, double precioLibro, double &totalVentas) {
    totalVentas = cantVendidas * precioLibro;
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "Cantidas vendidas: " << setw(3) << ' ' << setw(2) << cantVendidas << setw(5) << ' ' <<
            "Total ventas:"
            << setw(5) << ' ' << setw(5) << totalVentas << endl;
}

void imprimirEstadisticias(ofstream &archReporte, int cantVendidas, int sumaCalificacion,int peorCali,int dniPeor,
    int mejorCali,int dniMejor) {
    double promCali = (double) sumaCalificacion / cantVendidas;
    archReporte << "Promedio de calificaciones:" << setw(5) << ' ' << setw(4) << promCali << endl;
    archReporte<<"Mejor calificacion del cliente:"<<setw(5)<<' '<<dniMejor<<setw(5)<<' '<<"Calificacion:"<<
        setw(5)<<' '<<setw(2)<<mejorCali<<endl;
    archReporte<<"Peor calificacion del cliente:"<<setw(6)<<' '<<dniPeor<<setw(5)<<' '<<"Calificacion:"<<
        setw(5)<<' '<<setw(2)<<peorCali<<endl;
}

void calcularMejorPeorCali(int califacion, int dniCliente, int &peorCali, int &dniPeor, int &mejorCali, int &dniMejor) {
    if (califacion < peorCali) {
        peorCali = califacion;
        dniPeor = dniCliente;
    }
    if (califacion > mejorCali) {
        mejorCali = califacion;
        dniMejor = dniCliente;
    }
}

void imprimirResumen(ofstream &archReporte,int cantTotal,double ventasTotales) {
    imprimirLinea(archReporte,TAM_MAX,'=');
    archReporte<<"RESUMEN"<<endl;
    archReporte<<"Total de libros vendidos:"<<setw(8)<<cantTotal<<endl;
    archReporte<<"Total de ventas S/.:"<<setw(5)<<' '<<setw(5)<<ventasTotales<<endl;
    imprimirLinea(archReporte,TAM_MAX,'=');
}