#pragma once
#include <string>
#include "Fecha.h"

class Cancion {
private:
    int   _id;
    char  _nombre[50];
    int   _idArtista;          // FK -> Artista
    int   _idGenero;           // FK -> Genero
    Fecha _fechaPublicacion;   // composicion: la cancion "tiene una" Fecha
    int   _duracion;           // en segundos
    bool  _eliminado;

public:
    Cancion();
    Cancion(int id, std::string nombre, int idArtista, int idGenero,
            Fecha fechaPublicacion, int duracion);

    int         getId()               const;
    std::string getNombre()           const;
    int         getIdArtista()        const;
    int         getIdGenero()         const;
    Fecha       getFechaPublicacion() const;
    int         getDuracion()         const;
    bool        getEliminado()        const;

    void setId(int id);
    void setNombre(std::string nombre);
    void setIdArtista(int idArtista);
    void setIdGenero(int idGenero);
    void setFechaPublicacion(Fecha fechaPublicacion);
    void setDuracion(int duracion);
    void setEliminado(bool eliminado);
};
