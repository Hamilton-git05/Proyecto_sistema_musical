#pragma once
#include "Acceso.h"
#include <string>

// Es un log: solo se agrega al final (append-only). No tiene baja ni modificacion.
class AccesoArchivo {
private:
    std::string _nombreArchivo;

public:
    AccesoArchivo();

    bool   Guardar(Acceso acceso);
    Acceso Leer(int posicion);
    void   Leer(int cantidadALeer, Acceso *vec);
    int    getCantidadRegistros();
};
