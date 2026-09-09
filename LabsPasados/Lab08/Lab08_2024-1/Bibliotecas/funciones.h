//
// Created by USUARIO on 9/11/2025.
//

#ifndef LAB08_24_1_FUNCIONES_H
#define LAB08_24_1_FUNCIONES_H

void procesarCalificaciones(const char *nombArch, struct Alumno *arrAlumnos, int &cantAlumnos);

void abrirArchivoIfstream(const char *nombArch, ifstream &arch);

void abrirArchivoOfstream(const char *nombArch, ofstream &arch);

int buscarAlumno(struct Alumno *arrAlumnos, int cantAlumnos, int codAlum);

void completarAlumnos(const char *nombArch, struct Alumno *arrAlumnos, int cantAlumnos);

void leerFacultades(const char *nombArch, struct Alumno *arrAlumnos, int cantAlumnos);

void quitarGuion(char *nombre);

void completarNombreFacu(struct Alumno *arrAlumnos, int cantAlumnos, const char *codigo, const char *nombre);

void  imprimirReporte(const char *nombArch,struct Alumno *arrAlumnos,int cantAlumnos);
void imprimirEncabezado(ofstream &archReporte);
void imprimirLinea(ofstream &arch, int cant, char c);
#endif //LAB08_24_1_FUNCIONES_H
