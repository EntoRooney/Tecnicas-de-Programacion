//
// Created by aml on 8/09/2025.
//
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std ;

#include "funciones.h"
#define TAM_MAx 120

void leerDatos() {
    int ddC, mmC, anhioC, numCanal, numSeguidores, dd, mm, anhio, hh, min, ss, cantReproduciones, fechaConvertidaI,
            fechaConvertidaF, fechaConvertida, nrCanales = 0, horaTotalEnSegundos, horaEnSegundos, ultimoDia, ultimoMes,
            ultimoAnhio, fechaMin = 20251212, canTotalReproducciones, cantStreams = 0, segundosTotales = 0,
            numCanalMayor;
    double ingresosPublicidad, ingresosTotales = 0, ingresoMayor, ingresoMaximo;
    char c, codigoCanal, codigoCanalMayor;
    imprimirEncabezado(fechaConvertidaI, fechaConvertidaF);
    //leo datos sabiendo los limites
    while (true) {
        cin >> ddC;
        if (cin.eof()) break;
        cin >> c >> mmC >> c >> anhioC;
        fechaConvertida = anhioC * 10000 + mmC * 100 + ddC;
        if (fechaConvertida > fechaConvertidaI and fechaConvertida < fechaConvertidaF) {
            nrCanales++;
            cin >> ws >> codigoCanal >> numCanal;
            imprimirEncabezadoDeCanales(nrCanales);
            leerNombreCanal(codigoCanal, numCanal);
            cin >> numSeguidores;
            cout << setw(5) << " ";
            imprimirFecha(ddC, mmC, anhioC, fechaConvertida);
            cout << setw(9) << " " << numSeguidores;
            cout << endl;
            imprimirEncabezadoEstadisticas();
            horaTotalEnSegundos = 0;
            canTotalReproducciones = 0;
            while (true) {
                cin >> dd >> c >> mm >> c >> anhio >> hh >> c >> min >> c >> ss >> cantReproduciones;
                if (cin.get() == '\n') break;
                imprimirEstadisticas(dd, mm, anhio, hh, min, ss, cantReproduciones, horaEnSegundos, ultimoDia,
                                     ultimoMes, ultimoAnhio, fechaMin);
                cantStreams++;
                horaTotalEnSegundos += horaEnSegundos;
                canTotalReproducciones += cantReproduciones;
            }
            imprimirResumenDelCanal(horaTotalEnSegundos, ultimoDia, ultimoMes, ultimoAnhio, canTotalReproducciones,
                                    ingresosPublicidad);
            segundosTotales += horaTotalEnSegundos;
            ingresosTotales += ingresosPublicidad;
            calcularMayorIngreso(ingresosTotales, codigoCanal, numCanal, codigoCanalMayor,
                                 numCanalMayor, ingresoMayor, ingresoMaximo);
        } else {
            while (true) {
                if (cin.get() == '\n') break;
            }
        }
    }
    imprimirEstadisticasFinales(cantStreams, segundosTotales, ingresosTotales, ingresoMayor, codigoCanalMayor,
                                numCanalMayor);
}

void leerNombreCanal(char codigoCanal, int numCanal) {
    char c;
    int contador = 0;
    cin >> ws;
    cout << setw(5) << " ";
    while (true) {
        c = cin.get();
        if (c == ' ') break;
        contador++;
        if (c == '_') {
            c = ' ';
        }
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        cout << c;
    }
    cout << setw(18 - contador) << codigoCanal << numCanal;
}

void imprimirEncabezado(int &fechaConvertidaI, int &fechaConvertidaF) {
    int diaI = 9, mesI = 9, anhioI = 2022;
    int diaF = 1, mesF = 1, anhioF = 2023;
    cout << setw(34) << " " << "PLATAFORMA TP_Twitch" << endl;
    cout << setw(32) << " " << "REGISTRO DE LOS CANALES AFILIADOS" << endl;
    cout << setw(30) << " " << "FECHAS DE CREACION ENTRE EL ";
    imprimirFecha(diaI, mesI, anhioI, fechaConvertidaI);
    cout << " Y EL ";
    imprimirFecha(diaF, mesF, anhioF, fechaConvertidaF);
    cout << endl;
}

void imprimirFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    cout << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << anhio << setfill(' ');
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void imprimirLinea(int cant, char c) {
    for (int i = 0; i < cant; i++) {
        cout << c;
    }
    cout << endl;
}

void imprimirEncabezadoDeCanales(int nrCanales) {
    imprimirLinea(TAM_MAx, '=');
    cout << "CANAL No. " << nrCanales << endl;
    cout << setw(5) << " " << "NOMBRE" << setw(11) << " " << "CODIGO" << setw(4) << " " << "CREADO EL" << setw(5) << " "
            << "NUMERO DE SEGUIDORES" << endl;
}

