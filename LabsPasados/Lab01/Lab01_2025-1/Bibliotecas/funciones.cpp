#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 3/09/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte() {
    int ddI, mmI, anhioI, ddF, mmF, anhioF, dni, num1, num2, dd, mm, anhio, hh, min, ss, nroCompania = 0, dniMayor,
            dniMenor;;
    double multa, porTipo = 0, porFecha = 0, porHora = 0, monto = 0, totalRecaudado = 0, montoMayor, montoMenor,
    montoMinimo=100000,montoMaximo=1;
    char c, tipoVehi, gravedad;

    cin >> ddI >> c >> mmI >> c >> anhioI >> ddF >> c >> mmF >> c >> anhioF;
    imprimirEncabezado(ddI, mmI, anhioI, ddF, mmF, anhioF);

    while (true) {
        cin >> dni;
        if (cin.eof()) break;
        nroCompania++;
        imprimirNombre(dni, nroCompania);
        double multaTotales = 0, porTipoTotal = 0, porFechaTotal = 0, porHoratotal = 0, montoFinal = 0;

        while (true) {
            cin >> tipoVehi >> num1 >> c >> num2 >> dd >> c >> mm >> c >> anhio >> hh >> c >> min >> c >> ss;
            cin >> ws >> gravedad;
            imprimirDatos(tipoVehi, num1, num2, dd, mm, anhio, hh, min, ss, gravedad, ddI, mmI, anhioI, ddF, mmF,
                          anhioF, multa, porTipo, porFecha, porHora, monto);
            montosTotales(multa, porTipo, porFecha, porHora, monto, montoFinal, multaTotales,
                          porTipoTotal, porFechaTotal, porHoratotal);

            if (cin.get() == '\n') break;
        }
        imprimirEstadisticasFinales(multaTotales, porTipoTotal, porFechaTotal, porHoratotal, montoFinal);
        calcularEstadisticas(dni, montoFinal, totalRecaudado, dniMayor, montoMayor, dniMenor, montoMenor,
            montoMinimo,montoMaximo);
    }
    imprimirEstadisticas(totalRecaudado, dniMayor, montoMayor, dniMenor, montoMenor);
}

void imprimirNombre(int dni, int nroCompania) {
    int nroEspacios = 0;
    char c;
    cin >> ws;
    cout << "COMPANIA No." << setw(2) << " " << nroCompania << endl;
    cout << "REPRESENTATE LEGAL: ";

    while (true) {
        c = cin.get();
        if (c == ' ') break;
        if (c == '/' or c == '-') {
            c = ' ';
        }
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        nroEspacios++;
        cout << c;
    }
    cout << right << setw(45 - nroEspacios) << "DNI: " << dni << endl;
    imprimirEncabezadoVehi();
}

void imprimirEncabezado(int ddI, int mmI, int anhioI, int ddF, int mmF, int anhioF) {
    cout << setw(41) << " " << "MINISTERIO DE TRANSPORTE" << endl;
    cout << setw(36) << " " << "MULTAS IMPUESTAS A LAS COMPAÑIAS " << endl;
    cout << setw(23) << " " << "RANGO DE FECHAS A CONSIDERAR:  DEL " << setw(2) << " ";
    imprimirFecha(ddI, mmI, anhioI);
    cout << " AL ";
    imprimirFecha(ddF, mmF, anhioF);
    cout << endl;
    imprimirLinea(TAM_MAX, '=');
}

void imprimirFecha(int dd, int mes, int anhio) {
    cout << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << anhio << setfill(' ');
}

void imprimirLinea(int cant, char c) {
    for (int i = 0; i < cant; i++) {
        cout << c;
    }
    cout << endl;
}

void imprimirDatos(char tipoVehi, int num1, int num2, int dd, int mm, int anhio, int hh, int min, int ss,
                   char gravedad, int ddI, int mmI, int anhioI, int ddF, int mmF, int anhioF, double &multa,
                   double &porTipo, double &porFecha, double &porHora, double &montoTotal) {
    double incrementoPorTipo, incrementoPorFecha, incrementoPorhoras;
    cout << fixed << setprecision(2);

    imprimirTipoVehiculo(tipoVehi, incrementoPorTipo);
    imprimirPlaca(tipoVehi, num1, num2);
    imprimirFecha(dd, mm, anhio);
    cout << setw(5) << " ";
    imprimirHora(hh, min, ss);
    cout << setw(5) << " ";
    imprimirGravedad(gravedad, multa);
    incrementoFechas(dd, mm, anhio, ddI, mmI, anhioI, ddF, mmF, anhioF, incrementoPorFecha);
    incrementoHoras(hh, min, ss, incrementoPorhoras);
    porTipo = (multa) * incrementoPorTipo / 100;
    porFecha = (multa) * incrementoPorFecha / 100;
    porHora = (multa) * incrementoPorhoras / 100;
    montoTotal = multa + porTipo + porFecha + porHora;
    cout << right << setw(5) << " " << setw(6) << porTipo << setw(5) << " " << setw(6) << porFecha << setw(5)
            << " " << setw(6) << porHora << setw(5) << " " << setw(7) << montoTotal;
    cout << endl;
}

