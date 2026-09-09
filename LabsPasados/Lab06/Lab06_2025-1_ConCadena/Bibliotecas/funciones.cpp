#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>

using namespace std;

//
// Created by USUARIO on 2/11/2025.
//

#include "funciones.h"
#define NO_ENCONTRADO -1
#define TAM_MAX 150

void leerArrCodInfra(int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantInfra) {
    ifstream archTabla;
    abrirArchivoIfstream("ArchivosDeDatos/TablaDeInfracciones.txt", archTabla);
    int cod;
    double multa;

    while (true) {
        archTabla >> cod >> multa;
        if (archTabla.eof()) break;
        eliminarTexto(archTabla);
        insertarOrdenado(cod, multa, arrCodigoInfraccion, arrMultasInfraccion, cantInfra);
    }
}

void abrirArchivoIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo" << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchivoOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo" << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void eliminarTexto(ifstream &archTabla) {
    archTabla >> ws;
    while (true) {
        if (archTabla.get() == '\n') break;
    }
}

void insertarOrdenado(int cod, double multa, int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantInfra) {
    int pos = cantInfra - 1;
    while (pos >= 0 and arrCodigoInfraccion[pos] > cod) {
        arrCodigoInfraccion[pos + 1] = arrCodigoInfraccion[pos];
        arrMultasInfraccion[pos + 1] = arrMultasInfraccion[pos];
        pos--;
    }
    arrCodigoInfraccion[pos + 1] = cod;
    arrMultasInfraccion[pos + 1] = multa;
    cantInfra++;
}


void imprimirReportePrueba(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfra) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/PruebaTablaInf.txt", archReporte);
    archReporte << right << fixed << setprecision(2);
    archReporte << "REPORTE DE PRUEBA PARA CODIGOS" << endl;
    archReporte << "CODIGOS" << setw(5) << ' ' << "MULTA" << endl;
    imprimirLinea(archReporte, 45, '-');
    for (int i = 0; i < cantInfra; i++) {
        archReporte << arrCodigoInfraccion[i] << setw(5) << ' ' << setw(8) << arrMultasInfraccion[i] << endl;
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch.put('\n');
}

void leerMultasCometidas(int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfra,
                         int *arrDni, int *arrMultaMasAntigua, int *arrMultaMasRecientePagada,
                         double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int &cantDni) {
    ifstream archInfra;
    abrirArchivoIfstream("ArchivosDeDatos/InfraccionesCometidas.txt", archInfra);
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/PlacasRegistradas.txt", archReporte);
    //23/7/2023      P474-593      89941095     2060   P     22/8/2023

    int ddC, mesC, anhioC, num1, num2, dni, cod, fechaCometida, fechaPagada;
    char c, carPlaca;
    while (true) {
        int ddP = 0, mesP = 0, anhioP = 0;
        archInfra >> ddC >> c >> mesC >> c >> anhioC;
        if (archInfra.eof()) break;
        archInfra >> ws >> carPlaca >> num1 >> c >> num2 >> dni >> cod;
        if (archInfra.peek() != '\n') {
            archInfra >> c >> ddP >> c >> mesP >> c >> anhioP;
        }
        archReporte << dni << setw(5) << ' ' << carPlaca << num1 << "-" << num2 << endl;
        convertirFecha(ddC, mesC, anhioC, fechaCometida);
        convertirFecha(ddP, mesP, anhioP, fechaPagada);
        int idDni = busquedaBinaria(dni, arrDni, cantDni);
        int idMulta = busquedaBinaria(cod, arrCodigoInfraccion, cantInfra);
        if (idMulta != NO_ENCONTRADO) {
            if (idDni != NO_ENCONTRADO) {
                actualizarDni(arrMultaMasAntigua[idDni], arrMultaMasRecientePagada[idDni], arrTotalMultas[idDni],
                              arrTotalPagadas[idDni], arrTotalPendientes[idDni],
                              fechaCometida, fechaPagada, arrMultasInfraccion[idMulta]);
            } else {
                insertarDni(dni, fechaCometida, fechaPagada, arrMultasInfraccion[idMulta], arrDni, arrMultaMasAntigua,
                            arrMultaMasRecientePagada, arrTotalMultas, arrTotalPagadas, arrTotalPendientes, cantDni);
            }
        }
    }
}

