#include "ConfiguracionManager.h"
#include "SuscriptorArchivo.h"
#include "CancionArchivo.h"
#include "ArtistaArchivo.h"
#include "AccesoArchivo.h"
#include "PlanArchivo.h"
#include "GeneroArchivo.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

// opcion del submenu -> nombre de archivo base (sin extension)
string ConfiguracionManager::nombreBase(int opcion) {
    switch (opcion) {
        case 1: return "suscriptores";
        case 2: return "canciones";
        case 3: return "artistas";
        case 4: return "accesos";
        case 5: return "planes";
        case 6: return "generos";
    }
    return "";
}

// copia binaria de un archivo a otro
bool ConfiguracionManager::copiarArchivo(string origen, string destino) {
    FILE *o = fopen(origen.c_str(), "rb");
    if (o == NULL) return false;
    FILE *d = fopen(destino.c_str(), "wb");
    if (d == NULL) { fclose(o); return false; }

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), o)) > 0)
        fwrite(buffer, 1, n, d);

    fclose(o);
    fclose(d);
    return true;
}

// ── BACKUP ───────────────────────────────────────────────────────────────────
void ConfiguracionManager::RealizarBackup() {
    cout << "\n-- REALIZAR COPIA DE SEGURIDAD --" << endl;
    cout << "1 - Suscriptores" << endl;
    cout << "2 - Canciones" << endl;
    cout << "3 - Artistas" << endl;
    cout << "4 - Accesos" << endl;
    cout << "5 - Planes" << endl;
    cout << "6 - Generos" << endl;
    cout << "7 - Todos los archivos" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";

    int op;
    cin >> op;
    if (op == 0) return;

    if (op == 7) {
        for (int i = 1; i <= 6; i++) {
            string base = nombreBase(i);
            if (copiarArchivo(base + ".dat", base + ".bkp"))
                cout << "Backup de " << base << ".dat OK" << endl;
        }
        return;
    }

    string base = nombreBase(op);
    if (base == "") { cout << "Opcion invalida." << endl; return; }

    if (copiarArchivo(base + ".dat", base + ".bkp"))
        cout << "Backup de " << base << ".dat generado (" << base << ".bkp)." << endl;
    else
        cout << "No se pudo leer " << base << ".dat" << endl;
}

// ── RESTAURAR ─────────────────────────────────────────────────────────────────
void ConfiguracionManager::RestaurarBackup() {
    cout << "\n-- RESTAURAR COPIA DE SEGURIDAD --" << endl;
    cout << "1 - Suscriptores" << endl;
    cout << "2 - Canciones" << endl;
    cout << "3 - Artistas" << endl;
    cout << "4 - Accesos" << endl;
    cout << "5 - Planes" << endl;
    cout << "6 - Generos" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";

    int op;
    cin >> op;
    if (op == 0) return;

    string base = nombreBase(op);
    if (base == "") { cout << "Opcion invalida." << endl; return; }

    // codigo de confirmacion generado automaticamente
    srand(time(0));
    int codigo = rand() % 90000 + 10000;
    cout << "Restaurando " << base << ".bkp..." << endl;
    cout << "Para continuar ingrese el siguiente codigo: " << codigo << endl;
    cout << "Codigo de confirmacion: ";

    int ingresado;
    cin >> ingresado;

    if (ingresado != codigo) {
        cout << "Codigo incorrecto. Restauracion cancelada." << endl;
        return;
    }

    if (copiarArchivo(base + ".bkp", base + ".dat"))
        cout << base << ".dat restaurado correctamente." << endl;
    else
        cout << "No se encontro el backup " << base << ".bkp" << endl;
}

// ── EXPORTAR CSV ──────────────────────────────────────────────────────────────
void ConfiguracionManager::exportarSuscriptores() {
    SuscriptorArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("suscriptores.csv", "w");
    if (f == NULL) return;
    fprintf(f, "id,dni,nombre,apellido,telefono,email,fechaNacimiento,idPlan,idGenero,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Suscriptor s = repo.Leer(i);
        fprintf(f, "%d,%d,%s,%s,%s,%s,%s,%d,%d,%d\n",
                s.getId(), s.getDni(), s.getNombre().c_str(), s.getApellido().c_str(),
                s.getTelefono().c_str(), s.getEmail().c_str(), s.getFechaNacimiento().toString().c_str(),
                s.getIdPlan(), s.getIdGenero(), s.getEliminado());
    }
    fclose(f);
    cout << "suscriptores.csv generado." << endl;
}

