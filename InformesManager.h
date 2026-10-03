#pragma once
#include "SuscriptorArchivo.h"
#include "PlanArchivo.h"
#include "AccesoArchivo.h"
#include "CancionArchivo.h"
#include "ArtistaArchivo.h"
#include "GeneroArchivo.h"

// Los informes cruzan datos de varias entidades (varias clases Archivo).
class InformesManager {
private:
    SuscriptorArchivo _repoSuscriptor;
    PlanArchivo       _repoPlan;
    AccesoArchivo     _repoAcceso;
    CancionArchivo    _repoCancion;
    ArtistaArchivo    _repoArtista;
    GeneroArchivo     _repoGenero;

public:
    void RecaudacionAnualPorPlan();
    void RecaudacionPorSuscriptor();
    void CancionesMasReproducidas();
    void AccesosPorGenero();
};
