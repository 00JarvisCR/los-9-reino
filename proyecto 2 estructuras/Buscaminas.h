#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H

#include "Jugador.h"

class Buscaminas {
private:
	static const int TAMANO = 8;
	char tablero[TAMANO][TAMANO];
	char tableroVisible[TAMANO][TAMANO];
	bool minas[TAMANO][TAMANO];
	int minasRestantes;
	int celdasDescubiertas;
	bool juegoGanado;
	bool juegoPerdido;
	
	void inicializarTablero();
	void colocarMinas(int totalMinas);
	void calcularNumeros();
	int contarMinasAdyacentes(int fila, int columna);
	void revelarCeldasVacias(int fila, int columna);
	void mostrarTablero();
	bool verificarVictoria();
	
public:
	Buscaminas();
	void jugar(Jugador*& jugador);
};

#endif
