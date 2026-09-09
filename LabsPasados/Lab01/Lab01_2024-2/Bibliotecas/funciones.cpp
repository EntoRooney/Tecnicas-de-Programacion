#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//
// Created by USUARIO on 28/08/2025.
//

#include "funciones.h"
#define TAM_MAX 120

void imprimirReporte() {
    int dia, mes, anhio, dni, hi, mi, si, hf, mf, sf, totalPacientes = 0, pacientesSiMed = 0, pacientesPedri = 0
            , pacientesDerma = 0;
    double tarifaxHora, monto, duracionH, montoTotal, montoTotalMedinas = 0, montoMedDerma = 0;
    char c, especialidad, SN;
    int duracionI, duracionF, fechaConvertida, pacientesFechaCardio = 0, pacientesNOMed = 0;
    double ingresosTotales = 0;
    imprimirEncabezado();
    while (true) {
        cin >> dia;
        if (cin.eof()) break;
        cin >> c >> mes >> c >> anhio >> dni;
        cin >> hi >> c >> mi >> c >> si >> hf >> c >> mf >> c >> sf >> tarifaxHora;
        cin >> ws >> especialidad >> SN;
        if (SN == 'S') {
            cin >> monto;
            pacientesSiMed++;
            montoTotalMedinas += monto;
        } else {
            monto = 0;
        }
        if (especialidad == 'D') {
            montoMedDerma += monto;
            pacientesDerma++;
        } else if (especialidad == 'P') {
            pacientesPedri++;
        }
        totalPacientes++;
        imprimirFechayDni(dia, mes, anhio, dni);
        convertirfecha(dia, mes, anhio, fechaConvertida);
        imprimirHora(hi, mi, si, duracionI);
        imprimirHora(hf, mf, sf, duracionF);
        calcularDuracion(duracionI, duracionF, duracionH);
        imprimirEspecialidad(especialidad);
        imprimirPagoCM(tarifaxHora, monto, duracionH, montoTotal);
        cout << endl;
        ingresosTotales += montoTotal;
        if (fechaConvertida > 20240115) {
            if (especialidad == 'C') {
                pacientesFechaCardio++;
            }
        }
        if (montoTotal > 350) {
            if (SN != 'S') {
                pacientesNOMed++;
            }
        }
    }
    imprimirLinea(TAM_MAX, '=');
    cout << "Total de ingresos: " << ingresosTotales << endl;
    impresionEstadisticas(pacientesSiMed, montoTotalMedinas, montoMedDerma, totalPacientes, pacientesPedri,
                          pacientesDerma, pacientesFechaCardio, pacientesNOMed);
}

void imprimirEncabezado() {
    cout << setfill(' ') << setw(TAM_MAX / 2 + 1) << "EMPRESA DE SALUD S.A." << endl;
    imprimirLinea(TAM_MAX, '=');
    cout << setfill(' ') << setw(48) << "REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS" << endl;
    imprimirLinea(TAM_MAX, '=');
    cout << "Fecha" << setw(7) << " " << "Paciente"
            << setw(5) << " " << "Inicio" << setw(7) << " " << "Fin"
            << setw(6) << " " << "Duracion(H:M:S)"
            << setw(2) << " " << "Duracion(H)"
            << setw(2) << " " << "Especialidad"
            << setw(3) << " " << "Pago(cita+medicinas)"
            << setw(10) << " " << endl;
    imprimirLinea(TAM_MAX, '-');
}

void imprimirLinea(int cant, char c) {
    for (int i = 0; i <= cant; i++) {
        cout << c;
    }
    cout << endl;
}

void imprimirFechayDni(int dia, int mes, int anhio, int dni) {
    cout << setfill('0')
            << setw(2) << dia << "/"
            << setw(2) << mes << "/" << anhio
            << setfill(' ') << setw(10) << dni
            << setw(4) << " ";
}

