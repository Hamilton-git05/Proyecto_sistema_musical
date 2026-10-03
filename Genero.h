#pragma once
#include <string>

class Genero {
private:
    int  _id;
    char _descripcion[30];
    bool _eliminado;

public:
    Genero();
    Genero(int id, std::string descripcion);

    int         getId()          const;
    std::string getDescripcion() const;
    bool        getEliminado()   const;

    void setId(int id);
    void setDescripcion(std::string descripcion);
    void setEliminado(bool eliminado);
};
