#pragma once
#include <string>

class Artista {
private:
    int  _id;
    char _nombre[40];
    char _pais[30];
    bool _eliminado;

public:
    Artista();
    Artista(int id, std::string nombre, std::string pais);

    int         getId()        const;
    std::string getNombre()    const;
    std::string getPais()      const;
    bool        getEliminado() const;

    void setId(int id);
    void setNombre(std::string nombre);
    void setPais(std::string pais);
    void setEliminado(bool eliminado);
};
