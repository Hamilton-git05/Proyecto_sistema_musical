#pragma once
#include <string>

// Clase Fecha (composicion): las entidades estan "compuestas" por una Fecha,
// igual que el ejemplo Examen-Fecha del apunte de POO - Composicion.
// Solo tiene enteros, asi que se sigue serializando bien con fwrite/fread.
class Fecha {
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia()  const;
    int getMes()  const;
    int getAnio() const;

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    std::string toString() const;   // devuelve "DD/MM/AAAA"
    long        clave()    const;    // AAAAMMDD: numero comparable para ordenar/filtrar

    static Fecha hoy();                  // fecha actual del sistema
    static Fecha parse(std::string s);   // arma una Fecha desde "DD/MM/AAAA"
};
