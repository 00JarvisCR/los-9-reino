#include "RecuerdaSecuencia.h"
#include <thread>

RecuerdaSecuencia::RecuerdaSecuencia() {
	this->elementos = {"perro", "gato", "burro", "tigre",
						"uno", "dos", "tres", "amarillo",
						"azul", "rojo", "agua", "fuego",
						"aire", "tierra", "hola", "adios" };
}

void RecuerdaSecuencia::jugar(Jugador*& jugador) {
	insertarEnCola();
	
	cout << "=== Recuerda la Secuencia ===" << endl;
	cout << "-Premio: si ganas +40 puntos, si pierdes -20 puntos" << endl;
	cout << "-ingresa las palabras que salgan en el orden adecuado para ganar\n" << endl;
	
	Utilidades::pausar();
	Utilidades::limpiar();
	
	cout << "Recuerda la secuencia: ";
	mostrarSecuencia();
	
	cout << endl;
	espera();
	Utilidades::limpiar();
	
	string respuesta;
	for (int i = 0; i <= 5; i++) {
		cout << "Ingrese el elemento " << i+1 << ": ";
		respuesta = Utilidades::in_string("");
		cout << endl;
		
		if (verificarRespuesta(respuesta)){
			continue;
		}
		else {
			cout << "Te haz equivocado, -20 puntos para " << jugador->get_nombre() << endl;
			jugador->restarPuntos(20);
			int vidas = jugador->get_vidas();
			vidas -= 1;
			jugador->set_vidas(vidas);
			cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
			cout << "Vidas restantes: " << jugador->get_vidas() << endl;
			return;
		}
	}
	
	cout << "Lo haz conseiguido, Feliciades!! +40 puntos" << endl;
	jugador->aumentarPuntos(40);
	
	cout << "\nPuntos actuales de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
	cout << "Vidas restantes: " << jugador->get_vidas() << endl;
	
}

void RecuerdaSecuencia::espera() {
	this_thread::sleep_for(chrono::seconds(15)); // pausa por 5 segundos
}

vector<int> RecuerdaSecuencia::numeroAleatorio() {
	vector<int> numeros;
	
	// Llenar con números del 0 al 15 (o el rango que quieras)
	for (int i = 0; i < 16; i++) {
		numeros.push_back(i);
	}
	
	// Mezclar el vector
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(numeros.begin(), numeros.end(), default_random_engine(seed));
	
	// Tomar solo los primeros 6 elementos
	numeros.resize(6);
	
	return numeros;
}

void RecuerdaSecuencia::insertarEnCola() {
	
	vector<int> numeros = numeroAleatorio();
		
	for (int i = 0; i <= 5; i++){
		secuencia.push(elementos[numeros[i]]);
	}
}

bool RecuerdaSecuencia::verificarRespuesta(string respuesta) {
	if (respuesta == this->secuencia.front()){
		secuencia.pop();
		return true;
	}
	
	// vaciar la cola si se pierde
	for(int i = 0; i <= 5; i++) {
		if (!this->secuencia.empty()){
			this->secuencia.pop();
		}
	}
	return false;
}

void RecuerdaSecuencia::mostrarSecuencia(){
	queue<string> copia = this->secuencia;
	
	for(int i = 0; i <= 5; i++) {
		cout << copia.front() << " ";
		copia.pop();
	}
	
	cout << "\n";
}

