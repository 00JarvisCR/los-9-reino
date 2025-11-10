#include "Buscaminas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilidades.h"

using namespace std;

Buscaminas::Buscaminas() {
	srand(time(0));
}

void Buscaminas::inicializarTablero() {
	minasRestantes = 10;
	celdasDescubiertas = 0;
	juegoGanado = false;
	juegoPerdido = false;
	
	for(int i = 0; i < TAMANO; i++) {
		for(int j = 0; j < TAMANO; j++) {
			tablero[i][j] = ' ';
			tableroVisible[i][j] = '.';
			minas[i][j] = false;
		}
	}
}

void Buscaminas::colocarMinas(int totalMinas) {
	int minasColocadas = 0;
	while(minasColocadas < totalMinas) {
		int fila = rand() % TAMANO;
		int columna = rand() % TAMANO;
		
		if(!minas[fila][columna]) {
			minas[fila][columna] = true;
			minasColocadas++;
		}
	}
}

int Buscaminas::contarMinasAdyacentes(int fila, int columna) {
	int contador = 0;
	
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			int nuevaFila = fila + i;
			int nuevaColumna = columna + j;
			
			if(nuevaFila >= 0 && nuevaFila < TAMANO && 
			   nuevaColumna >= 0 && nuevaColumna < TAMANO) {
				if(minas[nuevaFila][nuevaColumna]) {
					contador++;
				}
			}
		}
	}
	
	return contador;
}

void Buscaminas::calcularNumeros() {
	for(int i = 0; i < TAMANO; i++) {
		for(int j = 0; j < TAMANO; j++) {
			if(!minas[i][j]) {
				int minasAdyacentes = contarMinasAdyacentes(i, j);
				if(minasAdyacentes > 0) {
					tablero[i][j] = '0' + minasAdyacentes;
				} else {
					tablero[i][j] = ' ';
				}
			} else {
				tablero[i][j] = '*';
			}
		}
	}
}

void Buscaminas::revelarCeldasVacias(int fila, int columna) {
	// Primero revelar la celda objetivo normalmente
	if(fila < 0 || fila >= TAMANO || columna < 0 || columna >= TAMANO) return;
	if(tableroVisible[fila][columna] != '.' && tableroVisible[fila][columna] != '!') return;
	if(tableroVisible[fila][columna] == '!') return;
	
	tableroVisible[fila][columna] = tablero[fila][columna];
	celdasDescubiertas++;
	
	// Luego buscar y revelar una segunda celda si es posible
	bool segundaCeldaRevelada = false;
	
	// Buscar en las celdas adyacentes primero
	for(int i = -1; i <= 1 && !segundaCeldaRevelada; i++) {
		for(int j = -1; j <= 1 && !segundaCeldaRevelada; j++) {
			if(i == 0 && j == 0) continue;
			
			int nuevaFila = fila + i;
			int nuevaColumna = columna + j;
			
			if(nuevaFila >= 0 && nuevaFila < TAMANO && 
			   nuevaColumna >= 0 && nuevaColumna < TAMANO) {
				if(tableroVisible[nuevaFila][nuevaColumna] == '.' && 
					!minas[nuevaFila][nuevaColumna]) {
					tableroVisible[nuevaFila][nuevaColumna] = tablero[nuevaFila][nuevaColumna];
					celdasDescubiertas++;
					segundaCeldaRevelada = true;
				}
			}
		}
	}
	
	// Si no encontramos en las adyacentes, buscar en cualquier parte del tablero
	if(!segundaCeldaRevelada) {
		for(int i = 0; i < TAMANO && !segundaCeldaRevelada; i++) {
			for(int j = 0; j < TAMANO && !segundaCeldaRevelada; j++) {
				if(tableroVisible[i][j] == '.' && !minas[i][j] && 
					(i != fila || j != columna)) {
					tableroVisible[i][j] = tablero[i][j];
					celdasDescubiertas++;
					segundaCeldaRevelada = true;
				}
			}
		}
	}
	
	// Si la celda original era vacia, seguir revelando normalmente
	if(tablero[fila][columna] == ' ') {
		for(int i = -1; i <= 1; i++) {
			for(int j = -1; j <= 1; j++) {
				if(i == 0 && j == 0) continue;
				int nuevaFila = fila + i;
				int nuevaColumna = columna + j;
				if(nuevaFila >= 0 && nuevaFila < TAMANO && 
				   nuevaColumna >= 0 && nuevaColumna < TAMANO) {
					if(tableroVisible[nuevaFila][nuevaColumna] == '.' || 
						tableroVisible[nuevaFila][nuevaColumna] == '!') {
						revelarCeldasVacias(nuevaFila, nuevaColumna);
					}
				}
			}
		}
	}
}

