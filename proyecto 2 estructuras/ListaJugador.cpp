#include "ListaJugador.h"

ListaJugador::ListaJugador() {
	this->listaJugadores = {};
}

bool ListaJugador::existeJugador(Jugador*& jugador) {
	for (auto it = this->listaJugadores.begin(); it != this->listaJugadores.end(); it++) {
		Jugador* actual = *it;
		
		if (actual->get_id() == jugador->get_id()){
			return true;
		}
	}
	return false;
}

void ListaJugador::agregar(Jugador* jugador) {
	this->listaJugadores.push_back(jugador);
}

Jugador* ListaJugador::buscar(string id) {
	for (auto it = this->listaJugadores.begin(); it != this->listaJugadores.end(); it++) {
		Jugador* actual = *it;
		
		if (actual->get_id() == id){
			return actual;
		}
	}
	return nullptr;
}

