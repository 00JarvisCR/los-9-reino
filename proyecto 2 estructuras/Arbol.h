#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
#include <iostream>

using namespace std;

class Arbol {
private:
	// se inicializan como constantes cada nodo para despues tener formado el arbol estructurado como se pide

	/*
	string titulos[9] = {"Tic-Tac-Toe", "Torres de Hanoi", "Sudoku 4x4", "Recuerda la Secuencia", "Buscaminas", "El Ahorcado", "Cuatro en Raya", "Juego de memoria de pares", "Adivina el Numero"};
	int id[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int puntos[9] = {30, 40, 40, 40, 50, 40, 30, 30, 50};
	*/
	
public:
	Nodo* reino_1;
	Nodo* reino_2;
	Nodo* reino_3;
	Nodo* reino_4;
	Nodo* reino_5;
	Nodo* reino_6;
	Nodo* reino_7;
	Nodo* reino_8;
	Nodo* reino_9;
	
	~Arbol();
	Arbol();
	
	Nodo* get_raiz(); // para obtener el reino 1

};

#endif

