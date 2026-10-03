#include "Suscriptor.h"
#include <cstring>
using namespace std;

Suscriptor::Suscriptor() {
    setId(0);
    setDni(0);
    setNombre("");
    setApellido("");
    setTelefono("");
    setEmail("");
    setFechaNacimiento(Fecha());
    setIdPlan(0);
    setIdGenero(0);
    setEliminado(false);
}

Suscriptor::Suscriptor(int id, int dni, string nombre, string apellido,
                       string telefono, string email, Fecha fechaNacimiento,
                       int idPlan, int idGenero) {
    setId(id);
    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
    setFechaNacimiento(fechaNacimiento);
    setIdPlan(idPlan);
    setIdGenero(idGenero);
    setEliminado(false);
}

int Suscriptor::getId() const {
    return _id;
}
int Suscriptor::getDni() const {
    return _dni;
}
string Suscriptor::getNombre() const {
    return string(_nombre);
}
string Suscriptor::getApellido() const {
    return string(_apellido);
}
string Suscriptor::getTelefono() const {
    return string(_telefono);
}
string Suscriptor::getEmail() const {
    return string(_email);
}
Fecha Suscriptor::getFechaNacimiento() const {
    return _fechaNacimiento;
}
int Suscriptor::getIdPlan() const {
    return _idPlan;
}
int Suscriptor::getIdGenero() const {
    return _idGenero;
}
bool Suscriptor::getEliminado() const {
    return _eliminado;
}

void Suscriptor::setId(int id) {
    _id = id;
}
void Suscriptor::setDni(int dni) {
    _dni = dni;
}
void Suscriptor::setNombre(string nombre) {
    strncpy(_nombre, nombre.c_str(), 29);
    _nombre[29] = '\0';
}
void Suscriptor::setApellido(string apellido) {
    strncpy(_apellido, apellido.c_str(), 29);
    _apellido[29] = '\0';
}
void Suscriptor::setTelefono(string telefono) {
    strncpy(_telefono, telefono.c_str(), 19);
    _telefono[19] = '\0';
}
void Suscriptor::setEmail(string email) {
    strncpy(_email, email.c_str(), 49);
    _email[49] = '\0';
}
void Suscriptor::setFechaNacimiento(Fecha fechaNacimiento) {
    _fechaNacimiento = fechaNacimiento;
}
void Suscriptor::setIdPlan(int idPlan) {
    _idPlan = idPlan;
}
void Suscriptor::setIdGenero(int idGenero) {
    _idGenero = idGenero;
}
void Suscriptor::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}