void convertirFecha(int dd, int mes, int anhio, int &fecha) {
    fecha = anhio * 10000 + mes * 100 + dd;
}

int busquedaBinaria(int codBuscado, int *arr, int cant) {
    int limInf = 0, limSup = cant - 1, puntoMedio;
    while (true) {
        if (limInf > limSup)return NO_ENCONTRADO;
        puntoMedio = (limInf + limSup) / 2;
        if (codBuscado == arr[puntoMedio]) return puntoMedio;
        if (arr[puntoMedio] > codBuscado) {
            limSup = puntoMedio - 1;
        } else {
            limInf = puntoMedio + 1;
        }
    }
}

void actualizarDni(int &arrMultaMasAntigua, int &arrMultaMasRecientePagada,
                   double &arrTotalMultas, double &arrTotalPagadas, double &arrTotalPendientes,
                   int fechaCometida, int fechaPagada, double arrMultasInfraccion) {
    if (arrMultaMasAntigua == 0 or arrMultaMasAntigua > fechaCometida) {
        arrMultaMasAntigua = fechaCometida;
    }
    if (arrMultaMasRecientePagada == 0 or arrMultaMasRecientePagada < fechaPagada) {
        arrMultaMasRecientePagada = fechaPagada;
    }
    if (fechaPagada != 0) {
        arrTotalPagadas += arrMultasInfraccion;
    } else {
        arrTotalPendientes += arrMultasInfraccion;
    }
    arrTotalMultas += arrMultasInfraccion;
}

void insertarDni(int dni, int fechaCometida, int fechaPagada, double multa, int *arrDni, int *arrMultaMasAntigua,
                 int *arrMultaMasRecientePagada, double *arrTotalMultas, double *arrTotalPagadas,
                 double *arrTotalPendientes, int &cantDni) {
    int pos = cantDni - 1;
    while (pos >= 0 and arrDni[pos] > dni) {
        arrDni[pos + 1] = arrDni[pos];
        arrMultaMasAntigua[pos + 1] = arrMultaMasAntigua[pos];
        arrMultaMasRecientePagada[pos + 1] = arrMultaMasRecientePagada[pos];
        arrTotalMultas[pos + 1] = arrTotalMultas[pos];
        arrTotalPagadas[pos + 1] = arrTotalPagadas[pos];
        arrTotalPendientes[pos + 1] = arrTotalPendientes[pos];
        pos--;
    }
    arrDni[pos + 1] = dni;
    arrMultaMasAntigua[pos + 1] = fechaCometida;
    if (fechaPagada != 0) {
        arrMultaMasRecientePagada[pos + 1] = fechaPagada;
        arrTotalPagadas[pos + 1] += multa;
    } else {
        arrTotalPendientes[pos + 1] += multa;
    }
    arrTotalMultas[pos + 1] += multa;
    cantDni++;
}

