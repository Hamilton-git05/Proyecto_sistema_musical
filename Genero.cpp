#include "Genero.h"
#include <cstring>
using namespace std;

Genero::Genero() {
    setId(0);
    setDescripcion("");
    setEliminado(false);
}

Genero::Genero(int id, string descripcion) {
    setId(id);
    setDescripcion(descripcion);
    setEliminado(false);
}

int Genero::getId() const {
    return _id;
}
string Genero::getDescripcion() const {
    return string(_descripcion);
}
bool Genero::getEliminado() const {
    return _eliminado;
}

void Genero::setId(int id) {
    _id = id;
}
void Genero::setDescripcion(string descripcion) {
    strncpy(_descripcion, descripcion.c_str(), 29);
    _descripcion[29] = '\0';
}
void Genero::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
