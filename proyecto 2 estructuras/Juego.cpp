#include "Juego.h"

Juego::Juego() {
	
}

void Juego::jugar() {
	int opcion; // para interactuar con el el juego
	
	cout << "Bienvenido al Juego de los 9 reinos." << endl;
	
	cout << "\n-Respecto vayas avanzando en los juego se te abriran caminos para elejir." << endl;
	
	cout << "\n-Si llegas a menos de -50 puntos perderas el juego y\ntendras que empezar desde el inicio." << endl;
	
	cout << "\n-Si pierdes todas tus vidas perderas el juego y\ntendras que empezar desde el inicio." << endl;
	
	cout << "\n-Para poder ganar tiene que llegar hasta el ultimo juego\nno importa que camino elijas." << endl;
	
	cout << "\n-Tambien deberas tener minimo 150 puntos para que puedas ganar, de lo contrario\nno contara llegar al final.\n\n" << endl;
	
	
	cout << "========================================================================" << endl;
	cout << "                    Presion ENTER para seguir" << endl;
	cout << "========================================================================" << endl;

	Utilidades::pausar("");
	Utilidades::limpiar();
	
	do {
		opcion = menu_inicial();
		
		switch (opcion) {
		case 1:
			opc_jugar();
			break;
			
		case 2:
			Utilidades::limpiar();
			cout << this->lista.mejoresJugadores() << endl;
			break;
			
		case 3:
			cout << "Saliendo..." << endl;
			return; // se sale
			break;
			
		default:
			break;
		}
		Utilidades::pausar();
		Utilidades::limpiar();
	} while(true);
	
	
	
}

void Juego::cual_jugar(Nodo* actual, Jugador*& jugador) {
	int id_actual = actual->get_id();
	
	// se inicializan los reinos
	TicTacToe reino_1;
	TorresHanoi reino_2;
	Sudoku reino_3;
	RecuerdaSecuencia reino_4;
	Buscaminas reino_5;
	Ahorcado reino_6;
	CuatroEnRaya reino_7;
	MemoriaPares reino_8;
	AdivinaNumero reino_9;
	
	
	if (!actual->get_se_jugo()){
		switch(id_actual){
		case 1:
			reino_1.jugar(jugador);
			cout << "tic tak tou" <<endl;
			break;
			
		case 2:
			reino_2.jugar(jugador);
			cout << "torres" << endl;
			break;
			
		case 3:
			reino_3.jugar(jugador);
			cout << "sudoku" << endl;
			break;
			
		case 4:
			reino_4.jugar(jugador);
			cout << "secuencia" << endl;
			break;
			
		case 5:
			reino_5.jugar(jugador);
			break;
			
		case 6:
			reino_6.jugar(jugador);
			break;
			
		case 7:
			reino_7.jugar(jugador);
			break;
			
		case 8:
			reino_8.jugar(jugador);
			break;
			
		case 9:
			reino_9.jugar(jugador);
			break;
			
		default:
			cout << "Error: id no reconocido..." << endl;
			break;
		}
		
		actual->set_se_jugo(true); // se pone el juego como que ya se jugo para que no se vuelva jugar
	}
	else {
		cout << "\nEste juego ya ha sido jugado, no puede volver a jugarlo. " << endl;
	}
}

