#pragma once
#include "CancionManager.h"

class CancionMenu {
private:
    CancionManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
