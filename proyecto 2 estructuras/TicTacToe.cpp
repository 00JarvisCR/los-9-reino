#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

TicTacToe::TicTacToe() {
	srand(time(0));
	jugadorActual = 'X'; // Jugador humano es 'X'
}

void TicTacToe::inicializarTablero() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			tablero[i][j] = ' ';
		}
	}
}

void TicTacToe::mostrarTablero() {
	cout << "\n  1   2   3" << endl;
	for(int i = 0; i < 3; i++) {
		cout << i+1 << " ";
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
	// Convertir de 1-3 a 0-2 para el array interno
	fila--;
	columna--;
	
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
	cout << "Las posiciones van del 1 al 3" << endl;
	
	bool juegoCompleto = false;
	
	while(!juegoCompleto) {
		// Reiniciar el juego para cada partida
		inicializarTablero();
		jugadorActual = 'X';
		bool juegoTerminado = false;
		
		cout << "\n--- NUEVA PARTIDA ---" << endl;
		mostrarTablero();
		
		while(!juegoTerminado) {
			if(jugadorActual == 'X') {
				// Turno del jugador humano
				int fila, columna;
				cout << "Tu turno (X) \n";
				fila = Utilidades::in_int("ingrese la fila (1-3): ");
				columna = Utilidades::in_int("ingrese la columna (1-3): ");
				
				// Validar entrada
				if(fila < 1 || fila > 3 || columna < 1 || columna > 3) {
					cout << "\nPosición inválida. Usa números del 1 al 3." << endl;
					continue;
				}
				
				if(!hacerMovimiento(fila, columna)) {
					cout << "\nCasilla ocupada. Intenta de nuevo." << endl;
					continue;
				}
				
				// Verificar si el jugador ganó después de su movimiento
				if(verificarGanador()) {
					mostrarTablero();
					cout << "\nFelicidades! Has ganado! +30 puntos\n" << endl;
					jugador->aumentarPuntos(30);
					juegoTerminado = true;
					juegoCompleto = true;
					break;
				}
				
				// Verificar empate después del movimiento del jugador
				if(verificarEmpate()) {
					mostrarTablero();
					cout << "\nEmpate! Se reinicia el juego.\n" << endl;
					juegoTerminado = true;
					break; // Sale del juego actual pero no del bucle principal
				}
				
				cambiarJugador();
				
			} else {
				// Turno de la computadora
				cout << "\nTurno de la computadora (O)..." << endl;
				movimientoComputadora();
				
				// Mostrar tablero después del movimiento de la computadora
				mostrarTablero();
				
				// Verificar si la computadora ganó
				if(verificarGanador()) {
					cout << "La computadora gana! -15 puntos\n" << endl;
					jugador->restarPuntos(15);
					
					int vidas = jugador->get_vidas();
					vidas -= 1;
					jugador->set_vidas(vidas);
					
					juegoTerminado = true;
					juegoCompleto = true;
					break;
				}
				
				// Verificar empate después del movimiento de la computadora
				if(verificarEmpate()) {
					cout << "Empate! Se reinicia el juego." << endl;
					juegoTerminado = true;
					break; // Sale del juego actual pero no del bucle principal
				}
				
				cambiarJugador();
			}
		}
	}
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
	cout << "Vidas restantes: " << jugador->get_vidas() << endl;
}
