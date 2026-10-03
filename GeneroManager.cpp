#include "GeneroManager.h"
#include <iostream>
#include <string>
using namespace std;

void GeneroManager::Mostrar(Genero genero) {
    cout << "ID: "          << genero.getId()          << endl;
    cout << "Descripcion: " << genero.getDescripcion() << endl;
    cout << endl;
}

// seleccion alfabetico por descripcion
void GeneroManager::Ordenar(Genero *vec, int cantidad) {
    int i, j, pos;
    Genero aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getDescripcion() < vec[pos].getDescripcion()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

void GeneroManager::Listar() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay generos registrados." << endl;
        return;
    }

    Genero *vec = new Genero[cant];
    if (vec == nullptr) return;

    _repo.Leer(cant, vec);

    // get activos
    int activos = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) activos++;

    if (activos == 0) {
        cout << "No hay generos activos." << endl;
        delete[] vec;
        return;
    }

    // get NO eliminados
    Genero *actVec = new Genero[activos];
    int k = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) actVec[k++] = vec[i];

    Ordenar(actVec, activos);

    cout << "LISTA DE GENEROS" << endl;
    cout << "----------------" << endl;
    for (int i = 0; i < activos; i++) {
        Mostrar(actVec[i]);
    }

    delete[] vec;
    delete[] actVec;
}

// busca un genero activo por id (usado para validar FK desde otras capas)
bool GeneroManager::Buscar(int id, Genero &genero) {
    int pos = _repo.Buscar(id);
    if (pos == -1) return false;
    genero = _repo.Leer(pos);
    return !genero.getEliminado();
}
