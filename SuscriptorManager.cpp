#include "SuscriptorManager.h"
#include <iostream>
#include <string>
using namespace std;

// calcula la edad (en anios) a partir de la fecha de nacimiento y la fecha de hoy
int SuscriptorManager::Edad(Fecha fechaNacimiento) {
    Fecha hoy = Fecha::hoy();

    int edad = hoy.getAnio() - fechaNacimiento.getAnio();
    // si todavia no cumplio anios este anio, resto uno
    if (hoy.getMes() < fechaNacimiento.getMes() ||
        (hoy.getMes() == fechaNacimiento.getMes() && hoy.getDia() < fechaNacimiento.getDia()))
        edad--;
    return edad;
}

void SuscriptorManager::Mostrar(Suscriptor suscriptor) {
    // resolver descripcion del plan (FK)
    string descPlan = "(desconocido)";
    int posP = _repoPlan.Buscar(suscriptor.getIdPlan());
    if (posP != -1) descPlan = _repoPlan.Leer(posP).getDescripcion();

    // resolver genero de preferencia (FK, 0 = sin preferencia)
    string descGenero = "Sin preferencia";
    if (suscriptor.getIdGenero() != 0) {
        int posG = _repoGenero.Buscar(suscriptor.getIdGenero());
        if (posG != -1) descGenero = _repoGenero.Leer(posG).getDescripcion();
    }

    cout << "ID: "        << suscriptor.getId()              << endl;
    cout << "DNI: "       << suscriptor.getDni()             << endl;
    cout << "Nombre: "    << suscriptor.getApellido() << ", " << suscriptor.getNombre() << endl;
    cout << "Telefono: "  << suscriptor.getTelefono()        << endl;
    cout << "Email: "     << suscriptor.getEmail()           << endl;
    cout << "Nacimiento: "<< suscriptor.getFechaNacimiento().toString() << " (" << Edad(suscriptor.getFechaNacimiento()) << " anios)" << endl;
    cout << "Plan: "      << descPlan                        << endl;
    cout << "Genero pref.: " << descGenero                   << endl;
    cout << endl;
}

// seleccion alfabetico por apellido
void SuscriptorManager::OrdenarPorApellido(Suscriptor *vec, int cantidad) {
    int i, j, pos;
    Suscriptor aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getApellido() < vec[pos].getApellido()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// seleccion por edad descendente (del mas grande al mas chico)
void SuscriptorManager::OrdenarPorEdad(Suscriptor *vec, int cantidad) {
    int i, j, pos;
    Suscriptor aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (Edad(vec[j].getFechaNacimiento()) > Edad(vec[pos].getFechaNacimiento())) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

void SuscriptorManager::Alta() {
    int    id = _repo.getCantidadRegistros() + 1;
    int    dni, idPlan, idGenero;
    string nombre, apellido, telefono, email, fechaNac;

    // input
    cout << "ID: " << id << endl;

    cout << "DNI: ";
    cin >> dni;

    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Apellido: ";
    getline(cin, apellido);

    cout << "Telefono: ";
    getline(cin, telefono);

    cout << "Email: ";
    getline(cin, email);

    cout << "Fecha de nacimiento (DD/MM/AAAA): ";
    getline(cin, fechaNac);

    cout << "ID de plan: ";
    cin >> idPlan;

    cout << "ID de genero de preferencia (0 = ninguno): ";
    cin >> idGenero;

    // check plan (FK)
    int posPlan = _repoPlan.Buscar(idPlan);
    if (posPlan == -1 || _repoPlan.Leer(posPlan).getEliminado()) {
        cout << "Plan inexistente o dado de baja. Alta cancelada." << endl;
        return;
    }

    // check genero (FK) solo si no es 0
    if (idGenero != 0) {
        int posGen = _repoGenero.Buscar(idGenero);
        if (posGen == -1 || _repoGenero.Leer(posGen).getEliminado()) {
            cout << "Genero inexistente o dado de baja. Alta cancelada." << endl;
            return;
        }
    }

    Suscriptor suscriptor(id, dni, nombre, apellido, telefono, email, Fecha::parse(fechaNac), idPlan, idGenero);

    char confirmar;
    cout << "Confirmar (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        _repo.Guardar(suscriptor);
        cout << "Suscriptor registrado con ID " << id << "." << endl;
    }
}

void SuscriptorManager::Baja() {
    int id;
    cout << "ID del suscriptor a dar de baja: ";
    cin >> id;

    int pos = _repo.Buscar(id);
    if (pos == -1) {
        cout << "Suscriptor no encontrado." << endl;
        return;
    }

    Suscriptor s = _repo.Leer(pos);
    if (s.getEliminado()) {
        cout << "El suscriptor ya estaba dado de baja." << endl;
        return;
    }

    cout << s.getApellido() << ", " << s.getNombre()
         << " (DNI: " << s.getDni() << ")" << endl;

    char confirmar;
    cout << "Confirmar baja (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        s.setEliminado(true);
        _repo.Guardar(s, pos);
        cout << "Suscriptor dado de baja correctamente." << endl;
    }
}

