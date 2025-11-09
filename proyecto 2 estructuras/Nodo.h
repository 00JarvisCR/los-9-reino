#ifndef NODO_H
#define NODO_H

#include <iostream>
using namespace std;

class Nodo {
private:
	int id;
	string nombre_minijuego;
	int puntos;
	bool se_jugo; // para verificar si ya se jugo el juego o no (para cuando se devuelva no tener que volver a pasarlo para moverse)

	Nodo* anterior; // anterior primario (el primer anterior creado)
	Nodo* siguiente; // siguiente primario (el primer siguiente creado)
	
	Nodo* ant_secundario; // anterior secundario (solo se va usar si ya tiene un anterior)
	Nodo* sig_secundario; // siguiente secundario (solo se va usar si ya tiene un siguiente)
	
	Nodo* sig_terciario; // solo para el reino 2
	
public:
	Nodo(int id, string nombre_minijuego, int puntos);
	
	void set_se_jugo(bool se_jugo);
	bool get_se_jugo();
	
	int get_id();
	
	string get_nombre_minijuego();
	
	int get_puntos();
	
	// anterior
	void set_anterior(Nodo* anterior);
	Nodo* get_anterior();
	
	// siguiente
	void set_siguiente(Nodo* siguiente);
	Nodo* get_siguiente();
	
	// anterior secundario
	void set_ant_secundario(Nodo* ant_secundario);
	Nodo* get_ant_secundario();
	
	// siguiente secundario
	void set_sig_secundario(Nodo* sig_secundario);
	Nodo* get_sig_secundario();
	
	// siguiente terciario (solo para reino 2)
	void set_sig_terciario(Nodo* sig_terciario);
	Nodo* get_sig_terciario();
	
};
#endif

