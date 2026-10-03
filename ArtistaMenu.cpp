#include "ArtistaMenu.h"
#include <iostream>
using namespace std;

void ArtistaMenu::mostrarOpciones() {
    cout << "\n===== ARTISTAS =====" << endl;
    cout << "1 - Listar por nombre" << endl;
    cout << "2 - Listar por pais" << endl;
    cout << "3 - Consultar por ID" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";
}

void ArtistaMenu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;
        switch (opcion) {
            case 1: _manager.ListarPorNombre(); break;
            case 2: _manager.ListarPorPais();   break;
            case 3: _manager.ConsultarPorId();  break;
            case 0:                            break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
