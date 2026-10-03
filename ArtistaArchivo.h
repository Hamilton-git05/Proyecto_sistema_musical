#pragma once
#include "Artista.h"
#include <string>

class ArtistaArchivo {
private:
    std::string _nombreArchivo;

public:
    ArtistaArchivo();

    bool    Guardar(Artista artista);
    bool    Guardar(Artista artista, int posicion);
    Artista Leer(int posicion);
    void    Leer(int cantidadALeer, Artista *vec);
    int     getCantidadRegistros();
    int     Buscar(int id);
};
