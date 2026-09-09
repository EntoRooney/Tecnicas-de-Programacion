#include <fstream>
#include <iostream>
#include <iomanip>
#include <string.h>
//Ento Rooney Lazaro Trujillo
//20222032
using namespace std;

#include "funciones.h"
#define TAM_MAX 120
#define NO_ENCONTRADO -1

//llenamos los arreglos de categoria
void leerArrCategorias(struct Categoria *arrCategorias, int &cantidadCategorias) {
    ifstream archCategoria;
    abrirArchivoIfstream("ArchivosDeDatos/Categorias.csv", archCategoria);
    //UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
    int i = 0;
    while (true) {
        arrCategorias[i].codigo = leerCadenaExacta(archCategoria, ',');
        if (archCategoria.eof()) break;
        arrCategorias[i].nombre = leerCadenaExacta(archCategoria, ',');
        arrCategorias[i].descripcion = leerCadenaExacta(archCategoria, '\n');
        arrCategorias[i].reproducciones = new struct Reproduccion[15];
        i++;
    }
    cantidadCategorias = i;
}
//abrir cada archivo
void abrirArchivoIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
    }
}

void abrirArchivoOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    arch << right << fixed << setprecision(2);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
    }
}

char *leerCadenaExacta(ifstream &arch, char delim) {
    char cadena[300], *ptr;
    arch.getline(cadena, 300, delim);
    if (arch.eof()) return nullptr;
    ptr = new char[strlen(cadena) + 1];
    strcpy(ptr, cadena);
    return ptr;
}
//usaremos 3 fors para imprimir cada indice que nos piden
void imprimirReportePrueba(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias,
                           bool segundoReporte, bool tercerReporte) {
    ofstream archReporte;
    abrirArchivoOfstream(nombArch, archReporte);
    archReporte << setw(41) << ' ' << "REPORTE POR CATEGORIAS" << endl;
    for (int i = 0; i < cantidadCategorias; i++) {
        imprimirLinea(archReporte,TAM_MAX, '=');
        archReporte << "Codigo:" << setw(10) << ' ' << arrCategorias[i].codigo << endl;
        archReporte << "Nombre:" << setw(10) << ' ' << arrCategorias[i].nombre << endl;
        archReporte << "Descripcion:" << setw(5) << ' ' << arrCategorias[i].descripcion << endl;
        if (segundoReporte) {
            for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
                imprimirLinea(archReporte,TAM_MAX, '-');
                archReporte << "REPRODUCCIONES:" << endl;
                archReporte << "CANAL: " << arrCategorias[i].reproducciones[j].canal <<
                        setw(40 - strlen(arrCategorias[i].reproducciones[j].canal)) << ' ' <<
                        "RATING:" << setw(6) << arrCategorias[i].reproducciones[j].rating << setw(5) <<
                        ' ' << "DURACION: ";
                imprimirDuracion(archReporte, arrCategorias[i].reproducciones[j].duracion);
                archReporte << endl;
                if (tercerReporte) {
                    archReporte << setw(3) << ' ' << "COMENTARIOS:" << endl;
                    for (int z = 0; z < arrCategorias[i].reproducciones[j].numComentarios; z++) {
                        archReporte << setw(3) << ' ' << "- " << arrCategorias[i].reproducciones[j].comentarios[z]
                                << endl;
                    }
                }
            }
        }
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch.put('\n');
}
//me piden en la estructura de Categoria la duracion total y el promedio de Rating pero
//en el reporte final no hay dichos datos, igual lo calculé pero nunca lo he usado
void leerStreamsRepro(struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream archStreams;
    abrirArchivoIfstream("ArchivosDeDatos/StreamsReproducidos.csv", archStreams);
    //Sardoche,ZT132U54,4.410,01:41:48

    int hh, min, ss, tiempoSeg = 0;
    double rating;
    char nombre[100], codCategoria[100], c;
    while (true) {
        archStreams.getline(nombre, 100, ',');
        if (archStreams.eof()) break;
        archStreams.getline(codCategoria, 100, ',');
        archStreams >> rating >> c >> hh >> c >> min >> c >> ss >> ws;
        convertirDuracion(hh, min, ss, tiempoSeg);
        int idCategoria = buscarCategoria(arrCategorias, cantidadCategorias, codCategoria);
        if (idCategoria != NO_ENCONTRADO) {
            int pos = arrCategorias[idCategoria].numReproducciones;
            arrCategorias[idCategoria].reproducciones[pos].canal = new char[strlen(nombre) + 1];
            strcpy(arrCategorias[idCategoria].reproducciones[pos].canal, nombre);
            arrCategorias[idCategoria].reproducciones[pos].rating = rating;
            arrCategorias[idCategoria].reproducciones[pos].duracion = tiempoSeg;
            arrCategorias[idCategoria].promedioRating += rating;
            arrCategorias[idCategoria].duracionTotal += tiempoSeg;
            arrCategorias[idCategoria].numReproducciones++;
            arrCategorias[idCategoria].reproducciones[pos].numComentarios = 0;
        }
    }
    for (int i = 0; i < cantidadCategorias; i++) {
        arrCategorias[i].promedioRating /= arrCategorias[i].promedioRating / arrCategorias[i].numReproducciones;
    }
}

void convertirDuracion(int hh, int min, int ss, int &tiempoSeg) {
    tiempoSeg = hh * 3600 + min * 60 + ss;
}

int buscarCategoria(struct Categoria *arrCategorias, int cantidadCategorias, const char *codCategoria) {
    for (int i = 0; i < cantidadCategorias; i++) {
        if (strcmp(codCategoria, arrCategorias[i].codigo) == 0) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void imprimirDuracion(ofstream &archReporte, int duracion) {
    int hh = duracion / 3600;
    int min = (duracion % 3600) / 60;
    int ss = duracion % 60;
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}
//ordenamos usando la libreia cstring
void ordenarPorNombreCat(struct Categoria *arrCategorias, int cantidadCategorias) {
    for (int i = 0; i < cantidadCategorias - 1; i++) {
        for (int j = i + 1; j < cantidadCategorias; j++) {
            if (strcmp(arrCategorias[i].nombre, arrCategorias[j].nombre) > 0) {
                struct Categoria aux = arrCategorias[i];
                arrCategorias[i] = arrCategorias[j];
                arrCategorias[j] = aux;
            }
        }
    }
}

//usando la libreria cstring, hallamos los comentarios
void leerComentariosCanal(struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream archComentarios;
    abrirArchivoIfstream("ArchivosDeDatos/ComentariosAlCanal.csv", archComentarios);
    //LCK,this is the problem with d1 rewards no consumables
    char nombCanal[50], comentario[100];
    while (true) {
        archComentarios.getline(nombCanal, 50, ',');
        if (archComentarios.eof()) break;
        archComentarios.getline(comentario, 100, '\n');
        for (int i = 0; i < cantidadCategorias; i++) {
            for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
                if (strcmp(arrCategorias[i].reproducciones[j].canal, nombCanal) == 0) {
                    int pos = arrCategorias[i].reproducciones[j].numComentarios;

                    arrCategorias[i].reproducciones[j].comentarios[pos] = new char[strlen(comentario) + 1];
                    strcpy(arrCategorias[i].reproducciones[j].comentarios[pos], comentario);

                    arrCategorias[i].reproducciones[j].numComentarios++;
                }
            }
        }
    }
}
