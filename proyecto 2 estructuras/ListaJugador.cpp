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

list<Jugador*> ListaJugador::getLista() const {
	return listaJugadores;
}

string ListaJugador::mejoresJugadores() {
	// Si no hay jugadores, retornar mensaje
	if (listaJugadores.empty()) {
		return "No hay jugadores registrados.";
	}
	
	// se convierte la lista a vector para que sea mas facil de ordenar con shell sort
	vector<Jugador*> jugadoresVector(listaJugadores.begin(), listaJugadores.end());
	int n = jugadoresVector.size();
	
	// Implementación de Shell Sort por puntos
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			Jugador* temp = jugadoresVector[i];
			int j;
			
			// Ordenar de mayor a menor
			for (j = i; j >= gap && jugadoresVector[j - gap]->get_puntos() < temp->get_puntos(); j -= gap) {
				jugadoresVector[j] = jugadoresVector[j - gap];
			}
			jugadoresVector[j] = temp;
		}
	}
	
	string resultado = "TOP 3 MEJORES JUGADORES\n\n";
	
	int limite = (n < 3) ? n : 3; // muestra los que hay si hay menos de 3
	
	for (int i = 0; i < limite; i++) {
		resultado += to_string(i + 1) + ". " + 
			jugadoresVector[i]->get_nombre() + " --> " + 
			to_string(jugadoresVector[i]->get_puntos()) + " puntos\n";
	}
	
	return resultado;
}

