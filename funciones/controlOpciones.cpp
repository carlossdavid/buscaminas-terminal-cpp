#include "../encabezados/funciones.h"

// Desplegar un menu 
int desplegarMenu(string archivo, int inicioX, int inicioY, string listaOpciones[], int numeroOpciones, int opcion_size) {
    bool salir = false;
    int op;

    tcursor cursorPos; cursorPos.y = 0; cursorPos.x = 0;

    // Dibujar
    imprimirArchivoRapido(archivo);
    
    
    // loop main 
    do {
        // Redibujar cursor
        rlutil::locate(inicioX+cursorPos.x, inicioY+cursorPos.y); 
        
        cout << "»" << "  ";

        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        cout << setw(opcion_size) << left << listaOpciones[cursorPos.y];

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        // Controlar 
        switch(rlutil::getkey()) 
        {
        case ARRIBA: // UP
            // Borrar cursor anterior
            rlutil::locate(inicioX, inicioY+cursorPos.y); 
            cout << "  " << setw(opcion_size + 1) << left  << listaOpciones[cursorPos.y]; 

            cursorPos.y--;
            if (cursorPos.y < 0) cursorPos.y = 0;
            break;

        case ABAJO: // DOWN 
            // Borrar cursor anterior
            rlutil::locate(inicioX, inicioY+cursorPos.y); 
            cout << "  " << setw(opcion_size + 1 ) << left << listaOpciones[cursorPos.y]; 
            
            cursorPos.y++;
            if (cursorPos.y > numeroOpciones-1) cursorPos.y = numeroOpciones-1; 
            break;

        case ENTER: // ENTER
            op = cursorPos.y;
            salir = true; 
            break; 
        }
    } while (!salir);
    return op; 
}

int menuPrincipal () {
    string archivo = "src/menuPrincipal.txt"; 
    int inicioX = 19, inicioY = 23;
    int opcion_size = 14; 
    string listaOpciones[4] = {
        "JUGAR", 
        "DIFICULTAD", 
        "PUNTAJES",
        "SALIR"
    };
    int op = desplegarMenu(archivo, inicioX, inicioY, listaOpciones, 4, opcion_size);
    return op; 
}

void menuDificultad (tConfig& config) {
    string archivo = "src/menuDificultad.txt"; 
    int inicioX = 1, inicioY = 12;
    int opcion_size = 47; 
    int nOpciones = 5;
    string listaOpciones[nOpciones] = {
        "Si tocas una mina ganas: 5 x 5 y 3 minas",  
        "Principiante: 8 x 8 y 10 minas",
        "Intermedio: 16 x 16 y 40 minas",
        "Experto: 16 x 30 y 70 minas", 
        "Vidente: 30 x 30 y 130 mina",
    } ;

    int op; 
    rlutil::cls();
    op = desplegarMenu(archivo, inicioX, inicioY, listaOpciones, nOpciones, opcion_size);

    switch (op)
    {
    case 0:
        config.filas = 5;
        config.columnas = 5; 
        config.minas = 3;
        config.dificultad = 1;
        break;
    case 1:
        config.filas = 8;
        config.columnas = 8; 
        config.minas = 10;
        config.dificultad = 2;
        break;
    case 2:
        config.filas = 16;
        config.columnas = 16; 
        config.minas = 40;
        config.dificultad = 3;
        break;
    case 3:
        config.filas = 16;
        config.columnas = 30; 
        config.minas = 99;
        config.dificultad = 4;
        break;
    case 4: 
        config.filas = 30;
        config.columnas = 30; 
        config.minas = 130;
        config.dificultad = 7;
        break;
    }
}

void menuPerder (tConfig config, vector<vector<tCelda>>& tablero) {
    string archivo = "src/menuPerder.txt"; 
    int inicioX = 31 , inicioY = 12;
    int opcion_size = 16; 
    int nOpciones = 3;
    string listaOpciones[nOpciones] = {
        "JUGAR DE NUEVO",
        "VER TABLERO",
        "SALIR"
    };
    int op = desplegarMenu(archivo, inicioX, inicioY, listaOpciones, nOpciones, opcion_size);

    if (op == 0) iniciarJuego(config); 
    if (op == 1) {
        rlutil::cls(); 
        imprimirTablero(config, tablero);
        rlutil::anykey();
    }
}

void menuGanar(int movimientos, int dificultad) {
    
    string archivo = "src/menuGanar.txt";
    rlutil::cls(); 
    rlutil::locate(1,1);
    imprimirArchivoRapido(archivo);
    int posX = 0; 
    int flag = true; 
    int tecla; 
    string nombre; 
    rlutil::showcursor();
    
    rlutil::locate(46, 12); 
    cout << setw(3) << movimientos; 

    while (flag) {
        rlutil::locate(41 + posX, 14 );
        tecla = rlutil::getkey();
        switch (tecla) {
        case rlutil::KEY_BACKSPACE: // BACKSPACE
            if (posX>0) {
                if (nombre.length() <= 4) {
                    posX -= 2; 
                    rlutil::locate(41 + posX, 14);
                }
                cout << "_";    
                nombre.pop_back();
            }
            break;
        case rlutil::KEY_ENTER: // ENTER 
            // Se verifica si el nombre no está vació 
            if (nombre.size() > 0) {
                flag = false;
                // Se guarda el score y el nombre en el log del juego
                guardarPuntaje(nombre, movimientos, dificultad);
            }

            
            break; 
        default:
            if (isprint(tecla)) {
                cout << (char) toupper(tecla);
                if (posX < 8) {
                    posX+=2; 
                } else {
                    nombre = nombre.substr(0, 4); 
                }
                nombre += (char)toupper(tecla);
            }
            break;
        }
    }

    rlutil::hidecursor();
}

