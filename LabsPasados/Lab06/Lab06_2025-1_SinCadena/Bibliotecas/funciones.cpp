#include <iostream>
#include <fstream>
#include <iomanip>
#include <scoped_allocator>

using namespace std;

//
// Created by USUARIO on 26/10/2025.
//

#include "funciones.h"
#define NO_ENCONTRADO -1
#define TAM_MAX 120

void llenarArrInfraccion(int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantCodigos) {
    ifstream archCod;
    abrirArchivoIfstream("ArchivosDeDatos/TablaDeInfracciones.txt", archCod);
    int cod;
    double multa;
    while (true) {
        archCod >> cod >> multa;
        if (archCod.eof()) break;
        inserOrdenado(cod, multa, arrCodigoInfraccion, arrMultasInfraccion, cantCodigos);
        eliminarTexto(archCod);
    }
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
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void eliminarTexto(ifstream &archCod) {
    archCod >> ws;
    while (true) {
        if (archCod.get() == '\n') break;
    }
}

void inserOrdenado(int cod, double multa, int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantCodigos) {
    int pos = cantCodigos - 1;
    while (pos >= 0 and arrCodigoInfraccion[pos] > cod) {
        arrCodigoInfraccion[pos + 1] = arrCodigoInfraccion[pos];
        arrMultasInfraccion[pos + 1] = arrMultasInfraccion[pos];
        pos--;
    }
    arrCodigoInfraccion[pos + 1] = cod;
    arrMultasInfraccion[pos + 1] = multa;
    cantCodigos++;
}

void imprimirReportePrueba(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantCodigos) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/PruebaTablaInf.txt", archReporte);
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(2) << ' ' << "REPORTE DE MULTAS" << endl;
    archReporte << "CODIGO" << setw(5) << ' ' << "MULTA    " << endl;
    imprimirLinea(archReporte, 22, '=');
    for (int i = 0; i < cantCodigos; i++) {
        archReporte << arrCodigoInfraccion[i] << setw(5) << ' ' << setw(8) << arrMultasInfraccion[i] << endl;
    }
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void llenarArrInfraCometidas(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantCodigos, int *arrDni,
                             int *arrMasMultaAntigua, int *arrUltimaMulta,
                             double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes,
                             int &cantDni) {
    ifstream archInfra;
    abrirArchivoIfstream("ArchivosDeDatos/InfraccionesCometidas.txt", archInfra);
    int ddC, mesC, anhioC, basuraInt, dni, codigo, fechaCometida;
    char c, pago = 'N';
    while (true) {
        int fechaPago = 0, ddP = 0, mesP = 0, anhioP = 0;
        archInfra >> ddC;
        if (archInfra.eof()) break;
        archInfra >> c >> mesC >> c >> anhioC >> ws >> c >> basuraInt >> c >> basuraInt >> dni >> codigo;
        if (archInfra.peek() != '\n') {
            archInfra >> c >> ddP >> c >> mesP >> c >> anhioP;
        }
        convertirFecha(ddC, mesC, anhioC, fechaCometida);
        convertirFecha(ddP, mesP, anhioP, fechaPago);
        int idMulta = buscarBinaria(codigo, arrCodigoInfraccion, cantCodigos);
        int idDni = buscarBinaria(dni, arrDni, cantDni);
        if (idMulta != -1) {
            if (idDni != -1) {
                actualizarDni(arrMasMultaAntigua[idDni], arrUltimaMulta[idDni], arrTotalMultas[idDni],
                              arrTotalPagadas[idDni], arrTotalPendientes[idDni], fechaCometida, fechaPago,
                              arrMultasInfraccion[idMulta]);
            } else {
                insertarDni(arrDni, arrMasMultaAntigua, arrUltimaMulta, arrTotalMultas, arrTotalPagadas,
                            arrTotalPendientes, cantDni, dni, fechaCometida, fechaPago, arrMultasInfraccion[idMulta]);
            }
        }
    }
}

int buscarBinaria(int nuevoDato, int *arr, int cantMax) {
    int limInferior = 0, limSuperior = cantMax - 1, puntoMedio;
    while (true) {
        if (limInferior > limSuperior) return -1;
        puntoMedio = (limSuperior + limInferior) / 2;
        if (arr[puntoMedio] == nuevoDato) return puntoMedio;
        if (arr[puntoMedio] > nuevoDato) {
            limSuperior = puntoMedio - 1;
        } else {
            limInferior = puntoMedio + 1;
        }
    }
}

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void actualizarDni(int &arrMasMultaAntigua, int &arrUltimaMulta, double &arrTotalMultas,
                   double &arrTotalPagadas, double &arrTotalPendientes, int fechaCometida, int fechaPago,
                   double arrMultasInfraccion) {
    if (arrMasMultaAntigua == 0 or fechaCometida < arrMasMultaAntigua) arrMasMultaAntigua = fechaCometida;

    if (fechaPago != 0) {
        if (arrUltimaMulta == 0 or fechaPago > arrUltimaMulta) {
            arrUltimaMulta = fechaPago;
        }
        arrTotalPagadas += arrMultasInfraccion;
    } else {
        arrTotalPendientes += arrMultasInfraccion;
    }
    arrTotalMultas += arrMultasInfraccion;
}

void insertarDni(int *arrDni, int *arrMasMultaAntigua, int *arrUltimaMulta, double *arrTotalMultas,
                 double *arrTotalPagadas,
                 double *arrTotalPendientes, int &cantDni, int dni, int fechaCometida, int fechaPago,
                 double arrMultasInfraccion) {
    int pos = cantDni - 1;

    while (pos>=0 and arrDni[pos]>dni ) {
        arrDni[pos + 1] = arrDni[pos];
        arrMasMultaAntigua[pos + 1] = arrMasMultaAntigua[pos];
        arrUltimaMulta[pos + 1] = arrUltimaMulta[pos];
        arrTotalMultas[pos + 1] = arrTotalMultas[pos];
        arrTotalPagadas[pos + 1] = arrTotalPagadas[pos];
        arrTotalPendientes[pos + 1] = arrTotalPendientes[pos];
        pos--;
    }
    arrDni[pos + 1] = dni;
    arrMasMultaAntigua[pos + 1] = fechaCometida;
    if (fechaPago != 0) {
        arrUltimaMulta[pos + 1] = fechaPago;
        arrTotalPagadas[pos + 1] += arrMultasInfraccion;
    } else {
        arrTotalPendientes[pos + 1] += arrMultasInfraccion;
    }
    arrTotalMultas[pos + 1] += arrMultasInfraccion;
    cantDni++;
}

void imprimirReporte(int *arrDni, int *arrMasMultaAntigua, int *arrUltimaMulta, double *arrTotalMultas,
                     double *arrTotalPagadas,
                     double *arrTotalPendientes, int cantDni) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/ReporteDeMultas.txt", archReporte);
    imprimirEncabezado(archReporte);
    double totalMultas = 0, totalPagadas = 0, totalPendientes = 0;
    for (int i = 0; i < cantDni; i++) {
        archReporte << setw(3) << ' ' << setfill('0') << setw(2) << i + 1 << ")" << setfill(' ') << setw(5) << ' ' <<
                arrDni[i] << setw(6) << ' ';
        imprimirFecha(archReporte, arrMasMultaAntigua[i]);
        archReporte << setw(6) << ' ';
        imprimirFecha(archReporte, arrUltimaMulta[i]);
        archReporte << setw(6) << ' ' << setw(8) << arrTotalMultas[i] <<
                setw(6) << ' ' << setw(8) << arrTotalPagadas[i]
                << setw(6) << ' ' << setw(8) << arrTotalPendientes[i] << endl;
        totalMultas += arrTotalMultas[i];
        totalPagadas += arrTotalPagadas[i];
        totalPendientes += arrTotalPendientes[i];
    }
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte <<"TOTALES:"<< setw(48) << ' ' << setw(8) << totalMultas << setw(5) << ' ' << setw(8) << totalPagadas << setw(5) <<
            ' ' << setw(8) << totalPendientes << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(38) << ' ' << "MINISTERIO DE TRANSPORTES" << endl;
    archReporte << setw(39) << ' ' << "LISTADO DE INFRACCIONES" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(26) << ' ' << "MULTA MAS" << setw(5) << ' ' << "ULTIMA MULTA" << setw(5) << ' ' << "TOTAL EN"
            << setw(7) << ' ' << "MULTAS" << setw(8) << ' ' << "MULTAS" << endl;
    archReporte << setw(3) << ' ' << "No." << setw(8) << ' ' << "DNI" << setw(10) << ' ' << "ANTIGUA"
            << setw(9) << ' ' << "PAGADA" << setw(9) << ' ' << "MULTAS" << setw(8) << ' ' << "PAGADA" << setw(6) << ' '
            << "PENDIENTES"
            << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}

void imprimirFecha(ofstream &archReporte, int arrUltimaMulta) {
    int anhio = arrUltimaMulta / 10000;
    int mes = (arrUltimaMulta % 10000) / 100;
    int dia = arrUltimaMulta % 100;
    archReporte << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}
