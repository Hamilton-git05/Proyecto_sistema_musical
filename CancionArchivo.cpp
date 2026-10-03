#include "CancionArchivo.h"
#include <cstdio>
using namespace std;

CancionArchivo::CancionArchivo() {
    _nombreArchivo = "canciones.dat";
}

// Guarda al final (alta / carga inicial)
bool CancionArchivo::Guardar(Cancion cancion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&cancion, sizeof(Cancion), 1, p);
    fclose(p);
    return escribio;
}

// Sobreescribe (usado en baja/modificacion)
bool CancionArchivo::Guardar(Cancion cancion, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "r+b");
    if (p == NULL) return false;
    fseek(p, posicion * sizeof(Cancion), SEEK_SET);
    bool escribio = fwrite(&cancion, sizeof(Cancion), 1, p);
    fclose(p);
    return escribio;
}

Cancion CancionArchivo::Leer(int posicion) {
    Cancion aux;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Cancion), SEEK_SET);
    fread(&aux, sizeof(Cancion), 1, p);
    fclose(p);
    return aux;
}

void CancionArchivo::Leer(int cantidadALeer, Cancion *vec) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Cancion), cantidadALeer, p);
    fclose(p);
}

int CancionArchivo::getCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Cancion);
}

// Devuelve la posicion del registro con ese id, -1 si no existe
int CancionArchivo::Buscar(int id) {
    int cant = getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Cancion c = Leer(i);
        if (c.getId() == id) return i;
    }
    return -1;
}
