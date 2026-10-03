#include "Acceso.h"
using namespace std;

Acceso::Acceso() {
    setIdCancion(0);
    setIdSuscriptor(0);
    setFecha(Fecha());
    setEliminado(false);
}

Acceso::Acceso(int idCancion, int idSuscriptor, Fecha fecha) {
    setIdCancion(idCancion);
    setIdSuscriptor(idSuscriptor);
    setFecha(fecha);
    setEliminado(false);
}

int Acceso::getIdCancion() const {
    return _idCancion;
}
int Acceso::getIdSuscriptor() const {
    return _idSuscriptor;
}
Fecha Acceso::getFecha() const {
    return _fecha;
}
bool Acceso::getEliminado() const {
    return _eliminado;
}

void Acceso::setIdCancion(int idCancion) {
    _idCancion = idCancion;
}
void Acceso::setIdSuscriptor(int idSuscriptor) {
    _idSuscriptor = idSuscriptor;
}
void Acceso::setFecha(Fecha fecha) {
    _fecha = fecha;
}
void Acceso::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
