#include "ArtistaManager.h"
#include <iostream>
#include <string>
using namespace std;

void ArtistaManager::Mostrar(Artista artista) {
    cout << "ID: "     << artista.getId()     << endl;
    cout << "Nombre: " << artista.getNombre() << endl;
    cout << "Pais: "   << artista.getPais()   << endl;
    cout << endl;
}

// seleccion alfabetico por nombre
void ArtistaManager::OrdenarPorNombre(Artista *vec, int cantidad) {
    int i, j, pos;
    Artista aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getNombre() < vec[pos].getNombre()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// seleccion alfabetico por pais
void ArtistaManager::OrdenarPorPais(Artista *vec, int cantidad) {
    int i, j, pos;
    Artista aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getPais() < vec[pos].getPais()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

void ArtistaManager::ListarPorNombre() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay artistas registrados." << endl;
        return;
    }

    Artista *vec = new Artista[cant];
    if (vec == nullptr) return;

    _repo.Leer(cant, vec);
    OrdenarPorNombre(vec, cant);

    cout << "ARTISTAS (por nombre)" << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < cant; i++) {
        if (!vec[i].getEliminado()) Mostrar(vec[i]);
    }

    delete[] vec;
}

void ArtistaManager::ListarPorPais() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay artistas registrados." << endl;
        return;
    }

    Artista *vec = new Artista[cant];
    if (vec == nullptr) return;

    _repo.Leer(cant, vec);
    OrdenarPorPais(vec, cant);

    cout << "ARTISTAS (por pais)" << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < cant; i++) {
        if (!vec[i].getEliminado()) Mostrar(vec[i]);
    }

    delete[] vec;
}

void ArtistaManager::ConsultarPorId() {
    int id;
    cout << "ID del artista: ";
    cin >> id;

    int pos = _repo.Buscar(id);
    if (pos == -1) {
        cout << "Artista no encontrado." << endl;
        return;
    }

    Artista a = _repo.Leer(pos);
    if (a.getEliminado()) {
        cout << "El artista esta dado de baja." << endl;
        return;
    }
    Mostrar(a);
}

// busca un artista activo por id (usado para validar/mostrar FK desde otras capas)
bool ArtistaManager::Buscar(int id, Artista &artista) {
    int pos = _repo.Buscar(id);
    if (pos == -1) return false;
    artista = _repo.Leer(pos);
    return !artista.getEliminado();
}
