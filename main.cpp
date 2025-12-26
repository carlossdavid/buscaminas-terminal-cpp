#include "encabezados/funciones.h"

int main () {
    // Configuracion de la consola
    // Establecer codificacion UTF8 para caracteres especiales
    // Limpiar y ocultar cursor
    SetConsoleOutputCP(CP_UTF8);
    rlutil::cls();
    rlutil::hidecursor(); 
     
    // Inicializacion de configuraciones del juego
    tConfig config;     

    // Desplejar menu principal 
    int seleccion;

    do {
        seleccion = menuPrincipal();
        rlutil::cls();

        switch (seleccion)
        {
        case 0: 
            iniciarJuego(config);
            break;        
        case 1:
            menuDificultad(config);
            break;
        case 2: 
            mostrarPuntajes();
            break;
        }
        rlutil::cls();
    }while (seleccion != 3);
        
        
    return 0;
}