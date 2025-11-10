#include "Sudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilidades.h"

using namespace std;

Sudoku::Sudoku() {
	srand(time(0));
}

void Sudoku::inicializarTablero() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			tablero[i][j] = 0;
			tableroResuelto[i][j] = 0;
			celdasFijas[i][j] = false;
		}
	}
}

bool Sudoku::verificarFila(int fila, int numero) {
	for(int j = 0; j < 4; j++) {
		if(tablero[fila][j] == numero) {
			return false;
		}
	}
	return true;
}

bool Sudoku::verificarColumna(int columna, int numero) {
	for(int i = 0; i < 4; i++) {
		if(tablero[i][columna] == numero) {
			return false;
		}
	}
	return true;
}

bool Sudoku::verificarSubcuadrante(int filaInicio, int columnaInicio, int numero) {
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			if(tablero[filaInicio + i][columnaInicio + j] == numero) {
				return false;
			}
		}
	}
	return true;
}

bool Sudoku::esNumeroValido(int fila, int columna, int numero) {
	return verificarFila(fila, numero) && 
		verificarColumna(columna, numero) && 
		verificarSubcuadrante(fila - fila % 2, columna - columna % 2, numero);
}

bool Sudoku::resolverSudoku(int fila, int columna) {
	if(fila == 4) {
		return true;
	}
	
	if(columna == 4) {
		return resolverSudoku(fila + 1, 0);
	}
	
	if(tableroResuelto[fila][columna] != 0) {
		return resolverSudoku(fila, columna + 1);
	}
	
	for(int numero = 1; numero <= 4; numero++) {
		if(esNumeroValido(fila, columna, numero)) {
			tableroResuelto[fila][columna] = numero;
			
			if(resolverSudoku(fila, columna + 1)) {
				return true;
			}
			
			tableroResuelto[fila][columna] = 0;
		}
	}
	return false;
}

void Sudoku::generarPuzzle() {
	inicializarTablero();
	
	// Crear un tablero base valido
	int base[4][4] = {
		{1, 2, 3, 4},
	{3, 4, 1, 2},
		{2, 1, 4, 3},
	{4, 3, 2, 1}
	};
	
	// Copiar el base al tablero resuelto
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			tableroResuelto[i][j] = base[i][j];
		}
	}
	
	// Mezclar el tablero con algunos intercambios
	for(int k = 0; k < 10; k++) {
		int op = rand() % 3;
		if(op == 0) {
			// Intercambiar dos filas en el mismo bloque
			int bloque = rand() % 2;
			int fila1 = bloque * 2;
			int fila2 = fila1 + 1;
			for(int j = 0; j < 4; j++) {
				swap(tableroResuelto[fila1][j], tableroResuelto[fila2][j]);
			}
		} else if(op == 1) {
			// Intercambiar dos columnas en el mismo bloque
			int bloque = rand() % 2;
			int col1 = bloque * 2;
			int col2 = col1 + 1;
			for(int i = 0; i < 4; i++) {
				swap(tableroResuelto[i][col1], tableroResuelto[i][col2]);
			}
		}
	}
	
	// Copiar el tablero resuelto al tablero de juego
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			tablero[i][j] = tableroResuelto[i][j];
		}
	}
	
	// Eliminar algunas celdas para crear el puzzle
	int celdasAEliminar = 8 + rand() % 3;
	int eliminadas = 0;
	
	while(eliminadas < celdasAEliminar) {
		int i = rand() % 4;
		int j = rand() % 4;
		
		if(tablero[i][j] != 0) {
			tablero[i][j] = 0;
			celdasFijas[i][j] = false;
			eliminadas++;
		}
	}
	
	// Marcar las celdas restantes como fijas
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(tablero[i][j] != 0) {
				celdasFijas[i][j] = true;
			}
		}
	}
}

void Sudoku::mostrarTablero() {
	cout << "\n   SUDOKU 4x4\n";
	cout << "    1   2   3   4\n";
	cout << "  +---+---+---+---+\n";
	
	for(int i = 0; i < 4; i++) {
		cout << i+1 << " | ";
		for(int j = 0; j < 4; j++) {
			if(tablero[i][j] == 0) {
				cout << " ";
			} else {
				cout << tablero[i][j];
			}
			
			if(j < 3) cout << " | ";
		}
		cout << " |\n";
		
		if(i < 3) {
			cout << "  +---+---+---+---+\n";
		}
	}
	cout << "  +---+---+---+---+\n\n";
}

