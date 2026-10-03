#pragma once
#include "AccesoManager.h"

class AccesoMenu {
private:
    AccesoManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
