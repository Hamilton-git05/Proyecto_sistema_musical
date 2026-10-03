#pragma once
#include "GeneroArchivo.h"

// Catalogo de solo lectura: se pre-carga por script, no se da de alta/baja por menu.
class GeneroManager {
private:
    GeneroArchivo _repo;

    void Mostrar(Genero genero);
    void Ordenar(Genero *vec, int cantidad);

public:
    void Listar();
    bool Buscar(int id, Genero &genero);
};
