#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 9/11/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void generaArchivoEnlace(const char *categoria, char *nombArch, char *enlace) {
    char cadena[150];
    strcpy(cadena, categoria);

    if (cadena[0] >= 'a' and cadena[0] <= 'z') {
        cadena[0] -= ('a' - 'A');
    }

    for (int i = 1; cadena[i] != '\0'; i++) {
        if (cadena[i - 1] == '_' and cadena[i] >= 'a' and cadena[i] <= 'z') {
            cadena[i] -= ('a' - 'A');
        }
    }

    strcpy(nombArch, "ArchivosDeReporte/");
    strcat(nombArch, cadena);
    strcat(nombArch, ".txt");

    strcpy(enlace, "https://Laboratorio06_2025_2/ArchivosDeReporte/");
    strcat(enlace, cadena);
}

void leerArrCategorias(char **arrCodCat, char **arrNombCat, int &cantCategorias) {
    ifstream archCat;
    abrirArchivoIfstream("ArchivosDeDatos/Categorias.txt", archCat);
    //UM163F47   just_chatting
    int i = 0;
    while (true) {
        arrCodCat[i] = leerCadenaExacta(archCat, ' ');
        if (archCat.eof()) break;
        arrNombCat[i] = leerCadenaExacta(archCat, '\n');
        i++;
    }
    cantCategorias = i;
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
    char aux[100], *ptr;
    arch.getline(aux, 100, delim);
    if (arch.eof()) return nullptr;
    ptr = new char[strlen(aux) + 1];
    strcpy(ptr, aux);
    return ptr;
}

void imprimirReporteCat(char **arrCodCat, char **arrNombCat, int cantCategorias) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt", archReporte);
    archReporte << setw(1) << ' ' << "REPORTE PARA CATEGORIAS" << endl;
    archReporte << "CODIGO" << setw(7) << ' ' << "NOMBRE" << endl;
    imprimirLinea(archReporte, 50, '-');
    for (int i = 0; i < cantCategorias; i++) {
        archReporte << arrCodCat[i] << setw(4) << ' ' << arrNombCat[i] << endl;
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch << endl;
}

void leerArrStreams(int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                    double *arrTasaDOffStream, int *arrDuracion, int &cantStreams) {
    ifstream archStream;
    abrirArchivoIfstream("ArchivosDeDatos/Reproducciones.txt", archStream);
    //31/8/2025  Sardoche    ZT132U54    4.410    0.715    1:41:48
    int dd, mes, anhio, hh, min, ss, i = 0;
    char c;
    while (true) {
        archStream >> dd;
        if (archStream.eof()) break;
        archStream >> c >> mes >> c >> anhio;
        arrNombCanal[i] = leerCadenaExacta(archStream, ' ');
        arrCodCate[i] = leerCadenaExacta(archStream, ' ');
        archStream >> arrRatingStream[i] >> arrTasaDOffStream[i] >> hh >> c >> min >> c >> ss;
        convertirFecha(dd, mes, anhio, arrFecha[i]);
        convertirHora(hh, min, ss, arrDuracion[i]);
        i++;
    }
    cantStreams = i;
}

void convertirFecha(int dd, int mes, int anhio, int &arrFecha) {
    arrFecha = anhio * 10000 + mes * 100 + dd;
}

void convertirHora(int hh, int min, int ss, int &arrDuracion) {
    arrDuracion = hh * 3600 + min * 60 + ss;
}

