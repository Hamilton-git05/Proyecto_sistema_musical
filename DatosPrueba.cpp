#include "DatosPrueba.h"
#include "Fecha.h"
#include "GeneroArchivo.h"
#include "ArtistaArchivo.h"
#include "PlanArchivo.h"
#include "CancionArchivo.h"
#include "SuscriptorArchivo.h"
#include "AccesoArchivo.h"

// Carga datos de ejemplo SOLO si cada archivo esta vacio (no pisa datos del usuario).
void DatosPrueba::Cargar() {
    GeneroArchivo     generoRepo;
    ArtistaArchivo    artistaRepo;
    PlanArchivo       planRepo;
    CancionArchivo    cancionRepo;
    SuscriptorArchivo suscriptorRepo;
    AccesoArchivo     accesoRepo;

    // ── GENEROS ────────────────────────────────────────────────────────────────
    if (generoRepo.getCantidadRegistros() == 0) {
        generoRepo.Guardar(Genero(1, "Rock"));
        generoRepo.Guardar(Genero(2, "Pop"));
        generoRepo.Guardar(Genero(3, "Bandas Sonoras"));
        generoRepo.Guardar(Genero(4, "Infantil"));
    }

    // ── ARTISTAS ───────────────────────────────────────────────────────────────
    if (artistaRepo.getCantidadRegistros() == 0) {
        artistaRepo.Guardar(Artista(1, "Harry Potter",   "Reino Unido"));
        artistaRepo.Guardar(Artista(2, "Homero Simpson", "Estados Unidos"));
        artistaRepo.Guardar(Artista(3, "Queen",          "Reino Unido"));
        artistaRepo.Guardar(Artista(4, "Bob Esponja",    "Estados Unidos"));
        artistaRepo.Guardar(Artista(5, "Smash Mouth",    "Estados Unidos"));
        artistaRepo.Guardar(Artista(6, "Shrek",          "Estados Unidos"));
        artistaRepo.Guardar(Artista(7, "Led Zeppelin",   "Reino Unido"));
        artistaRepo.Guardar(Artista(8, "Walter White",   "Estados Unidos"));
    }

    // ── PLANES ─────────────────────────────────────────────────────────────────
    if (planRepo.getCantidadRegistros() == 0) {
        planRepo.Guardar(Plan(1, "Basico",    500.0f));
        planRepo.Guardar(Plan(2, "Premium",  1200.0f));
        planRepo.Guardar(Plan(3, "Familiar", 1800.0f));
    }

    // ── CANCIONES (idArtista, idGenero, fecha, duracion) ─────────────────────────
    if (cancionRepo.getCantidadRegistros() == 0) {
        cancionRepo.Guardar(Cancion(1,  "Wingardium Leviosaaaa",   1, 3, Fecha(1, 11, 2001), 178));
        cancionRepo.Guardar(Cancion(2,  "El Baile de la Escoba",   1, 3, Fecha(1, 11, 2001), 203));
        cancionRepo.Guardar(Cancion(3,  "Mmm Donuts",              2, 4, Fecha(15, 5, 2000), 165));
        cancionRepo.Guardar(Cancion(4,  "D Oh D Oh D Oh",          2, 4, Fecha(15, 5, 2000), 142));
        cancionRepo.Guardar(Cancion(5,  "Bohemian Rhapsody",       3, 1, Fecha(31, 10, 1975), 354));
        cancionRepo.Guardar(Cancion(6,  "La Cancion de la Medusa", 4, 4, Fecha(1, 7, 2002), 190));
        cancionRepo.Guardar(Cancion(7,  "All Star",                5, 2, Fecha(4, 5, 1999), 237));
        cancionRepo.Guardar(Cancion(8,  "Ojala Salga el Sol",      6, 3, Fecha(18, 5, 2004), 198));
        cancionRepo.Guardar(Cancion(9,  "Stairway to Heaven",      7, 1, Fecha(8, 11, 1971), 482));
        cancionRepo.Guardar(Cancion(10, "Mi Tesoro (Balada)",      8, 2, Fecha(20, 1, 2008), 310));
    }

    // ── SUSCRIPTORES (dni, nombre, apellido, tel, email, fechaNac, idPlan, idGenero)
    if (suscriptorRepo.getCantidadRegistros() == 0) {
        suscriptorRepo.Guardar(Suscriptor(1, 28345671, "Hamilton",   "Yaluzan",  "1145678901", "hyaluzan@mail.com", Fecha(12, 3, 1990), 1, 1));
        suscriptorRepo.Guardar(Suscriptor(2, 30456782, "Juan Pablo", "Olivera",  "1156789012", "jolivera@mail.com", Fecha(25, 7, 1985), 2, 2));
        suscriptorRepo.Guardar(Suscriptor(3, 32567893, "Joaquin",    "Blanco",   "1167890123", "jblanco@mail.com",  Fecha(8, 11, 1998), 1, 1));
        suscriptorRepo.Guardar(Suscriptor(4, 12345678, "Marge",      "Simpson",  "1178901234", "msimpson@mail.com", Fecha(19, 10, 1975), 3, 4));
        suscriptorRepo.Guardar(Suscriptor(5, 87654321, "Hermione",   "Granger",  "1189012345", "hgranger@mail.com", Fecha(30, 1, 2000), 2, 0));
    }

    // ── ACCESOS (idCancion, idSuscriptor, fecha) ─────────────────────────────────
    if (accesoRepo.getCantidadRegistros() == 0) {
        accesoRepo.Guardar(Acceso(5, 1, Fecha(10, 1, 2026)));
        accesoRepo.Guardar(Acceso(5, 2, Fecha(15, 1, 2026)));
        accesoRepo.Guardar(Acceso(5, 3, Fecha(20, 2, 2026)));
        accesoRepo.Guardar(Acceso(5, 4, Fecha(5, 3, 2026)));
        accesoRepo.Guardar(Acceso(9, 2, Fecha(6, 3, 2026)));
        accesoRepo.Guardar(Acceso(9, 5, Fecha(7, 4, 2026)));
        accesoRepo.Guardar(Acceso(1, 5, Fecha(8, 4, 2026)));
        accesoRepo.Guardar(Acceso(7, 4, Fecha(9, 5, 2026)));
        accesoRepo.Guardar(Acceso(3, 4, Fecha(10, 5, 2026)));
        accesoRepo.Guardar(Acceso(10, 2, Fecha(11, 6, 2026)));
        accesoRepo.Guardar(Acceso(7, 1, Fecha(12, 6, 2026)));
        accesoRepo.Guardar(Acceso(9, 3, Fecha(13, 6, 2026)));
    }
}
