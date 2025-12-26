#pragma once
/// LIBRERIAS ///
#include <iostream>
#include <iomanip> // dar formato al output (ej. setw(), setfill())
#include <string> // utilizar strings
#include <random> // crear numeros random
#include <vector> // crear vectores
#include <fstream> // manejo de archivos
#include "rlutil.h" // manejo de interfaz 

using namespace std;

// --- CONSTANTES ---
const int inicioX = 1, inicioY = 3;

// --- ESTRUCTURAS GLOBALES ---
// Valor de las Casillas 
enum CASILLAS {
    VACIO,
    MINA 
};

enum CONTROLES {
    SALIR       = 0, // ESC
    ENTER       = 1, // ENTER
	BACKSPACE   = 8, // BACKSCAPE

	ARRIBA      = 14, // FLECHA DE ARRIBA
    ABAJO       = 15, // FLECHA DE ABAJO
	IZQUIERDA   = 16, // FLECHA DE IZQUIERDA
	DERECHA     = 17, // FLECHA DE DERECHA 

    KEY_BANDERA = 102, // LETRA f  
    KEY_BANDERA_MAYUS = KEY_BANDERA - 32 // LETRA F 
};

typedef struct {
    int fila = 0;
    int columna = 0;
    bool primeraIteracion = true; 
    int minas_restantes;
    int movimientos = 0; 
} tplayerCursor;

typedef struct {
    int filas = 8;
    int columnas = 8;
    int minas = 1; 
    int dificultad = 2; 
} tConfig;

typedef struct {
    CASILLAS estado = VACIO;
    int minasAlrededor = 0;  
    bool bandera = false; 
    bool despejada = false; 
    bool activa = false; 
} tCelda; 

typedef struct {
    int y;
    int x; 
} tcursor;

