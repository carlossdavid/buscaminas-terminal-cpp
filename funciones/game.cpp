#include "../encabezados/funciones.h"

// Agrega al tablero casillas con minas 
void crear_minas(tConfig config, vector<vector<tCelda>>& tablero, int minas) {
    // Colocar minas aleatoriamente en la matriz de minas
    int contador_minas = 0;
    while (true)
    {
        int fila_aleatoria = rand() % config.filas;
        int columna_aleatoria = rand() % config.columnas;
        // Poner mina en la matriz de minas
        if (tablero[fila_aleatoria][columna_aleatoria].estado == VACIO){
            tablero[fila_aleatoria][columna_aleatoria].estado = MINA;
            contador_minas++;

            // Ir creando pistas 
            for (int i = -1; i<=1; i++) {
                for (int j = -1; j<=1; j++) {
                    if (j==0 && i==0) continue;
                    int filaTmp = fila_aleatoria + j;
                    int colTmp = columna_aleatoria + i; 

                    if (filaTmp >=0 && filaTmp < config.filas && colTmp >=0 && colTmp < config.columnas){
                        tablero[filaTmp][colTmp].minasAlrededor++;
                    }
                }
            }
        }

        if (contador_minas >= minas){ 
            break;
        }
    }
}

void evitarPrimeraMina (tConfig config, vector<vector<tCelda>>& t, tplayerCursor p) {
    // Si la primera seleccion se reubica 
    if (t[p.fila][p.columna].estado == MINA) {
        bool reubicada = false; 
        // QUITAMOS LA MINA DE LA SELECCION 
        t[p.fila][p.columna].estado = VACIO;
        // Actualizamos pistas
        for (int i = -1; i<=1; i++) {
            for (int j = -1; j <= 1; j++)
            {
                if (j == 0 && i == 0) {
                    continue;
                }

                int filaTmp = p.fila + j;
                int colTmp = p.columna+ i;

                if (casillaValida(config, filaTmp, colTmp))
                {
                    t[filaTmp][colTmp].minasAlrededor--;

                }
            }
        }

        // Se busca la primera casilla libre para poner una mina, que no sea la casilla seleccionada 
        for (int f = 0; f < config.filas && !reubicada; f++) {
            for (int c = 0; c < config.columnas && !reubicada; c++) {
                if ( (f != p.fila || c != p.columna) && t[f][c].estado != MINA) {
                    t[f][c].estado = MINA;
                    t[f][c].minasAlrededor = 0;
                    
                    // Actualizamos Pistas
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            if (j == 0 && i == 0) {
                                continue;
                            }
                            int filaTmp = f + j;
                            int colTmp = c + i;

                            if (filaTmp >= 0 && filaTmp < config.filas && colTmp >= 0 && colTmp < config.columnas)
                            {
                                t[filaTmp][colTmp].minasAlrededor++;
                            }
                        }
                    }
                    reubicada = true;
                }
            }
        }
    } 
}

void revelarMinas( vector<vector<tCelda>>& t, tConfig config) {
    for (int f = 0; f < config.filas; f++) {
        for (int c = 0; c < config.columnas; c++) {
            if (t[f][c].estado == MINA) {
                t[f][c].despejada = true;
                imprimirCelda(t[f][c], convertirX(c), convertirY(f));
                rlutil::msleep(50); 
            }
        }
    }
    rlutil::msleep(800);
}

bool desvelarCasillas (const tConfig config, int fila, int columna, vector<vector<tCelda>>& t) {

    // VALIDADOR DE LIMITES Y EVITAR REDUNDANCIAS (volver a despejar celdas que ya fueron despejadas)
    if (!casillaValida(config, fila, columna) || t[fila][columna].despejada ) {
        return false; 
    } 
    
    if (t[fila][columna].estado == MINA){
        revelarMinas(t, config); 
        return true;
    }

    // Despejar celda actual 
    t[fila][columna].despejada = true;
    imprimirCelda(t[fila][columna], convertirX(columna), convertirY(fila));
    if ( t[fila][columna].minasAlrededor == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++){
                if (!(i== 0 && j==0)) desvelarCasillas(config, fila + i, columna + j, t);
            }
        }
    }

    return false; 
}

bool casillaValida(const tConfig config, int fila, int columna) {
    return fila >= 0 && fila < config.filas && columna >= 0 && columna < config.columnas;
}

