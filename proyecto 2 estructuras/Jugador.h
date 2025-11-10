#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador {
private:
	int puntos;
	int vidas;
	string nombre;
	string id;
	
public:
	Jugador(string nombre, string id, int puntos, int vidas);
	
	void aumentarPuntos(int puntos_de_juego); // solamente se le pasa el atributo de los puntos del juego
	void restarPuntos(int puntos_de_juego); // solamente se le pasa el atributo de los puntos del juego
	
	void set_nombre(string nombre);
	string get_nombre();
	
	void set_id(string id);
	string get_id();
	
	void set_puntos(int puntos);
	int get_puntos();
	
	void set_vidas(int vidas);
	int get_vidas();
};

#endif

