#include "CancionManager.h"
#include <iostream>
#include <string>
using namespace std;

void CancionManager::Mostrar(Cancion cancion) {
    // resolver nombre del artista (FK)
    string nombreArtista = "(desconocido)";
    int posA = _repoArtista.Buscar(cancion.getIdArtista());
    if (posA != -1) nombreArtista = _repoArtista.Leer(posA).getNombre();

    // resolver descripcion del genero (FK)
    string nombreGenero = "(desconocido)";
    int posG = _repoGenero.Buscar(cancion.getIdGenero());
    if (posG != -1) nombreGenero = _repoGenero.Leer(posG).getDescripcion();

    cout << "ID: "         << cancion.getId()               << endl;
    cout << "Nombre: "     << cancion.getNombre()           << endl;
    cout << "Artista: "    << nombreArtista                 << endl;
    cout << "Genero: "     << nombreGenero                  << endl;
    cout << "Fecha pub.: " << cancion.getFechaPublicacion().toString() << endl;
    cout << "Duracion: "   << cancion.getDuracion()         << " seg" << endl;
    cout << endl;
}

// seleccion alfabetico por nombre
void CancionManager::OrdenarPorNombre(Cancion *vec, int cantidad) {
    int i, j, pos;
    Cancion aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getNombre() < vec[pos].getNombre()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// seleccion cronologico por fecha de publicacion
void CancionManager::OrdenarPorFecha(Cancion *vec, int cantidad) {
    int i, j, pos;
    Cancion aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getFechaPublicacion().clave() < vec[pos].getFechaPublicacion().clave()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// seleccion por duracion (ascendente)
void CancionManager::OrdenarPorDuracion(Cancion *vec, int cantidad) {
    int i, j, pos;
    Cancion aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getDuracion() < vec[pos].getDuracion()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// seleccion por idArtista (agrupa las del mismo artista)
void CancionManager::OrdenarPorArtista(Cancion *vec, int cantidad) {
    int i, j, pos;
    Cancion aux;

    for (i = 0; i < cantidad - 1; i++) {
        pos = i;
        for (j = i + 1; j < cantidad; j++) {
            if (vec[j].getIdArtista() < vec[pos].getIdArtista()) {
                pos = j;
            }
        }
        aux      = vec[i];
        vec[i]   = vec[pos];
        vec[pos] = aux;
    }
}

// ── LISTADOS ────────────────────────────────────────────────────────────────

void CancionManager::ListarPorNombre() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay canciones cargadas." << endl; return; }

    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorNombre(vec, cant);

    cout << "CANCIONES (por nombre)" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) Mostrar(vec[i]);

    delete[] vec;
}

void CancionManager::ListarPorFecha() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay canciones cargadas." << endl; return; }

    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorFecha(vec, cant);

    cout << "CANCIONES (por fecha de publicacion)" << endl;
    cout << "------------------------------------" << endl;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) Mostrar(vec[i]);

    delete[] vec;
}

void CancionManager::ListarPorDuracion() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay canciones cargadas." << endl; return; }

    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorDuracion(vec, cant);

    cout << "CANCIONES (por duracion)" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) Mostrar(vec[i]);

    delete[] vec;
}

void CancionManager::ListarPorArtista() {
    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay canciones cargadas." << endl; return; }

    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorArtista(vec, cant);

    cout << "CANCIONES (por artista)" << endl;
    cout << "-----------------------" << endl;
    for (int i = 0; i < cant; i++)
        if (!vec[i].getEliminado()) Mostrar(vec[i]);

    delete[] vec;
}

// ── CONSULTAS ───────────────────────────────────────────────────────────────

void CancionManager::ConsultarPorGenero() {
    int idGenero;
    cout << "ID del genero: ";
    cin >> idGenero;

    // check genero (FK)
    int posG = _repoGenero.Buscar(idGenero);
    if (posG == -1) { cout << "Genero no encontrado." << endl; return; }

    int cant = _repo.getCantidadRegistros();
    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorNombre(vec, cant);

    cout << "CANCIONES DEL GENERO: " << _repoGenero.Leer(posG).getDescripcion() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        if (!vec[i].getEliminado() && vec[i].getIdGenero() == idGenero) {
            Mostrar(vec[i]);
            hay = true;
        }
    }
    if (!hay) cout << "No hay canciones de ese genero." << endl;

    delete[] vec;
}

void CancionManager::ConsultarPorArtista() {
    int idArtista;
    cout << "ID del artista: ";
    cin >> idArtista;

    // check artista (FK)
    int posA = _repoArtista.Buscar(idArtista);
    if (posA == -1) { cout << "Artista no encontrado." << endl; return; }

    int cant = _repo.getCantidadRegistros();
    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorNombre(vec, cant);

    cout << "CANCIONES DEL ARTISTA: " << _repoArtista.Leer(posA).getNombre() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        if (!vec[i].getEliminado() && vec[i].getIdArtista() == idArtista) {
            Mostrar(vec[i]);
            hay = true;
        }
    }
    if (!hay) cout << "Este artista no tiene canciones cargadas." << endl;

    delete[] vec;
}

void CancionManager::ConsultarPorRangoDuracion() {
    int min, max;
    cout << "Duracion minima (seg): ";
    cin >> min;
    cout << "Duracion maxima (seg): ";
    cin >> max;

    int cant = _repo.getCantidadRegistros();
    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);
    OrdenarPorDuracion(vec, cant);

    cout << "CANCIONES ENTRE " << min << " Y " << max << " SEG" << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        int d = vec[i].getDuracion();
        if (!vec[i].getEliminado() && d >= min && d <= max) {
            Mostrar(vec[i]);
            hay = true;
        }
    }
    if (!hay) cout << "No hay canciones en ese rango de duracion." << endl;

    delete[] vec;
}

void CancionManager::ConsultarPorFecha() {
    string fecha;
    cout << "Fecha de publicacion exacta (DD/MM/AAAA): ";
    cin >> fecha;
    long claveBuscada = Fecha::parse(fecha).clave();

    int cant = _repo.getCantidadRegistros();
    Cancion *vec = new Cancion[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    cout << "CANCIONES PUBLICADAS EL " << fecha << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        if (!vec[i].getEliminado() && vec[i].getFechaPublicacion().clave() == claveBuscada) {
            Mostrar(vec[i]);
            hay = true;
        }
    }
    if (!hay) cout << "No hay canciones publicadas en esa fecha." << endl;

    delete[] vec;
}

// busca una cancion activa por id (usado para validar/mostrar FK desde otras capas)
bool CancionManager::Buscar(int id, Cancion &cancion) {
    int pos = _repo.Buscar(id);
    if (pos == -1) return false;
    cancion = _repo.Leer(pos);
    return !cancion.getEliminado();
}
