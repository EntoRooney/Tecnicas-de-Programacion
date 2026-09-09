#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

//
// Created by USUARIO on 7/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120
#define M_PI 3.14159265358979323846

void imprimirReporte() {
    int dd, mes, anhio, dni, hhI, mmI, ssI, hh, mm, ss, grados, minutos, segundos;
    double velocidad;
    char c;
    cin >> dd >> c >> mes >> c >> anhio;
    imprimirEncabezado(dd, mes, anhio);
    while (true) {
        double distanciaAcumulada=0,xAnterior=0,yAnterior=0;
        cin >> dni;
        if (cin.eof()) break;
        leerNombre(dni);
        cin >> hhI >> c >> mmI >> c >> ssI;
        while (true) {
            cin >> velocidad >> hh >> c >> mm >> c >> ss >> grados >> c >> minutos >> c >> segundos >> c;

            imprimirResultados(hhI, mmI, ssI, hh, mm, ss, grados, minutos, segundos, velocidad,distanciaAcumulada,
                xAnterior,yAnterior);
            hhI = hh;
            mmI = mm;
            ssI = ss;
            if (cin.get() == '\n') break;
        }

        cout << endl;
    }
}

void leerNombre(int dni) {
    int contador = 0;
    char c;
    cin >> ws;
    cout << "Repartidor:" << endl;
    cout << "Nombre ";
    while (true) {
        c = cin.get();
        if (c == ' ') break;
        contador++;
        cout << c;
    }
    cout << setw(50 - contador) << "DNI: " << dni << endl;
}

void imprimirEncabezado(int dd, int mes, int anhio) {
    cout << setw(50) << " " << "EMPRESA DE REPARTOS TP S.A." << endl;
    cout << setw(48) << " " << "FECHA DE LOS REPARTOS: ";
    imprimirFecha(dd, mes, anhio);
    cout << endl;
    imprimirLinea(TAM_MAX, '=');
    cout << fixed << setprecision(2);
}

void imprimirLinea(int cant, char c) {
    for (int i = 0; i < cant; i++) {
        cout << c;
    }
    cout << endl;
}

void imprimirFecha(int dd, int mes, int anhio) {
    cout << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << anhio << setfill(' ');
}

void imprimirHora(int hh, int mm, int ss) {
    cout << setfill('0') << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ');
}

void imprimirResultados(int hhI, int mmI, int ssI, int hh, int mm, int ss, int grados, int minutos, int segundos,
                        double velocidad,double &distanciaAcumulada,double &xAnterior,double &yAnterior) {
    double gradosSexa, distancia,x,y,pagoTramo;
    imprimirHora(hhI, mmI, ssI);
    cout << setw(5) << " ";
    imprimirHora(hh, mm, ss);
    cout << setw(5) << " " << velocidad;
    convertirGrados(grados, minutos, segundos, gradosSexa);
    calcularDistancia(hhI, mmI, ssI, hh, mm, ss, velocidad, distancia);
    cout << setw(5) << " " << distancia;
    calcularPuntosDistancia(gradosSexa, distancia, distanciaAcumulada, xAnterior, yAnterior, x, y);
    cout<<setw(5)<<" "<<xAnterior<<"-"<<yAnterior<<setw(5)<<" "<<x<<"-"<<y<<setw(5)<<" "<<distanciaAcumulada;
    calcularPagoTramos(distanciaAcumulada,pagoTramo);
    cout<<setw(5)<<" "<<pagoTramo;
    cout << endl;

    xAnterior = x;
    yAnterior = y;
}

void convertirGrados(int grados, int minutos, int segundos, double &gradosSexa) {
    gradosSexa = grados + ((double) minutos / 60) + ((double) segundos / 3600);
}

void calcularDistancia(int hhI, int mmI, int ssI, int hh, int mm, int ss, double velocidad, double &distancia) {
    double horaInicial, horafinal, duracion, duracionHoras;
    horaInicial = hhI * 3600 + mmI * 60 + ssI;
    horafinal = hh * 3600 + mm * 60 + ss;
    duracion = horafinal - horaInicial;
    duracionHoras = (double) duracion / 3600;
    distancia = velocidad * duracionHoras;
}

void calcularPuntosDistancia(double gradosSexa, double distancia, double &distanciaAcumulada,
                             double &xAnterior, double &yAnterior ,double &x,double &y) {
    double rad;
    rad = gradosSexa *M_PI / 180;

    x = xAnterior + distancia * cos(rad);
    y = yAnterior + distancia * sin(rad);
    distanciaAcumulada += distancia;
}

void calcularPagoTramos(double distanciaAcumulada,double &pagoTramo) {
    if (distanciaAcumulada<10.5) {
        pagoTramo = 8.5;
    }else if (distanciaAcumulada<20.5) {
        pagoTramo = 20.5;
    }else if (distanciaAcumulada<35.5) {
        pagoTramo = 29.85;
    }else {
        pagoTramo=45.69;
    }
}