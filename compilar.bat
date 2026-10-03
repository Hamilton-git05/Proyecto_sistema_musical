@echo off
cd /d "%~dp0"
echo Compilando...
g++ -o musica_demo.exe main.cpp Fecha.cpp DatosPrueba.cpp App.cpp SuscriptorMenu.cpp SuscriptorManager.cpp SuscriptorArchivo.cpp Suscriptor.cpp PlanMenu.cpp PlanManager.cpp PlanArchivo.cpp Plan.cpp CancionMenu.cpp CancionManager.cpp CancionArchivo.cpp Cancion.cpp ArtistaMenu.cpp ArtistaManager.cpp ArtistaArchivo.cpp Artista.cpp GeneroMenu.cpp GeneroManager.cpp GeneroArchivo.cpp Genero.cpp AccesoMenu.cpp AccesoManager.cpp AccesoArchivo.cpp Acceso.cpp InformesMenu.cpp InformesManager.cpp ConfiguracionMenu.cpp ConfiguracionManager.cpp -Wall -std=c++11
if %errorlevel% == 0 (
    echo OK - Ejecutable: musica_demo.exe
) else (
    echo ERROR de compilacion
)
pause
