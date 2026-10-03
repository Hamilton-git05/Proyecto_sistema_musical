#pragma once
#include "Plan.h"
#include <string>

class PlanArchivo {
private:
    std::string _nombreArchivo;

public:
    PlanArchivo();

    bool Guardar(Plan plan);
    bool Guardar(Plan plan, int posicion);
    Plan Leer(int posicion);
    void Leer(int cantidadALeer, Plan *vec);
    int  getCantidadRegistros();
    int  Buscar(int id);
};
