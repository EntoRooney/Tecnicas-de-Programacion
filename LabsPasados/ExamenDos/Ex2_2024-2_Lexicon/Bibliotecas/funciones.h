//
// Created by entol on 1/12/2025.
//

#ifndef EXAMENMIMAYORTERROR_FUNCIONES_H
#define EXAMENMIMAYORTERROR_FUNCIONES_H

void leerLexicon(const char *nombArch, struct Palabra *lexicon, int &cantLexicon);

void abrirArchivosIfstream(const char *nombArch, ifstream &arch);

void abrirArchivosOfstream(const char *nombArch, ofstream &arch);

char *leerCadenaExactaDelim(ifstream &arch, char delim);

void leerPlatos(const char *nombArch, struct Plato *platos, int &cantPlatos);

void leerAtenciones(const char *nombArch, struct Atencion *atenciones, int &cantAtenciones, struct Plato *platos,
                    int cantPlatos);

void convertirDuracion(int hh, int min, int &duracion);

int buscarCodPlato(const char *codigo, struct Plato *platos, int cantPlatos);

void llenarAtenciones(int idPlato, int cant, struct Atencion &atenciones, struct Plato *platos);

void leerComentarios(const char *nombArch, struct Atencion *atenciones, int cantAtenciones, struct Palabra *lexicon,
                     int cantLexicon);

int buscarCodAtencion(int codAtencion, struct Atencion *atenciones, int cantAtenciones);

char *preProcesar(const char *texto);

void procesarPalabras(struct Comentario &comentario, struct Palabra *lexicon, int cantLexicon);

int buscarPolaridad(const char *palabra, struct Palabra *lexicon, int cantLexicon);

void imprimirReporte(const char *nombArch, struct Atencion *atenciones, int cantAtenciones);

void imprimirLinea(ofstream &arch, int cant, char c);

void imprimirDuracion(ofstream &arch, int duracion);
#endif //EXAMENMIMAYORTERROR_FUNCIONES_H
