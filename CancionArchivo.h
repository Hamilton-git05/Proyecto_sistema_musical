#pragma once
#include "Cancion.h"
#include <string>

class CancionArchivo {
private:
    std::string _nombreArchivo;

public:
    CancionArchivo();

    bool    Guardar(Cancion cancion);
    bool    Guardar(Cancion cancion, int posicion);
    Cancion Leer(int posicion);
    void    Leer(int cantidadALeer, Cancion *vec);
    int     getCantidadRegistros();
    int     Buscar(int id);
};
