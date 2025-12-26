#include "../encabezados/funciones.h"

void guardarPuntaje (string nombre, int movimientos, int dificultad){

    // Abrir archivo en modo escritura sin sobreescribir el archivo (ios::app) abreviacion de append  
    ofstream archivo("./src/puntajes.csv", ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        rlutil::cls();
        cout << "ERROR ARCHIVO PUNTAJES.CSV" << endl;
        rlutil::msleep(1000); 
        return;
    }
    // Se calcula el score obtenido de acuerdo a la dificultad y los movimientos 
    double score =  (1/(double)movimientos) * dificultad * 1000;
    
    // Se añade la nueva puntuacion 
    archivo << nombre << "," << movimientos << "," << (int) score << endl; 
    
    // Cerrar el archivo
    archivo.close();
}

void mostrarPuntajes() {
    // REFRESCA PANTALLA 
    rlutil::cls();
    // Abrir archivo 
    ifstream archivo ("./src/puntajes.csv");

    if (!archivo.is_open()) {
        cout << "ERROR ARCHIVO PUNTAJES.CSV" << endl;
        rlutil::msleep(1000); 
        return;
    }

    string linea;
    // Imprimir csv con formato
    while(getline(archivo, linea)) {
        stringstream palabra(linea);
        string nombre, movimientos, score;

        getline(palabra, nombre, ',');
        getline(palabra, movimientos, ',');
        getline(palabra, score, ',');

        cout << "+" << right << setw(9) << setfill('-') ;
        cout << "+" << right << setw(14) << setfill('-'); 
        cout << "+" << right << setw(9) << setfill('-') << "+" << endl<< setfill (' ');
        cout << "|"<< left << setw(8) << nombre; 
        cout << "|"<< left << setw(13) << movimientos; 
        cout << "|" << left << setw(8) << score << "|" << endl; 
        
    }
    cout << "+" << right << setw(9) << setfill('-') ;
    cout << "+" << right << setw(14) << setfill('-'); 
    cout << "+" << right << setw(9) << setfill('-') << "+" << endl<< setfill (' ');
    archivo.close();
    cout << endl << "Presiona cualquier tecla para salir";
    rlutil::anykey();


}

void imprimirArchivoRapido(string nombre_archivo){
    ifstream archivo;
    archivo.open(nombre_archivo);

    if (archivo.is_open()) {
        cout << archivo.rdbuf();
    }
}
