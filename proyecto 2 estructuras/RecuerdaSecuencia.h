#ifndef RECUERDASECUENCIA_H
#define RECUERDASECUENCIA_H

#include "Jugador.h"
#include "Utilidades.h"

#include <iostream>

#include <queue>

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

class RecuerdaSecuencia {
private:
	vector<string> elementos;
	queue<string> secuencia;
	
public:
	RecuerdaSecuencia();
	void jugar(Jugador*& jugador);
	
	void espera();
	
	vector<int> numeroAleatorio();
	
	void insertarEnCola();
	
	bool verificarRespuesta(string respuesta);
	
	void mostrarSecuencia();
	
	
};

#endif
