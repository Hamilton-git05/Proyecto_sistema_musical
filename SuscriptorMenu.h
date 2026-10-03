#pragma once
#include "SuscriptorManager.h"

class SuscriptorMenu {
private:
    SuscriptorManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
