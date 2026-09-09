//
// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "funciones.h"
#define TAM_MAX 150


void abrirArchIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void imprimirReporte(ifstream &archCanales, ifstream &archCategorias, ifstream &archIdiomas, ifstream &archStreams,
                     ofstream &archReporte) {
    imprimirEncabezado(archReporte);
    int codStream, hh, min, seg, codIdioma, numCategoria, numCanalMayor, numCanalMenor, cantidad = 0, duracion = 0,
            duracionSeg;
    char c, codCategoria, codCanalMenor, codCanalMayor;
    bool encontrado = false;
    while (true) {
        //leo los streams
        double tasaDropMenor = 99999, tasaDropMayor = -1;
        int nroVecesReproducida = 0, duracionResumen = 0;
        archStreams >> codStream;
        if (archStreams.eof()) break;
        archStreams >> hh >> c >> min >> c >> seg >> codIdioma >> ws >> codCategoria >> numCategoria;
        //imprimo su categoria y idioma
        imprimirCategoria(archCategorias, archReporte, codStream, codCategoria, numCategoria);
        imprimirIdioma(archIdiomas, archReporte, codIdioma, hh, min, seg, duracionSeg);
        imprimirCanales(archCanales, archReporte, codStream, encontrado, duracionSeg,
                        nroVecesReproducida, duracionResumen, tasaDropMenor, codCanalMenor,
                        numCanalMenor, tasaDropMayor, codCanalMayor, numCanalMayor);
        imprimirResumenStream(archReporte, nroVecesReproducida, duracionResumen, tasaDropMenor, codCanalMenor,
                              numCanalMenor, tasaDropMayor, codCanalMayor, numCanalMayor);
        cantidad += nroVecesReproducida;
        duracion += duracionResumen;
    }
    imprimirResumenFinal(archReporte, cantidad, duracion);
}

void imprimirEncabezado(ofstream &archReporte) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(30) << ' ' << "PLATAFORMA DE STREAMING TP" << endl;
    archReporte << setw(30) << ' ' << "REPRODUCCION DE STREAMS" << endl;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirCategoria(ifstream &archCategorias, ofstream &archReporte, int codStream, char codCategoria,
                       int numCategoria) {
    archCategorias.clear();
    archCategorias.seekg(0, ios::beg);
    int numCategoriaArch;
    char codCategoriaArch;

    while (true) {
        archCategorias >> codCategoriaArch >> numCategoriaArch;
        if (archCategorias.eof())break;
        if (codCategoriaArch == codCategoria and numCategoriaArch == numCategoria) {
            imprimirLinea(archReporte,TAM_MAX, '=');
            archReporte << "STREAM:" << setw(2) << ' ' << codStream << setw(5) << ' ' << "CATEGORIA: " << codCategoria
                    << numCategoria << " - ";
            imprimirTexto(archCategorias, archReporte, true, 60, '\n');
        } else {
            while (true) {
                if (archCategorias.get() == '\n') break;
            }
        }
    }
}

void imprimirTexto(ifstream &arch, ofstream &archReporte, bool enMayus, int cant, char delim) {
    arch >> ws;
    char c;
    int contador = 0;
    while (true) {
        c = arch.get();
        if (c == delim) break;
        contador++;
        if (c == '_' or c == '-') c = ' ';
        if (enMayus) {
            if ('a' <= c and c <= 'z') {
                c = c - 'a' + 'A';
            }
        }
        archReporte.put(c);
    }
    archReporte << setw(cant - contador) << ' ';
}

void imprimirIdioma(ifstream &archIdiomas, ofstream &archReporte, int codIdioma, int hh, int min, int seg,
                    int &duracionSeg) {
    archIdiomas.clear();
    archIdiomas.seekg(0, ios::beg);
    int codIdiomaArch;
    while (true) {
        archIdiomas >> codIdiomaArch;
        if (archIdiomas.eof()) break;
        if (codIdiomaArch == codIdioma) {
            archReporte << "IDIOMA: " << codIdioma << " - ";
            imprimirTexto(archIdiomas, archReporte, false, 15, '\n');
            imprimirDuracion(archReporte, hh, min, seg, duracionSeg);
            archReporte.put('\n');
            imprimirLinea(archReporte,TAM_MAX, '=');
        } else {
            while (true) {
                if (archIdiomas.get() == '\n') break;
            }
        }
    }
}

