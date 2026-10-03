#pragma once
#include "InformesManager.h"

class InformesMenu {
private:
    InformesManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
