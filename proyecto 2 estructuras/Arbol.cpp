#include "Arbol.h"

Arbol::Arbol() {
	this->reino_1 = new Nodo(1, "Tic-Tac-Toe", 30);
	this->reino_2 = new Nodo(2, "Torres de Hanoi", 40);
	this->reino_3 = new Nodo(3, "Sudoku 4x4", 40);
	this->reino_4 = new Nodo(4, "Recuerda la Secuencia", 40);
	this->reino_5 = new Nodo(5, "Buscaminas", 50);
	this->reino_6 = new Nodo(6, "El Ahorcado", 40);
	this->reino_7 = new Nodo(7, "Cuatro en Raya", 30);
	this->reino_8 = new Nodo(8, "Juego de memoria de pares", 30);
	this->reino_9 = new Nodo(9, "Adivina el Numero", 50);
	
	//relaciones
	
	reino_1->set_siguiente(reino_2);
	reino_2->set_siguiente(reino_3);
	reino_3->set_siguiente(reino_5);
	reino_2->set_sig_secundario(reino_5);
	reino_5->set_siguiente(reino_7);
	reino_7->set_siguiente(reino_9);
	reino_2->set_sig_terciario(reino_4);
	reino_4->set_siguiente(reino_6);
	reino_6->set_siguiente(reino_8);
	reino_8->set_siguiente(reino_7);
	reino_8->set_sig_secundario(reino_9);
	
	//reino_7->set_ant_secundario(reino_8);
	//reino_9->set_ant_secundario(reino_8);
	//reino_8->set_anterior(reino_6);
	//reino_6->set_anterior(reino_4);
	//reino_4->set_anterior(reino_2);
	//reino_9->set_anterior(reino_7);
	//reino_7->set_anterior(reino_5);
	//reino_5->set_ant_secundario(reino_2);
	//reino_5->set_anterior(reino_3);
	//reino_3->set_anterior(reino_2);
	//reino_2->set_anterior(reino_1);
}

Arbol::~Arbol() {
	delete reino_9;
	delete reino_8;
	delete reino_7;
	delete reino_6;
	delete reino_5;
	delete reino_4;
	delete reino_3;
	delete reino_2;
	delete reino_1;
}

Nodo* Arbol::get_raiz(){
	return this->reino_1;
}

void Arbol::resetear(){
	this->reino_1->set_se_jugo(false);
	this->reino_2->set_se_jugo(false);
	this->reino_3->set_se_jugo(false);
	this->reino_4->set_se_jugo(false);
	this->reino_5->set_se_jugo(false);
	this->reino_6->set_se_jugo(false);
	this->reino_7->set_se_jugo(false);
	this->reino_8->set_se_jugo(false);
	this->reino_9->set_se_jugo(false);
}

