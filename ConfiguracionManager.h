#pragma once
#include <string>

// Version simple: trabaja en la misma carpeta del ejecutable.
// Backups con extension .bkp y exportaciones .csv.
class ConfiguracionManager {
private:
    std::string nombreBase(int opcion);   // opcion -> nombre de archivo sin extension
    bool copiarArchivo(std::string origen, std::string destino);

    void exportarSuscriptores();
    void exportarCanciones();
    void exportarArtistas();
    void exportarAccesos();
    void exportarPlanes();
    void exportarGeneros();
    void exportarUno(int opcion);

public:
    void RealizarBackup();
    void RestaurarBackup();
    void ExportarCSV();
};
