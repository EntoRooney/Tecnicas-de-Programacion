//
// Created by aml on 27/10/2025.
//
#include <iostream>
#include <fstream>
#include <iomanip>
//Ento Rooney Lazaro Trujillo
//20222032

using namespace std;

#include "funciones.h"
#define NO_ENCONTRADO -1
#define TAM_MAX 150

void leerArrStreams(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream,
                    char *arrCarCateStream, int *arrNumCateStream, int &cantStreams) {
    ifstream archStreams;
    abrirArchivoIfstream("ArchivosDeDatos/Streams.txt", archStreams);

    //803100    1:22:25    4003    C1072
//leemos los arreglos del stream
    int cod, hh, mm, ss, idioma, numCat, duracionSeg;
    char c, carCat;

    while (true) {
        archStreams >> cod;
        if (archStreams.eof()) break;
        archStreams >> hh >> c >> mm >> c >> ss >> idioma >> ws >> carCat >> numCat;
        convertirDuracion(hh, mm, ss, duracionSeg);
        insertarOrdenadoStreams(arrCodigoStream, arrDuracionStrem, arrIdiomaStream, arrCarCateStream, arrNumCateStream,
                                cantStreams, cod, duracionSeg, idioma, carCat, numCat);
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

void convertirDuracion(int hh, int mm, int ss, int &duracionSeg) {
    duracionSeg = hh * 3600 + mm * 60 + ss;
}

void insertarOrdenadoStreams(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream, char *arrCarCateStream,
                             int *arrNumCateStream, int &cantStreams, int cod, int duracionSeg, int idioma, char carCat,
                             int numCat) {
    int pos = cantStreams - 1;
//insertar ordenado
    while (pos >= 0 and arrCodigoStream[pos] > cod) {
        arrCodigoStream[pos + 1] = arrCodigoStream[pos];
        arrDuracionStrem[pos + 1] = arrDuracionStrem[pos];
        arrIdiomaStream[pos + 1] = arrIdiomaStream[pos];
        arrCarCateStream[pos + 1] = arrCarCateStream[pos];
        arrNumCateStream[pos + 1] = arrNumCateStream[pos];
        pos--;
    }
    arrCodigoStream[pos + 1] = cod;
    arrDuracionStrem[pos + 1] = duracionSeg;
    arrIdiomaStream[pos + 1] = idioma;
    arrCarCateStream[pos + 1] = carCat;
    arrNumCateStream[pos + 1] = numCat;
    cantStreams++;
}
//imprimimosreporte de prueba
void imprimirReportePrueba(int *arrCodigoStream, int *arrDuracionStrem, int *arrIdiomaStream, char *arrCarCateStream,
                           int *arrNumCateStream, int cantStreams) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/ReportePrueba.txt", archReporte);
    archReporte << right << fixed << setprecision(2);
    archReporte << " REPORTE DE PRUEBA PARA LOS STREAMS " << endl;
    archReporte << "CODIGO" << setw(5) << ' ' << "DURACION" << setw(5) << ' ' << "IDIOMA" << setw(2) << ' ' <<
            "CATEGORIA" << endl;
    imprimirLinea(archReporte, 60, '-');
    for (int i = 0; i < cantStreams; i++) {
        archReporte << arrCodigoStream[i] << setw(5) << ' ';
        imprimirDuracion(archReporte, arrDuracionStrem[i]);
        archReporte << setw(5) << ' ' << arrIdiomaStream[i] << setw(5) << ' ' << arrCarCateStream[i] << arrNumCateStream
                [i] << endl;
    }
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte.put('\n');
}

void imprimirDuracion(ofstream &archReporte, int arrDuracionStrem) {
    int hh = arrDuracionStrem / 3600;
    int mm = (arrDuracionStrem % 3600) / 60;
    int ss = (arrDuracionStrem) % 60;
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ');
}
//actualizamos los arreglos
void leerArrCanales(int *arrCodigoStream, int *arrIdiomaStream, char *arrCarCateStream, int *arrNumCateStream,
                    int *arrDuracionStrem, int *arrFechaMasAntigua, int *arrFechaMasReciente, double *arrPromRat,
                    double *arrPromDrop, int *arrNumRepro, int *arrDuracionTotal, int cantStreams) {
    ifstream archCanales;
    abrirArchivoIfstream("ArchivosDeDatos/Canales.txt", archCanales);

    int bsr, cod, ddR, mesR, anhioR, fecha;
    double rating, drop;
    char c;

    while (true) {
        archCanales >> bsr >> c >> bsr >> c >> bsr;
        if (archCanales.eof()) break;
        archCanales >> ws >> c >> bsr;
        eliminarTexto(archCanales);
        while (true) {
            archCanales >> cod >> ddR >> c >> mesR >> c >> anhioR >> bsr >> c >> bsr >> c >> bsr >> rating >> drop;
            int idCodigo = busquedaBinaria(cod, arrCodigoStream, cantStreams);
            convertirFecha(ddR, mesR, anhioR, fecha);
            if (idCodigo != NO_ENCONTRADO) {
                actualiazarArr(arrFechaMasAntigua[idCodigo], arrFechaMasReciente[idCodigo], arrPromRat[idCodigo],
                               arrPromDrop[idCodigo], arrNumRepro[idCodigo], arrDuracionTotal[idCodigo], fecha, rating,
                               drop, arrDuracionStrem[idCodigo]);
            }
            if (archCanales.get() == '\n') break;
        }
    }
    for (int i = 0; i < cantStreams; i++) {
        if (arrNumRepro[i] != 0) {
            (arrPromDrop[i] /= arrNumRepro[i]);
            arrPromRat[i] /= arrNumRepro[i];
        }
    }
}

void eliminarTexto(ifstream &archCanales) {
    archCanales >> ws;
    while (true) {
        if (archCanales.get() == ' ')break;
    }
}

int busquedaBinaria(int cod, int *arrCodigoStream, int cantStreams) {
    int limInf = 0, limSup = cantStreams - 1, puntoMedio;

    while (true) {
        if (limInf > limSup) return NO_ENCONTRADO;
        puntoMedio = (limInf + limSup) / 2;
        if (arrCodigoStream[puntoMedio] == cod) return puntoMedio;
        if (arrCodigoStream[puntoMedio] > cod) {
            limSup = puntoMedio - 1;
        } else {
            limInf = puntoMedio + 1;
        }
    }
}

void convertirFecha(int dd, int mes, int anhio, int &fecha) {
    fecha = anhio * 10000 + mes * 100 + dd;
}

void actualiazarArr(int &arrFechaMasAntigua, int &arrFechaMasReciente, double &arrPromRat,
                    double &arrPromDrop, int &arrNumRepro, int &arrDuracionTotal, int fecha, double rating,
                    double drop, int arrDuracionStrem) {
    if (arrFechaMasAntigua == 0 or fecha < arrFechaMasAntigua) {
        arrFechaMasAntigua = fecha;
    }

    if (arrFechaMasReciente == 0 or fecha > arrFechaMasReciente) {
        arrFechaMasReciente = fecha;
    }
    arrPromRat += rating;
    arrPromDrop += drop;
    arrNumRepro++;
    arrDuracionTotal += arrDuracionStrem;
}

void imprimirReporte(const char *nombArch, bool imprimirResumen, int *arrCodigoStream, int *arrIdiomaStream,
                     char *arrCarCateStream, int *arrNumCateStream, int *arrDuracionStrem, int *arrFechaMasAntigua,
                     int *arrFechaMasReciente, double *arrPromRat, double *arrPromDrop, int *arrNumRepro,
                     int *arrDuracionTotal,
                     int cantStreams) {
    ofstream archReporte;
    abrirArchivoOfstream(nombArch, archReporte);
    imprimirEncabezado(archReporte);
    int menorDuracion = 1000000, mayorDuracion = -1, codMenor, codMayor;
    for (int i = 0; i < cantStreams; i++) {
        archReporte << setw(1) << ' ' << arrCodigoStream[i] << setw(5) << ' ' << arrIdiomaStream[i]
                << setw(5) << ' ' << arrCarCateStream[i] << arrNumCateStream[i] << setw(5) << ' ';
        imprimirDuracion(archReporte, arrDuracionStrem[i]);
        archReporte << setw(5) << ' ';
        if (arrFechaMasAntigua[i] != 0) {
            imprimirFecha(archReporte, arrFechaMasAntigua[i]);
            archReporte << setw(5) << ' ';
            imprimirFecha(archReporte, arrFechaMasReciente[i]);
            archReporte << setw(9) << ' ' << setw(5) << arrPromRat[i] << setw(12) << ' ' << setw(5) <<
                    arrPromDrop[i] * 100 << "%"
                    << setw(12) << ' ' << setw(5) << arrNumRepro[i] << setw(9) << ' ';
            imprimirDuracion(archReporte, arrDuracionTotal[i]);
            calcularResumen(arrCodigoStream[i], arrDuracionTotal[i],
                            menorDuracion, codMenor, mayorDuracion, codMayor);
        } else {
            archReporte << "NO ENCONTRADO";
        }
        archReporte << endl;
    }
    if (imprimirResumen) {
        imprimirDatosResumen(archReporte, menorDuracion, codMenor, mayorDuracion, codMayor);
    }
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << right << fixed << setprecision(2);
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(37) << ' ' << "PLATAFORMA DE STREAMING TP" << endl;
    archReporte << setw(28) << ' ' << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "STREAM" << setw(5) << ' ' << "IDIOMA" << setw(3) << ' ' << "CATEGORIA" << setw(2) << ' ' <<
            "DURACION"
            << setw(4) << ' ' << "REP.ANTIGUA" << setw(4) << ' ' << "REP.RECIENTE" << setw(3) << ' ' << "PROM.RAT.CAL"
            << setw(2) << ' ' << "PROM.TASA.DROP-OFF"
            << setw(9) << ' ' << "#REPRO." << setw(5) << ' ' << "TOT.REPR." << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}


void imprimirFecha(ofstream &archReporte, int arrFechaMasReciente) {
    int anhio = arrFechaMasReciente / 10000;
    int mm = (arrFechaMasReciente % 10000) / 100;
    int dd = (arrFechaMasReciente) % 100;
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << anhio << setfill(' ');
}

void calcularResumen(int arrCodigoStream, int arrDuracionTotal, int &menorDuracion, int &codMenor,
                     int &mayorDuracion, int &codMayor) {
    if (arrDuracionTotal < menorDuracion) {
        menorDuracion = arrDuracionTotal;
        codMenor = arrCodigoStream;
    }
    if (arrDuracionTotal > mayorDuracion) {
        mayorDuracion = arrDuracionTotal;
        codMayor = arrCodigoStream;
    }
}

void imprimirDatosResumen(ofstream &archReporte, int menorDuracion, int codMenor, int mayorDuracion, int codMayor) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "RESUMEN:" << endl;
    archReporte << "STREAM CON MAYOR DURACION" << setw(5) << ' ' << codMayor << " - ";
    imprimirDuracion(archReporte, mayorDuracion);
    archReporte << " hrs." << endl;
    archReporte << "STREAM CON MENOR DURACION" << setw(5) << ' ' << codMenor << " - ";
    imprimirDuracion(archReporte, menorDuracion);
    archReporte << " hrs." << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}
