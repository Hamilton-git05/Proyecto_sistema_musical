#include "ConfiguracionMenu.h"
#include <iostream>
using namespace std;

void ConfiguracionMenu::mostrarOpciones() {
    cout << "\n===== CONFIGURACION =====" << endl;
    cout << "1 - Realizar copia de seguridad" << endl;
    cout << "2 - Restaurar copia de seguridad" << endl;
    cout << "3 - Exportar datos (CSV)" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void ConfiguracionMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.RealizarBackup();   break;
            case 2: _manager.RestaurarBackup();  break;
            case 3: _manager.ExportarCSV();      break;
            case 0:                             break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
