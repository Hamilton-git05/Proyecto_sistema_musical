#include "PlanManager.h"
#include <iostream>
#include <string>
using namespace std;

void PlanManager::Mostrar(Plan plan) {
    cout << "ID: "          << plan.getId()          << endl;
    cout << "Descripcion: " << plan.getDescripcion() << endl;
    cout << "Precio: $"     << plan.getPrecio()      << "/mes" << endl;
    cout << endl;
}

// seleccion por precio mensual (ascendente)
void PlanManager::Ordenar(Plan *vec, int cantidad) {
    int i, j, pos;
    Plan aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getPrecio() < vec[pos].getPrecio()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

void PlanManager::Alta() {
    int    id = _repo.getCantidadRegistros() + 1;
    string descripcion;
    float  precio;

    // input
    cout << "ID: " << id << endl;

    cin.ignore();
    cout << "Descripcion: ";
    getline(cin, descripcion);

    cout << "Precio mensual: $";
    cin >> precio;

    Plan plan(id, descripcion, precio);

    char confirmar;
    cout << "Confirmar (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        _repo.Guardar(plan);
        cout << "Plan registrado con ID " << id << "." << endl;
    }
}

void PlanManager::Baja() {
    int id;
    cout << "ID del plan a dar de baja: ";
    cin >> id;

    int pos = _repo.Buscar(id);
    if (pos == -1) {
        cout << "Plan no encontrado." << endl;
        return;
    }

    Plan plan = _repo.Leer(pos);
    if (plan.getEliminado()) {
        cout << "El plan ya estaba dado de baja." << endl;
        return;
    }

    cout << "Plan: " << plan.getDescripcion()
         << " ($" << plan.getPrecio() << "/mes)" << endl;
    char confirmar;
    cout << "Confirmar baja (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        plan.setEliminado(true);
        _repo.Guardar(plan, pos);
        cout << "Plan dado de baja correctamente." << endl;
    }
}

void PlanManager::Modificar() {
    int id;
    cout << "ID del plan a modificar: ";
    cin >> id;

    int pos = _repo.Buscar(id);
    if (pos == -1) {
        cout << "Plan no encontrado." << endl;
        return;
    }

    Plan plan = _repo.Leer(pos);
    if (plan.getEliminado()) {
        cout << "El plan esta dado de baja." << endl;
        return;
    }

    cout << "Datos actuales:" << endl;
    Mostrar(plan);

    string descripcion;
    float  precio;

    // input
    cin.ignore();
    cout << "Nueva descripcion (" << plan.getDescripcion() << "): ";
    getline(cin, descripcion);

    cout << "Nuevo precio mensual (" << plan.getPrecio() << "): $";
    cin >> precio;

    // set valores
    plan.setDescripcion(descripcion);
    plan.setPrecio(precio);

    char confirmar;
    cout << "Confirmar cambios (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        _repo.Guardar(plan, pos);
        cout << "Plan modificado correctamente." << endl;
    }
}

void PlanManager::Listar() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay planes registrados." << endl;
        return;
    }

    Plan *vec = new Plan[cant];
    if (vec == nullptr) return;

    _repo.Leer(cant, vec);

    int activos = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) activos++;

    if (activos == 0) {
        cout << "No hay planes activos." << endl;
        delete[] vec;
        return;
    }

    Plan *actVec = new Plan[activos];
    int k = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) actVec[k++] = vec[i];

    Ordenar(actVec, activos);

    cout << "LISTA DE PLANES (por precio)" << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < activos; i++) {
        Mostrar(actVec[i]);
    }

    delete[] vec;
    delete[] actVec;
}

bool PlanManager::Buscar(int id, Plan &plan) {
    int pos = _repo.Buscar(id);
    if (pos == -1) return false;
    plan = _repo.Leer(pos);
    return !plan.getEliminado();
}