void imprimirDuracion(ofstream &arch, int hh, int min, int seg, int &duracion) {
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << seg << setfill(' ');
    duracion = hh * 3600 + min * 60 + seg;
}

void imprimirCanales(ifstream &archCanales, ofstream &archReporte, int codStream, bool encontrado, int duracionSeg,
                     int &nroVecesReproducida, int &duracionResumen, double &tasaDropMenor, char &codCanalMenor,
                     int &numCanalMenor, double &tasaDropMayor, char &codCanalMayor, int &numCanalMayor) {
    archCanales.clear();
    archCanales.seekg(0, ios::beg);
    int ddI, mesI, anhioI, numCanal, bsr, hhI, minI, ssI, codStreamArch, canalNro = 0, duracionI, duracionTotal;
    char c, codCanal;
    double rating, tasaDrop;
    while (true) {
        int nroStream = 0, duracionTiempo = 0;
        double sumaRating = 0, sumaTasaDrop = 0;
        bool encontradoG = false;
        archCanales >> bsr;
        if (archCanales.eof()) break;
        archCanales >> c >> bsr >> c >> bsr >> ws >> codCanal >> numCanal;
        eliminarTexto(archCanales);
        while (true) {
            archCanales >> codStreamArch >> ddI >> c >> mesI >> c >> anhioI >> hhI >> c >> minI >> c >>
                    ssI >> rating >> tasaDrop;
            if (codStreamArch == codStream) {
                nroStream++;
                if (!encontradoG) {
                    canalNro++;
                    imprimirEncabezadoCanales(archReporte, canalNro, codCanal, numCanal);
                    encontradoG = true;
                }
                imprimirDatos(archReporte, nroStream, ddI, mesI, anhioI, hhI, minI, ssI, duracionI, duracionSeg,
                              duracionTotal, rating, tasaDrop);
                calcularDatos(nroStream, duracionSeg, rating, tasaDrop, duracionTiempo, sumaRating, sumaTasaDrop,
                              nroVecesReproducida, duracionResumen, codCanal, numCanal, tasaDropMenor, codCanalMenor,
                              numCanalMenor, tasaDropMayor, codCanalMayor, numCanalMayor);
            }
            if (archCanales.get() == '\n') break;
        }
        if (encontradoG) {
            imprimirResumenCanal(archReporte, duracionTiempo, sumaRating, sumaTasaDrop, nroStream);
            imprimirLinea(archReporte,TAM_MAX, '-');
        }
    }
}


void eliminarTexto(ifstream &archCanales) {
    archCanales >> ws;
    char c;
    while (true) {
        c = archCanales.get();
        if (c == ' ') break;
    }
}

void imprimirEncabezadoCanales(ofstream &archReporte, int canalNro, char codCanal, int numCanal) {
    archReporte << setw(2) << ' ' << setfill('0') << setw(2) << canalNro << ")" << setfill(' ')
            << setw(2) << "CANAL: " << codCanal << numCanal << endl;
    archReporte << setw(5) << ' ' << "REPRODUCCIONES" << endl;
    archReporte << setw(5) << ' ' << "No." << setw(5) << ' ' << "FECHA" << setw(5) << ' ' << "INICIO"
            << setw(5) << ' ' << "FIN" << setw(5) << ' ' << "RATING CALIDAD" << setw(5) << ' ' << "TASA DROP-OFF" <<
            endl;
}


void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) << anhio << setfill(' ');
}

void imprimirHoraFinal(ofstream &archReporte, int duracionI, int duracionSeg, int &duracionTotal) {
    int x;
    duracionTotal = duracionI + duracionSeg;
    int hh = duracionTotal / 3600;
    int min = (duracionTotal % 3600) / 60;
    int seg = duracionTotal % 60;
    imprimirDuracion(archReporte, hh, min, seg, x);
}

