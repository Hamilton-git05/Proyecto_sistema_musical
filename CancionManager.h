#pragma once
#include "CancionArchivo.h"
#include "ArtistaArchivo.h"
#include "GeneroArchivo.h"

class CancionManager {
private:
    CancionArchivo _repo;
    ArtistaArchivo _repoArtista;   // resolver nombre del artista (FK)
    GeneroArchivo  _repoGenero;    // resolver descripcion del genero (FK)

    void Mostrar(Cancion cancion);
    void OrdenarPorNombre(Cancion *vec, int cantidad);
    void OrdenarPorFecha(Cancion *vec, int cantidad);
    void OrdenarPorDuracion(Cancion *vec, int cantidad);
    void OrdenarPorArtista(Cancion *vec, int cantidad);

public:
    void ListarPorNombre();
    void ListarPorFecha();
    void ListarPorDuracion();
    void ListarPorArtista();
    void ConsultarPorGenero();
    void ConsultarPorArtista();
    void ConsultarPorRangoDuracion();
    void ConsultarPorFecha();
    bool Buscar(int id, Cancion &cancion);
};
