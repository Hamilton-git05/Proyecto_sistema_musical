#include "InformesMenu.h"
#include <iostream>
using namespace std;

void InformesMenu::mostrarOpciones() {
    cout << "\n===== INFORMES =====" << endl;
    cout << "1 - Recaudacion anual por plan" << endl;
    cout << "2 - Recaudacion por suscriptor" << endl;
    cout << "3 - Canciones mas reproducidas" << endl;
    cout << "4 - Accesos por genero" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void InformesMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.RecaudacionAnualPorPlan();   break;
            case 2: _manager.RecaudacionPorSuscriptor();  break;
            case 3: _manager.CancionesMasReproducidas();  break;
            case 4: _manager.AccesosPorGenero();          break;
            case 0:                                      break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