void imprimirDatos(ofstream &archReporte, int nroStream, int ddI, int mesI, int anhioI, int hhI, int minI, int ssI,
                   int &duracionI, int duracionSeg, int &duracionTotal, double rating, double tasaDrop) {
    archReporte << setw(5) << ' ' << setfill('0') << setw(2) << nroStream << ")" << setfill(' ');
    archReporte << setw(2) << ' ';
    imprimirFecha(archReporte, ddI, mesI, anhioI);
    archReporte << setw(2) << ' ';
    imprimirDuracion(archReporte, hhI, minI, ssI, duracionI);
    archReporte << setw(2) << ' ';
    imprimirHoraFinal(archReporte, duracionI, duracionSeg, duracionTotal);
    archReporte << setw(6) << ' ' << setw(5) << rating << setw(13) << ' ' << setw(4) << tasaDrop << "%" <<
            endl;
}

void imprimirResumenCanal(ofstream &archReporte, int duracionTotal, double sumaRating,
                          double sumaTasaDrop, int nroStream) {
    int xx;
    archReporte << setw(5) << ' ' << "TOTAL TIEMPO REPRODUCCIONES: ";
    int hh = duracionTotal / 3600;
    int min = (duracionTotal % 3600) / 60;
    int seg = duracionTotal % 60;
    imprimirDuracion(archReporte, hh, min, seg, xx);
    archReporte << endl;
    double promedioRating = sumaRating / nroStream;
    double promedioTasa = sumaTasaDrop / nroStream;
    archReporte << setw(5) << ' ' << "PROMEDIO RATING CALIDAD:" << setw(13) << promedioRating << endl;
    archReporte << setw(5) << ' ' << "PROMEDIO TASA DROP-OFF:" << setw(14) << promedioTasa << "%" << endl;
}

void calcularDatos(int nroStream, int duracionSeg, double rating, double tasaDrop,
                   int &duracionTiempo, double &sumaRating, double &sumaTasaDrop,
                   int &nroVecesReproducida, int &duracionResumen, char codCanal,
                   int numCanal, double &tasaDropMenor, char &codCanalMenor, int &numCanalMenor, double &tasaDropMayor,
                   char &codCanalMayor, int &numCanalMayor) {
    duracionTiempo += nroStream * duracionSeg;
    sumaRating += rating;
    sumaTasaDrop += tasaDrop;
    nroVecesReproducida++;
    duracionResumen += duracionTiempo;
    if (tasaDrop < tasaDropMenor) {
        tasaDropMenor = tasaDrop;
        codCanalMenor = codCanal;
        numCanalMenor = numCanal;
    }
    if (tasaDrop > tasaDropMayor) {
        tasaDropMayor = tasaDrop;
        codCanalMayor = codCanal;
        numCanalMayor = numCanal;
    }
}

void imprimirResumenStream(ofstream &archReporte, int nroVecesReproducida, int duracionResumen, double tasaDropMenor,
                           char codCanalMenor,
                           int numCanalMenor, double tasaDropMayor, char codCanalMayor, int numCanalMayor) {
    int xx;
    archReporte << "RESUMEN DEL STREAM" << endl;
    archReporte << "#VECES REPRODUCIDAS:" << setw(5) << ' ' << nroVecesReproducida << endl;
    archReporte << "TIEMPO TOTAL REPRODUCCION: ";
    int hh = duracionResumen / 3600;
    int min = (duracionResumen % 3600) / 60;
    int seg = duracionResumen % 60;
    imprimirDuracion(archReporte, hh, min, seg, xx);
    archReporte << endl;
    archReporte << "TASA DROP-OFF MENOR: " << tasaDropMenor << " CANAL: " << codCanalMenor << numCanalMenor << endl;
    archReporte << "TASA DROP-OFF MAYOR: " << tasaDropMayor << " CANAL: " << codCanalMayor << numCanalMayor << endl;
}

void imprimirResumenFinal(ofstream &archReporte, int cantidad, int duracion) {
    imprimirLinea(archReporte,TAM_MAX, '=');
    archReporte << "RESUMEN DEL TOTAL" << endl;
    int xx;
    imprimirLinea(archReporte,TAM_MAX, '-');
    archReporte << "# STREAMS: " << cantidad << endl;
    archReporte << "DURACION TOTAL REPRODUCCION: ";
    int hh = duracion / 3600;
    int min = (duracion % 3600) / 60;
    int seg = duracion % 60;
    imprimirDuracion(archReporte, hh, min, seg, xx);
    archReporte << endl;
    imprimirLinea(archReporte,TAM_MAX, '=');
}
