#pragma once
#include "Fecha.h"

class Acceso {
private:
    int   _idCancion;       // FK -> Cancion
    int   _idSuscriptor;    // FK -> Suscriptor
    Fecha _fecha;           // composicion: el acceso "tiene una" Fecha
    bool  _eliminado;

public:
    Acceso();
    Acceso(int idCancion, int idSuscriptor, Fecha fecha);

    int   getIdCancion()    const;
    int   getIdSuscriptor() const;
    Fecha getFecha()        const;
    bool  getEliminado()    const;

    void setIdCancion(int idCancion);
    void setIdSuscriptor(int idSuscriptor);
    void setFecha(Fecha fecha);
    void setEliminado(bool eliminado);
};
