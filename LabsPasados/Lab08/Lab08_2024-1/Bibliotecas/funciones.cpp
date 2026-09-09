#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "Alumno.h"

using namespace std;

//
// Created by USUARIO on 9/11/2025.
//

#include "funciones.h"
#define NO_ENCONTRADO -1
#define TAM_MAX 170

void procesarCalificaciones(const char *nombArch, struct Alumno *arrAlumnos, int &cantAlumnos) {
    ifstream archCali;
    abrirArchivoIfstream(nombArch, archCali);
    //DER614   5.75   20238549   16   20205830   17   20205844
    char curso[7];
    double cred;
    int codAlum, nota;
    while (true) {
        archCali >> curso;
        if (archCali.eof()) break;
        archCali >> cred;
        while (true) {
            archCali >> codAlum >> nota;
            int idAlumno = buscarAlumno(arrAlumnos, cantAlumnos, codAlum);
            if (idAlumno == NO_ENCONTRADO) {
                idAlumno = cantAlumnos;
                arrAlumnos[cantAlumnos].codigo = codAlum;
                cantAlumnos++;
            }
            arrAlumnos[idAlumno].numCursos++;
            arrAlumnos[idAlumno].numCreditos += cred;
            arrAlumnos[idAlumno].sumaPonderada += (nota * cred);
            if (archCali.get() == '\n') break;
        }
    }
    for (int i = 0; i < cantAlumnos; i++) {
        if (arrAlumnos[i].numCreditos > 0) {
            arrAlumnos[i].promPonderado = arrAlumnos[i].sumaPonderada / arrAlumnos[i].numCreditos;
        }
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
    arch<<right<<fixed<<setprecision(2);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

int buscarAlumno(struct Alumno *arrAlumnos, int cantAlumnos, int codAlum) {
    for (int i = 0; i < cantAlumnos; i++) {
        if (arrAlumnos[i].codigo == codAlum) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void completarAlumnos(const char *nombArch, struct Alumno *arrAlumnos, int cantAlumnos) {
    ifstream archAlumnos;
    abrirArchivoIfstream(nombArch, archAlumnos);
    int cod, idAlumno;
    char c, nombre[50], codFac[15];
    //20227341,DIAZ ANTEZANO MAGALI SILVANA,EEGGCC
    while (true) {
        archAlumnos >> cod;
        if (archAlumnos.eof()) break;
        archAlumnos.get();
        archAlumnos.getline(nombre, 50, ',');
        archAlumnos >> codFac;
        idAlumno = buscarAlumno(arrAlumnos, cantAlumnos, cod);
        if (idAlumno != NO_ENCONTRADO) {
            strcpy(arrAlumnos[idAlumno].nombre, nombre);
            strcpy(arrAlumnos[idAlumno].facultad.codigo, codFac);
        }
    }
}

void leerFacultades(const char *nombArch, struct Alumno *arrAlumnos, int cantAlumnos) {
    ifstream archFacu;
    abrirArchivoIfstream(nombArch, archFacu);
    char nombre[50], codigo[20];

    while (true) {
        archFacu >> nombre;
        if (archFacu.eof()) break;
        archFacu >> codigo;
        quitarGuion(nombre);
        completarNombreFacu(arrAlumnos, cantAlumnos, codigo, nombre);
    }
}

void quitarGuion(char *nombre) {
    for (int i = 0; nombre[i]; i++) {
        if (nombre[i] == '_') nombre[i] = ' ';
    }
}

void completarNombreFacu(struct Alumno *arrAlumnos, int cantAlumnos, const char *codigo, const char *nombre) {
    for (int i = 0; i < cantAlumnos; i++) {
        if (strcmp(arrAlumnos[i].facultad.codigo, codigo) == 0) {
            strcpy(arrAlumnos[i].facultad.nombre, nombre);
        }
    }
}

void imprimirReporte(const char *nombArch, struct Alumno *arrAlumnos, int cantAlumnos) {
    ofstream archReporte;
    abrirArchivoOfstream(nombArch, archReporte);
    imprimirEncabezado(archReporte);
    int codMayor;
    double credMayor;
    char nombreMayor[50],facMayor[50];
    for (int i=0;i<cantAlumnos;i++) {
        archReporte<<arrAlumnos[i].codigo<<" - "<<arrAlumnos[i].nombre<<setw(50-strlen(arrAlumnos[i].nombre))<<' '
        <<setw(2)<<arrAlumnos[i].numCursos<<setw(11)<<' '
        <<setw(7)<<arrAlumnos[i].sumaPonderada
        <<setw(13)<<' '<<setw(7)<<arrAlumnos[i].numCreditos
        <<setw(13)<<' '<<setw(7)<<arrAlumnos[i].promPonderado
        <<setw(5)<<' '<<arrAlumnos[i].facultad.nombre<<endl;
        if (i==0 or arrAlumnos[i].numCreditos>credMayor) {
            codMayor=arrAlumnos[i].codigo;
            credMayor=arrAlumnos[i].numCreditos;
            strcpy(nombreMayor, arrAlumnos[i].nombre);
            strcpy(facMayor, arrAlumnos[i].facultad.nombre);
        }
    }
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte<<"Alumno con mayor numero de creditos: "<<endl;
    archReporte<<nombreMayor<<" ["<<codMayor<<"] con "<<setw(5)<<credMayor<<" creditos de la "<<facMayor<<endl;
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(55) << ' ' << "INSTITUCION EDUCATIVA_TP" << endl;
    archReporte << setw(44) << ' ' << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    archReporte << setw(59) << ' ' << "CICLO: 2024-1" << endl;
    archReporte << setw(56) << ' ' << "TODAS LAS FACULTADES" << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << setw(6) << ' ' << "ALUMNO"
            << setw(43) << ' ' << "No. de Cursos"
            << setw(4) << ' ' << "Suma Ponderada"
            << setw(5) << ' ' << "No. de Creditos"
            << setw(6) << ' ' << "Prom Ponderado"
            << setw(10) << ' ' << "Facultad" << endl;
    imprimirLinea(archReporte,TAM_MAX, '-');
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch << endl;
}
