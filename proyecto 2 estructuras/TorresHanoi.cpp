#include "TorresHanoi.h"
#include <iostream>
#include <cmath>

using namespace std;

TorresHanoi::TorresHanoi(int numDiscos) {
	discos = (numDiscos < 3) ? 3 : (numDiscos > 8) ? 8 : numDiscos;
	movimientos = 0;
	movimientosMinimos = calcularMovimientosMinimos();
	inicializarTorres();
}

void TorresHanoi::inicializarTorres() {
	// Limpiar todas las torres
	for(int i = 0; i < 3; i++) {
		while(!torres[i].empty()) {
			torres[i].pop();
		}
	}
	
	// Llenar la primera torre con discos (más grande en la base)
	for(int i = discos; i >= 1; i--) {
		torres[0].push(i); // Disco más grande primero (en la base)
	}
}

void TorresHanoi::mostrarTorres() {
	cout << "\n=== TORRES DE HANOI ===" << endl;
	cout << "Movimientos: " << movimientos << " (Minimo posible: " << movimientosMinimos << ")" << endl;
	cout << endl;
	
	// Crear copias temporales para mostrar
	stack<int> temp[3];
	for(int i = 0; i < 3; i++) {
		temp[i] = torres[i];
	}
	
	vector<vector<int>> torresArray(3, vector<int>(discos, 0));
	
	// Convertir pilas a arrays para mostrar (base = índice 0)
	for(int i = 0; i < 3; i++) {
		int altura = 0;
		vector<int> discosEnTorre;
		
		// Extraer discos de la pila temporal
		while(!temp[i].empty()) {
			discosEnTorre.push_back(temp[i].top());
			temp[i].pop();
		}
		
		// Colocar en el array con el disco más grande en la base (índice 0)
		for(int j = discosEnTorre.size() - 1; j >= 0; j--) {
			torresArray[i][altura] = discosEnTorre[j];
			altura++;
		}
	}
	
	cout << "  Torre 1      Torre 2      Torre 3" << endl;
	cout << " +------+     +------+     +------+" << endl;
	
	// Mostrar de arriba hacia abajo (pirámide invertida en el array)
	for(int i = discos - 1; i >= 0; i--) {
		for(int j = 0; j < 3; j++) {
			cout << " |";
			if(torresArray[j][i] != 0) {
				int tamanio = torresArray[j][i];
				int espacios = (discos - tamanio);
				int anchoTotal = discos * 2;
				
				// Espacios a la izquierda (centrado)
				for(int k = 0; k < espacios; k++) {
					cout << " ";
				}
				
				// Disco (proporcional a su tamaño)
				for(int k = 0; k < tamanio * 2; k++) {
					cout << "#";
				}
				
				// Espacios a la derecha
				for(int k = 0; k < espacios; k++) {
					cout << " ";
				}
			} else {
				// Torre vacía
				for(int k = 0; k < discos * 2; k++) {
					cout << " ";
				}
			}
			cout << "|    ";
		}
		cout << endl;
	}
	
	// Base de las torres
	for(int i = 0; i < 3; i++) {
		cout << " +";
		for(int j = 0; j < discos * 2; j++) {
			cout << "-";
		}
		cout << "+    ";
	}
	cout << endl;
}

bool TorresHanoi::moverDisco(int origen, int destino) {
	origen--;
	destino--;
	
	if(origen < 0 || origen > 2 || destino < 0 || destino > 2) {
		cout << "Error: Las torres deben ser 1, 2 o 3." << endl;
		return false;
	}
	
	if(origen == destino) {
		cout << "Error: No puedes mover un disco a la misma torre." << endl;
		return false;
	}
	
	// Verificar si la torre origen está vacía (LIFO - no hay elemento para sacar)
	if(torres[origen].empty()) {
		cout << "Error: La torre origen esta vacia." << endl;
		return false;
	}
	
	// Obtener el disco superior de la torre origen (LIFO)
	int discoOrigen = torres[origen].top();
	
	// Verificar regla LIFO: solo se puede colocar sobre disco más grande o poste vacío
	if(!torres[destino].empty()) {
		int discoDestino = torres[destino].top();
		if(discoOrigen > discoDestino) {
			cout << "Error: No puedes colocar un disco mas grande (" << discoOrigen 
				<< ") sobre uno mas pequeno (" << discoDestino << ")." << endl;
			return false;
		}
	}
	
	// Realizar el movimiento (operaciones LIFO)
	torres[origen].pop(); // Sacar de la torre origen
	torres[destino].push(discoOrigen); // Poner en la torre destino
	
	movimientos++;
	return true;
}

bool TorresHanoi::verificarVictoria() {
	// Verificar si la tercera torre tiene todos los discos
	return (torres[2].size() == discos);
}

int TorresHanoi::calcularMovimientosMinimos() {
	return pow(2, discos) - 1;
}

void TorresHanoi::jugar(Jugador*& jugador) {
	cout << "=== TORRES DE HANOI ===" << endl;
	cout << "Premio: +40 puntos si ganas, -20 puntos si abandonas" << endl;
	bool jugando = true;
	
	while(jugando && !verificarVictoria()) {
		mostrarTorres();
		
		cout << "Opciones:" << endl;
		cout << "1. Mover disco" << endl;
		cout << "2. Rendirse" << endl;
		cout << "Elige una opcion (1-2): ";
		
		int opcion;
		opcion = Utilidades::in_int("");
		
		if(opcion == 1) {
			int origen, destino;
			
			origen = Utilidades::in_int("Ingresa torre origen (1-3): ");
			destino = Utilidades::in_int("Ingresa torre destino (1-3): ");
			
			if(moverDisco(origen, destino)) {
				cout << "Movimiento exitoso!" << endl;
			} else {
				cout << "Movimiento fallido. Intenta de nuevo." << endl;
			}
			
		} else if(opcion == 2) {
			cout << "Te has rendido. -20 puntos" << endl;
			jugador->restarPuntos(20);
			jugando = false;
		} else {
			cout << "Opcion invalida. Intenta de nuevo." << endl;
		}
	}
	
	if(verificarVictoria()) {
		mostrarTorres();
		cout << "¡Felicidades! ¡Has completado las Torres de Hanoi!\n" << endl;
		cout << "Movimientos realizados: " << movimientos << endl;
		cout << "Movimientos minimos: " << movimientosMinimos << endl << endl;
		
		if(movimientos == movimientosMinimos) {
			cout << "¡Perfecto! Lograste el minimo de movimientos posible!" << endl;
		}
		
		cout << "+40 puntos!" << endl;
		jugador->aumentarPuntos(40);
	}
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
}
