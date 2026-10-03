#include "PlanArchivo.h"
#include <cstdio>
using namespace std;

PlanArchivo::PlanArchivo() {
    _nombreArchivo = "planes.dat";
}

bool PlanArchivo::Guardar(Plan plan) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&plan, sizeof(Plan), 1, p);
    fclose(p);
    return escribio;
}

bool PlanArchivo::Guardar(Plan plan, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "r+b");
    if (p == NULL) return false;
    fseek(p, posicion * sizeof(Plan), SEEK_SET);
    bool escribio = fwrite(&plan, sizeof(Plan), 1, p);
    fclose(p);
    return escribio;
}

Plan PlanArchivo::Leer(int posicion) {
    Plan aux;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return aux;
    fseek(p, posicion * sizeof(Plan), SEEK_SET);
    fread(&aux, sizeof(Plan), 1, p);
    fclose(p);
    return aux;
}

void PlanArchivo::Leer(int cantidadALeer, Plan *vec) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vec, sizeof(Plan), cantidadALeer, p);
    fclose(p);
}

int PlanArchivo::getCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Plan);
}

int PlanArchivo::Buscar(int id) {
    int cant = getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Plan plan = Leer(i);
        if (plan.getId() == id) return i;
    }
    return -1;
}
