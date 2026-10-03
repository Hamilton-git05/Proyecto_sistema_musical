#include "Cancion.h"
#include <cstring>
using namespace std;

Cancion::Cancion() {
    setId(0);
    setNombre("");
    setIdArtista(0);
    setIdGenero(0);
    setFechaPublicacion(Fecha());
    setDuracion(0);
    setEliminado(false);
}

Cancion::Cancion(int id, string nombre, int idArtista, int idGenero,
                 Fecha fechaPublicacion, int duracion) {
    setId(id);
    setNombre(nombre);
    setIdArtista(idArtista);
    setIdGenero(idGenero);
    setFechaPublicacion(fechaPublicacion);
    setDuracion(duracion);
    setEliminado(false);
}

int Cancion::getId() const {
    return _id;
}
string Cancion::getNombre() const {
    return string(_nombre);
}
int Cancion::getIdArtista() const {
    return _idArtista;
}
int Cancion::getIdGenero() const {
    return _idGenero;
}
Fecha Cancion::getFechaPublicacion() const {
    return _fechaPublicacion;
}
int Cancion::getDuracion() const {
    return _duracion;
}
bool Cancion::getEliminado() const {
    return _eliminado;
}

void Cancion::setId(int id) {
    _id = id;
}
void Cancion::setNombre(string nombre) {
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}
void Cancion::setIdArtista(int idArtista) {
    _idArtista = idArtista;
}
void Cancion::setIdGenero(int idGenero) {
    _idGenero = idGenero;
}
void Cancion::setFechaPublicacion(Fecha fechaPublicacion) {
    _fechaPublicacion = fechaPublicacion;
}
void Cancion::setDuracion(int duracion) {
    _duracion = duracion;
}
void Cancion::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
