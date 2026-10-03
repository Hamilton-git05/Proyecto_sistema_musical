#include "App.h"

#include <iostream>
using namespace std;

// Menu -> manager -> archivo

void App::mostrarOpciones() {
    cout << "\n==============================" << endl;
    cout << "  GESTION DE MUSICA" << endl;
    cout << "==============================" << endl;
    cout << "1 - Suscriptores" << endl;
    cout << "2 - Planes" << endl;
    cout << "3 - Canciones" << endl;
    cout << "4 - Artistas" << endl;
    cout << "5 - Generos" << endl;
    cout << "6 - Accesos" << endl;
    cout << "7 - Informes" << endl;
    cout << "8 - Configuracion" << endl;
    cout << "0 - Salir" << endl;
    cout << "Opcion: ";
}

void App::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1:
                _suscriptorMenu.ejecutar();
                break;
            case 2:
                _planMenu.ejecutar();
                break;
            case 3:
                _cancionMenu.ejecutar();
                break;
            case 4:
                _artistaMenu.ejecutar();
                break;
            case 5:
                _generoMenu.ejecutar();
                break;
            case 6:
                _accesoMenu.ejecutar();
                break;
            case 7:
                _informesMenu.ejecutar();
                break;
            case 8:
                _configuracionMenu.ejecutar();
                break;
            case 0:
                cout << "Hasta luego." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}
