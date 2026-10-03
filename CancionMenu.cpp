#include "CancionMenu.h"
#include <iostream>
using namespace std;

void CancionMenu::mostrarOpciones() {
    cout << "\n===== CANCIONES =====" << endl;
    cout << "1 - Listar por nombre" << endl;
    cout << "2 - Listar por fecha" << endl;
    cout << "3 - Listar por duracion" << endl;
    cout << "4 - Listar por artista" << endl;
    cout << "5 - Consultar por genero" << endl;
    cout << "6 - Consultar por artista" << endl;
    cout << "7 - Consultar por rango de duracion" << endl;
    cout << "8 - Consultar por fecha" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void CancionMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.ListarPorNombre();          break;
            case 2: _manager.ListarPorFecha();           break;
            case 3: _manager.ListarPorDuracion();        break;
            case 4: _manager.ListarPorArtista();         break;
            case 5: _manager.ConsultarPorGenero();       break;
            case 6: _manager.ConsultarPorArtista();      break;
            case 7: _manager.ConsultarPorRangoDuracion();break;
            case 8: _manager.ConsultarPorFecha();        break;
            case 0:                                     break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