Nodo* Juego::avanzar(Nodo* actual) {
	Nodo* primario = actual->get_siguiente(); // siguiente primario
	Nodo* secundario = actual->get_sig_secundario(); // siguiente secundario
	Nodo* terciario = actual->get_sig_terciario(); // siguiente terciario
	
	Nodo* siguiente; // el nodo al cual se va tomar el valor del que se va avanzar
	
	cout << endl;
	cout << "      3 ----> 5 -----> 7 -------> 9       1. Tic-Tac-Toe            \n";
	cout << "      ^   /            ^      /           2. Torres de Hanoi        \n";
	cout << "      |  /             |     /            3. Sudoku 4x4             \n";
	cout << "1 --> 2 /              |    /             4. Recuerda la Secuencia  \n";
	cout << "      |                |   /              5. Busca Minas            \n";
	cout << "      v                |  /               6. Ahorcado               \n";
	cout << "      4 ----> 6 -----> 8 /                7. Cuatro en Raya         \n";
	cout << "                                          8. Juego Memoria de Pares \n";
	cout << "                                          9. Adivina el Numero      \n";
	
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Haz terminado el reino " << actual->get_id() << ".\nAhora elije a cual reino quieres continuar.\n\n" << endl;
	
	mostrarSiguientes(actual);
	
	int opcion;
	
	do {
		opcion = Utilidades::in_int("ingrese el numero correspondiente: ");
		
		if (opcion == 1 and primario != nullptr) {
			siguiente = primario; // toma el valor de el siguiente primario
			break;
		}
		
		else if (opcion == 2 and secundario != nullptr) {
			siguiente = secundario; // toma el valor de el siguiente secundario
			break;
		}
		
		else if (opcion == 3 and terciario != nullptr) {
			siguiente = terciario; // toma el valor de el siguiente terciario
			break;
		}
		else {
			cout << "Error: opcion no valida..." << endl;
		}
	}while(true);
	
	this->pila_juegos.push(actual); // se agrega el nodo actual a la pila
	
	return siguiente; // se retorna el siguiente
}

void Juego::mostrarSiguientes(Nodo* actual){
	
	Nodo* primario = actual->get_siguiente(); // siguiente primario
	Nodo* secundario = actual->get_sig_secundario(); // siguiente secundario
	Nodo* terciario = actual->get_sig_terciario(); // siguiente terciario
	
	if (primario != nullptr){
		cout << "- (1) " << primario->get_nombre_minijuego() << endl; // Muestra el id siguiente si tiene
	}
	
	if (secundario != nullptr) {
		cout << "- (2) " << secundario->get_nombre_minijuego() << endl; // Muestra el id siguiente secundario si tiene
	}
	
	if (terciario != nullptr) {
		cout << "- (3) " << terciario->get_nombre_minijuego() << endl; // Muestra el id siguiente terciario si tiene
	}
	
	cout << "\n\n";
}

Nodo* Juego::retroceder(Nodo* actual) {
	Nodo* anterior = this->pila_juegos.top(); // el anterior toma el valor de el ultimo agregado en la pila
	
	this->pila_juegos.pop(); // se elimina el ultimo de la pila
	
	return anterior;
}

Jugador* Juego::registrarse() {
	cout << "\n\nIdentificate:\n" << endl;
	string nombre = Utilidades::in_string("Ingresa tu nombre: ");
	string id = Utilidades::in_string("Ingrese su ID: ");
	cout << "\n\n";
	
	Jugador* jugador = new Jugador(nombre, id, 0, 3);
	
	if (this->lista.existeJugador(jugador)) {
		cout << "ID encontrado." << endl;
		cout << "Se ha logueado correctamente." << endl;
		cout << "Se te han reseteado los puntos." << endl;
		
		jugador = this->lista.buscar(id); // se usan los atributos oficiales de ese id
		jugador->set_vidas(3);
		jugador->set_puntos(0); // se resetean lo puntos por volver a jugar desde el inicio
	}
	else{
		cout << "ID nuevo." << endl;
		cout << "Registrado correctamente." << endl;
		cout << "Disfruta el juego." << endl;
		
		this->lista.agregar(jugador); // Se agrega a la lista
	}
	
	cout << "\n\n";
	this->arbol.resetear(); // pone todos los nodos como no jugados
	
	Archivos::GuardarJugadores(this->lista); // se guarda en los archivos
	
	return jugador;
}

