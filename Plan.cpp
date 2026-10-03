#include "Plan.h"
#include <cstring>
using namespace std;

Plan::Plan() {
    _id = 0;
    _descripcion[0] = '\0';
    _precio = 0.0f;
    _eliminado = false;
}

Plan::Plan(int id, string descripcion, float precio) {
    _id = id;
    strncpy(_descripcion, descripcion.c_str(), 29);
    _descripcion[29] = '\0';
    _precio = precio;
    _eliminado = false;
}

int Plan::getId() const {
    return _id;
}
string Plan::getDescripcion() const {
    return string(_descripcion);
}
float Plan::getPrecio() const {
    return _precio;
}
bool Plan::getEliminado() const {
    return _eliminado;
}

void Plan::setId(int id) {
    _id = id;
}
void Plan::setDescripcion(string descripcion) {
    strncpy(_descripcion, descripcion.c_str(), 29);
    _descripcion[29] = '\0';
}
void Plan::setPrecio(float precio) {
    _precio = precio;
}
void Plan::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
