#ifndef JUEGO_H
#define JUEGO_H

#include <stack>

#include "Arbol.h"
#include "ListaJugador.h"

#include "TicTacToe.h"
#include "TorresHanoi.h"
#include "Sudoku.h"
#include "MemoriaPares.h"
#include "AdivinaNumero.h"
#include "Ahorcado.h"
#include "Buscaminas.h"
#include "CuatroEnRaya.h"
#include "RecuerdaSecuencia.h"

class Juego {
private:
	Arbol arbol;
	stack<Nodo*> pila_juegos; // se crea una pila donde se almacenaran los niveles que uno vaya pasando
	ListaJugador lista;
	
	
public:
	Juego();
	
	Nodo* avanzar(Nodo* actual);// es donde se pide al jugador a cual nodo quiere avanzar y se devulve el numero que escogio
	Nodo* retroceder(Nodo* actual); // es donde se pedira al jugador a cual nodo anterior quiere retroceder de los que tenga en la pila
	
	void mostrarSiguientes(Nodo* actual);
	
	void cual_jugar(Nodo* actual, Jugador*& jugador); // funcion se jugara el juego que el usuario seleccione
	
	void jugar();
	
	int opciones(Nodo* actual, Jugador*& jugador); // aqui es donde uno elije si retroceder, avanzar o jugar
	
	Jugador* registrarse(); // aqui es donde uno pone los datos para jugar con un usuario
};

#endif

