#include <fstream>
#include "ListaMensajes.h"

void inicializarListaMensajes(tListaMensajes &listaMensajes, int tam_inicial) {
	listaMensajes.cont = 0;
	listaMensajes.max = tam_inicial; 
	listaMensajes.elem = new tMensaje[tam_inicial]; 
}

void cargarListaMensajes(tListaMensajes &listaMensajes, ifstream &archivo) {
	int numMensajes; 

	archivo >> numMensajes; 
	
	inicializarListaMensajes(listaMensajes, redondear(numMensajes));
	
	for (int i = 0; i < numMensajes; i++) {
		listaMensajes.elem[i] = leerMensaje(archivo); // Lee el mensaje y lo inserta en la lista
		listaMensajes.cont++;
	}
}

int redondear(int contador) {
	int nuevoContador;

	nuevoContador = ((contador / 10) + 1); 
	nuevoContador = nuevoContador * 10; 

	return nuevoContador;
}

void mostrarListaMensajes(const tListaMensajes &listaMensajes) {

	for (int i = 0; i < listaMensajes.cont; i++)
		// Recorre la lista de Mensajes, mostrando uno a uno
		mostrarMensaje(listaMensajes.elem[i]);
}

void guardarListaMensajes(const tListaMensajes &listaMensajes, ofstream &archivo) {
	tMensaje mensaje;

	// Escribe el número de mensajes que hay
	archivo << listaMensajes.cont << endl;
	
	for (int i = 0; i < listaMensajes.cont; i++) 
		// Guarda los mensajes en la lista de los mensajes uno a uno
		guardarMensaje(archivo,  listaMensajes.elem[i]);
}

void nuevaDimension(tListaMensajes &listaMensajes, int newCapacidad) {
	tMensajePtn PuntAuxMen; 

	PuntAuxMen = new tMensaje[newCapacidad];

	for (int i = 0; i < listaMensajes.cont; i++) {
		PuntAuxMen[i] = listaMensajes.elem[i]; // Copiamos lo que habia en el antiguo al nuevo
	}

	listaMensajes.max = newCapacidad;
	delete [] listaMensajes.elem; 

	listaMensajes.elem = PuntAuxMen;
}

void anadirMensajeFinal(tListaMensajes &listaMensajes, tMensaje mensaje) {
	int newCapacidad;

	// Compruebo si la capacidad del cont es la misma que la capacidad vieja
	if (listaMensajes.cont == listaMensajes.max) {
		newCapacidad = (((listaMensajes.max * 3)/ 2) + 1); // Si la lista esta llena ampliamos el array dinámico
		nuevaDimension(listaMensajes, newCapacidad);
	}

	listaMensajes.elem[listaMensajes.cont] = mensaje; // Inserto el mensaje en la lista de los mensajes
	listaMensajes.cont++;
}

void consultarUltimoMensaje(const tListaMensajes &listaMensajes) {
		
	mostrarMensaje(listaMensajes.elem[listaMensajes.cont - 1]); // Se muestra el último mensaje 
}

void destruirListaMensajes(tListaMensajes &listaMensajes) {
	delete []listaMensajes.elem; // Se destruyen todos a la vez
	listaMensajes.cont = 0;
	listaMensajes.max = 0;
}