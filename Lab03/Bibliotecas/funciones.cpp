//
// Created by aml on 22/09/2025.
//
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte(ifstream &archCanales, ifstream &archEtiquetas, ifstream &archRepro, ofstream &archReporte) {
    double tarifaDuracion, rating;
    int dd, mes, anhio, numCanal, nroCanal = 0, etiqueta, etiqueta2;
    char codCanal, c;
    imprimirEncabezado(archReporte, tarifaDuracion);

    while (true) {
        int nroEtiqueta = 0, duracionSegunTotales = 0;
        archCanales >> dd;
        if (archCanales.eof()) break;
        nroCanal++;
        archCanales >> c >> mes >> c >> anhio >> ws;
        archCanales >> codCanal >> numCanal;
        leerNombre(archCanales, archReporte, dd, mes, anhio, codCanal, numCanal, nroCanal);
        archCanales >> rating;
        archReporte << right << setw(10) << ' ' << setw(4) << rating << endl;
        imprimirEncabezadoEtiquetas(archReporte);
        while (true) {
            archCanales >> etiqueta;
            imprimirEtiquetas(archEtiquetas, archRepro, archReporte, etiqueta,
                              codCanal, numCanal, nroEtiqueta, duracionSegunTotales);
            if (archCanales.get() == '\n')break;
        }
        imprimirEstadisticas(archReporte, duracionSegunTotales, rating, tarifaDuracion);
    }
}

void imprimirEncabezado(ofstream &archReporte, double &tarifaDuracion) {
    // cout<<"POR FAVOR INGRESE LA TARIFA POR DURACION"<<endl;
    // cin>>tarifaDuracion;
    tarifaDuracion = 0.78;
    archReporte << setw(40) << ' ' << "PLATAFORMA TP_Twitch" << endl;
    archReporte << setw(20) << ' ' << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifaDuracion <<
            " POR CADA MINUTO Y FRACCION" << endl;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void leerNombre(ifstream &archCanales, ofstream &archReporte, int dd, int mes, int anhio, char codCanal,
                int numCanal, int nroCanal) {
    imprimirEncabezadoCanal(archReporte, nroCanal);
    char c;
    int contador = 0;
    archCanales >> ws;
    archReporte << setw(5) << ' ';
    while (true) {
        c = archCanales.get();
        contador++;
        if (c == ' ')break;
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        archReporte.put(c);
    }
    archReporte << setw(18 - contador) << ' ' << codCanal << numCanal << setw(5) << ' ';
    imprimirFecha(archReporte, dd, mes, anhio);
}

void imprimirEncabezadoCanal(ofstream &archReporte, int nroCanal) {
    imprimirLinea(archReporte, TAM_MAX, '=');
    archReporte << "CANAL No. " << nroCanal << endl;
    archReporte << setw(5) << ' ' << "NOMBRE" << setw(10) << ' ' << "CODIGO" << setw(5) << ' ' << "CREADO EL"
            << setw(5) << ' ' << "RATING DE CALIDAD" << endl;
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio <<
            setfill(' ');
}

void imprimirEtiquetas(ifstream &archEtiquetas, ifstream &archRepro, ofstream &archReporte, int etiqueta
                       , char codCanal, int numCanal, int &nroEtiqueta, int &duracionSegunTotales) {
    archRepro.clear();
    archRepro.seekg(0, ios::beg);
    int dd, mes, anhio, numCanalArch, cantRepro, etiquetaArch;
    char c, codCanalArch;

    while (true) {
        archRepro >> dd;
        if (archRepro.eof()) break;
        archRepro >> c >> mes >> c >> anhio >> ws;
        archRepro >> codCanalArch >> numCanalArch >> etiquetaArch;

        if (codCanal == codCanalArch and numCanalArch == numCanal and etiquetaArch == etiqueta) {
            nroEtiqueta++;
            archRepro >> cantRepro;
            archReporte << setw(5) << ' ' << setfill('0') << setw(2) << nroEtiqueta << ")" << setfill(' ');
            imprimirDatos(archReporte, dd, mes, anhio, etiqueta);
            imprimirDescripcion(archEtiquetas, archReporte, etiqueta, cantRepro, duracionSegunTotales);
        } else {
            while (true) {
                if (archRepro.get() == '\n') break;
            }
        }
    }
}

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int etiqueta) {
    archReporte << setw(3) << ' ';
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(3) << ' ' << etiqueta << setw(4) << ' ';
}

