//
// Created by aml on 13/10/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerArrStreams(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                    int &cantStreams);

void abrirArchIfstream(const char *nombArch, ifstream &arch);

void abrirArchOfstream(const char *nombArch, ofstream &arch);

void calcularDuracion(int hh, int min, int ss, int &duracion);

void imprimirReporteSimple(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                           int cantStreams);

void actualizarArr(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                   int cantStreams,
                   int *arrFechaPrime, int *arrFechaUlti, double *arrPromRati, double *arrPromTasa, int *arrCantRepro,
                   int *arrTotalRepro);

void eliminarTexto(ifstream &archCanales);

int buscarIdStream(int *arrCodStream, int codStreamArch, int cantStreams);

void convertirDuracion(int hh, int min, int ss, int &duracion);

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida);

void  imprimirReporte(int *arrCodStream, int *arrDuracion, int *arrIdioma, char *arrCodCate, int *arrNumCate,
                   int cantStreams,
                   int *arrFechaPrime, int *arrFechaUlti, double *arrPromRati, double *arrPromTasa, int *arrCantRepro,
                   int *arrTotalRepro);

#endif //FUNCIONES_H
