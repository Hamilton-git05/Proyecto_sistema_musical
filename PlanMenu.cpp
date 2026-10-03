#include "PlanMenu.h"
#include <iostream>
using namespace std;

void PlanMenu::mostrarOpciones() {
    cout << "\n===== PLANES =====" << endl;
    cout << "1 - Alta" << endl;
    cout << "2 - Baja" << endl;
    cout << "3 - Modificar" << endl;
    cout << "4 - Listar" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void PlanMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.Alta();      break;
            case 2: _manager.Baja();      break;
            case 3: _manager.Modificar(); break;
            case 4: _manager.Listar();    break;
            case 0:                      break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
