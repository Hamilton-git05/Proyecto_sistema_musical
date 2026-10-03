#include "Fecha.h"
#include <cstdio>
#include <ctime>
using namespace std;

Fecha::Fecha() {
    _dia  = 0;
    _mes  = 0;
    _anio = 0;
}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia  = dia;
    _mes  = mes;
    _anio = anio;
}

int Fecha::getDia() const {
    return _dia;
}
int Fecha::getMes() const {
    return _mes;
}
int Fecha::getAnio() const {
    return _anio;
}

void Fecha::setDia(int dia) {
    _dia = dia;
}
void Fecha::setMes(int mes) {
    _mes = mes;
}
void Fecha::setAnio(int anio) {
    _anio = anio;
}

// "DD/MM/AAAA"
string Fecha::toString() const {
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", _dia, _mes, _anio);
    return string(buffer);
}

// AAAAMMDD: permite comparar dos fechas como simples enteros
long Fecha::clave() const {
    return (long)_anio * 10000 + _mes * 100 + _dia;
}

// fecha actual del sistema
Fecha Fecha::hoy() {
    time_t t = time(0);
    tm *h = localtime(&t);
    return Fecha(h->tm_mday, h->tm_mon + 1, h->tm_year + 1900);
}

// arma una Fecha a partir del texto "DD/MM/AAAA"
Fecha Fecha::parse(string s) {
    int dia, mes, anio;
    if (sscanf(s.c_str(), "%d/%d/%d", &dia, &mes, &anio) != 3)
        return Fecha();
    return Fecha(dia, mes, anio);
}
