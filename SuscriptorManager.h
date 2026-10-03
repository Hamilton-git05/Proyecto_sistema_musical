#pragma once
#include "SuscriptorArchivo.h"
#include "PlanArchivo.h"
#include "GeneroArchivo.h"

class SuscriptorManager {
private:
    SuscriptorArchivo _repo;
    PlanArchivo       _repoPlan;     // validar plan (FK)
    GeneroArchivo     _repoGenero;   // validar genero de preferencia (FK)

    void Mostrar(Suscriptor suscriptor);
    void OrdenarPorApellido(Suscriptor *vec, int cantidad);
    void OrdenarPorEdad(Suscriptor *vec, int cantidad);
    int  Edad(Fecha fechaNacimiento);   // calcula la edad a partir de la fecha de nac.

public:
    void Alta();
    void Baja();
    void Modificar();
    void ListarPorApellido();
    void ListarPorEdad();
    void ConsultarPorDNI();
    void ConsultarPorRangoEdad();
    void ConsultarPorGenero();
    void ConsultarPorPlan();
};
