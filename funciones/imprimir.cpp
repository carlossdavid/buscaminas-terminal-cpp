#include "../encabezados/funciones.h"

int convertirX (int x) {
    return inicioX + 1 + (x*3);
}

int convertirY (int y) {
    return inicioY + 1 + y; 
}

void moverCursor(vector<vector<tCelda>>& tablero, tplayerCursor& cursor, int nuevaFila, int nuevaColumna) {
    // APAGAR CELDA ACTUAL 
    tablero[cursor.fila][cursor.columna].activa = false;
    imprimirCelda(tablero[cursor.fila][cursor.columna], 
                  convertirX(cursor.columna), convertirY(cursor.fila));

    // ACTUALIZAR CELDA 
    cursor.fila = nuevaFila;
    cursor.columna = nuevaColumna;

    // ENCENDER NUEVO CURSOR
    tablero[cursor.fila][cursor.columna].activa = true;
    imprimirCelda(tablero[cursor.fila][cursor.columna], convertirX(cursor.columna), convertirY(cursor.fila));
}


void imprimirTablero(tConfig config, vector<vector<tCelda>>& tablero) {

    int ancho_mapa = (config.columnas* 3) + 2;
    int alto_mapa = config.filas + 2;
    int finX = ancho_mapa + inicioX - 1, finY = alto_mapa + inicioY - 1;  

    // --- CONTADOR DE MINAS RESTANTES --- 
    rlutil::locate(1,1); 
    cout << "Controles: Poner Bandera [F] Revelar Casilla [ENTER] Salir [S]" << endl;
    cout << "MINAS RESTANTES: "<< setw(3) << config.minas; 

    // --- Imprimir los límites del tablero --- ///
    // Lineas superior e inferior horizontales 
    for (int i = inicioX; i < finX; i++) {
        rlutil::locate(i, inicioY); cout << "═";
        rlutil::locate(i, finY); cout << "═";
    }
    // Lineas laterales
    for (int i = inicioY; i < finY; i++) {
        rlutil::locate(inicioX, i); cout << "║";
        rlutil::locate(finX, i); cout << "║";
    }
    // Esquinas 
    rlutil::locate(inicioX, inicioY); cout << "╔";
    rlutil::locate(finX, inicioY); cout << "╗";
    rlutil::locate(inicioX, finY); cout << "╚";
    rlutil::locate(finX, finY); cout << "╝";

    // CELDAS 
    int x = 0, y = inicioY+1, k = 0; 

    for (const auto& row : tablero) { 
        for (const auto& celda : row ) {
            x = inicioX + 1 + (k*3);
            imprimirCelda(celda, x, y);    
            k++; 
        }
        y++; k = 0;  
    }

}

void imprimirCelda(tCelda celda, int x, int y) {
    rlutil::locate(x, y);
    
    if (celda.activa) {
        rlutil::setBackgroundColor(rlutil::CYAN);
        rlutil::setColor(rlutil::WHITE);
    } else if (celda.bandera) {
        rlutil::setBackgroundColor(rlutil::YELLOW);
        rlutil::setColor(rlutil::RED);
    } else if (!celda.despejada) {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::WHITE);
    } else if (celda.estado == MINA) {
        rlutil::setBackgroundColor(rlutil::RED);
        rlutil::setColor(rlutil::WHITE);
    } else if(celda.minasAlrededor != 0) {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::BLUE);
    }  else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }

    // IMPRIMIR CONTENIDO 
    if (celda.bandera) {
        cout << "|>";
    } else if (!celda.despejada) {
        cout<<"░░"; 
    } else if (celda.estado == MINA) {
        cout << "**";
    } else if (celda.minasAlrededor > 0) {
        cout << " " << celda.minasAlrededor; 
    } else {
        cout << "__"; 
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    cout<< "|"; 

}
