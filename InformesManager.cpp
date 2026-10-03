#include "InformesManager.h"
#include "Fecha.h"
#include <iostream>
#include <string>
using namespace std;

static const char *MESES[12] = {
    "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO",
    "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
};

// ── 1. Recaudacion anual por plan, desglosada por mes ────────────────────────
// Criterio: un suscriptor factura el precio de su plan en cada mes en que tuvo
// al menos un acceso registrado.
void InformesManager::RecaudacionAnualPorPlan() {
    int anio;
    cout << "Ingrese anio: ";
    cin >> anio;

    int cantPlanes = _repoPlan.getCantidadRegistros();
    if (cantPlanes == 0) { cout << "No hay planes." << endl; return; }
    Plan *planes = new Plan[cantPlanes];
    _repoPlan.Leer(cantPlanes, planes);

    int cantSus = _repoSuscriptor.getCantidadRegistros();
    Suscriptor *sus = new Suscriptor[cantSus > 0 ? cantSus : 1];
    if (cantSus > 0) _repoSuscriptor.Leer(cantSus, sus);

    int cantAcc = _repoAcceso.getCantidadRegistros();
    Acceso *acc = new Acceso[cantAcc > 0 ? cantAcc : 1];
    if (cantAcc > 0) _repoAcceso.Leer(cantAcc, acc);

    cout << "\nFACTURACION DEL ANIO " << anio << endl;

    float totalGeneral = 0;
    // una fila por plan activo, con el subtotal de cada mes
    for (int p = 0; p < cantPlanes; p++) {
        if (planes[p].getEliminado()) continue;

        cout << "\nPLAN: " << planes[p].getDescripcion()
             << " ($" << planes[p].getPrecio() << "/mes)" << endl;

        float totalPlan = 0;
        for (int m = 0; m < 12; m++) {
            float monto = 0;
            // por cada suscriptor de este plan, ver si tuvo acceso en (mes, anio)
            for (int s = 0; s < cantSus; s++) {
                if (sus[s].getEliminado()) continue;
                if (sus[s].getIdPlan() != planes[p].getId()) continue;

                bool tuvo = false;
                for (int a = 0; a < cantAcc; a++) {
                    if (acc[a].getIdSuscriptor() == sus[s].getId() &&
                        acc[a].getFecha().getAnio() == anio &&
                        acc[a].getFecha().getMes() == (m + 1)) {
                        tuvo = true;
                        break;
                    }
                }
                if (tuvo) monto += planes[p].getPrecio();
            }
            if (monto > 0)
                cout << "  " << MESES[m] << ": $" << monto << endl;
            totalPlan += monto;
        }
        cout << "  TOTAL PLAN: $" << totalPlan << endl;
        totalGeneral += totalPlan;
    }

    cout << "\nTOTAL FACTURADO " << anio << ": $" << totalGeneral << endl;

    delete[] planes;
    delete[] sus;
    delete[] acc;
}

