#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

TicTacToe::TicTacToe() {
	srand(time(0));
	inicializarTablero();
	jugadorActual = 'X'; // Jugador humano es 'X'
	juegoTerminado = false;
}

void TicTacToe::inicializarTablero() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			tablero[i][j] = ' ';
		}
	}
}

void TicTacToe::mostrarTablero() {
	cout << "\n  0   1   2" << endl;
	for(int i = 0; i < 3; i++) {
		cout << i << " ";
		for(int j = 0; j < 3; j++) {
			cout << tablero[i][j];
			if(j < 2) cout << " | ";
		}
		cout << endl;
		if(i < 2) cout << "  ---------" << endl;
	}
	cout << endl;
}

bool TicTacToe::hacerMovimiento(int fila, int columna) {
	if(fila < 0 || fila > 2 || columna < 0 || columna > 2) {
		return false;
	}
	if(tablero[fila][columna] != ' ') {
		return false;
	}
	tablero[fila][columna] = jugadorActual;
	return true;
}

bool TicTacToe::verificarGanador() {
	// Verificar filas
	for(int i = 0; i < 3; i++) {
		if(tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
			return true;
		}
	}
	
	// Verificar columnas
	for(int i = 0; i < 3; i++) {
		if(tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) {
			return true;
		}
	}
	
	// Verificar diagonales
	if(tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
		return true;
	}
	if(tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
		return true;
	}
	
	return false;
}

bool TicTacToe::verificarEmpate() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(tablero[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

void TicTacToe::cambiarJugador() {
	jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
}

void TicTacToe::movimientoComputadora() {
	// 1. Primero: Intentar ganar (buscar movimiento que haga ganar a 'O')
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(tablero[i][j] == ' ') {
				tablero[i][j] = 'O';
				if(verificarGanador()) {
					return;
				}
				tablero[i][j] = ' ';
			}
		}
	}
	
	// 2. Segundo: Intentar bloquear (buscar movimiento que evitaría que 'X' gane)
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(tablero[i][j] == ' ') {
				tablero[i][j] = 'X';
				if(verificarGanador()) {
					tablero[i][j] = 'O'; // Bloquear colocando 'O' aquí
					return;
				}
				tablero[i][j] = ' ';
			}
		}
	}
	
	// 3. Tercero: Tomar el centro si está disponible
	if(tablero[1][1] == ' ') {
		tablero[1][1] = 'O';
		return;
	}
	
	// 4. Cuarto: Tomar una esquina si está disponible
	int esquinas[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
	for(int k = 0; k < 4; k++) {
		int i = esquinas[k][0];
		int j = esquinas[k][1];
		if(tablero[i][j] == ' ') {
			tablero[i][j] = 'O';
			return;
		}
	}
	
	// 5. Quinto: Tomar cualquier posición disponible (movimiento aleatorio)
	int fila, columna;
	do {
		fila = rand() % 3;
		columna = rand() % 3;
	} while(tablero[fila][columna] != ' ');
	
	tablero[fila][columna] = 'O';
}

void TicTacToe::jugar(Jugador*& jugador) {
	cout << "=== TRES EN RAYA ===" << endl;
	cout << "Premio: si ganas +30 puntos, si pierdes -15 puntos" << endl;
	cout << "Tu eres 'X', la computadora es 'O'" << endl;
	
	// Mostrar tablero inicial vacío
	mostrarTablero();
	
	while(!juegoTerminado) {
		
		
		if(jugadorActual == 'X') {
			// Turno del jugador humano
			int fila, columna;
			cout << "Tu turno (X) \n";
			fila = Utilidades::in_int("ingrese la fila: ");
			columna = Utilidades::in_int("ingrese la columna: ");
			
			if(!hacerMovimiento(fila, columna)) {
				cout << "\nMovimiento invalido. Intenta de nuevo." << endl;
				continue;
			}
			
			// Verificar si el jugador ganó después de su movimiento
			if(verificarGanador()) {
				mostrarTablero();
				cout << "\n¡Felicidades! ¡Has ganado! +30 puntos\n" << endl;
				jugador->aumentarPuntos(30);
				juegoTerminado = true;
				break;
			}
			
			// Verificar empate después del movimiento del jugador
			if(verificarEmpate()) {
				mostrarTablero();
				cout << "\n¡Empate! No hay cambios en los puntos.\n" << endl;
				juegoTerminado = true;
				break;
			}
			
			cambiarJugador();
			
		} else {
			// Turno de la computadora
			cout << "\n\nTurno de la computadora (O)..." << endl;
			movimientoComputadora();
			
			// Mostrar tablero después del movimiento de la computadora
			mostrarTablero();
			
			// Verificar si la computadora ganó
			if(verificarGanador()) {
				cout << "¡La computadora gana! -15 puntos\n" << endl;
				jugador->restarPuntos(15);
				juegoTerminado = true;
				break;
			}
			
			// Verificar empate después del movimiento de la computadora
			if(verificarEmpate()) {
				cout << "¡Empate! Vuelve a intentarlo" << endl;
				juegoTerminado = true;
				break;
			}
			
			cambiarJugador();
		}
	}
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
}
