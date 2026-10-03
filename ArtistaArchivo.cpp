#include "ArtistaArchivo.h"
#include <cstdio>
using namespace std;

ArtistaArchivo::ArtistaArchivo() {
    _nombreArchivo = "artistas.dat";
}

// Guarda al final (alta)
bool ArtistaArchivo::Guardar(Artista artista) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&artista, sizeof(Artista), 1, p);
    fclose(p);
    return escribio;
}

// Sobreescribe (usado en baja/modificacion)
bool ArtistaArchivo::Guardar(Artista artista, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "r+b");
    if (p == NULL) return false;
    fseek(p, posicion * sizeof(Artista), SEEK_SET);
    bool escribio = fwrite(&artista, sizeof(Artista), 1, p);
    fclose(p);
    return escribio;
}

Artista ArtistaArchivo::Leer(int posicion) {
    Artista aux;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Artista), SEEK_SET);
    fread(&aux, sizeof(Artista), 1, p);
    fclose(p);
    return aux;
}

void ArtistaArchivo::Leer(int cantidadALeer, Artista *vec) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Artista), cantidadALeer, p);
    fclose(p);
}

int ArtistaArchivo::getCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Artista);
}

// Devuelve la posicion del registro con ese id, -1 si no existe
int ArtistaArchivo::Buscar(int id) {
    int cant = getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Artista a = Leer(i);
        if (a.getId() == id) return i;
    }
    return -1;
}
