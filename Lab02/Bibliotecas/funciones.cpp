//
// Nombre:Ento Rooney Lazaro Trujillo
// Codigo:20222032

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;
#include "funciones.h"
#define TAM_MAX 125

void imprimirReporte(ifstream &archDatos, ofstream &archReporte) {
    int fechaInicial, fechaFinal, ddC, mesC, anhioC, numCanal, fechaConvertida, numCompania = 0, dd, mes, anhio,
            hh, min, ss, cantRepro, horaEnSegundos,cantStreams=0,duracionFinal=0;
    double tarifaRepro, tarifaStream, ingresosPorDuracion,ingresosPorPublicidad,ingresosFinalesDuracion=0,ingresosFinalesPublicidad=0;
    char c, codCanal;
    imprimirEncabezadoInicial(archReporte, fechaInicial, fechaFinal, tarifaRepro, tarifaStream);
    while (true) {
        int totalSegundos = 0,totalCantRepro=0;
        double totalIngresosDuracion=0,engagemente=0;
        //antes que nada leo las fechas de creacion
        archDatos >> ddC;
        if (archDatos.eof()) break;
        archDatos >> c >> mesC >> c >> anhioC >> ws >> codCanal >> numCanal;
        convertirFecha(ddC, mesC, anhioC, fechaConvertida);
        //VERIFICO LAS FECHAS QUE ME DAN COMO LIMITES
        //EN CASO NO SE ENCUENTRE ESAS FECHAS, ME SALTO TODA LA LINEA
        if (fechaConvertida >= fechaInicial and fechaConvertida <= fechaFinal) {
            numCompania++;
            leerNombre(archDatos, archReporte, ddC, mesC, anhioC, codCanal, numCanal, numCompania,engagemente);
            imprimirEncabezadoDatos(archReporte);
            while (true) {
                archDatos >> dd >> c >> mes >> c >> anhio >> hh >> c >> min >> c >> ss >> cantRepro;
                cantStreams++;
                imprimirDatos(archReporte, dd, mes, anhio, hh, min, ss, tarifaStream, cantRepro,ingresosPorDuracion, horaEnSegundos);
                totalSegundos += horaEnSegundos;
                totalIngresosDuracion+=ingresosPorDuracion;
                totalCantRepro+=cantRepro;
                if (archDatos.get() == '\n')break;
            }
            imprimirResumenCanal(archReporte,totalSegundos,totalIngresosDuracion,totalCantRepro,tarifaRepro,ingresosPorPublicidad,engagemente);
            duracionFinal+=totalSegundos;
            ingresosFinalesDuracion+=totalIngresosDuracion;
            ingresosFinalesPublicidad+=ingresosPorPublicidad;
        } else {
            while (true) {
                if (archDatos.get() == '\n')break;
            }
        }
    }
    imprimirResumenFinal(archReporte,cantStreams,duracionFinal,ingresosFinalesDuracion,ingresosFinalesPublicidad);
}