// ── 2. Recaudacion por suscriptor en un anio ─────────────────────────────────
// total = (meses con al menos un acceso) * precio del plan
void InformesManager::RecaudacionPorSuscriptor() {
    int anio;
    cout << "Ingrese anio: ";
    cin >> anio;

    int cantSus = _repoSuscriptor.getCantidadRegistros();
    if (cantSus == 0) { cout << "No hay suscriptores." << endl; return; }
    Suscriptor *sus = new Suscriptor[cantSus];
    _repoSuscriptor.Leer(cantSus, sus);

    int cantAcc = _repoAcceso.getCantidadRegistros();
    Acceso *acc = new Acceso[cantAcc > 0 ? cantAcc : 1];
    if (cantAcc > 0) _repoAcceso.Leer(cantAcc, acc);

    cout << "\nRECAUDACION POR SUSCRIPTOR - ANIO " << anio << endl;
    cout << "----------------------------------------" << endl;

    float totalGeneral = 0;
    for (int s = 0; s < cantSus; s++) {
        if (sus[s].getEliminado()) continue;

        // precio del plan del suscriptor
        float precio = 0;
        int posP = _repoPlan.Buscar(sus[s].getIdPlan());
        if (posP != -1) precio = _repoPlan.Leer(posP).getPrecio();

        // meses distintos con al menos un acceso en el anio
        bool mesUsado[12] = { false };
        for (int a = 0; a < cantAcc; a++) {
            if (acc[a].getIdSuscriptor() == sus[s].getId() &&
                acc[a].getFecha().getAnio() == anio) {
                int mes = acc[a].getFecha().getMes();
                if (mes >= 1 && mes <= 12) mesUsado[mes - 1] = true;
            }
        }
        int meses = 0;
        for (int m = 0; m < 12; m++) if (mesUsado[m]) meses++;

        float total = meses * precio;
        totalGeneral += total;

        cout << sus[s].getApellido() << ", " << sus[s].getNombre()
             << " | meses activos: " << meses
             << " | total: $" << total << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "TOTAL GENERAL: $" << totalGeneral << endl;

    delete[] sus;
    delete[] acc;
}

// ── 3. Canciones mas reproducidas en un rango de fechas ──────────────────────
void InformesManager::CancionesMasReproducidas() {
    string desde, hasta;
    cout << "Fecha desde (DD/MM/AAAA, 0 = anio actual): ";
    cin >> desde;

    if (desde == "0") {
        int anio = Fecha::hoy().getAnio();
        desde = Fecha(1, 1, anio).toString();
        hasta = Fecha(31, 12, anio).toString();
    } else {
        cout << "Fecha hasta (DD/MM/AAAA): ";
        cin >> hasta;
    }
    long claveDesde = Fecha::parse(desde).clave();
    long claveHasta = Fecha::parse(hasta).clave();

    int cantC = _repoCancion.getCantidadRegistros();
    if (cantC == 0) { cout << "No hay canciones cargadas." << endl; return; }
    Cancion *canciones = new Cancion[cantC];
    _repoCancion.Leer(cantC, canciones);

    int *conteo = new int[cantC];
    for (int i = 0; i < cantC; i++) conteo[i] = 0;

    // contar accesos dentro del rango por cada cancion
    int cantA = _repoAcceso.getCantidadRegistros();
    if (cantA > 0) {
        Acceso *acc = new Acceso[cantA];
        _repoAcceso.Leer(cantA, acc);
        for (int i = 0; i < cantA; i++) {
            long c = acc[i].getFecha().clave();
            if (c < claveDesde || c > claveHasta) continue;
            for (int j = 0; j < cantC; j++) {
                if (canciones[j].getId() == acc[i].getIdCancion()) {
                    conteo[j]++;
                    break;
                }
            }
        }
        delete[] acc;
    }

    // seleccion descendente por conteo (mueve cancion y conteo a la vez)
    for (int i = 0; i < cantC - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < cantC; j++)
            if (conteo[j] > conteo[pos]) pos = j;
        int auxN = conteo[i]; conteo[i] = conteo[pos]; conteo[pos] = auxN;
        Cancion auxC = canciones[i]; canciones[i] = canciones[pos]; canciones[pos] = auxC;
    }

    cout << "\nCANCIONES MAS REPRODUCIDAS - " << desde << " AL " << hasta << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < cantC; i++) {
        if (canciones[i].getEliminado()) continue;

        // resolver artista y genero (FK)
        string nombreArtista = "(desconocido)";
        int posA = _repoArtista.Buscar(canciones[i].getIdArtista());
        if (posA != -1) nombreArtista = _repoArtista.Leer(posA).getNombre();

        string nombreGenero = "(desconocido)";
        int posG = _repoGenero.Buscar(canciones[i].getIdGenero());
        if (posG != -1) nombreGenero = _repoGenero.Leer(posG).getDescripcion();

        cout << (i + 1) << ") " << canciones[i].getNombre()
             << " - " << nombreArtista
             << " - " << nombreGenero
             << " | accesos: " << conteo[i] << endl;
    }

    delete[] canciones;
    delete[] conteo;
}

// ── 4. Cantidad de accesos por genero en un rango de fechas ──────────────────
void InformesManager::AccesosPorGenero() {
    string desde, hasta;
    cout << "Fecha desde (DD/MM/AAAA, 0 = anio actual): ";
    cin >> desde;

    if (desde == "0") {
        int anio = Fecha::hoy().getAnio();
        desde = Fecha(1, 1, anio).toString();
        hasta = Fecha(31, 12, anio).toString();
    } else {
        cout << "Fecha hasta (DD/MM/AAAA): ";
        cin >> hasta;
    }
    long claveDesde = Fecha::parse(desde).clave();
    long claveHasta = Fecha::parse(hasta).clave();

    int cantG = _repoGenero.getCantidadRegistros();
    if (cantG == 0) { cout << "No hay generos cargados." << endl; return; }
    Genero *generos = new Genero[cantG];
    _repoGenero.Leer(cantG, generos);

    int *conteo = new int[cantG];
    for (int i = 0; i < cantG; i++) conteo[i] = 0;

    // por cada acceso del rango, ubicar la cancion -> su genero -> sumar
    int cantA = _repoAcceso.getCantidadRegistros();
    if (cantA > 0) {
        Acceso *acc = new Acceso[cantA];
        _repoAcceso.Leer(cantA, acc);
        for (int i = 0; i < cantA; i++) {
            long c = acc[i].getFecha().clave();
            if (c < claveDesde || c > claveHasta) continue;

            int posC = _repoCancion.Buscar(acc[i].getIdCancion());
            if (posC == -1) continue;
            int idGen = _repoCancion.Leer(posC).getIdGenero();

            for (int j = 0; j < cantG; j++) {
                if (generos[j].getId() == idGen) { conteo[j]++; break; }
            }
        }
        delete[] acc;
    }

    // seleccion descendente por conteo
    for (int i = 0; i < cantG - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < cantG; j++)
            if (conteo[j] > conteo[pos]) pos = j;
        int auxN = conteo[i]; conteo[i] = conteo[pos]; conteo[pos] = auxN;
        Genero auxG = generos[i]; generos[i] = generos[pos]; generos[pos] = auxG;
    }

    cout << "\nACCESOS POR GENERO - " << desde << " AL " << hasta << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < cantG; i++) {
        if (generos[i].getEliminado()) continue;
        cout << generos[i].getDescripcion() << ": " << conteo[i] << endl;
    }

    delete[] generos;
    delete[] conteo;
}
