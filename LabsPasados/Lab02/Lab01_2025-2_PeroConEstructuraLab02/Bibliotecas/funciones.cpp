#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 14/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte(ifstream &archDatos, ofstream &archReporte) {
    int fechaInicial, fechaFinal, ddC, mesC, anhioC, fechaConvertida, numCanal, dd, mes, anhio, hh, min, ss, cantRepro,
            cantCanal = 0, ddUltima, mesUltima, anhioUltima, cantTotalStreams = 0, horaFinalSegundos = 0, numCanalMax;
    double ingresosTotales = 0, ingresosMaximo = 0;
    char c, codCanal, codCanalMax;
    imprimirEncabezado(archReporte, fechaInicial, fechaFinal);
    while (true) {
        archDatos >> ddC;
        if (archDatos.eof()) break;
        archDatos >> c >> mesC >> c >> anhioC;
        convertirFecha(ddC, mesC, anhioC, fechaConvertida);
        if (fechaConvertida >= fechaInicial and fechaConvertida <= fechaFinal) {
            cantCanal++;
            archDatos >> codCanal >> numCanal;
            leerNombreCanal(archDatos, archReporte, cantCanal, ddC, mesC, anhioC, codCanal, numCanal);
            int horaTotalSegundos = 0, totalReproducciones = 0, fechaMax = 0;
            double ingresosPublicidad = 0;
            while (true) {
                archDatos >> dd >> c >> mes >> c >> anhio >> hh >> c >> min >> c >> ss >> cantRepro;
                imprimirDatos(archReporte, dd, mes, anhio, hh, min, ss, cantRepro, horaTotalSegundos,
                              fechaMax, ddUltima, mesUltima, anhioUltima,
                              totalReproducciones);
                cantTotalStreams++;
                if (archDatos.get() == '\n') break;
            }
            imprimirResumen(archReporte, horaTotalSegundos, ddUltima, mesUltima, anhioUltima, totalReproducciones,
                            ingresosPublicidad);
            horaFinalSegundos += horaTotalSegundos;
            ingresosTotales += ingresosPublicidad;
            calcularMayoresIngresos(ingresosPublicidad, codCanal, numCanal, ingresosMaximo, codCanalMax, numCanalMax);
        } else {
            while (true) {
                if (archDatos.get() == '\n') break;
            }
        }
    }
    imprimirResumenFinal(archReporte, cantTotalStreams, horaFinalSegundos, ingresosTotales, ingresosMaximo, codCanalMax,
                         numCanalMax);
}

void imprimirEncabezado(ofstream &archReporte, int &fechaInicial, int &fechaFinal) {
    int ddI, mesI, anhioI, ddF, mesF, anhioF;
    ddI = 9;
    mesI = 9;
    anhioI = 2022;
    ddF = 1;
    mesF = 1;
    anhioF = 2023;
    convertirFecha(ddI, mesI, anhioI, fechaInicial);
    convertirFecha(ddF, mesF, anhioF, fechaFinal);
    archReporte << setw(28) << " " << "PLATAFORMA TP_Twitch" << endl;
    archReporte << setw(20) << " " << "REGISTRO DE LOS CANALES AFILIADOS" << endl;
    archReporte << setw(15) << " " << "FECHAS DE CREACION ENTRE EL ";
    imprimirFecha(archReporte, ddI, mesI, anhioI);
    archReporte << " Y EL ";
    imprimirFecha(archReporte, ddF, mesF, anhioF);
    archReporte << endl;
}

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio <<
            setfill(' ');
}

void leerNombreCanal(ifstream &archDatos, ofstream &archReporte, int cantCanal, int ddC, int mesC, int anhioC,
                     char codCanal,
                     int numCanal) {
    int contador = 0, cantSeguidores;
    char c;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "Canal No. " << cantCanal << endl;
    archReporte << setw(6) << " " << "NOMBRE" << setw(14) << " " << "CODIGO" << setw(10) << " " << "CREADO EL" <<
            setw(5) << " "
            << "NUMERO DE SEGUIDORES" << endl;
    archDatos >> ws;
    archReporte << setw(6) << " ";
    while (true) {
        c = archDatos.get();
        if (c == ' ') break;
        contador++;
        if (c == '_') {
            c = ' ';
        }
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        archReporte.put(c);
    }
    archDatos >> cantSeguidores;
    archReporte << setw(20 - contador) << " " << codCanal << numCanal << setw(10) << " ";
    imprimirFecha(archReporte, ddC, mesC, anhioC);
    archReporte << setw(10) << " " << cantSeguidores << endl;
    imprimirEncabezadoDatos(archReporte);
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte << c;
    }
    archReporte << endl;
}

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int hh, int min, int ss,
                   int cantRepro, int &horaTotalSegundos, int &fechaMax, int &ddUltima, int &mesUltima,
                   int &anhioUltima, int &totalReproducciones) {
    int horaEnSegundos, fechaConvertida;
    archReporte << setw(12) << " ";
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(22) << " ";
    imprimirHora(archReporte, hh, min, ss);
    archReporte << right << setw(24) << cantRepro << endl;
    convertirHora(hh, min, ss, horaEnSegundos);
    horaTotalSegundos += horaEnSegundos;
    convertirFecha(dd, mes, anhio, fechaConvertida);
    calcularUltimaPublicacion(fechaConvertida, fechaMax, ddUltima, mesUltima, anhioUltima);
    totalReproducciones += cantRepro;
}

