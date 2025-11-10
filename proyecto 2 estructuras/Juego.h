#ifndef JUEGO_H
#define JUEGO_H

#include <stack>

#include "Arbol.h"
#include "ListaJugador.h"
#include "Archivos.h"

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
	Arbol arbol; // arbol con los nodos de los minijuegos
	stack<Nodo*> pila_juegos; // se crea una pila donde se almacenaran los niveles que uno vaya pasando
	ListaJugador lista = Archivos::CargarJugadores(); // lista de los jugadores para guardarlos y mostrar los mejores
	
	
public:
	Juego();
	
	Nodo* avanzar(Nodo* actual);// es donde se pide al jugador a cual nodo quiere avanzar y se devulve el numero que escogio
	Nodo* retroceder(Nodo* actual); // es donde se pedira al jugador a cual nodo anterior quiere retroceder de los que tenga en la pila
	
	void mostrarSiguientes(Nodo* actual); // muestra las opciones que tiene cuando se quiere avanzar al siguiente minijuego
	
	void cual_jugar(Nodo* actual, Jugador*& jugador); // funcion se jugara el juego que el usuario seleccione
	
	void jugar(); // es donde se recopilan todo, (un main que invoca el juego completo)
	
	int opciones(Nodo* actual, Jugador*& jugador); // aqui es donde uno elije si retroceder, avanzar o jugar
	
	Jugador* registrarse(); // aqui es donde uno pone los datos para jugar con un usuario
	
	int menu_inicial(); // aqui saldra el menu inicial con opciones de jugar, ver top 3 y salir
	
	void opc_jugar(); //aqui es donde se invocaran todos los minijuegos cuando en el menu inicial se escoja jugar
	
	void opc_top3(); // aqui es donde se mostraran los top 3 mejores jugadores cuando en el menu inicial se escoja ver top 3
};

#endif

