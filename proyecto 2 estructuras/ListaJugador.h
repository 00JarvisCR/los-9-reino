#ifndef LISTAJUGADOR_H
#define LISTAJUGADOR_H

#include "Jugador.h"
#include <list>

class ListaJugador {
private:
	list<Jugador*> listaJugadores;
public:
	ListaJugador();
	void agregar(Jugador* jugador);
	Jugador* buscar(string id);
	string listar();
	bool existeJugador(Jugador*& jugador);
};

#endif

