#include "SuscriptorArchivo.h"

#include <cstdio>
using namespace std;

SuscriptorArchivo::SuscriptorArchivo() {
    _nombreArchivo = "suscriptores.dat";
}

/*
SuscriptorArchivo::SuscriptorArchivo(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}
*/

// Guarda al final (alta)
bool SuscriptorArchivo::Guardar(Suscriptor suscriptor) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&suscriptor, sizeof(Suscriptor), 1, p);
    fclose(p);
    return escribio;
}

// Sobreescribe (usado en modificacion)
bool SuscriptorArchivo::Guardar(Suscriptor suscriptor, int posicion) {
    FILE* p = fopen(_nombreArchivo.c_str(), "r+b");
    if (p == NULL) return false;
    fseek(p, posicion * sizeof(Suscriptor), SEEK_SET);
    bool escribio = fwrite(&suscriptor, sizeof(Suscriptor), 1, p);
    fclose(p);
    return escribio;
}

Suscriptor SuscriptorArchivo::Leer(int posicion) {
    Suscriptor aux;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Suscriptor), SEEK_SET);
    fread(&aux, sizeof(Suscriptor), 1, p);
    fclose(p);
    return aux;
}

void SuscriptorArchivo::Leer(int cantidadALeer, Suscriptor* vec) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Suscriptor), cantidadALeer, p);
    fclose(p);
}

int SuscriptorArchivo::getCantidadRegistros() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Suscriptor);
}

int SuscriptorArchivo::Buscar(int id) {
    int cant = getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Suscriptor s = Leer(i);
        if (s.getId() == id) return i;
    }
    return -1;
}
