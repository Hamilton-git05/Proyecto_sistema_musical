#pragma once
#include "SuscriptorMenu.h"
#include "PlanMenu.h"
#include "CancionMenu.h"
#include "ArtistaMenu.h"
#include "GeneroMenu.h"
#include "AccesoMenu.h"
#include "InformesMenu.h"
#include "ConfiguracionMenu.h"

class App {
private:
    SuscriptorMenu    _suscriptorMenu;
    PlanMenu          _planMenu;
    CancionMenu       _cancionMenu;
    ArtistaMenu       _artistaMenu;
    GeneroMenu        _generoMenu;
    AccesoMenu        _accesoMenu;
    InformesMenu      _informesMenu;
    ConfiguracionMenu _configuracionMenu;

    void mostrarOpciones();

public:
    void ejecutar();
};
