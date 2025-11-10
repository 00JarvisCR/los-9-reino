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
	
	// Convertir la lista a vector para facilitar el ordenamiento
	vector<Jugador*> jugadoresVector(listaJugadores.begin(), listaJugadores.end());
	int n = jugadoresVector.size();
	
	// Implementación de Shell Sort por puntos (descendente)
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			Jugador* temp = jugadoresVector[i];
			int j;
			
			// Ordenar de mayor a menor (descendente por puntos)
			for (j = i; j >= gap && jugadoresVector[j - gap]->get_puntos() < temp->get_puntos(); j -= gap) {
				jugadoresVector[j] = jugadoresVector[j - gap];
			}
			jugadoresVector[j] = temp;
		}
	}
	
	// Construir el string con los top 3
	string resultado = "TOP 3 MEJORES JUGADORES\n\n";
	
	int limite = (n < 3) ? n : 3; // Si hay menos de 3, mostrar los que hay
	
	for (int i = 0; i < limite; i++) {
		resultado += to_string(i + 1) + ". " + 
			jugadoresVector[i]->get_nombre() + " --> " + 
			to_string(jugadoresVector[i]->get_puntos()) + " puntos\n";
	}
	
	return resultado;
}