void imprimirDescripcion(ifstream &archEtiquetas, ofstream &archReporte, int etiqueta, int cantRepro,
                         int &duracionSegunTotales) {
    archEtiquetas.clear();
    archEtiquetas.seekg(0, ios::beg);
    int etiquetaArch, duracionReproSegundos;
    int hhD, minD;
    while (true) {
        archEtiquetas >> etiquetaArch;
        if (archEtiquetas.eof()) break;
        archEtiquetas >> ws;
        if (etiquetaArch == etiqueta) {
            leerDescripcion(archEtiquetas, archReporte, hhD, minD, cantRepro, duracionSegunTotales);
        } else {
            while (true) {
                if (archEtiquetas.get() == '\n') break;
            }
        }
    }
}

void leerDescripcion(ifstream &archEtiquetas, ofstream &archReporte, int &hhD, int &minD, int cantRepro,
                     int &duracionSegunTotales) {
    char c;
    int contador = 0, hhFinal, minFinal, ssFinal;
    int segundosDuracion, duracionReproSegundos;
    archEtiquetas >> ws;
    archReporte << setw(5) << ' ';
    while (true) {
        c = archEtiquetas.get();
        contador++;
        if (c == ' ')break;

        archReporte.put(c);
    }
    archEtiquetas >> hhD >> c >> minD;
    segundosDuracion = hhD * 3600 + minD * 60;
    duracionReproSegundos = segundosDuracion * cantRepro;
    duracionSegunTotales += duracionReproSegundos;
    calcularHora(duracionReproSegundos, hhFinal, minFinal, ssFinal);
    archReporte << setw(20 - contador) << ' ' << setfill('0') << setw(2) << hhD << ":" << setw(2) << minD
            << setfill(' ') << setw(16) << ' ' << setw(4) << cantRepro << setw(24) << ' ';
    imprimirHora(archReporte, hhFinal, minFinal, ssFinal);
    archReporte << endl;
}

void imprimirEncabezadoEtiquetas(ofstream &archReporte) {
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << "ETIQUETAS REPRODUCIDAS:" << endl;
    archReporte << setw(5) << ' ' << "No." << setw(5) << ' ' << "FECHA" << setw(5) << ' ' << "ETIQUETA" <<
            setw(7) << ' ' << "DESCRIPCION" << setw(8) << ' ' << "DURACION" << setw(5) << ' ' <<
            "CANTIDAD DE REPRODUCCIONES" <<
            setw(5) << ' ' << "TIEMPO TOTAL REPRODUCIDO" << endl;
}

void calcularHora(int duracionReproSegundos, int &hhFinal, int &minFinal, int &ssFinal) {
    hhFinal = duracionReproSegundos / 3600;
    minFinal = (duracionReproSegundos % 3600) / 60;
    ssFinal = duracionReproSegundos % 60;
}

void imprimirHora(ofstream &archReporte, int hhFinal, int minFinal, int ssFinal) {
    archReporte << setfill('0') << setw(2) << hhFinal << ":" << setw(2) << minFinal << ":" << setw(2) << ssFinal <<
            setfill(' ');
}

void imprimirEstadisticas(ofstream &archReporte, int duracionSegunTotales, int rating, double tarifaDuracion) {
    imprimirLinea(archReporte, TAM_MAX, '-');
    double porcentaje;
    int hh, min, ss;
    double horaEnMinutos = (double)( duracionSegunTotales % 3600) / 60;
    calcularHora(duracionSegunTotales, hh, min, ss);
    archReporte << "TIEMPO TOTAL DE REPRODUCCIONES DE ETIQUETAS:" << setw(4) << ' ';
    imprimirHora(archReporte, hh, min, ss);
    archReporte << endl;
    archReporte << "PORCENTAJE POR RATING DE CALIDAD:" << setw(21) << ' ';
    imprimirRating(archReporte, rating, porcentaje);
    double ingresos = horaEnMinutos * porcentaje * tarifaDuracion;
    archReporte << "INGRESOS POR REPRODUCCION DE ETIQUETAS:" << setw(14) << ' ' << setw(5) << ingresos << endl;
}

void imprimirRating(ofstream &archReporte, int rating, double &porcentaje) {
    if (rating <= 5 and rating >= 4) {
        archReporte << "+30%";
        porcentaje = 130 / 100;
    } else if (rating < 4 and rating >= 3) {
        archReporte << "+20%";
        porcentaje = 120 / 100;
    } else if (rating < 3 and rating >= 2) {
        archReporte << "+0%";
        porcentaje = 100 / 100;
    } else if (rating < 2 and rating >= 1) {
        archReporte << "-25%";
        porcentaje = 75 / 100;
    }
    archReporte << endl;
}