int Juego::opciones(Nodo* actual, Jugador*& jugador) {
	cout <<endl;
	cout << "      3 ----> 5 -----> 7 -------> 9       1. Tic-Tac-Toe            \n";
	cout << "      ^   /            ^      /           2. Torres de Hanoi        \n";
	cout << "      |  /             |     /            3. Sudoku 4x4             \n";
	cout << "1 --> 2 /              |    /             4. Recuerda la Secuencia  \n";
	cout << "      |                |   /              5. Busca Minas            \n";
	cout << "      v                |  /               6. Ahorcado               \n";
	cout << "      4 ----> 6 -----> 8 /                7. Cuatro en Raya         \n";
	cout << "                                          8. Juego Memoria de Pares \n";
	cout << "                                          9. Adivina el Numero      \n";
	cout << "---------------------------------------------------------------------" << endl;
	
	cout << "Actualmente te encuentras en el Reino " << actual->get_id() << ": " << actual->get_nombre_minijuego() << endl;
	cout << "Puntos de " << jugador->get_nombre() << ": " << jugador->get_puntos() << endl;
	cout << "Vidas de " << jugador->get_nombre() << ": " << jugador->get_vidas() << endl;
	
	cout << "\n\nElije una opcion:\n" << endl;
	cout << "- (1) Jugar " << actual->get_nombre_minijuego() << endl;
	cout << "- (2) Avanzar" << endl;
	cout << "- (3) Retroceder" << endl;
	cout << "- (4) Salir" << endl;
	
	int opcion;
	do {
		opcion = Utilidades::in_int("Ingrese la opcion correspondiente: ");
		
		if (opcion > 4 or opcion < 1){
			cout << "\n\nIngrese una opcion valida..." << endl;
		}
		else{
			return opcion;
		}
	} while(true);
	
}

int Juego::menu_inicial() {
	cout << "ELije una opcion:\n" << endl;
	cout << "- (1) Entrar al Juego" << endl;
	cout << "- (2) Ver top 3 Mejores Jugadores" << endl;
	cout << "- (3) Salir\n" << endl;
	
	int opcion;
	
	do {
		opcion = Utilidades::in_int("Ingrese la opcion correspondiente: ");
		
		if (opcion > 3 or opcion < 1){
			cout << "\n\nIngrese una opcion valida..." << endl;
		}
		else{
			return opcion;
		}
	} while(true);
}

void Juego::opc_jugar() {
	Nodo* actual = this->arbol.get_raiz(); // se inicializa el nodo actual como la raiz para empezar el juego
	
	Jugador* jugador = registrarse();
	
	if(jugador->get_id() == "" or jugador->get_nombre() == ""){
		cout << "Error: jugador no reconocido" << endl;
		return;
	}
	
	Utilidades::pausar();
	Utilidades::limpiar();
	
	do{
		int opcion = opciones(actual, jugador);
		
		switch (opcion) {
		case 1:
			Utilidades::limpiar();
			cual_jugar(actual, jugador);
			
			if (jugador->get_vidas() <= 0) {
				cout << "\n\nTe quedaste sin vidas, vuelve a intentarlo." << endl;
				return; // se sale
			}
			
			if (jugador->get_puntos() <= -50) {
				cout << "\n\nTus puntos llegaron al minimo, vuelve a intentarlo." << endl;
				return; // se sale
			}
			
			break;
			
		case 2:
			if (!actual->get_se_jugo()){
				cout << "\nTienes que pasar este nivel para poder avanzar" << endl;
			}
			else if(actual->get_id() == 9 and jugador->get_puntos() >= 150){
				Utilidades::limpiar();
				cout << "Haz ganado el juego, felicidades!!\n\n" << endl;
				
				Archivos::GuardarJugadores(this->lista); // se guarda la lista con el jugador actualizado
				
				return; // se sale
			}
			else if(actual->get_id() == 9 and jugador->get_puntos() < 150) {
				Utilidades::limpiar();
				cout << "Tienes que tener minimo 150 puntos para terminar el Juego" <<endl;
				cout << "\n-Te recomiendo devolverte y buscar otros minijuegos\nque no hayas jugado par ganar puntos" << endl;
			}
			else{
				Utilidades::limpiar();
				actual = avanzar(actual);
			}
			break;
			
		case 3:
			if (actual->get_id() == 1) {
				cout << "\nNo puedes retroceder mas" << endl;
			}
			else{
				actual = retroceder(actual);
			}
			break;
			
		case 4:
			cout << "\n\nSaliendo de Los Nueve Reinos...\n" << endl;
			return;
			
		default:
			break;
		}
		cout << "\n";
		Utilidades::pausar();
		Utilidades::limpiar();
	} while(true);
}
