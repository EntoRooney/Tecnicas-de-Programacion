#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
//Nombre: Ento Rooney Lazaro Trujillo
//Codigo: 20222032

using namespace std;

#include "funciones.h"
#include "Categoria .h"
#include "Reproduccion .h"

#define NO_ENCONTRADO -1
#define TAM_MAX 120

//leemos categorias usando getline ya que es un archivo .csv
void leerCategorias(const char *nombArch, struct Categoria *arrCategorias, int &cantidadCategorias) {
    ifstream archCat;
    abrirArchivoIfstream(nombArch, archCat);
    //    UM163F47,just chatting
    char cod[20], nombre[100];
    int i = 0;
    while (true) {
        archCat.getline(cod, 20, ',');
        if (archCat.eof()) break;
        archCat.getline(nombre, 100, '\n');
        archCat>>ws;
        strcpy(arrCategorias[i].codigo, cod);
        strcpy(arrCategorias[i].nombre, nombre);
        i++;
    }
    cantidadCategorias = i;
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
    arch << right << fixed << setprecision(2);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void imprimirReportePrueba(const char *nombrArch, struct Categoria *arrCategorias, int cantidadCategorias,
                           bool reporteDos) {
    //usamos bool porque luego nos piden que imprmimas más cosas en los otros items más adelante
    ofstream archReporte;
    abrirArchivoOfstream(nombrArch, archReporte);
    archReporte << setw(5) << ' ' << "REPORTE PARA CATEGORIAS" << endl;
    archReporte << setw(1) << ' ' << "CODIGO" << setw(6) << ' ' << "NOMBRE" << endl;
    imprimirLinea(archReporte, 50, '-');
    for (int i = 0; i < cantidadCategorias; i++) {
        archReporte << arrCategorias[i].codigo << setw(5) << ' ' << arrCategorias[i].nombre<<endl;
        if (reporteDos) {
            archReporte << setw(1) << ' ' << "CANAL" << setw(9) << ' ' << "RATING" << setw(5) << ' ' << "DURACION";
            archReporte << endl;
            for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
                archReporte << arrCategorias[i].reproducciones[j].canal <<
                        setw(15 - strlen(arrCategorias[i].reproducciones[j].canal)) << ' ' << setw(6) <<
                        arrCategorias[i].reproducciones[j].rating << setw(6) << ' ';
                imprimirDuracion(archReporte, arrCategorias[i].reproducciones[j].duracion);
                archReporte << endl;
            }
        }
        if (reporteDos) {
            imprimirLinea(archReporte, 50, '-');
        }
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch.put('\n');
}

//leemos streams usando getline ya que es un archivo .csv
void leerStreams(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream archStreams;
    abrirArchivoIfstream(nombArch, archStreams);
    //Sardoche,ZT132U54,4.410,01:41:48
    char nomCanal[50], codCate[50], c;
    double ratCalidad;
    int hh, mm, ss, duracionSeg;
    while (true) {
        archStreams.getline(nomCanal, 50, ',');
        if (archStreams.eof()) break;
        archStreams.getline(codCate, 50, ',');
        archStreams >> ratCalidad >> c >> hh >> c >> mm >> c >> ss;
        convertirDuracion(hh, mm, ss, duracionSeg);
        archStreams>>ws;
        int idCategoria = buscarCategoria(arrCategorias, cantidadCategorias, codCate);
        if (idCategoria != NO_ENCONTRADO) {
            int posRepro = arrCategorias[idCategoria].numReproducciones;
            if (posRepro < 15) {
                strcpy(arrCategorias[idCategoria].reproducciones[posRepro].canal, nomCanal);
                arrCategorias[idCategoria].reproducciones[posRepro].duracion = duracionSeg;
                arrCategorias[idCategoria].reproducciones[posRepro].rating = ratCalidad;
            }
            arrCategorias[idCategoria].numReproducciones++;
        }
    }
}

void convertirDuracion(int hh, int mm, int ss, int &duracion) {
    duracion = hh * 3600 + mm * 60 + ss;
}

int buscarCategoria(struct Categoria *arrCategorias, int cantidadCategorias, const char *codCate) {
    for (int i = 0; i < cantidadCategorias; i++) {
        if (strcmp(arrCategorias[i].codigo, codCate) == 0) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}


void imprimirDuracion(ofstream &archReporte, int duracion) {
    int hh = duracion / 3600;
    int mm = (duracion % 3600) / 60;
    int ss = (duracion) % 60;
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ');
}

void calcularPromedios(struct Categoria *arrCategorias, int cantidadCategorias) {
    //calculamos promedios y inicializamos adentro del for para que por cada categoria se acumule
    for (int i = 0; i < cantidadCategorias; i++) {
        int duracionTotal = 0;
        double sumaRating = 0;
        for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
            duracionTotal += arrCategorias[i].reproducciones[j].duracion;
            sumaRating += arrCategorias[i].reproducciones[j].rating;
        }
        arrCategorias[i].duracionTotal = duracionTotal;
        arrCategorias[i].promedioRating = sumaRating / arrCategorias[i].numReproducciones;
    }
}

//imprimimos el reporte final, basicamente es la misma estructura del reporte pasado
void imprimirReporte(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {

    ofstream archReporte;
    abrirArchivoOfstream(nombArch, archReporte);

    archReporte << setw(11) << ' ' << "REPORTE POR CATEGORIAS" << endl;
    for (int i = 0; i < cantidadCategorias; i++) {
        archReporte << "CODIGO: " << arrCategorias[i].codigo << endl;
        archReporte << "NOMBRE: " << arrCategorias[i].nombre << endl;
        imprimirLinea(archReporte, 50, '-');
        archReporte << "REPRODUCCIONES: " << endl;
        archReporte << "CANAL " << setw(13) << ' ' << "RATING" << setw(5) << ' ' << "DURACION";
        archReporte << endl;

        for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
            archReporte << arrCategorias[i].reproducciones[j].canal <<
                    setw(18 - strlen(arrCategorias[i].reproducciones[j].canal)) << ' ' << setw(6) <<
                    arrCategorias[i].reproducciones[j].rating << setw(6) << ' ';
            imprimirDuracion(archReporte, arrCategorias[i].reproducciones[j].duracion);
            archReporte << endl;
        }

        imprimirLinea(archReporte, 50, '-');
        archReporte << "RATING PROMEDIO: " << setw(4) << ' ' << arrCategorias[i].promedioRating << endl;
        archReporte << "DURACION TOTAL: " << setw(5) << ' ';
        imprimirDuracion(archReporte, arrCategorias[i].duracionTotal);
        archReporte << endl;
        imprimirLinea(archReporte, 50, '=');
    }
}