bool verificarVictoria(tConfig config, vector<vector<tCelda>>& t) {
    
    int casillasDeveladas = 0;
    int totalCeldas = config.columnas*config.filas; 
    for (auto& row: t) {
        for (auto& c: row) {
            if(c.despejada) casillasDeveladas++; 
        }
    }
    if (casillasDeveladas == totalCeldas-config.minas) {
        return true; 
    }

    return false; 
}


// Gestiona la lógica principal del juego 
void iniciarJuego(tConfig config) {
    rlutil::cls();
    // Iniciar semilla para crear numeros aleatorios 
    srand(time(NULL));
    
    // Crear cursor del jugador 
    tplayerCursor playerCursor; 
    playerCursor.minas_restantes = config.minas;

    // Iniciar Parametros del juego 
    bool gameOver = false; 

    // Crear tablero con vector bidimensional
    // Como vector es un objeto se utiliza su constructor para incializar todos los valores de tipo tCelda
    // El prototipo utilizado es vector1<vector2<tipo>> nombre(tamaño1, vector2(tamaño2, contenido) )
    // Se crea un vector de tamaño filas, cada fila contiene un vector de tamaño columnas, cada columna contiene un tCelda por defecto. 
    tCelda porDefecto;
    vector<vector<tCelda>> tablero(config.filas, vector<tCelda>(config.columnas, porDefecto)); 

    /// CREAR MINAS 
    crear_minas(config, tablero, config.minas);
    
    // Posicionar el cursor en su posicion inicial 
    tablero[playerCursor.columna][playerCursor.fila].activa = true; 

    /// Imprimir tablero
    imprimirTablero(config, tablero);

    // BUCLE PRINCPAL DEL JUEGO 
    while (!gameOver) {
        tCelda& celdaActual =tablero[playerCursor.fila][playerCursor.columna];  
        switch(rlutil::getkey()) {
        case ARRIBA:
            if (playerCursor.fila > 0) moverCursor(tablero, playerCursor, playerCursor.fila - 1, playerCursor.columna);
            break;
        case ABAJO: 
            if (playerCursor.fila < config.filas - 1) moverCursor(tablero, playerCursor, playerCursor.fila + 1, playerCursor.columna);
            break;
        case IZQUIERDA:
            if (playerCursor.columna > 0) moverCursor(tablero, playerCursor, playerCursor.fila, playerCursor.columna-1);
            break;
        case DERECHA:
            if (playerCursor.columna < config.columnas - 1) moverCursor(tablero, playerCursor, playerCursor.fila, playerCursor.columna+1);
            break; 
        case KEY_BANDERA:
        case KEY_BANDERA_MAYUS: // Es la letra puede ser mayuscula o minínscula indistintamente
            if (celdaActual.bandera) {
                celdaActual.bandera = false;
                playerCursor.minas_restantes++;
            } else if (celdaActual.despejada == false) {
                celdaActual.bandera = true;
                playerCursor.minas_restantes--;
            }
            rlutil::locate(18, 2);
            cout << setw(3) << playerCursor.minas_restantes; 
            imprimirCelda(celdaActual, convertirX(playerCursor.columna), convertirY(playerCursor.fila));
            break;
        case ENTER:
            // Evitar que una casilla con bandera sea desvelada
            if (celdaActual.bandera == false 
                 && celdaActual.despejada == false) {
                // Se agrega 1 a los movimientos del jugador para el registro del score
                playerCursor.movimientos++;

                // Evitar mina en la primera casilla seleccionada 
                if (playerCursor.primeraIteracion) {
                    playerCursor.primeraIteracion = false;
                    evitarPrimeraMina (config, tablero, playerCursor);
                }

                // Desvela las casillas y devuelve verdadero si se encuentra una mina 
                if (desvelarCasillas(config, playerCursor.fila, playerCursor.columna, tablero)) {
                    // Se termina el juego 
                    gameOver = true; 
                    // Se despliega la animacion y menu de juego terminado 
                    rlutil::cls(); 
                    menuPerder(config, tablero); 
                } else {
                    // Si la casilla no era mina se verifica en cada movimiento si el jugador ya gano 
                    if (verificarVictoria(config, tablero)) {
                        // Si el jugador gano, se finaliza el juego y se despliega el menu de ganar
                        gameOver = true; 
                        menuGanar(playerCursor.movimientos, config.dificultad); 
                    }; 
                }
            }
            break;
        case SALIR:
            gameOver = true;
            break;
        } 
    }
    rlutil::cls();
}