#pragma once
#include "ArtistaArchivo.h"

// Catalogo de solo lectura: se pre-carga por script, no se da de alta/baja por menu.
class ArtistaManager {
private:
    ArtistaArchivo _repo;

    void Mostrar(Artista artista);
    void OrdenarPorNombre(Artista *vec, int cantidad);
    void OrdenarPorPais(Artista *vec, int cantidad);

public:
    void ListarPorNombre();
    void ListarPorPais();
    void ConsultarPorId();
    bool Buscar(int id, Artista &artista);
};
