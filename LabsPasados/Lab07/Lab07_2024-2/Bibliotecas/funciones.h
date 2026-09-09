//
// Created by USUARIO on 2/11/2025.
//

#ifndef LAB07_24_2_FUNCIONES_H
#define LAB07_24_2_FUNCIONES_H

void leerArrRepartidores(int *arrDniRepartidor, char * *arrNombreRepartidor, char * *arrVehiRepartidor,
                         int *arrCodDistRepartidor, char * *arrDistritoRepartidor, int &cantRepartidores);

void abrirArchivosIfstream(const char *nombArch, ifstream &arch);

void abrirArchivosOfstream(const char *nombArch, ofstream &arch);

void modificarTexto(char *texto, bool pasarMayus);

void leerArrPlatos(int *arrCodPlato, char * *arrNombrePlato, double *arrPrecioPlato, char * *arrCategoriaPlato,
                   double *arrDescPlato, int &cantPlatos);

void imrprimirReportePrueba(int *arrCodPlato, char **arrNombrePlato, double *arrPrecioPlato, char **arrCategoriaPlato,
                            double *arrDescPlato, int cantPlatos,
                            int *arrDniRepartidor, char * *arrNombreRepartidor, char * *arrVehiRepartidor,
                            int *arrCodDistRepartidor, char * *arrDistritoRepartidor, int cantRepartidores);

void imprimirEncabezadoPlatos(ofstream &archReporte);

void imprimirLinea(ofstream &archReporte, int cant, char c);

void imprimirEncabezadoRepartidores(ofstream &archReporte);


#endif //LAB07_24_2_FUNCIONES_H
