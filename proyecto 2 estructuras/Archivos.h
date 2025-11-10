#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "ListaJugador.h"
#include <fstream>
#include <iostream>

using namespace std;

class Archivos {
public:
	// Métodos estáticos
	static bool GuardarJugadores(ListaJugador& listaJugadores);
	static ListaJugador CargarJugadores();
};

#endif
