#pragma once
#include "PlanArchivo.h"

class PlanManager {
private:
    PlanArchivo _repo;

    void Mostrar(Plan plan);
    void Ordenar(Plan *vec, int cantidad);

public:
    void Alta();
    void Baja();
    void Modificar();
    void Listar();
    bool Buscar(int id, Plan &plan);
};