void SuscriptorManager::Modificar() {
    int id;
    cout << "ID del suscriptor a modificar: ";
    cin >> id;

    int pos = _repo.Buscar(id);
    if (pos == -1) {
        cout << "Suscriptor no encontrado." << endl;
        return;
    }

    Suscriptor s = _repo.Leer(pos);
    if (s.getEliminado()) {
        cout << "El suscriptor esta dado de baja." << endl;
        return;
    }

    cout << "Datos actuales:" << endl;
    Mostrar(s);

    int    dni, idPlan, idGenero;
    string nombre, apellido, telefono, email, fechaNac;

    // input
    cout << "Nuevo DNI (" << s.getDni() << "): ";
    cin >> dni;

    cin.ignore();
    cout << "Nuevo nombre (" << s.getNombre() << "): ";
    getline(cin, nombre);

    cout << "Nuevo apellido (" << s.getApellido() << "): ";
    getline(cin, apellido);

    cout << "Nuevo telefono (" << s.getTelefono() << "): ";
    getline(cin, telefono);

    cout << "Nuevo email (" << s.getEmail() << "): ";
    getline(cin, email);

    cout << "Nueva fecha de nacimiento (" << s.getFechaNacimiento().toString() << "): ";
    getline(cin, fechaNac);

    cout << "Nuevo ID de plan (" << s.getIdPlan() << "): ";
    cin >> idPlan;

    cout << "Nuevo ID de genero (" << s.getIdGenero() << ", 0 = ninguno): ";
    cin >> idGenero;

    // check plan (FK)
    int posPlan = _repoPlan.Buscar(idPlan);
    if (posPlan == -1 || _repoPlan.Leer(posPlan).getEliminado()) {
        cout << "Plan inexistente o dado de baja. Modificacion cancelada." << endl;
        return;
    }

    // check genero (FK) solo si no es 0
    if (idGenero != 0) {
        int posGen = _repoGenero.Buscar(idGenero);
        if (posGen == -1 || _repoGenero.Leer(posGen).getEliminado()) {
            cout << "Genero inexistente o dado de baja. Modificacion cancelada." << endl;
            return;
        }
    }

    // set valores
    s.setDni(dni);
    s.setNombre(nombre);
    s.setApellido(apellido);
    s.setTelefono(telefono);
    s.setEmail(email);
    s.setFechaNacimiento(Fecha::parse(fechaNac));
    s.setIdPlan(idPlan);
    s.setIdGenero(idGenero);

    char confirmar;
    cout << "Confirmar cambios (S/N): ";
    cin >> confirmar;

    if (tolower(confirmar) == 's') {
        _repo.Guardar(s, pos);
        cout << "Suscriptor modificado correctamente." << endl;
    }
}

