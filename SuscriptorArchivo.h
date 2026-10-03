#pragma once
#include "Suscriptor.h"
#include <string>

class SuscriptorArchivo {
private:
    std::string _nombreArchivo;

public:
    SuscriptorArchivo();
    SuscriptorArchivo(std::string nombreArchivo);

    bool       Guardar(Suscriptor suscriptor);
    bool       Guardar(Suscriptor suscriptor, int posicion);
    Suscriptor Leer(int posicion);
    void       Leer(int cantidadALeer, Suscriptor *vec);
    int        getCantidadRegistros();
    int        Buscar(int id);
};
