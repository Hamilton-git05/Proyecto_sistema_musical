#include "AccesoManager.h"
#include <iostream>
#include <string>
using namespace std;

void AccesoManager::Registrar() {
    int idSuscriptor, idCancion;

    cout << "ID del suscriptor: ";
    cin >> idSuscriptor;

    cout << "ID de la cancion: ";
    cin >> idCancion;

    // check suscriptor (FK)
    int posS = _repoSuscriptor.Buscar(idSuscriptor);
    if (posS == -1 || _repoSuscriptor.Leer(posS).getEliminado()) {
        cout << "Suscriptor inexistente o dado de baja. Acceso no registrado." << endl;
        return;
    }

    // check cancion (FK)
    int posC = _repoCancion.Buscar(idCancion);
    if (posC == -1 || _repoCancion.Leer(posC).getEliminado()) {
        cout << "Cancion inexistente o dada de baja. Acceso no registrado." << endl;
        return;
    }

    // la fecha se toma automaticamente del sistema (Fecha::hoy)
    Acceso acceso(idCancion, idSuscriptor, Fecha::hoy());
    _repo.Guardar(acceso);
    cout << "Acceso registrado el " << acceso.getFecha().toString() << "." << endl;
}

void AccesoManager::ConsultarPorRangoFechas() {
    string desde, hasta;
    cout << "Fecha desde (DD/MM/AAAA): ";
    cin >> desde;
    cout << "Fecha hasta (DD/MM/AAAA): ";
    cin >> hasta;

    long claveDesde = Fecha::parse(desde).clave();
    long claveHasta = Fecha::parse(hasta).clave();

    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay accesos registrados." << endl; return; }

    Acceso *vec = new Acceso[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    cout << "ACCESOS DEL " << desde << " AL " << hasta << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        long c = vec[i].getFecha().clave();
        if (c >= claveDesde && c <= claveHasta) {
            // resolver nombres (FK)
            string nombreCancion = "(desconocida)";
            int posC = _repoCancion.Buscar(vec[i].getIdCancion());
            if (posC != -1) nombreCancion = _repoCancion.Leer(posC).getNombre();

            string nombreSus = "(desconocido)";
            int posS = _repoSuscriptor.Buscar(vec[i].getIdSuscriptor());
            if (posS != -1) {
                Suscriptor s = _repoSuscriptor.Leer(posS);
                nombreSus = s.getApellido() + ", " + s.getNombre();
            }

            cout << vec[i].getFecha().toString() << " - " << nombreCancion
                 << " - " << nombreSus << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay accesos en ese rango de fechas." << endl;

    delete[] vec;
}

void AccesoManager::ConsultarPorSuscriptor() {
    int idSuscriptor;
    cout << "ID del suscriptor: ";
    cin >> idSuscriptor;

    // check suscriptor (FK)
    int posS = _repoSuscriptor.Buscar(idSuscriptor);
    if (posS == -1) { cout << "Suscriptor no encontrado." << endl; return; }
    Suscriptor s = _repoSuscriptor.Leer(posS);

    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay accesos registrados." << endl; return; }

    Acceso *vec = new Acceso[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    cout << "ACCESOS DE: " << s.getApellido() << ", " << s.getNombre() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        if (vec[i].getIdSuscriptor() == idSuscriptor) {
            string nombreCancion = "(desconocida)";
            int posC = _repoCancion.Buscar(vec[i].getIdCancion());
            if (posC != -1) nombreCancion = _repoCancion.Leer(posC).getNombre();

            cout << vec[i].getFecha().toString() << " - " << nombreCancion << endl;
            hay = true;
        }
    }
    if (!hay) cout << "Este suscriptor no tiene accesos registrados." << endl;

    delete[] vec;
}

void AccesoManager::ConsultarPorCancion() {
    int idCancion;
    cout << "ID de la cancion: ";
    cin >> idCancion;

    // check cancion (FK)
    int posC = _repoCancion.Buscar(idCancion);
    if (posC == -1) { cout << "Cancion no encontrada." << endl; return; }
    Cancion c = _repoCancion.Leer(posC);

    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay accesos registrados." << endl; return; }

    Acceso *vec = new Acceso[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    cout << "ACCESOS A LA CANCION: " << c.getNombre() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        if (vec[i].getIdCancion() == idCancion) {
            string nombreSus = "(desconocido)";
            int posS = _repoSuscriptor.Buscar(vec[i].getIdSuscriptor());
            if (posS != -1) {
                Suscriptor s = _repoSuscriptor.Leer(posS);
                nombreSus = s.getApellido() + ", " + s.getNombre();
            }

            cout << vec[i].getFecha().toString() << " - " << nombreSus << endl;
            hay = true;
        }
    }
    if (!hay) cout << "Esta cancion no tiene accesos registrados." << endl;

    delete[] vec;
}

void AccesoManager::ConsultarPorArtista() {
    int idArtista;
    cout << "ID del artista: ";
    cin >> idArtista;

    // check artista (FK)
    int posA = _repoArtista.Buscar(idArtista);
    if (posA == -1) { cout << "Artista no encontrado." << endl; return; }

    int cant = _repo.getCantidadRegistros();
    if (cant == 0) { cout << "No hay accesos registrados." << endl; return; }

    Acceso *vec = new Acceso[cant];
    if (vec == nullptr) return;
    _repo.Leer(cant, vec);

    cout << "ACCESOS A CANCIONES DE: " << _repoArtista.Leer(posA).getNombre() << endl;
    cout << "----------------------" << endl;
    bool hay = false;
    for (int i = 0; i < cant; i++) {
        // resolver la cancion del acceso y comparar su artista
        int posC = _repoCancion.Buscar(vec[i].getIdCancion());
        if (posC == -1) continue;
        Cancion c = _repoCancion.Leer(posC);
        if (c.getIdArtista() == idArtista) {
            cout << vec[i].getFecha().toString() << " - " << c.getNombre() << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay accesos a canciones de ese artista." << endl;

    delete[] vec;
}