void imprimirEncabezadoInicial(ofstream &archReporte, int &fechaInicial, int &fechaFinal, double &tarifaRepro,
                               double &tarifaStream) {
    //PEDIMOS AL USUARIO LAS FECHAS JUNTO CON LAS TARIFAS
    int ddI, mesI, anhioI, ddF, mesF, anhioF;
    //
    // cout << "POR FAVOR INSERTE LA FECHA INICIAL" << endl;
    // cin >> ddI >> mesI >> anhioI;
    // cout << "POR FAVOR INSERTE LA FECHA FINAL" << endl;
    // cin >> ddF >> mesF >> anhioF;
    // cout << "POR FAVOR INSERTE LA TARIFA DE REPRODUCCIONES" << endl;
    // cin >> tarifaRepro;
    // cout << "POR FAVOR INSERTE LA TARIDA POR DURACION DEL STREAM" << endl;
    // cin >> tarifaStream;
    ddI = 10;
    mesI = 9;
    anhioI = 2022;
    ddF = 1;
    mesF = 1;
    anhioF = 2023;
    tarifaRepro = 2.57;
    tarifaStream = 0.78;
    archReporte << setw(41) << " " << "PLATAFORMA TP_Twitch" << endl;
    archReporte << setw(33) << " " << "REGISTRO DE LOS CANALES AFILIDADOS" << endl;
    archReporte << setw(22) << " " << "FECHAS DE CREACION ENTRE EL ";
    imprimirFecha(archReporte, ddI, mesI, anhioI);
    archReporte << " Y EL ";
    imprimirFecha(archReporte, ddF, mesF, anhioF);
    archReporte << endl;
    archReporte << setw(11) << " " << "TARIFA POR NUMERO DE REPRODUCCIONES: " << tarifaRepro <<
            " POR CADA 1,000 REPRODUCCIONES Y FRACCION" << endl;
    archReporte << setw(21) << " " << "TARIFA POR DURACION DEL STREAM: " << tarifaStream <<
            " POR CADA MINUTO  Y FRACCION" << endl;
    convertirFecha(ddI, mesI, anhioI, fechaInicial);
    convertirFecha(ddF, mesF, anhioF, fechaFinal);
    archReporte << fixed << setprecision(2);
}

void imprimirFecha(ofstream &archReporte, int dd, int mes, int anhio) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mes << "/" << setw(4) <<
            anhio << setfill(' ');
}

void convertirFecha(int dd, int mes, int anhio, int &fechaConvertida) {
    fechaConvertida = anhio * 10000 + mes * 100 + dd;
}

void leerNombre(ifstream &archDatos, ofstream &archReporte, int ddC, int mesC, int anhioC, char codCanal,
                int numCanal, int numCompania,double &engagemente) {
    //LEEMOS EL NOMBRE Y TAMBIEN COMO SABEMOS Q NO USAREMOS LOS DATOS LONGLONG VARIAS VECES, LLAMAMOS COMO PARAMETRO AL
    // ENGAGAMENTE
    long long seguidorPorMes, visitasPorMes, maxEspectadores;
    char c;
    int contador = 0;
    imprimirLinea(archReporte, TAM_MAX, '=');
    archReporte << "CANAL No. " << numCompania << endl;
    imprimirEncabezadoCanales(archReporte);
    archReporte << setw(5) << " ";
    archDatos >> ws;

    while (true) {
        c = archDatos.get();
        if (c == ' ') break;
        contador++;
        if (c == '_') {
            c = ' ';
        }
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }
        archReporte.put(c);
    }
    archReporte << setw(15 - contador) << " " << codCanal << numCanal << setw(5) << " ";
    imprimirFecha(archReporte, ddC, mesC, anhioC);
    archDatos >> seguidorPorMes >> visitasPorMes >> maxEspectadores;
    archReporte << setw(14) << " " << setw(7) << seguidorPorMes << setw(20) << " " << setw(8) << visitasPorMes
            << setw(19) << " " << setw(8) << maxEspectadores << endl;
    engagemente=(double)(seguidorPorMes+((double)visitasPorMes/1000))/maxEspectadores;
}

void imprimirLinea(ofstream &archReporte, int cant, char c) {
    for (int i = 0; i < cant; i++) {
        archReporte.put(c);
    }
    archReporte << endl;
}

void imprimirEncabezadoCanales(ofstream &archReporte) {
    archReporte << setw(5) << " " << "NOMBRE" << setw(9) << " " << "CODIGO" << setw(4) << " " << "CREADO EL"
            << setw(5) << " " << "SEGUIDORES NUEVOS POR MES" << setw(5) << " "
            << "VISITAS NUEVAS POR MES" << setw(5) << " " << "MAXIMO DE ESPECTADORES" << endl;
}

void imprimirEncabezadoDatos(ofstream &archReporte) {
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << setw(7) << " " << "ULTIMAS REPRODUCCIONES" << endl;
    archReporte << setw(10) << " " << "FECHA DE PULICACION" << setw(7) << " " << "TIEMPO DE DURACION"
            << setw(7) << " " << "INGRESOS POR DURACION" << setw(7) << " " << "NUMERO DE REPRODUCCIONES" << endl;
}