void imprimirEstadisticas(int dd, int mm, int anhio, int hh, int min, int ss, int cantReproduciones,
                          int &horaEnSegundos, int &ultimoDia, int &ultimoMes, int &ultimoAnhio, int fechaMin) {
    int fechaConvertidaX;
    cout << setw(5) << " ";
    imprimirFecha(dd, mm, anhio, fechaConvertidaX);
    cout << setw(20) << " ";
    imprimirHora(hh, min, ss);
    cout << right << setw(23) << cantReproduciones << endl;
    convertirHora(hh, min, ss, horaEnSegundos);
    sacarUltimaFecha(fechaConvertidaX, ultimoDia, ultimoMes, ultimoAnhio, fechaMin);
}

void imprimirHora(int hh, int min, int ss) {
    cout << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" <<
            setw(2) << ss << setfill(' ');
}

void imprimirEncabezadoEstadisticas() {
    imprimirLinea(TAM_MAx, '-');
    cout << setw(2) << " " << "ULTIMAS REPRODUCCIONES" << endl;
    cout << setw(5) << " " << "FECHA DE PUBLICACION" << setw(5) << " " << "TIEMPO DE DURACION" << setw(5) << " " <<
            "NUMERO DE REPRODUCCIONES"
            << endl;
}

void convertirHora(int hh, int min, int ss, int &horaEnSegundos) {
    horaEnSegundos = hh * 3600 + min * 60 + ss;
}

void imprimirResumenDelCanal(int horaTotalEnSegundos, int ultimoDia, int ultimoMes, int ultimoAnhio,
                             int canTotalReproducciones, double &ingresosPublicidad) {
    imprimirLinea(TAM_MAx, '-');
    int hhT, minT, ssT, fechaConvertida;
    hhT = horaTotalEnSegundos / 3600;
    minT = (horaTotalEnSegundos % 3600) / 60;
    ssT = (horaTotalEnSegundos % 60);
    cout << setw(5) << " " << "RESUMEN DEL CANAL:" << endl;
    cout << setw(5) << " " << "DURACION TOTAL DE LAS REPRODUCIONES: " << setw(5) << " ";
    imprimirHora(hhT, minT, ssT);
    cout << endl;
    cout << setw(5) << " " << "ULTIMA PUBLICACION: " << setw(22) << " ";
    imprimirFecha(ultimoDia, ultimoMes, ultimoAnhio, fechaConvertida);
    cout << endl;
    cout << setw(5) << " " << "TOTAL DE REPRODUCCIONES: " << setw(17) << " " << canTotalReproducciones << endl;
    int tarifaReproduciones = canTotalReproducciones / 1000;
    ingresosPublicidad = (double) (tarifaReproduciones + 1) * 3.25;
    cout << setw(5) << " " << "INGRESOS POR PUBLICIDAD: " << setw(17) << " " << "$" << ingresosPublicidad << endl;
}

void sacarUltimaFecha(int fechaConvertidaX, int &ultimoDia, int &ultimoMes, int &ultimoAnhio, int &fechaMin) {
    if (fechaConvertidaX < fechaMin) {
        fechaMin = fechaConvertidaX;
        ultimoDia = fechaMin % 100;
        ultimoMes = (fechaMin % 10000) / 100;
        ultimoAnhio = fechaMin / 10000;
    }
}

void imprimirEstadisticasFinales(int cantStreams, int segundosTotales, double ingresosTotales,
                                 double ingresoMayor, char codigoCanal, int numCanal) {
    imprimirLinea(TAM_MAx, '=');
    int hh = segundosTotales / 3600;
    int min = (segundosTotales % 3600) / 60;
    int segundos = segundosTotales % 60;
    cout << "RESUMEN FINAL" << endl;
    cout << "CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES" << setw(20) << " " << cantStreams << endl;
    cout << "DURACION TOTAL DE LOS STREAMS PUBLICADOS" << setw(25) << " ";
    imprimirHora(hh, min, segundos);
    cout << endl;
    cout << "INGRESOS TOTALES POR PUBLICIDAD" << setw(35) << " " << "$" << ingresosTotales << endl;
    cout << "CANAL CON MAYORES INGRESOS POR PUBLICIDAD" << setw(15) << " " << codigoCanal << numCanal<<
    " CON $" << ingresoMayor << endl;
}

void calcularMayorIngreso(double ingresosTotales, char codigoCanal, int numCanal, char &codigoCanalMayor,
                          int &numCanalMayor, double &ingresoMayor, double ingresoMaximo) {
    if (ingresosTotales > ingresoMaximo) {
        ingresoMaximo = ingresosTotales;
        ingresoMayor = ingresosTotales;
        codigoCanalMayor = codigoCanal;
        numCanalMayor = numCanal;
    }
}
