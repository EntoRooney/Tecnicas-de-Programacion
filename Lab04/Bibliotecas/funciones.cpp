//
// Created by aml on 29/09/2025.
//
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "funciones.h"
#define TAM_MAX 120
#define TAM_CANAL 48
#define TAM_ETI 26


void leerCanales(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int &cantCanales) {
    ifstream archCanales("ArchivosDeDatos/Canales.txt", ios::in);
    if (not archCanales.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/Canales.txt no se puede abrir correctamente";
        exit(1);
    }

    int etiqueta, i = 0, fechaConvertida, dd, mes, anhio;
    char c;
    while (true) {
        archCanales >> dd;
        if (archCanales.eof()) break;
        archCanales >> c >> mes >> c >> anhio >> ws;
        convertirFecha(dd, mes, anhio, fechaConvertida);
        arrFecha[i] = fechaConvertida;
        archCanales >> arrCodigo[i];
        archCanales >> arrNumCod[i];
        eliminarTexto(archCanales);
        archCanales >> arrRating[i];

        while (true) {
            archCanales >> etiqueta;
            if (archCanales.get() == '\n') break;
        }
        i++;
    }
    cantCanales = i;
}

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void eliminarTexto(ifstream &archCanales) {
    char c;
    archCanales >> ws;
    while (true) {
        c = archCanales.get();
        if (c == ' ' or c == '\n') break;
    }
}

void leerEtiquetas(int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int &cantEtiquetas) {
    ifstream archEtiquetas("ArchivosDeDatos/Etiquetas.txt", ios::in);
    if (not archEtiquetas.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/Etiquetas.txt no se puede abrir correctamente";
        exit(1);
    }
    int i = 0;
    char c;

    while (true) {
        archEtiquetas >> arrEtiquetas[i];
        if (archEtiquetas.eof()) break;
        eliminarTexto(archEtiquetas);
        archEtiquetas >> arrDuracionMin[i] >> c >> arrDuracionSeg[i];
        i++;
    }
    cantEtiquetas = i;
}