void imprimirDatos(ofstream &archReporte, int dd, int mes, int anhio, int hh, int min, int ss,
                   double tarifaStream, int cantRepro, double &ingresosPorDuracion, int &horaEnSegundos) {
    //IMPRIMIMOS LOS DATOS
    double horaEnMinutos;
    archReporte << setw(10) << " ";
    imprimirFecha(archReporte, dd, mes, anhio);
    archReporte << setw(20) << " ";
    imprimirHora(archReporte, hh, min, ss);
    convertirHoraMinutos(hh, min, ss, horaEnMinutos, horaEnSegundos);
    ingresosPorDuracion = horaEnMinutos * tarifaStream;
    archReporte << right << setw(20) << " " << setw(5) << ingresosPorDuracion;
    archReporte << setw(24) << " " << setw(7) << cantRepro << endl;
}

void imprimirHora(ofstream &archReporte, int hh, int min, int ss) {
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) <<
            ss << setfill(' ');
}

void convertirHoraMinutos(int hh, int min, int ss, double &horaEnMinutos, int &horaEnSegundos) {
    horaEnSegundos = hh * 3600 + min * 60 + ss;
    horaEnMinutos = (double) (horaEnSegundos % 3600) / 60;
}

void imprimirResumenCanal(ofstream &archReporte, int totalSegundos, double totalIngresosDuracion, int totalCantRepro,
                          double tarifaRepro, double &ingresosPorPublicidad,double engagemente) {
    int hh,min,ss;
    hh=totalSegundos/3600;
    min=(totalSegundos%3600)/60;
    ss=(totalSegundos%60);
    imprimirLinea(archReporte, TAM_MAX, '-');
    archReporte << setw(8) << " " << "RESUMEN DEL CANAL:" << endl;
    archReporte << setw(8) << " " << "DURACION TOTAL DE LAS REPRODUCCIONES:"<<setw(10)<<" " ;
    imprimirHora(archReporte, hh, min, ss);
    archReporte<<endl;
    archReporte << setw(8) << " " << "INGRESOS POR DURACION:" <<setw(25)<<" "<<"$"<<
    setw(7)<<totalIngresosDuracion<< endl;
    archReporte << setw(8) << " " << "TOTAL DE REPRODUCCIONES:" <<setw(23)<<" "<<totalCantRepro<< endl;
    ingresosPorPublicidad=((double)totalCantRepro/1000)*tarifaRepro;
    archReporte << setw(8) << " " << "INGRESOS POR PUBLICIDAD:"<<setw(23)<<" " <<"$"<<
    setw(7)<<ingresosPorPublicidad<< endl;
    archReporte << setw(8) << " " << "ENGAGEMENT INDEX:" <<setw(30)<<" "<<
        setw(8)<<engagemente<< endl;
}

void imprimirResumenFinal(ofstream &archReporte,int cantStreams,int duracionFinal,double ingresosFinalesDuracion,
    double ingresosFinalesPublicidad) {
    int hh,min,ss;
    hh=duracionFinal/3600;
    min=(duracionFinal%3600)/60;
    ss=(duracionFinal%60);
    imprimirLinea(archReporte, TAM_MAX, '=');
    archReporte<<"RESUEMN FINAL:"<<endl;
    archReporte<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES:"<<setw(10)<<" "<<cantStreams<<endl;
    archReporte<<"DURACION TOTAL DE LOS STREAMS PUBLICADOS:"<<setw(14)<<" ";
    imprimirHora(archReporte, hh, min, ss);
    archReporte<<endl;
    archReporte<<"INGRESOS TOTALES POR DURACION:"<<setw(25)<<" "<<"$"<<
    setw(8)<<ingresosFinalesDuracion<<endl;
    archReporte<<"INGRESOS TOTALES POR PUBLICIDAD:"<<setw(23)<<" "<<"$"<<
    setw(8)<<ingresosFinalesPublicidad<<endl;
}