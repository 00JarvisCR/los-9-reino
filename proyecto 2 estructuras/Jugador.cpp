#include "Jugador.h"

Jugador::Jugador(string nombre, string id) {
	this->nombre = nombre;
	this->vidas = 3;
	this->puntos = 0;
	this->id = id;
}

void Jugador::aumentarPuntos(int puntos) {this->puntos += puntos;}
void Jugador::restarPuntos(int puntos) {this->puntos -= puntos;}

void Jugador::set_nombre(string nombre) {this->nombre = nombre;}
string Jugador::get_nombre() {return this->nombre;}

void Jugador::set_id(string id) {this->id = id;}
string Jugador::get_id() {return this->id;}

void Jugador::set_puntos(int puntos) {this->puntos = puntos;}
int Jugador::get_puntos() {return this->puntos;}