void imprimirEncabezadoDatos(ofstream &archReporte) {
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(5) << " " << "ULTIMAS REPRODUCCIONES" << endl;
    archReporte << setw(12) << " " << "FECHA DE PUBLICACION" << setw(7) << " " << "TIEMPO DE DURACION" << setw(7) << " "
            << "NUMERO DE REPRODUCCIONES" << endl;
}

void imprimirHora(ofstream &archReporte, int hh, int min, int ss) {
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss <<
            setfill(' ');
}

void convertirHora(int hh, int min, int ss, int &horaEnSegundos) {
    horaEnSegundos = hh * 3600 + min * 60 + ss;
}

void calcularUltimaPublicacion(int fechaConvertida, int &fechaMax, int &ddUltima, int &mesUltima, int &anhioUltima) {
    if (fechaConvertida > fechaMax) {
        fechaMax = fechaConvertida;
        anhioUltima = fechaConvertida / 10000;
        mesUltima = (fechaConvertida % 10000) / 100;
        ddUltima = fechaConvertida % 100;
    }
}


void imprimirResumen(ofstream &archReporte, int horaTotalSegundos, int ddUltima, int mesUltima, int anhioUltima,
                     int totalReproducciones, double &ingresosPublicidad) {
    int hh, mm, ss;
    archReporte << fixed << setprecision(2);
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << setw(6) << " " << "RESUMEN DEL CANAL:" << endl;
    archReporte << setw(6) << " " << "DURACION TOTAL DE LAS REPRODUCCIONES:" << setw(5) << " ";
    hh = horaTotalSegundos / 3600;
    mm = (horaTotalSegundos % 3600) / 60;
    ss = horaTotalSegundos % 60;
    imprimirHora(archReporte, hh, mm, ss);
    archReporte << endl;
    archReporte << setw(6) << " " << "ULTIMA PUBLICACION:" << setw(23) << " ";
    imprimirFecha(archReporte, ddUltima, mesUltima, anhioUltima);
    archReporte << endl;
    archReporte << setw(6) << " " << "TOTAL DE REPRODUCCIONES:" << setw(18) << " " << totalReproducciones << endl;
    ingresosPublicidad = ((double) totalReproducciones / 1000) * 3.25;
    archReporte << setw(6) << " " << "INGRESOS POR PUBLICIDAD:" << setw(18) << " " << "$" << setw(8) <<
            ingresosPublicidad << endl;
}

void imprimirResumenFinal(ofstream &archReporte, int cantTotalStreams, int horaFinalSegundos, double ingresosTotales,
                          double ingresosMaximo, char codCanalMax, int numCanalMax) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    int hh, mm, ss;
    archReporte << "RESUMEN FINAL:" << endl;
    archReporte << "CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES:" << setw(10) << " " << cantTotalStreams <<
            endl;
    archReporte << "DURACION TOTAL DE LOS STREAMS PUBLICADOS:" << setw(15) << " ";
    hh = horaFinalSegundos / 3600;
    mm = (horaFinalSegundos % 3600) / 60;
    ss = horaFinalSegundos % 60;
    imprimirHora(archReporte, hh, mm, ss);
    archReporte << endl;
    archReporte << "INGRESOS TOTALES POR PUBLICIDAD" << setw(25) << " " << "$" << setw(8) <<
            ingresosTotales << endl;
    archReporte << "CANAL CON MAYORES INGRESOS POR PUBLICIDAD" << setw(5) << " " << codCanalMax << numCanalMax
            << " CON " << "$" << setw(8) << ingresosMaximo << endl;
}

void calcularMayoresIngresos(double ingresosPublicidad, char codCanal, int numCanal, double &ingresosMaximo,
                             char &codCanalMax, int &numCanalMax) {
    if (ingresosPublicidad > ingresosMaximo) {
        ingresosMaximo = ingresosPublicidad;
        numCanalMax = numCanal;
        codCanalMax = codCanal;
    }
}
