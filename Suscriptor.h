#pragma once
#include <string>
#include "Fecha.h"

class Suscriptor {
private:
    int   _id;
    int   _dni;
    char  _nombre[30];
    char  _apellido[30];
    char  _telefono[20];
    char  _email[50];
    Fecha _fechaNacimiento;   // composicion: el suscriptor "tiene una" Fecha
    int   _idPlan;            // FK -> Plan
    int   _idGenero;          // FK -> Genero (0 = sin preferencia)
    bool  _eliminado;

public:
    Suscriptor();
    Suscriptor(int id, int dni, std::string nombre, std::string apellido,
               std::string telefono, std::string email, Fecha fechaNacimiento,
               int idPlan, int idGenero);

    int         getId()              const;
    int         getDni()             const;
    std::string getNombre()          const;
    std::string getApellido()        const;
    std::string getTelefono()        const;
    std::string getEmail()           const;
    Fecha       getFechaNacimiento() const;
    int         getIdPlan()          const;
    int         getIdGenero()        const;
    bool        getEliminado()       const;

    void setId(int id);
    void setDni(int dni);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setTelefono(std::string telefono);
    void setEmail(std::string email);
    void setFechaNacimiento(Fecha fechaNacimiento);
    void setIdPlan(int idPlan);
    void setIdGenero(int idGenero);
    void setEliminado(bool eliminado);
};
