#include "GeneroMenu.h"
#include <iostream>
using namespace std;

void GeneroMenu::ejecutar() {
    cout << "\n===== GENEROS =====" << endl;
    _manager.Listar();
}
