#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;
#include "Bibliotecas/funciones.h"

#include "Bibliotecas/Palabra.h"
#include "Bibliotecas/Comentario.h"
#include "Bibliotecas/Plato.h"
#include "Bibliotecas/Atencion.h"

int main() {
    struct Palabra lexicon[100]{};
    int cantLexicon = 0;
    leerLexicon("ArchivosDeDatos/lexicon.csv", lexicon, cantLexicon);

    struct Plato *platos;
    platos = new struct Plato[200]{};
    int cantPlatos = 0;
    leerPlatos("ArchivosDeDatos/platos.csv", platos, cantPlatos);

    struct Atencion atenciones[100]{};
    int cantAtenciones = 0;
    leerAtenciones("ArchivosDeDatos/atenciones.txt", atenciones, cantAtenciones, platos, cantPlatos);

    leerComentarios("ArchivosDeDatos/comentarios.csv", atenciones, cantAtenciones, lexicon, cantLexicon);

    imprimirReporte("ArchivosDeReporte/ReporteAtencionesAnalisisSentimiento.txt", atenciones, cantAtenciones);

    return 0;
}
