#include "AccesoMenu.h"
#include <iostream>
using namespace std;

void AccesoMenu::mostrarOpciones() {
    cout << "\n===== ACCESOS =====" << endl;
    cout << "1 - Registrar acceso" << endl;
    cout << "2 - Consultar por rango de fechas" << endl;
    cout << "3 - Consultar por suscriptor" << endl;
    cout << "4 - Consultar por cancion" << endl;
    cout << "5 - Consultar por artista" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void AccesoMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.Registrar();              break;
            case 2: _manager.ConsultarPorRangoFechas();break;
            case 3: _manager.ConsultarPorSuscriptor(); break;
            case 4: _manager.ConsultarPorCancion();    break;
            case 5: _manager.ConsultarPorArtista();    break;
            case 0:                                   break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
