//
// Created by aml on 13/10/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void abrirArchIfstream(const char *nombArch, ifstream &arch);

void abrirArchOfstream(const char *nombArch, ofstream &arch);

void imprimirReporte(ifstream &archCanales, ifstream &archCategorias, ifstream &archIdiomas,
                     ifstream &archStreams, ofstream &archReporte);

void imprimirEncabezado(ofstream &archReporte);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirCategoria(ifstream &archCategorias, ofstream &archReporte, int codStream, char codCategoria,
                       int numCategoria);

void imprimirTexto(ifstream &arch, ofstream &archReporte, bool enMayus, int cant, char delim);

void imprimirIdioma(ifstream &archIdiomas, ofstream &archReporte, int codIdioma, int hh, int min, int seg,
                    int &duracionSeg);

void imprimirDuracion(ofstream &arch, int hh, int min, int seg, int &duracion);

void eliminarTexto(ifstream &archCanales);

void imprimirCanales(ifstream &archCanales, ofstream &archReporte, int codStream, bool encontrado, int duracionSeg,
                     int &nroVecesReproducida, int &duracionResumen, double &tasaDropMenor, char &codCanalMenor,
                     int &numCanalMenor, double &tasaDropMayor, char &codCanalMayor, int &numCanalMayor);

void imprimirEncabezadoCanales(ofstream &archReporte, int canalNro, char codCanal, int numCanal);

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio);

void imprimirHoraFinal(ofstream &archReporte, int duracionI, int duracionSeg, int &duracionTotal);

void imprimirDatos(ofstream &archReporte, int nroStream, int ddI, int mesI, int anhioI, int hhI, int minI, int ssI,
                   int &duracionI, int duracionSeg, int &duracionTotal, double rating, double tasaDrop);

void imprimirResumenCanal(ofstream &archReporte, int duracionTotal, double sumaRating,
                          double sumaTasaDrop, int nroStream);


void calcularDatos(int nroStream, int duracionSeg, double rating, double tasaDrop,
                   int &duracionTiempo, double &sumaRating, double &sumaTasaDrop,
                   int &nroVecesReproducida, int &duracionResumen, char codCanal,
                   int numCanal, double &tasaDropMenor, char &codCanalMenor, int &numCanalMenor, double &tasaDropMayor,
                   char &codCanalMayor, int &numCanalMayor);

void imprimirResumenStream(ofstream &archReporte, int nroVecesReproducida, int duracionResumen, double tasaDropMenor,
                           char codCanalMenor,
                           int numCanalMenor, double tasaDropMayor, char codCanalMayor, int numCanalMayor);

void imprimirResumenFinal(ofstream &archReporte, int cantidad, int duracion);
#endif //FUNCIONES_H