void imprimirHora(int hh, int mm, int ss, int &duracion) {
    cout << setfill('0') << setw(2)
            << hh << ":"
            << setw(2) << mm << ":"
            << setw(2) << ss
            << setfill(' ')
            << setw(4) << " ";
    duracion = ss + mm * 60 + hh * 3600;
}

void calcularDuracion(int duracionI, int duracionF, double &duracionH) {
    cout << fixed;
    cout.precision(4);
    int duracionTotal, duracionHora, duracionMin, duracionSeg;
    int Xduracion; //asignamos esto porque no nos valdrá de nada
    // double duracionH;
    duracionTotal = duracionF - duracionI;
    duracionHora = duracionTotal / 3600;
    duracionMin = (duracionTotal % 3600) / 60;
    duracionSeg = duracionTotal % 60;
    imprimirHora(duracionHora, duracionMin, duracionSeg, Xduracion);
    duracionH = (double) duracionTotal / 3600;
    cout << setw(6) << " " << duracionH;
}

void imprimirEspecialidad(char especialidad) {
    cout << setw(5) << " " << setw(13);
    cout << left;
    if (especialidad == 'C') {
        cout << "Cardiología";
    } else if (especialidad == 'D') {
        cout << "Dermatología";
    } else {
        cout << "Pediatría";
    }
    cout << right;
}

void imprimirPagoCM(double tarifaxHora, double monto, double duracionH, double &montoTotal) {
    cout << fixed;
    cout.precision(2);
    montoTotal = (tarifaxHora * duracionH) + monto;
    cout << setw(4) << " " << setw(7) << montoTotal;
}

void impresionEstadisticas(int pacientesSiMed, double montoTotalMedinas, double montoMedDerma, int totalPacientes,
                           int pacientesPedri, int pacientesDerma, int pacientesFechaCardio, int pacientesNOMed) {
    double promeSiMed, promePaciDer, porcentajePaciSinMed, porcentajePaciPedri, porcentajePaciNoMed;
    int totalPacienteNoMed;
    promeSiMed = (double) montoTotalMedinas / pacientesSiMed;
    promePaciDer = (double) montoMedDerma / pacientesDerma;
    totalPacienteNoMed = totalPacientes - pacientesSiMed;
    porcentajePaciSinMed = ((double) totalPacienteNoMed / totalPacientes) * 100;
    porcentajePaciPedri = ((double) pacientesPedri / (totalPacientes)) * 100;
    porcentajePaciNoMed = ((double) pacientesNOMed / totalPacientes) * 100;


    imprimirLinea(TAM_MAX, '=');
    cout << setw(10) << ' ' << "ESTADISTICAS OBTENIDAS:" << endl;
    cout << setw(10) << ' ' << "Promedio de gastos por medicina de los pacientes que le recetaron medicionas:" <<
            setw(10) << ' ' << promeSiMed << endl;
    cout << setw(10) << ' ' << "Promedio de gastos por medicina de los pacientes que se atendieron en dermatologia:" <<
            setw(4) << ' ' << promePaciDer << endl;
    cout << setw(10) << ' ' << "Porcentaje de pacientes que no le recetaron medicinas:" <<
            setw(34) << " " << porcentajePaciSinMed << "%" << endl;
    cout << setw(10) << ' ' << "Porcentaje de pacientes que se atendieron en pediatria:" <<
            setw(33) << ' ' << porcentajePaciPedri << "%" << endl;
    cout << setw(10) << ' ' << "Cantidad de pacientes que se atendieron en cardiologia despues del 15/01/2024" <<
            setw(11) << ' ' << pacientesFechaCardio << endl;
    cout << setw(10) << ' ' << "Porcentaje de pacientes que no le recetaron medicinas y que gasto más de 350.00" <<
            setw(9) << ' ' << porcentajePaciNoMed << "%" << endl;
    imprimirLinea(TAM_MAX, '=');
}

void convertirfecha(int dia, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dia;
}