void imprimirReporteStream(int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                           double *arrTasaDOffStream, int *arrDuracion, int cantStreams) {
    ofstream archReporte;
    abrirArchivoOfstream("ArchivosDeReporte/ReporteDePruebaDeStreamsReproducidos.txt", archReporte);
    archReporte << setw(50) << ' ' << "REPORTE PARA STREAMS" << endl;
    archReporte << "FECHA" << setw(10) << ' ' << "NOMBRE" << setw(16) << ' ' << "CODIGO" << setw(8) << ' ' << "RATING"
            << setw(2) << ' ' << "TASA DROP O." << setw(2) << ' ' << "DURACION" << endl;
    imprimirLinea(archReporte, TAM_MAX, '-');
    for (int i = 0; i < cantStreams; i++) {
        imprimirFecha(archReporte, arrFecha[i]);
        archReporte << setw(5) << ' ' << arrNombCanal[i] << setw(20 - strlen(arrNombCanal[i])) << ' '
                << arrCodCate[i] << setw(15 - strlen(arrCodCate[i])) << ' ' << setw(6) << arrRatingStream[i]
                << setw(5) << ' ' << setw(6) << arrTasaDOffStream[i] << setw(6) << ' ';
        imprimirHora(archReporte, arrDuracion[i]);
        archReporte << endl;
    }
}

void imprimirFecha(ofstream &arch, int fecha) {
    int anhio = fecha / 10000;
    int mes = (fecha % 10000) / 100;
    int dd = (fecha % 100);
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void imprimirHora(ofstream &arch, int duracion) {
    int hh = duracion / 3600;
    int mm = (duracion % 3600) / 60;
    int ss = (duracion % 60);
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ');
}

void imprimirReportes(char **arrCodCat, char **arrNombCat, int cantCategorias,
                      int *arrFecha, char **arrNombCanal, char **arrCodCate, double *arrRatingStream,
                      double *arrTasaDOffStream, int *arrDuracion, int cantStreams) {
    char nombArch[200], enlace[300];

    for (int i = 0; i < cantCategorias; i++) {
        generaArchivoEnlace(arrNombCat[i], nombArch, enlace);

        ofstream archReporte;
        abrirArchivoOfstream(nombArch, archReporte);
        imprimirEncabezado(archReporte, arrCodCat[i], arrNombCat[i], enlace);
        int cant = 0, duracionTotal = 0;
        double sumaRat = 0, sumaTasaD = 0;
        for (int j = 0; j < cantStreams; j++) {
            if (strcmp(arrCodCat[i], arrCodCate[j]) == 0) {
                imprimirFecha(archReporte, arrFecha[j]);
                archReporte << setw(5) << ' ' << arrNombCanal[j] << setw(15 - strlen(arrNombCanal[j])) << ' ' <<
                        setw(6) << arrRatingStream[j] << setw(5) << ' ' << setw(6) << arrTasaDOffStream[j] <<
                        setw(5) << ' ';
                imprimirHora(archReporte, arrDuracion[j]);
                archReporte << endl;
                cant++;
                sumaRat += arrRatingStream[j];
                sumaTasaD += arrTasaDOffStream[j];
                duracionTotal += arrDuracion[j];
            }
        }
        imprimirResumen(archReporte,sumaRat,sumaTasaD,cant,duracionTotal);
    }
}

void imprimirEncabezado(ofstream &archReporte, const char *arrCodCat, const char *arrNombCat, const char *enlace) {
    archReporte << "Codigo: " << arrCodCat << endl;
    archReporte << "Nombre: " << arrNombCat << endl;
    archReporte << "Enlace: " << enlace << endl;
    archReporte << "REPRODUCCIONES:" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "FECHA" << setw(10) << ' ' << "CANAL" << setw(11) << ' ' << "RATING" << setw(4) << ' ' <<
            "DROP-OFF" << setw(3) << ' ' << "DURACION" << endl;
}

void imprimirResumen(ofstream &archReporte,double sumaRat,double sumaTasaD,int cant,int duracionTotal) {
    double promRat=sumaRat/cant;
    double promTasaD=sumaTasaD/cant;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte<<"PROMEDIO DE RATING:"<<setw(8)<<promRat<<endl;
    archReporte<<"PROMEDIO DE DROP-OFF:"<<setw(6)<<promTasaD<<endl;
    archReporte<<"DURACION TOTAL:"<<setw(4)<<' ';
    imprimirHora(archReporte,duracionTotal);
    archReporte<<endl;
}
