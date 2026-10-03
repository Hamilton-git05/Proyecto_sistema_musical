#pragma once
#include "GeneroManager.h"

// Catalogo de solo lectura: ejecutar() simplemente muestra el listado.
class GeneroMenu {
private:
    GeneroManager _manager;

public:
    void ejecutar();
};