bool Sudoku::verificarVictoria() {
	// Verificar que todas las celdas esten llenas
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(tablero[i][j] == 0) {
				return false;
			}
		}
	}
	
	// Verificar filas
	for(int i = 0; i < 4; i++) {
		bool numeros[5] = {false};
		for(int j = 0; j < 4; j++) {
			int num = tablero[i][j];
			if(num < 1 || num > 4 || numeros[num]) {
				return false;
			}
			numeros[num] = true;
		}
	}
	
	// Verificar columnas
	for(int j = 0; j < 4; j++) {
		bool numeros[5] = {false};
		for(int i = 0; i < 4; i++) {
			int num = tablero[i][j];
			if(num < 1 || num > 4 || numeros[num]) {
				return false;
			}
			numeros[num] = true;
		}
	}
	
	// Verificar subcuadrantes 2x2
	for(int bloqueFila = 0; bloqueFila < 4; bloqueFila += 2) {
		for(int bloqueColumna = 0; bloqueColumna < 4; bloqueColumna += 2) {
			bool numeros[5] = {false};
			for(int i = bloqueFila; i < bloqueFila + 2; i++) {
				for(int j = bloqueColumna; j < bloqueColumna + 2; j++) {
					int num = tablero[i][j];
					if(num < 1 || num > 4 || numeros[num]) {
						return false;
					}
					numeros[num] = true;
				}
			}
		}
	}
	
	return true;
}

void Sudoku::jugar(Jugador*& jugador) {
	cout << "=== SUDOKU 4x4 ===" << endl;
	cout << "Premio: si ganas +40 puntos, si pierdes -20 puntos" << endl;
	cout << "Reglas: Completa el tablero con numeros del 1 al 4" << endl;
	cout << "        Sin repetir en filas, columnas o cuadrantes 2x2" << endl;
	cout << "        Las celdas iniciales no se pueden modificar" << endl;
	
	bool juegoCompleto = false;
	
	while(!juegoCompleto) {
		generarPuzzle();
		bool juegoTerminado = false;
		int intentos = 3;
		
		cout << "\n--- NUEVO PUZZLE ---" << endl;
		cout << "Oportunidades de fallar: " << intentos << endl;
		
		int vidas;
		
		while(!juegoTerminado && intentos > 0) {
			mostrarTablero();
			
			cout << "Opciones:" << endl;
			cout << "1. Colocar numero" << endl;
			cout << "2. Verificar solucion" << endl;
			cout << "3. Rendirse" << endl;
			
			int opcion = Utilidades::in_int("Selecciona una opcion: ");
			cout << endl;
			
			
			
			switch(opcion) {
			case 1: {
				int fila = Utilidades::in_int("Fila (1-4): ");
				int columna = Utilidades::in_int("Columna (1-4): ");
				int numero = Utilidades::in_int("Numero (1-4): ");
				
				if(fila < 1 || fila > 4 || columna < 1 || columna > 4 || numero < 1 || numero > 4) {
					cout << "\nEntrada invalida. Usa numeros del 1 al 4." << endl;
					continue;
				}
				
				fila--;
				columna--;
				
				if(celdasFijas[fila][columna]) {
					cout << "Esta celda es fija y no se puede modificar." << endl;
					continue;
				}
				
				if(!esNumeroValido(fila, columna, numero)) {
					cout << "\nNumero invalido! Se repite en fila, columna o cuadrante." << endl;
					intentos--;
					cout << "Intentos restantes: " << intentos << endl;
					if(intentos == 0) {
						cout << "\nHas perdido! -20 puntos" << endl;
						jugador->restarPuntos(20);
						vidas = jugador->get_vidas();
						vidas -= 1;
						jugador->set_vidas(vidas);
						juegoTerminado = true;
						juegoCompleto = true;
					}
				} else {
					tablero[fila][columna] = numero;
					cout << "\nNumero colocado correctamente." << endl;
				}
				break;
			}
			case 2: {
				if(verificarVictoria()) {
					cout << "\nFelicidades! Has resuelto el Sudoku! +40 puntos" << endl;
					jugador->aumentarPuntos(40);
					juegoTerminado = true;
					juegoCompleto = true;
				} else {
					cout << "El tablero no esta completo o tiene errores." << endl;
				}
				break;
			}
			case 3: {
				cout << "\nTe has rendido. -20 puntos" << endl;
				jugador->restarPuntos(20);
				vidas = jugador->get_vidas();
				vidas -= 1;
				jugador->set_vidas(vidas);
				juegoTerminado = true;
				juegoCompleto = true;
				break;
			}
			default:
				cout << "Opcion invalida." << endl;
			}
		}
		
		if(intentos == 0 && !juegoCompleto) {
			cout << "\nHas perdido! -20 puntos" << endl;
			jugador->restarPuntos(20);
			vidas = jugador->get_vidas();
			vidas -= 1;
			jugador->set_vidas(vidas);
			juegoCompleto = true;
		}
	}
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
	cout << "Vidas restantes: " << jugador->get_vidas() << endl;
}