void imprimirTipoVehiculo(char tipoVehi, double &incrementoPorTipo) {
    if (tipoVehi == 'P') {
        cout << "- PEQUEÑO" << setw(5) << " ";
        incrementoPorTipo = 2.7;
    } else if (tipoVehi == 'M') {
        cout << "- MEDIANO" << setw(5) << " ";
        incrementoPorTipo = 11.7;
    } else {
        cout << "- GRANDE" << setw(6) << " ";
        incrementoPorTipo = 15.3;
    }
}

void imprimirPlaca(char tipoVehi, int num1, int num2) {
    cout << tipoVehi << num1 << num2;
    cout << setw(5) << " ";
}

void imprimirHora(int hh, int min, int ss) {
    cout << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void imprimirGravedad(char gravedad, double &multa) {
    if (gravedad == 'L') {
        cout << "LEVE " << setw(8) << " ";
        multa = 158.33;
    } else if (gravedad == 'G') {
        cout << "GRAVE" << setw(8) << " ";
        multa = 516.75;
    } else {
        cout << "MUY GRAVE" << setw(3) << " ";
        multa = 3920.25;
    }
    cout << right << setw(6) << multa;
}

void imprimirEncabezadoVehi() {
    imprimirLinea(TAM_MAX, '-');
    cout << "VEHICULOS INFRACCIONADOS: " << endl;
    cout << setw(94) << " " << "INCREMENTOS" << endl;
    cout << setw(2) << " " << "TIPO" << setw(8) << " " << "PLACA" << setw(8) << " " << "FECHA" << setw(11) << " " <<
            "HORA" << setw(6) << " " << "GRAVEDAD" << setw(5) << " " << "MULTA" << setw(5) << " " << "POR TIPO" <<
            setw(5) << " " << "POR FECHA" << setw(2) << " " << "POR HORA" << setw(2) << " " << "TOTAL A PAGAR" <<
            endl;
    cin >> ws;
}

void incrementoFechas(int dd, int mm, int anhio, int ddI, int mmI, int anhioI, int ddF, int mmF,
                      int anhioF, double &incrementoPorFecha) {
    int fechaConvertida, fechaConvertidaI, fechaConvertidaF;

    convertidorDeFechas(dd, mm, anhio, fechaConvertida);
    convertidorDeFechas(ddI, mmI, anhioI, fechaConvertidaI);
    convertidorDeFechas(ddF, mmF, anhioF, fechaConvertidaF);

    if (fechaConvertidaI > fechaConvertida) {
        incrementoPorFecha = 10.75;
    } else if (fechaConvertidaI <= fechaConvertida and fechaConvertida < fechaConvertidaF) {
        incrementoPorFecha = 7.25;
    } else {
        incrementoPorFecha = 0;
    }
}

void convertidorDeFechas(int dd, int mm, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mm * 100 + dd;
}

void incrementoHoras(int hh, int min, int ss, double &incrementoPorhoras) {
    int horaConvertida;
    horaConvertida = hh * 10000 + min * 100 + ss;
    if (horaConvertida > 43000 and horaConvertida < 112500) {
        incrementoPorhoras = 8.5;
    } else if (horaConvertida >= 112500 and horaConvertida < 204000) {
        incrementoPorhoras = 5.8;
    } else {
        incrementoPorhoras = 3.7;
    }
}

void montosTotales(double multa, double porTipo, double porFecha, double porHora, double monto, double &montoFinal,
                   double &multaTotales, double &porTipoTotal, double &porFechaTotal, double &porHoratotal) {
    montoFinal += monto;
    multaTotales += multa;
    porTipoTotal += porTipo;
    porFechaTotal += porFecha;
    porHoratotal += porHora;
}

void imprimirEstadisticasFinales(double multaTotales, double porTipoTotal, double porFechaTotal, double porHoratotal,
                                 double montoFinal) {
    imprimirLinea(TAM_MAX, '-');
    cout << "PAGO TOTAL" << right << setw(56) << " " << setw(7) << multaTotales << setw(5) << " " << setw(6) <<
            porTipoTotal << setw(5) << " " << setw(6) << porFechaTotal << setw(5) << " " << setw(6) << porHoratotal
            << setw(4) << " " << setw(6) << montoFinal << endl;
    imprimirLinea(TAM_MAX, '=');
}

void calcularEstadisticas(int dni, double montoFinal, double &totalRecaudado, int &dniMayor, double &montoMayor,
                          int &dniMenor, double &montoMenor,double &montoMinimo,double &montoMaximo) {

    totalRecaudado = totalRecaudado + montoFinal;
    if (montoFinal < montoMinimo) {
        montoMinimo = montoFinal;
        montoMenor = montoFinal;
        dniMenor = dni;
    }
    if (montoFinal > montoMaximo) {
        montoMaximo = montoFinal;
        dniMayor=dni;
        montoMayor = montoFinal;
    }
}

void imprimirEstadisticas(double totalRecaudado, int dniMayor, double montoMayor, int dniMenor, double montoMenor) {
    cout<<"TOTAL DE PAGOS"<<setw(6)<<" "<<totalRecaudado<<endl;
    imprimirLinea(TAM_MAX, '/');
    cout << "COMPAÑIA CON MAYOR PAGO DE INFRACCIONES" << endl;
    cout << "DNI" << dniMayor << endl;
    cout << "MONTO" << montoMayor << endl;
    imprimirLinea(TAM_MAX, '/');
    cout << "COMPAÑIA CON MENOR PAGO DE INFRACCIONES" << endl;
    cout << "DNI" << dniMenor << endl;
    cout << "MONTO" << montoMenor << endl;
}
