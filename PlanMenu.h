#pragma once
#include "PlanManager.h"

class PlanMenu {
private:
    PlanManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
