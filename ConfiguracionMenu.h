#pragma once
#include "ConfiguracionManager.h"

class ConfiguracionMenu {
private:
    ConfiguracionManager _manager;

    void mostrarOpciones();

public:
    void ejecutar();
};
