#pragma once
#include "definiciones.h"

// --- GAME --- //  
bool casillaValida(const tConfig config, int fila, int columna);
void crear_minas(tConfig config, vector<vector<tCelda>>& tablero, int minas);
bool desvelarCasillas (const tConfig config, int fila, int columna, vector<vector<tCelda>>& t);
void evitarPrimeraMina (tConfig config, vector<vector<tCelda>>& t, tplayerCursor p);
void revelarMinas( vector<vector<tCelda>>& t, tConfig config);
bool verificarVictoria(tConfig config, vector<vector<tCelda>>& t);
void iniciarJuego(tConfig config); 



// --- CONTROL DE OPCIONES --- //
int menuPrincipal();
int desplegarMenu(string archivo, int inicioX, int inicioY, string listaOpciones[], int numeroOpciones,  int opcion_size);
void menuDificultad (tConfig& config);
void menuPerder (const tConfig config,  vector<vector<tCelda>>& tablero);
void menuGanar(int movimientos, int dificultad);

// --- IMPRIMIR --- //
void imprimirTablero(tConfig config, vector<vector<tCelda>>& tablero); 
void imprimirCelda(tCelda celda, int x, int y);
int convertirX (int x);
int convertirY (int y);
void moverCursor(vector<vector<tCelda>>& tablero, tplayerCursor& cursor, int nuevaFila, int nuevaColumna);

// --- MANEJO DE ARCHIVOS --- //
void guardarPuntaje(string nombre, int movimientos, int dificultad); 
void imprimirArchivoRapido(string nombre_archivo); 
void mostrarPuntajes();