//ordenamos usando burbuja
void ordenarArr(int *arrCodigoStream, int *arrIdiomaStream,
                char *arrCarCateStream, int *arrNumCateStream, int *arrDuracionStrem, int *arrFechaMasAntigua,
                int *arrFechaMasReciente, double *arrPromRat, double *arrPromDrop, int *arrNumRepro,
                int *arrDuracionTotal,
                int cantStreams) {
    for (int i = 0; i < cantStreams - 1; i++) {
        for (int j = i; j < cantStreams; j++) {
            if ((((arrCarCateStream[i] > arrCarCateStream[j]) or (arrCarCateStream[i] == arrCarCateStream[j]
            and arrNumCateStream[i] > arrNumCateStream[j])) or (arrCarCateStream[i] == arrCarCateStream[j]
            and arrNumCateStream[i] == arrNumCateStream[j]) and arrPromDrop[i] < arrPromDrop[j])) {
                //if (arrPromDrop[i] > arrPromDrop[j]) {
                    intercambiarInt(arrCodigoStream[i], arrCodigoStream[j]);
                    intercambiarInt(arrIdiomaStream[i], arrIdiomaStream[j]);
                    intercambiarChar(arrCarCateStream[i], arrCarCateStream[j]);
                    intercambiarInt(arrNumCateStream[i], arrNumCateStream[j]);
                    intercambiarInt(arrDuracionStrem[i], arrDuracionStrem[j]);
                    intercambiarInt(arrFechaMasAntigua[i], arrFechaMasAntigua[j]);
                    intercambiarInt(arrFechaMasReciente[i], arrFechaMasReciente[j]);
                    intercambiarDouble(arrPromRat[i], arrPromRat[j]);
                    intercambiarDouble(arrPromDrop[i], arrPromDrop[j]);
                    intercambiarInt(arrNumRepro[i], arrNumRepro[j]);
                    intercambiarInt(arrDuracionTotal[i], arrDuracionTotal[j]);
                //}
            }
        }
    }
}


void intercambiarInt(int &datoI, int &datoJ) {
    int aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void intercambiarChar(char &datoI, char &datoJ) {
    char aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void intercambiarDouble(double &datoI, double &datoJ) {
    double aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}
