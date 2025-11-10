#include "Archivos.h"

bool Archivos::GuardarJugadores(ListaJugador& listaJugadores) {
	ofstream archivo("jugadores.txt");
	
	if (!archivo.is_open()) {
		cout << "Error: No se pudo crear/abrir el archivo para guardar" << endl;
		return false;
	}
	
	// Obtener la lista de jugadores usando el método getLista()
	list<Jugador*> jugadores = listaJugadores.getLista();
	
	// Verificar si hay jugadores para guardar
		if (jugadores.empty()) {
		archivo << "// Archivo de jugadores (vacío)" << endl;
		//cout << "Archivo creado pero sin jugadores (lista vacía)" << endl;
	}
	else {
		// Guardar cada jugador en el archivo
		for (Jugador* jugador : jugadores) {
			archivo << jugador->get_id() << "," 
				<< jugador->get_nombre() << "," 
				<< jugador->get_puntos() << "," 
				<< jugador->get_vidas() << endl;
		}
		//cout << jugadores.size() << " jugadores guardados exitosamente!" << endl;
	}
		
	archivo.close();
	return true;
}

ListaJugador Archivos::CargarJugadores() {
	ListaJugador lista;
	ifstream archivo("jugadores.txt");
	
	// Si el archivo no existe, lo creamos vacío
	if (!archivo.is_open()) {
		cout << "Archivo no encontrado. Creando archivo vacío..." << endl;
		
		// Crear archivo vacío
		ofstream nuevoArchivo("jugadores.txt");
		if (nuevoArchivo.is_open()) {
			nuevoArchivo << "// Archivo de jugadores" << endl;
			nuevoArchivo.close();
			cout << "Archivo 'jugadores.txt' creado exitosamente!" << endl;
		}
		
		return lista; // Retorna lista vacía
	}
	
	// Si el archivo existe, cargar los datos
	string linea;
	while (getline(archivo, linea)) {
		// Ignorar líneas de comentarios
		if (linea.empty() || linea.find("//") == 0) {
			continue;
		}
		
		// Buscar las comas que separan los datos
		size_t pos1 = linea.find(',');
		size_t pos2 = linea.find(',', pos1 + 1);
		size_t pos3 = linea.find(',', pos2 + 1);
		
		if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
			// Extraer los datos
			string id = linea.substr(0, pos1);
			string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			int puntos = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
			int vidas = stoi(linea.substr(pos3 + 1));
			
			// Crear jugador y agregar a la lista
			Jugador* nuevoJugador = new Jugador(nombre, id, puntos, vidas);
			lista.agregar(nuevoJugador);
		}
	}
	
	archivo.close();
	cout << ".\n" << endl;
	return lista;
}
