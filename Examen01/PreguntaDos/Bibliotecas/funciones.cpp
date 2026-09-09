// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funciones.h"
#define NO_ENCONTRADO -1

void leerArrStreams(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                    int &cantStreams) {
    ifstream archStreams;
    abrirArchIfstream("ArchivoDeDatos/Streams.txt", archStreams);
    int i = 0, hh, min, ss, duracion;
    char c;
    while (true) {
        archStreams >> arrCodStream[i];
        if (archStreams.eof()) break;
        archStreams >> hh >> c >> min >> c >> ss;
        calcularDuracion(hh, min, ss, duracion);
        arrDuracion[i] = duracion;
        archStreams >> arrIdioma[i] >> ws >> arrCodCate[i] >> arrNumCate[i];
        i++;
    }
    cantStreams = i;
}

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

void calcularDuracion(int hh, int min, int ss, int &duracion) {
    duracion = hh * 3600 + min * 60 + ss;
}

void imprimirReporteSimple(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                           int cantStreams) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/ReporteSimple.txt", archReporte);
    archReporte << right << fixed << setprecision(2);
    archReporte << setw(10) << ' ' << "REPORTE PARA LOS STREAMS" << endl;
    archReporte << setw(1) << ' ' << "CODIGO" << setw(3) << ' ' << "DURACION(s)" << setw(1) << ' ' << "IDIOMA" <<
            setw(6)
            << ' ' << "CATEGORIA" << endl;
    for (int i = 0; i < cantStreams; i++) {
        archReporte << arrCodStream[i] << setw(5) << ' ' << setw(5) << arrDuracion[i]
                << setw(5) << ' ' << setw(5) << arrIdioma[i]
                << setw(5) << ' ' << setw(5) << arrCodCate[i] << arrNumCate[i] << endl;
    }
}

void actualizarArr(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                   int cantStreams, int *arrFechaPrime, int *arrFechaUlti, double *arrPromRati, double *arrPromTasa,
                   int *arrCantRepro,
                   int *arrTotalRepro) {
    ifstream archCanales;
    abrirArchIfstream("ArchivoDeDatos/Canales.txt", archCanales);
    int bsr, codStreamArch,dd,mes,anhio,hh,min,ss,duracion,fechaConvertida;
    double rating,drop;
    char codCanalArch,c;
    while (true) {
        archCanales >> bsr >> c >> bsr >> c >> bsr;
        if (archCanales.eof()) break;
        archCanales>>ws>>c>>bsr;
        eliminarTexto(archCanales);
        while (true) {
            archCanales >> codStreamArch >>dd>> c >> mes >> c >> anhio>>hh>> c >> min >> c >> ss>>rating>>drop;
            int idStream=buscarIdStream(arrCodStream,codStreamArch,cantStreams);
            convertirDuracion(hh,min,ss,duracion);
            convertirFecha(dd,mes,anhio,fechaConvertida);
            if (idStream!=NO_ENCONTRADO) {
                arrCantRepro[idStream]++;
                arrPromRati[idStream] += rating;
                arrPromTasa[idStream]+=drop;
                arrTotalRepro[idStream]+=duracion;
                if (arrFechaPrime[idStream]==0 or fechaConvertida>arrFechaPrime[idStream]) {
                    arrFechaPrime[idStream]=fechaConvertida;
                }
                if (arrFechaUlti[idStream]==0 or fechaConvertida<arrFechaUlti[idStream]) {
                    arrFechaUlti[idStream]=fechaConvertida;
                }

            }
            if (archCanales.get()=='\n') break;
        }

    }
    for (int i = 0; i < cantStreams; i++) {
        arrPromRati[i]/=arrCantRepro[i];
    }

    for (int i = 0; i < cantStreams; i++) {
        arrPromTasa[i]/=arrCantRepro[i];
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

int buscarIdStream(int *arrCodStream,int codStreamArch,int cantStreams) {
    for (int i = 0; i < cantStreams; i++) {
        if (arrCodStream[i] == codStreamArch) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void convertirDuracion(int hh,int min,int ss,int &duracion) {
    duracion=hh*3600+min*60+ss;
}

void convertirFecha(int dd,int mes,int anhio,int &fechaConvertida) {
    fechaConvertida=anhio*10000+mes*100+dd;
}

void  imprimirReporte(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                   int cantStreams,
                   int *arrFechaPrime, int *arrFechaUlti, double *arrPromRati, double *arrPromTasa, int *arrCantRepro,
                   int *arrTotalRepro) {
    ofstream archReporte;
    abrirArchOfstream("ArchivosDeReporte/Reproducciones-Streams.txt", archReporte);
    archReporte<<setw(4)<<' '<<"PLATAFORMA DE STREAMING TP"<<endl;

    for (int i = 0; i < cantStreams; i++) {
        archReporte<<arrCodStream[i]<<setw(4)<<' '<<arrIdioma[i]<<setw(4)<<' '<<arrCodCate[i]<<arrNumCate[i]
        <<setw(5)<<' ';
        // imprimirFecha(archReporte,arrFechaPrime[i]);
        archReporte<<setw(5)<<' ';
        // imprimirFecha(archReporte,arrFechaUlti[i]);

        archReporte<<arrPromRati[i]<<setw(4)<<' '<<arrPromTasa[i]<<arrDuracion[i]<<' '<<arrCantRepro[i]<<endl;
    }
}