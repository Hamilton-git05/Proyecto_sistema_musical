#pragma once
#include <string>

class Plan {
private:
    int   _id;
    char  _descripcion[30];
    float _precio;
    bool  _eliminado;

public:
    Plan();
    Plan(int id, std::string descripcion, float precio);

    int         getId()          const;
    std::string getDescripcion() const;
    float       getPrecio()      const;
    bool        getEliminado()   const;

    void setId(int id);
    void setDescripcion(std::string descripcion);
    void setPrecio(float precio);
    void setEliminado(bool eliminado);
};
