#include "AccesoArchivo.h"
#include <cstdio>
using namespace std;

AccesoArchivo::AccesoArchivo() {
    _nombreArchivo = "accesos.dat";
}

// Guarda al final (registro de acceso)
bool AccesoArchivo::Guardar(Acceso acceso) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&acceso, sizeof(Acceso), 1, p);
    fclose(p);
    return escribio;
}

Acceso AccesoArchivo::Leer(int posicion) {
    Acceso aux;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Acceso), SEEK_SET);
    fread(&aux, sizeof(Acceso), 1, p);
    fclose(p);
    return aux;
}

void AccesoArchivo::Leer(int cantidadALeer, Acceso *vec) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Acceso), cantidadALeer, p);
    fclose(p);
}

int AccesoArchivo::getCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Acceso);
}