void imprimirReporte(int *arrDni, int *arrMultaMasAntigua, int *arrMultaMasRecientePagada,
                     double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int cantDni) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/ReporteDeMultas.txt", archReporte);
    ifstream archPlacas;
    abrirArchivoIfstream("ArchivosDeReporte/PlacasRegistradas.txt", archPlacas);
    imprimirEncabezado(archReporte);
    double totalMultas=0,totalPagadas=0,totalPendientes=0;
    for (int i = 0; i < cantDni; i++) {
        char listaDePlacas[100]{};
        buscarPlacas(archPlacas, arrDni[i], listaDePlacas);
        archReporte << setw(3) << ' ' << setfill('0') << setw(2) << i + 1 << ")" << setfill(' ');
        archReporte << setw(4) << ' ' << arrDni[i] << setw(5) << ' ';
        imprimirPlacas(archReporte, listaDePlacas, 50);
        imprimirFecha(archReporte, arrMultaMasAntigua[i]);
        archReporte << setw(5) << ' ';
        imprimirFecha(archReporte, arrMultaMasRecientePagada[i]);
        archReporte << setw(5) << ' ' << setw(8) << arrTotalMultas[i]
                << setw(5) << ' ' << setw(8) << arrTotalPagadas[i]
                << setw(5) << ' ' << setw(8) << arrTotalPendientes[i] << endl;
        totalMultas+=arrTotalMultas[i];
        totalPagadas+=arrTotalPagadas[i];
        totalPendientes+=arrTotalPendientes[i];
    }
    imprimirLinea(archReporte,TAM_MAX,'=');
    archReporte<<"TOTALES:"<<setw(94)<<' '<<setw(8)<<totalMultas
    <<setw(4)<<' '<<setw(8)<<totalPagadas
    <<setw(5)<<' '<<setw(8)<<totalPendientes<<endl;
    imprimirLinea(archReporte,TAM_MAX,'=');
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(50) << ' ' << "MINISTERIO DE TRANSPORTES" << endl;
    archReporte << setw(51) << ' ' << "LISTADO DE INFRACCIONES" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(73) << ' ' << "MULTA MAS" << setw(2) << ' ' << "ULTIMA MULTA" << setw(6) << ' ' << "TOTAL EN"
            << setw(6) << ' ' << "MULTAS" << setw(8) << ' ' << "MULTAS" << endl;
    archReporte << setw(3) << ' ' << "No." << setw(5) << ' ' << "DNI"
            << setw(27) << ' ' << "PLACAS"
            << setw(27) << ' ' << "ANTIGUA"
            << setw(6) << ' ' << "PAGADA"
            << setw(10) << ' ' << "MULTAS"
            << setw(7) << ' ' << "PAGADA"
            << setw(6) << ' ' << "PENDIENTES" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}

void imprimirFecha(ofstream &archReporte, int arrFecha) {
    int anhio = arrFecha / 10000;
    int mm = (arrFecha % 10000) / 100;
    int dd = (arrFecha % 100);
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << anhio << setfill(' ');
}

void buscarPlacas(ifstream &archPlacas, int dniBuscado, char *listaDePlacas) {
    int dniArch;
    char placa[10];

    archPlacas.clear();
    archPlacas.seekg(0, ios::beg);
    while (true) {
        archPlacas >> dniArch;
        if (archPlacas.eof())break;
        archPlacas >> placa;
        if (dniArch == dniBuscado) {
            agregarPlaca(listaDePlacas, placa);
        }
    }
}

void agregarPlaca(char *listaDePlacas, const char *placaNueva) {
    if (strlen(listaDePlacas) == 0) {
        strcpy(listaDePlacas, placaNueva);
        return;
    }
    char placaAux[10];
    int i = 0, j = 0;
    bool repetida = false;

    while (true) {
        if (listaDePlacas[i] == '/' or listaDePlacas[i] == '\0') {
            placaAux[j] = '\0';

            if (strcmp(placaAux, placaNueva) == 0) {
                repetida = true;
                break;
            }

            if (listaDePlacas[i] == '\0') break;
            j = 0;
        } else {
            placaAux[j++] = listaDePlacas[i];
        }
        i++;
    }
    if (not repetida) {
        strcat(listaDePlacas, "/");
        strcat(listaDePlacas, placaNueva);
    }
}

void imprimirPlacas(ofstream &archReporte, const char *listaDePlacas, int ancho) {
    int contador = strlen(listaDePlacas);
    archReporte << listaDePlacas << setw(ancho - contador) << ' ';
}
