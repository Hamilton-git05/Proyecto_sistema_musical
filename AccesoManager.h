#pragma once
#include "AccesoArchivo.h"
#include "CancionArchivo.h"
#include "SuscriptorArchivo.h"
#include "ArtistaArchivo.h"

class AccesoManager {
private:
    AccesoArchivo     _repo;
    CancionArchivo    _repoCancion;     // validar cancion (FK) y mostrar su nombre
    SuscriptorArchivo _repoSuscriptor;  // validar suscriptor (FK) y mostrar su nombre
    ArtistaArchivo    _repoArtista;     // resolver artista en consulta por artista

public:
    void Registrar();
    void ConsultarPorRangoFechas();
    void ConsultarPorSuscriptor();
    void ConsultarPorCancion();
    void ConsultarPorArtista();
};
