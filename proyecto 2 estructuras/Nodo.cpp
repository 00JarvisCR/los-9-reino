#include "Nodo.h"

Nodo::Nodo(int id, string nombre_minijuego, int puntos) {
	this->id = id;
	this->nombre_minijuego = nombre_minijuego;
	this->puntos = puntos;
	this->se_jugo = false;
	
	this->anterior = nullptr;
	this->siguiente = nullptr;
	
	this->ant_secundario = nullptr;
	this->sig_secundario = nullptr;
}
 
void Nodo::set_se_jugo(bool se_jugo) {this->se_jugo = se_jugo;}
bool Nodo::get_se_jugo() {return this->se_jugo;}

int Nodo::get_id() {return this->id;}

string Nodo::get_nombre_minijuego() {return this->nombre_minijuego;}

int Nodo::get_puntos() {return this->puntos;}

void Nodo::set_anterior(Nodo* anterior) {this->anterior = anterior;}
Nodo* Nodo::get_anterior() {return this->anterior;}

void Nodo::set_siguiente(Nodo* siguiente) {this->siguiente = siguiente;}
Nodo* Nodo::get_siguiente() {return this->siguiente;}

void Nodo::set_ant_secundario(Nodo* ant_secundario) {this->ant_secundario = ant_secundario;}
Nodo* Nodo::get_ant_secundario() {return this->ant_secundario;}

void Nodo::set_sig_secundario(Nodo* sig_secundario) {this->sig_secundario = sig_secundario;}
Nodo* Nodo::get_sig_secundario() {return this->sig_secundario;}	

void Nodo::set_sig_terciario(Nodo* sig_terciario) {this->sig_terciario = sig_terciario;}
Nodo* Nodo::get_sig_terciario() {return this->sig_terciario;}	
