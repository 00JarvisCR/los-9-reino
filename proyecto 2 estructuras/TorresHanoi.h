#ifndef TORRESHANOI_H
#define TORRESHANOI_H

#include "Utilidades.h"

#include "Jugador.h"
#include <stack>
#include <vector>

using namespace std;

class TorresHanoi {
private:
	int discos;
	int movimientos;
	int movimientosMinimos;
	stack<int> torres[3]; // 3 torres usando pilas
	
	void inicializarTorres();
	void mostrarTorres();
	bool moverDisco(int origen, int destino);
	bool verificarVictoria();
	int calcularMovimientosMinimos();
	
public:
	TorresHanoi(int numDiscos = 3);
	void jugar(Jugador*& jugador);
};

#endif
