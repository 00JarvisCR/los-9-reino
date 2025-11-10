#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
#include <iostream>

using namespace std;

class Arbol {
private:
	Nodo* reino_1;
	Nodo* reino_2;
	Nodo* reino_3;
	Nodo* reino_4;
	Nodo* reino_5;
	Nodo* reino_6;
	Nodo* reino_7;
	Nodo* reino_8;
	Nodo* reino_9;
	
public:	
	~Arbol();
	Arbol();
	
	Nodo* get_raiz(); // para obtener el reino 1
	
	void resetear(); // para poner todos los nodos que ya han sido jugados como no jugados, para cuando se vuelva a jugar

};

#endif