void ConfiguracionManager::exportarCanciones() {
    CancionArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("canciones.csv", "w");
    if (f == NULL) return;
    fprintf(f, "id,nombre,idArtista,idGenero,fechaPublicacion,duracion,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Cancion c = repo.Leer(i);
        fprintf(f, "%d,%s,%d,%d,%s,%d,%d\n",
                c.getId(), c.getNombre().c_str(), c.getIdArtista(), c.getIdGenero(),
                c.getFechaPublicacion().toString().c_str(), c.getDuracion(), c.getEliminado());
    }
    fclose(f);
    cout << "canciones.csv generado." << endl;
}

void ConfiguracionManager::exportarArtistas() {
    ArtistaArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("artistas.csv", "w");
    if (f == NULL) return;
    fprintf(f, "id,nombre,pais,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Artista a = repo.Leer(i);
        fprintf(f, "%d,%s,%s,%d\n",
                a.getId(), a.getNombre().c_str(), a.getPais().c_str(), a.getEliminado());
    }
    fclose(f);
    cout << "artistas.csv generado." << endl;
}

void ConfiguracionManager::exportarAccesos() {
    AccesoArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("accesos.csv", "w");
    if (f == NULL) return;
    fprintf(f, "idCancion,idSuscriptor,fecha,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Acceso a = repo.Leer(i);
        fprintf(f, "%d,%d,%s,%d\n",
                a.getIdCancion(), a.getIdSuscriptor(), a.getFecha().toString().c_str(), a.getEliminado());
    }
    fclose(f);
    cout << "accesos.csv generado." << endl;
}

void ConfiguracionManager::exportarPlanes() {
    PlanArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("planes.csv", "w");
    if (f == NULL) return;
    fprintf(f, "id,descripcion,precio,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Plan p = repo.Leer(i);
        fprintf(f, "%d,%s,%.2f,%d\n",
                p.getId(), p.getDescripcion().c_str(), p.getPrecio(), p.getEliminado());
    }
    fclose(f);
    cout << "planes.csv generado." << endl;
}

void ConfiguracionManager::exportarGeneros() {
    GeneroArchivo repo;
    int cant = repo.getCantidadRegistros();
    FILE *f = fopen("generos.csv", "w");
    if (f == NULL) return;
    fprintf(f, "id,descripcion,eliminado\n");
    for (int i = 0; i < cant; i++) {
        Genero g = repo.Leer(i);
        fprintf(f, "%d,%s,%d\n",
                g.getId(), g.getDescripcion().c_str(), g.getEliminado());
    }
    fclose(f);
    cout << "generos.csv generado." << endl;
}

void ConfiguracionManager::exportarUno(int opcion) {
    switch (opcion) {
        case 1: exportarSuscriptores(); break;
        case 2: exportarCanciones();    break;
        case 3: exportarArtistas();     break;
        case 4: exportarAccesos();      break;
        case 5: exportarPlanes();       break;
        case 6: exportarGeneros();      break;
        default: cout << "Opcion invalida." << endl; break;
    }
}

void ConfiguracionManager::ExportarCSV() {
    cout << "\n-- EXPORTAR DATOS (CSV) --" << endl;
    cout << "1 - Suscriptores" << endl;
    cout << "2 - Canciones" << endl;
    cout << "3 - Artistas" << endl;
    cout << "4 - Accesos" << endl;
    cout << "5 - Planes" << endl;
    cout << "6 - Generos" << endl;
    cout << "7 - Todos los archivos" << endl;
    cout << "0 - Volver" << endl;
    cout << "Opcion: ";

    int op;
    cin >> op;
    if (op == 0) return;

    if (op == 7) {
        for (int i = 1; i <= 6; i++) exportarUno(i);
        return;
    }
    exportarUno(op);
}
