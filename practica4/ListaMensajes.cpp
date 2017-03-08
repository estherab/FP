#include <fstream>
#include "ListaMensajes.h"

void inicializarListaMensajes(tListaMensajes &listaMensajes) {
	listaMensajes.cont = 0;
}

void cargarListaMensajes(tListaMensajes &listaMensajes, ifstream &archivo) {
	inicializarListaMensajes(listaMensajes);
	// Lee el número de mensajes que hay
	archivo >> listaMensajes.cont;

	for (int i = 0; i < listaMensajes.cont; i++) 
		listaMensajes.elem[i] = leerMensaje(archivo); // Lee el mensaje y lo inserta en la lista
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

void anadirMensajeFinal(tListaMensajes &listaMensajes, tMensaje mensaje) {

	if (listaMensajes.cont < MaxMen) {
		listaMensajes.elem[listaMensajes.cont] = mensaje; 
		listaMensajes.cont++;
	}
}

void consultarUltimoMensaje(const tListaMensajes &listaMensajes) {
	
	mostrarMensaje(listaMensajes.elem[listaMensajes.cont - 1]); // Se muestra el último mensaje 
}
