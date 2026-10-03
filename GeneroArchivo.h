#pragma once
#include "Genero.h"
#include <string>

class GeneroArchivo {
private:
    std::string _nombreArchivo;

public:
    GeneroArchivo();

    bool   Guardar(Genero genero);
    bool   Guardar(Genero genero, int posicion);
    Genero Leer(int posicion);
    void   Leer(int cantidadALeer, Genero *vec);
    int    getCantidadRegistros();
    int    Buscar(int id);
};