void SuscriptorManager::ListarPorApellido() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay suscriptores registrados." << endl;
        return;
    }

    Suscriptor *vec = new Suscriptor[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    // get activos
    int activos = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) activos++;

    if (activos == 0) {
        cout << "No hay suscriptores activos." << endl;
        delete[] vec;
        return;
    }

    // get NO eliminados
    Suscriptor *actVec = new Suscriptor[activos];
    int k = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) actVec[k++] = vec[i];

    OrdenarPorApellido(actVec, activos);

    cout << "SUSCRIPTORES (por apellido)" << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < activos; i++) Mostrar(actVec[i]);

    delete[] vec;
    delete[] actVec;
}

void SuscriptorManager::ListarPorEdad() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) {
        cout << "No hay suscriptores registrados." << endl;
        return;
    }

    Suscriptor *vec = new Suscriptor[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    int activos = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) activos++;

    if (activos == 0) {
        cout << "No hay suscriptores activos." << endl;
        delete[] vec;
        return;
    }

    Suscriptor *actVec = new Suscriptor[activos];
    int k = 0;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) actVec[k++] = vec[i];

    OrdenarPorEdad(actVec, activos);

    cout << "SUSCRIPTORES (por edad, mayor a menor)" << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < activos; i++) Mostrar(actVec[i]);

    delete[] vec;
    delete[] actVec;
}

void SuscriptorManager::ConsultarPorDNI() {
    int dni;
    cout << "DNI a buscar: ";
    cin >> dni;

    int cant = _repo.getCantidadRegistros();
    for (int i = 0; i < cant; i++) {
        Suscriptor s = _repo.Leer(i);
        if (!s.getEliminado() && s.getDni() == dni) {
            Mostrar(s);
            return;
        }
    }
    cout << "No se encontro un suscriptor activo con ese DNI." << endl;
}

void SuscriptorManager::ConsultarPorRangoEdad() {
    int min, max;
    cout << "Edad minima: ";
    cin >> min;
    cout << "Edad maxima: ";
    cin >> max;

    int cant = _repo.getCantidadRegistros();
    cout << "SUSCRIPTORES ENTRE " << min << " Y " << max << " ANIOS" << endl;
    cout << "----------------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        Suscriptor s = _repo.Leer(i);
        if (s.getEliminado()) continue;
        int edad = Edad(s.getFechaNacimiento());
        if (edad >= min && edad <= max) {
            Mostrar(s);
            hay = true;
        }
    }
    if (!hay) cout << "No hay suscriptores en ese rango de edad." << endl;
}

void SuscriptorManager::ConsultarPorGenero() {
    int idGenero;
    cout << "ID del genero de preferencia: ";
    cin >> idGenero;

    // check genero (FK)
    int posG = _repoGenero.Buscar(idGenero);
    if (posG == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    int cant = _repo.getCantidadRegistros();
    cout << "SUSCRIPTORES CON PREFERENCIA: " << _repoGenero.Leer(posG).getDescripcion() << endl;
    cout << "----------------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        Suscriptor s = _repo.Leer(i);
        if (!s.getEliminado() && s.getIdGenero() == idGenero) {
            Mostrar(s);
            hay = true;
        }
    }
    if (!hay) cout << "No hay suscriptores con esa preferencia." << endl;
}

void SuscriptorManager::ConsultarPorPlan() {
    int idPlan;
    cout << "ID del plan: ";
    cin >> idPlan;

    // check plan (FK)
    int posP = _repoPlan.Buscar(idPlan);
    if (posP == -1) {
        cout << "Plan no encontrado." << endl;
        return;
    }

    int cant = _repo.getCantidadRegistros();
    cout << "SUSCRIPTORES DEL PLAN: " << _repoPlan.Leer(posP).getDescripcion() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        Suscriptor s = _repo.Leer(i);
        if (!s.getEliminado() && s.getIdPlan() == idPlan) {
            Mostrar(s);
            hay = true;
        }
    }
    if (!hay) cout << "No hay suscriptores en ese plan." << endl;
}
