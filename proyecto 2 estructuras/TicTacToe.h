#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Jugador.h"
#include "Utilidades.h"

class TicTacToe {
private:
	char tablero[3][3];
	char jugadorActual;
	bool juegoTerminado;
	
	void inicializarTablero();
	void mostrarTablero();
	bool hacerMovimiento(int fila, int columna);
	bool verificarGanador();
	bool verificarEmpate();
	void cambiarJugador();
	void movimientoComputadora();
	
public:
	TicTacToe();
	void jugar(Jugador*& jugador);
};

#endif
