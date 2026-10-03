#include "Artista.h"
#include <cstring>
using namespace std;

Artista::Artista() {
    setId(0);
    setNombre("");
    setPais("");
    setEliminado(false);
}

Artista::Artista(int id, string nombre, string pais) {
    setId(id);
    setNombre(nombre);
    setPais(pais);
    setEliminado(false);
}

int Artista::getId() const {
    return _id;
}
string Artista::getNombre() const {
    return string(_nombre);
}
string Artista::getPais() const {
    return string(_pais);
}
bool Artista::getEliminado() const {
    return _eliminado;
}

void Artista::setId(int id) {
    _id = id;
}
void Artista::setNombre(string nombre) {
    strncpy(_nombre, nombre.c_str(), 39);
    _nombre[39] = '\0';
}
void Artista::setPais(string pais) {
    strncpy(_pais, pais.c_str(), 29);
    _pais[29] = '\0';
}
void Artista::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
