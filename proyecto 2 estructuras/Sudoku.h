#ifndef SUDOKU_H
#define SUDOKU_H

#include "Jugador.h"
#include <iostream>
using namespace std;

class Sudoku {
private:
	int tablero[4][4];
	int tableroResuelto[4][4];
	bool celdasFijas[4][4];
	
	void inicializarTablero();
	void generarPuzzle();
	bool resolverSudoku(int fila, int columna);
	bool esNumeroValido(int fila, int columna, int numero);
	bool verificarFila(int fila, int numero);
	bool verificarColumna(int columna, int numero);
	bool verificarSubcuadrante(int filaInicio, int columnaInicio, int numero);
	void mostrarTablero();
	bool verificarVictoria();
	
public:
	Sudoku();
	void jugar(Jugador*& jugador);
};

#endif
