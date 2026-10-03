#include "SuscriptorMenu.h"
#include <iostream>
using namespace std;

void SuscriptorMenu::mostrarOpciones() {
    cout << "\n===== SUSCRIPTORES =====" << endl;
    cout << "1 - Alta" << endl;
    cout << "2 - Baja" << endl;
    cout << "3 - Modificar" << endl;
    cout << "4 - Listar por apellido" << endl;
    cout << "5 - Listar por edad" << endl;
    cout << "6 - Consultar por DNI" << endl;
    cout << "7 - Consultar por rango de edad" << endl;
    cout << "8 - Consultar por genero" << endl;
    cout << "9 - Consultar por plan" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void SuscriptorMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.Alta();                  break;
            case 2: _manager.Baja();                  break;
            case 3: _manager.Modificar();             break;
            case 4: _manager.ListarPorApellido();     break;
            case 5: _manager.ListarPorEdad();         break;
            case 6: _manager.ConsultarPorDNI();       break;
            case 7: _manager.ConsultarPorRangoEdad(); break;
            case 8: _manager.ConsultarPorGenero();    break;
            case 9: _manager.ConsultarPorPlan();      break;
            case 0:                                  break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
