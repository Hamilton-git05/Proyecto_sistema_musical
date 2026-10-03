#include "GeneroArchivo.h"
#include <cstdio>
using namespace std;

GeneroArchivo::GeneroArchivo() {
    _nombreArchivo = "generos.dat";
}

// Guarda al final (alta)
bool GeneroArchivo::Guardar(Genero genero) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&genero, sizeof(Genero), 1, p);
    fclose(p);
    return escribio;
}

// Sobreescribe (usado en baja/modificacion)
bool GeneroArchivo::Guardar(Genero genero, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "r+b");
    if (p == NULL) return false;
    fseek(p, posicion * sizeof(Genero), SEEK_SET);
    bool escribio = fwrite(&genero, sizeof(Genero), 1, p);
    fclose(p);
    return escribio;
}

Genero GeneroArchivo::Leer(int posicion) {
    Genero aux;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Genero), SEEK_SET);
    fread(&aux, sizeof(Genero), 1, p);
    fclose(p);
    return aux;
}

void GeneroArchivo::Leer(int cantidadALeer, Genero *vec) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Genero), cantidadALeer, p);
    fclose(p);
}

int GeneroArchivo::getCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Genero);
}

// Devuelve la posicion del registro con ese id, -1 si no existe
int GeneroArchivo::Buscar(int id) {
    int cant = getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Genero g = Leer(i);
        if (g.getId() == id) return i;
    }
    return -1;
}
