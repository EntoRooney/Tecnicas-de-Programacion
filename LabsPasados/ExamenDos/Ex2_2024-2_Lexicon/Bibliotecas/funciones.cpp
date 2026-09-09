#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"

#include "Palabra.h"
#include "Comentario.h"
#include "Plato.h"
#include "Atencion.h"

#define NO_ENCONTRADO -1
#define TAM_MAX 120

//
// Created by entol on 1/12/2025.
//

void leerLexicon(const char *nombArch, struct Palabra *lexicon, int &cantLexicon) {
    ifstream archLexicon;
    abrirArchivosIfstream(nombArch, archLexicon);
    //rapido,1
    int i = 0;
    while (true) {
        lexicon[i].texto = leerCadenaExactaDelim(archLexicon, ',');
        if (archLexicon.eof()) break;
        archLexicon >> lexicon[i].polaridad;
        archLexicon.get();
        i++;
    }
    cantLexicon = i;
}

void abrirArchivosIfstream(const char *nombArch, ifstream &arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

void abrirArchivosOfstream(const char *nombArch, ofstream &arch) {
    arch.open(nombArch, ios::out);
    arch << fixed << setprecision(2) << right;
    if (not arch.is_open()) {
        cout << "ERROR, el archivo " << nombArch << " no se pudo abrir correctamente";
        exit(1);
    }
}

char *leerCadenaExactaDelim(ifstream &arch, char delim) {
    char cadena[200], *ptr;
    arch.getline(cadena, 200, delim);
    if (arch.eof()) return nullptr;
    ptr = new char [strlen(cadena) + 1];
    strcpy(ptr, cadena);
    return ptr;
}

void leerPlatos(const char *nombArch, struct Plato *platos, int &cantPlatos) {
    ifstream archPlatos;
    abrirArchivosIfstream(nombArch, archPlatos);
    //A3H6GJ,Causa de Atun,12.57
    int i = 0;
    while (true) {
        platos[i].codigo = leerCadenaExactaDelim(archPlatos, ',');
        if (archPlatos.eof()) break;
        platos[i].nombre = leerCadenaExactaDelim(archPlatos, ',');
        archPlatos >> platos[i].precio;
        archPlatos.get();
        i++;
    }
    cantPlatos = i;
}

void leerAtenciones(const char *nombArch, struct Atencion *atenciones, int &cantAtenciones, struct Plato *platos,
                    int cantPlatos) {
    ifstream archAtenciones;
    abrirArchivosIfstream(nombArch, archAtenciones);
    //415217 21:36 B959AG 2 FK25HJ 1 S92K8X 3
    int hh, min, duracion, i = 0, cant;
    char codigo[10], c;
    while (true) {
        archAtenciones >> atenciones[i].codigo;
        if (archAtenciones.eof()) break;
        archAtenciones >> hh >> c >> min;
        convertirDuracion(hh, min, duracion);
        atenciones[i].hora = duracion;
        atenciones[i].platos_atentidos = new struct Plato[20];
        atenciones[i].comentarios = new struct Comentario[20];
        atenciones[i].cantidad_platos = 0;
        while (true) {
            archAtenciones >> codigo >> cant;
            int idPlato = buscarCodPlato(codigo, platos, cantPlatos);
            llenarAtenciones(idPlato, cant, atenciones[i], platos);
            if (archAtenciones.get() == '\n') break;
        }
        i++;
    }
    cantAtenciones = i;
}

void convertirDuracion(int hh, int min, int &duracion) {
    duracion = hh * 3600 + min * 60;
}

int buscarCodPlato(const char *codigo, struct Plato *platos, int cantPlatos) {
    for (int i = 0; i < cantPlatos; i++) {
        if (strcmp(platos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void llenarAtenciones(int idPlato, int cant, struct Atencion &atenciones, struct Plato *platos) {
    if (idPlato != NO_ENCONTRADO) {
        int pos = atenciones.cantidad_platos;
        atenciones.platos_atentidos[pos].codigo = new char [strlen(platos[idPlato].codigo) + 1];
        strcpy(atenciones.platos_atentidos[pos].codigo, platos[idPlato].codigo);

        atenciones.platos_atentidos[pos].nombre = new char [strlen(platos[idPlato].nombre) + 1];
        strcpy(atenciones.platos_atentidos[pos].nombre, platos[idPlato].nombre);

        atenciones.platos_atentidos[pos].precio = platos[idPlato].precio;
        atenciones.platos_atentidos[pos].cantidad = cant;

        atenciones.total_venta += atenciones.platos_atentidos[pos].precio *
                atenciones.platos_atentidos[pos].cantidad;

        atenciones.cantidad_platos++;
    }
}

void leerComentarios(const char *nombArch, struct Atencion *atenciones, int cantAtenciones, struct Palabra *lexicon,
                     int cantLexicon) {
    ifstream archComentarios;
    abrirArchivosIfstream(nombArch, archComentarios);
    int codAtencion;
    while (true) {
        archComentarios >> codAtencion;
        if (archComentarios.eof()) break;
        archComentarios.get();
        int idAtencion = buscarCodAtencion(codAtencion, atenciones, cantAtenciones);
        if (idAtencion != NO_ENCONTRADO) {
            int pos = atenciones[idAtencion].cantidad_comentarios;
            atenciones[idAtencion].comentarios[pos].texto = leerCadenaExactaDelim(archComentarios, '\n');

            atenciones[idAtencion].comentarios[pos].pre_procesado =
                    preProcesar(atenciones[idAtencion].comentarios[pos].texto);

            procesarPalabras(atenciones[idAtencion].comentarios[pos], lexicon, cantLexicon);

            atenciones[idAtencion].cantidad_comentarios++;
        }
    }
}

int buscarCodAtencion(int codAtencion, struct Atencion *atenciones, int cantAtenciones) {
    for (int i = 0; i < cantAtenciones; i++) {
        if (atenciones[i].codigo == codAtencion) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

char *preProcesar(const char *texto) {
    char textoLimpio[1000];
    int pos = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];

        if (isalpha(c) or c == ' ') {
            textoLimpio[pos++] = tolower(c);
        }
    }
    textoLimpio[pos] = '\0';

    char *limpio = new char[strlen(textoLimpio) + 1];
    strcpy(limpio, textoLimpio);
    return limpio;
}

void procesarPalabras(struct Comentario &comentario, struct Palabra *lexicon, int cantLexicon) {
    char palabra[200];
    int pos = 0;

    comentario.cantidad_palabras = 0;
    comentario.polaridad_total = 0;

    char *txt = comentario.pre_procesado;

    for (int i = 0; ; i++) {
        char c = txt[i];

        if (c != ' ' and c != '\0') {
            palabra[pos++] = c;
        } else {
            if (pos > 0) {
                palabra[pos] = '\0';

                int p = comentario.cantidad_palabras;

                comentario.palabras[p].polaridad = buscarPolaridad(palabra, lexicon, cantLexicon);

                comentario.polaridad_total += comentario.palabras[p].polaridad;

                comentario.cantidad_palabras++;
                pos = 0;
            }
        }
        if (c == '\0') break;
    }
}

int buscarPolaridad(const char *palabra, struct Palabra *lexicon, int cantLexicon) {
    for (int i = 0; i < cantLexicon; i++) {
        if (strcmp(lexicon[i].texto, palabra) == 0)
            return lexicon[i].polaridad;
    }
    return 0;
}

void imprimirReporte(const char *nombArch, struct Atencion *atenciones, int cantAtenciones) {
    ofstream archReporte;
    abrirArchivosOfstream(nombArch, archReporte);
    archReporte << setw(26) << ' ' << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    archReporte << setw(33) << ' ' << "RELACION DE ATENCIONES" << endl;
    for (int i = 0; i < cantAtenciones; i++) {
        int totalPolaridad = 0;
        imprimirLinea(archReporte, TAM_MAX, '=');
        archReporte << "No. ATENCION " << atenciones[i].codigo << setw(10) << ' ' << "Atendido a las: ";
        imprimirDuracion(archReporte, atenciones[i].hora);
        for (int j = 0; j < atenciones[i].cantidad_platos; j++) {
            imprimirLinea(archReporte, TAM_MAX, '-');
            archReporte << atenciones[i].platos_atentidos[j].codigo << ')' << setw(2) << ' ' <<
                    atenciones[i].platos_atentidos[j].nombre << setw(
                        40 - strlen(atenciones[i].platos_atentidos[j].nombre)) <<
                    ' ' << setw(6) << atenciones[i].platos_atentidos[j].precio << setw(4) <<
                    atenciones[i].platos_atentidos[j].cantidad << setw(9) <<
                    atenciones[i].platos_atentidos[j].precio * atenciones[i].platos_atentidos[j].cantidad << endl;
        }
        for (int z = 0; z < atenciones[i].cantidad_comentarios; z++
            ) {
            totalPolaridad += atenciones[i].comentarios[z].polaridad_total;
        }
        archReporte << endl;
        archReporte << "Total vendido : " << setw(10) << atenciones[i].total_venta << endl;
        archReporte << "Polaridad total de los comentarios : " << setw(6) << totalPolaridad << endl;
    }
}

void imprimirLinea(ofstream &arch, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch.put('\n');
}

void imprimirDuracion(ofstream &arch, int duracion) {
    int hh = duracion / 3600;
    int mm = (duracion % 3600) / 60;
    arch << setfill('0') << setw(2) << hh << ':' << setw(2) << mm << setfill(' ') << endl;
}