void emitirReporteCanales(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int cantCanales) {
    ofstream archReporte("ArchivosDeReporte/Reporte_Canales.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR, el archivo ArchivosDeReporte/Reporte_Canales.txt no se puede abrir correctamente";
        exit(1);
    }
    archReporte << fixed << setprecision(2);
    archReporte << right << setw(10) << ' ' << "REPORTE PARA CANALES" << endl;
    archReporte << setw(3) << ' ' << "FECHA EMITIDA" << setw(7) << ' ' << "CODIGO" << setw(8) << ' ' << "RATING" <<
            endl;
    imprimirLinea(archReporte,TAM_CANAL, '=');

    for (int i = 0; i < cantCanales; i++) {
        archReporte << setw(3) << ' ';
        imprimirFecha(arrFecha[i], archReporte);
        archReporte << setw(10) << ' ' << arrCodigo[i] << arrNumCod[i] << setw(10) << ' ' << setw(4) <<
                arrRating[i] << endl;
    }
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirFecha(int fecha, ofstream &archReporte) {
    int anhio = fecha / 10000;
    int mes = (fecha % 10000) / 100;
    int dia = (fecha % 100);
    archReporte << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void emitirReporteEtiquetas(int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int cantEtiquetas) {
    ofstream archReporte("ArchivosDeReporte/Reporte_Etiquetas.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR, el archivo ArchivosDeReporte/Reporte_Etiquetas.txt no se puede abrir correctamente";
        exit(1);
    }
    archReporte << right << setw(1) << ' ' << "REPORTE PARA ETIQUETAS" << endl;
    archReporte << setw(2) << ' ' << "ETIQUETA" << setw(3) << ' ' << "DURACION" << endl;
    imprimirLinea(archReporte,TAM_ETI, '=');

    for (int i = 0; i < cantEtiquetas; i++) {
        archReporte << setw(3) << ' ' << arrEtiquetas[i] << setw(5) << ' ' << setfill('0') << setw(2) <<
                arrDuracionMin[i] << ":" << setw(2) << arrDuracionSeg[i] << setfill(' ') << endl;
    }
}

void emitirReporte(int *arrFecha, char *arrCodigo, int *arrNumCod, double *arrRating, int cantCanales,
                   int *arrEtiquetas, int *arrDuracionMin, int *arrDuracionSeg, int cantEtiquetas,
                   int *arrNumRepro, int *arrSegundosTotales) {
    ifstream archRepro("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt", ios::in);
    if (not archRepro.is_open()) {
        cout << "ERROR, el archivo ArchivosDeDatos/ReproduccionesDeEtiquetas.txt.txt no se puede abrir correctamente";
        exit(1);
    }

    ofstream archReporte("ArchivosDeReporte/ReporteDeCanales_Y_Etiquetas.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR, el archivo ArchivosDeReporte/ReporteDeCanales_Y_Etiquetas.txt no se puede abrir correctamente";
        exit(1);
    }

    int idCanal, dd, mes, anhio, idEtiqueta, numCanalArch, etiqueta, numRepro, duracionSeg;
    double tarifa;
    char c, codCanalArch;
    imprimirEncabezado(archReporte, tarifa);
    while (true) {
        int totalSegundos = 0;
        archRepro >> dd;
        if (archRepro.eof()) break;
        archRepro >> c >> mes >> c >> anhio >> ws;
        archRepro >> codCanalArch >> numCanalArch;
        idCanal = buscarIdCanal(codCanalArch, numCanalArch, arrCodigo, arrNumCod,
                                cantCanales);
        if (idCanal >= 0) {
            archRepro >> etiqueta >> numRepro;
            arrNumRepro[idCanal] += numRepro;
            idEtiqueta = buscarIdEtiqueta(arrEtiquetas, etiqueta, cantEtiquetas);
            if (idEtiqueta >= 0) {
                convertirSegundos(arrDuracionMin[idEtiqueta], arrDuracionSeg[idEtiqueta],
                                  duracionSeg);
                totalSegundos += duracionSeg;
            } else {
                while (true) if (archRepro.get() == '\n')break;
            }
        } else {
            while (true) {
                if (archRepro.get() == '\n')break;
            }
        }
        arrSegundosTotales[idCanal] = totalSegundos*arrNumRepro[idCanal];
    }
    imprimirCanales(archReporte, arrCodigo, arrNumCod, arrFecha, arrRating, arrNumRepro, arrSegundosTotales,
                    cantCanales);
}

int buscarIdCanal(char codCanalArch, int numCanalArch, char *arrCodigo, int *arrNumCod, int cantCanales) {
    for (int i = 0; i < cantCanales; i++) {
        if (arrCodigo[i] == codCanalArch and arrNumCod[i] == numCanalArch) {
            return i;
        }
    }
    return -1;
}

void imprimirEncabezado(ofstream &archReporte, double &tarifa) {
    // cout<<"POR FAVOR INGRESE LA TARIFA POR DURACION"<<endl;
    // cin>>tarifa;
    tarifa = 0.78;
    archReporte << setw(10) << ' ' << "PLATAFORMA TP_Twitch" << endl;
    archReporte << setw(10) << ' ' << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifa <<
            " POR CADA MINUTO Y FRACCION" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "CANALES ADSCRITOS A LA PLATAFORMA" << endl;
}

void imprimirCanales(ofstream &archReporte, char *arrCodigo, int *arrNumCod, int *arrFecha, double *arrRating,
                     int *arrNumRepro, int *arrSegundosTotales, int cantCanales) {
    double rating;
    archReporte << right;
    archReporte << fixed << setprecision(2);
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(37) << ' ' << "RATING DE" << setw(6) << ' ' << "NUMERO TOTAL" << setw(6) << ' ' <<
            "TIEMPO TOTAL DE" << setw(4) << ' ' << "PORCENTAJE POR" << setw(3) << ' ' <<
            "INGRESOS POR REPRODUCCION" << endl;
    archReporte << "No." << setw(4) << ' ' << "CODIGO" << setw(4) << ' ' << "FECHA DE CREACION" << setw(4) << ' ' <<
            "CALIDAD" << setw(4) << ' ' << "DE REPRODUCCIONES" << setw(4) << ' ' << "REPRODUCCIONES"
            << setw(4) << ' ' << "RATING DE CALIDAD" << setw(4) << ' ' << "DE ETIQUETAS" << endl;
    int k = 1;
    for (int i = 0; i < cantCanales; i++) {
        archReporte << setw(1) << ' ' << setw(3) << k << ")" << setw(3) << ' ' << arrCodigo[i] << arrNumCod[i] <<
                setw(10) << ' ';
        imprimirFecha(arrFecha[i], archReporte);
        archReporte << setw(5) << ' ' << setw(5) << arrRating[i] << setw(10) << ' ' << setw(5) << arrNumRepro[i]
                << setw(14) << ' '<<setw(12);
        archReporte<<left;
        imprimirHora(arrSegundosTotales[i], archReporte);
        archReporte <<right<<setw(6)<<' ';
        imprimirRating(arrRating[i],archReporte,rating);
        archReporte<<endl;
        k++;
    }
}

int buscarIdEtiqueta(int *arrEtiquetas, int etiqueta, int cantEtiquetas) {
    for (int i = 0; i < cantEtiquetas; i++) {
        if (arrEtiquetas[i] == etiqueta) {
            return i;
        }
    }
    return -1;
}

void convertirSegundos(int arrDuracionMin, int arrDuracionSeg, int &duracionSeg) {
    duracionSeg = arrDuracionMin * 60 + arrDuracionSeg;
}


void imprimirHora(int horaSeg, ofstream &archReporte) {
    int hh = horaSeg / 3600;
    int min = (horaSeg % 3600) / 60;
    int ss = (horaSeg % 60);
    archReporte << setfill('0') << setw(3) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void imprimirRating(double arrRating,ofstream &archReporte,double &rating) {
    if (arrRating>=5 and arrRating<4) {
        archReporte<<"+30%";
        rating=130.0/100;
    }else if (arrRating>=4 and arrRating<3) {
        archReporte<<"+20%";
        rating=120.0/100;
    }else if (arrRating>=3 and arrRating<2) {
        archReporte<<"+0%";
        rating=100.0/100;
    }else {
        archReporte<<"-25%";
        rating=75.0/100;
    }
}
