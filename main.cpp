#include "DatosPrueba.h"
#include "App.h"

int main() {
    DatosPrueba datos;
    datos.Cargar();

    App app;
    app.ejecutar();

    return 0;
}