void Buscaminas::mostrarTablero() {
	cout << "\n   BUSCAMINAS 8x8\n";
	cout << "   ";
	for(int j = 0; j < TAMANO; j++) {
		cout << " " << j+1 ;
	}
	cout << endl;
	
	cout << "  +";
	for(int j = 0; j < TAMANO; j++) {
		cout << "--";
	}
	cout << "-+\n";
	
	for(int i = 0; i < TAMANO; i++) {
		cout << i+1 << " | ";
		for(int j = 0; j < TAMANO; j++) {
			cout << tableroVisible[i][j] << " ";
		}
		cout << "|\n";
	}
	
	cout << "  +";
	for(int j = 0; j < TAMANO; j++) {
		cout << "--";
	}
	cout << "-+\n";
	
	cout << "Minas restantes: " << minasRestantes << endl;
}

bool Buscaminas::verificarVictoria() {
	return celdasDescubiertas == (TAMANO * TAMANO - 10);
}

void Buscaminas::jugar(Jugador*& jugador) {
	cout << "=== BUSCAMINAS ===" << endl;
	cout << "Premio: si ganas +50 puntos, si pierdes -25 puntos" << endl;
	
	bool juegoCompleto = false;
	
	while(!juegoCompleto) {
		inicializarTablero();
		colocarMinas(10);
		calcularNumeros();
		
		juegoGanado = false;
		juegoPerdido = false;
		
		cout << "\n--- NUEVO JUEGO ---" << endl;
		
		while(!juegoGanado && !juegoPerdido) {
			mostrarTablero();
			
			cout << "\nOpciones:" << endl;
			cout << "1. Descubrir celda" << endl;
			cout << "2. Marcar/Desmarcar bandera (!)" << endl;
			cout << "3. Rendirse" << endl;
			
			int opcion = Utilidades::in_int("Selecciona una opcion: ");
			cout << endl;
			
			if(opcion == 1) {
				int fila = Utilidades::in_int("Fila (1-8): ");
				int columna = Utilidades::in_int("Columna (1-8): ");
				
				if(fila < 1 || fila > TAMANO || columna < 1 || columna > TAMANO) {
					cout << "\nPosicion invalida. Usa numeros del 1 al 8." << endl;
					continue;
				}
				
				fila--;
				columna--;
				
				if(tableroVisible[fila][columna] == '!') {
					cout << "\nPrimero quita la bandera (!) de esta celda." << endl;
					continue;
				}
				
				if(tableroVisible[fila][columna] != '.') {
					cout << "\nEsta celda ya esta descubierta." << endl;
					continue;
				}
				
				if(minas[fila][columna]) {
					for(int i = 0; i < TAMANO; i++) {
						for(int j = 0; j < TAMANO; j++) {
							if(minas[i][j]) {
								tableroVisible[i][j] = '*';
							}
						}
					}
					mostrarTablero();
					cout << "\nHas pisado una mina! -25 puntos" << endl;
					jugador->restarPuntos(25);
					jugador->set_vidas(jugador->get_vidas() - 1);
					juegoPerdido = true;
					juegoCompleto = true;
				} else {
					revelarCeldasVacias(fila, columna);
					
					if(verificarVictoria()) {
						mostrarTablero();
						cout << "\nFelicidades! Has ganado! +50 puntos" << endl;
						jugador->aumentarPuntos(50);
						juegoGanado = true;
						juegoCompleto = true;
					}
				}
				
			} else if(opcion == 2) {
				int fila = Utilidades::in_int("Fila (1-8): ");
				int columna = Utilidades::in_int("Columna (1-8): ");
				
				if(fila < 1 || fila > TAMANO || columna < 1 || columna > TAMANO) {
					cout << "\nPosicion invalida. Usa numeros del 1 al 8." << endl;
					continue;
				}
				
				fila--;
				columna--;
				
				if(tableroVisible[fila][columna] == '.') {
					tableroVisible[fila][columna] = '!';
					minasRestantes--;
					cout << "\nBandera colocada." << endl;
				} else if(tableroVisible[fila][columna] == '!') {
					tableroVisible[fila][columna] = '.';
					minasRestantes++;
					cout << "\nBandera removida." << endl;
				} else {
					cout << "\nNo puedes colocar bandera en una celda descubierta." << endl;
				}
				
			} else if(opcion == 3) {
				cout << "\nTe has rendido. -25 puntos" << endl;
				jugador->restarPuntos(25);
				jugador->set_vidas(jugador->get_vidas() - 1);
				juegoPerdido = true;
				juegoCompleto = true;
			} else {
				cout << "\nOpcion invalida." << endl;
			}
		}
	}
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
	cout << "Vidas restantes: " << jugador->get_vidas() << endl;
}
