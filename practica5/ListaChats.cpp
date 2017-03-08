#include <iostream>
#include <string>
using namespace std;

#include <fstream>

#include "Cliente.h"
#include "ListaChats.h"
#include "ListaMensajes.h"

void inicializarListaChat(tListaChats &listaChats, int tam_inicial) {
	
	listaChats.cont = 0;
	listaChats.max = tam_inicial; 
	listaChats.elem = new tChat[tam_inicial];
}

bool buscarChat(const tListaChats &listaChats, string nombre, int &posChats) {
	bool encontrado = false;
	posChats = 0;

	while (!encontrado && (posChats < listaChats.cont)) {
		if (listaChats.elem[posChats].hablaCon == nombre)
			encontrado = true;

		else
			posChats++;
	}

	return encontrado;
}


bool cargarListaChats(tListaChats &listaChats, string nombre) {
	tChat chat;
	ifstream archivoChats;
	bool cargado = false;
	int numChats;

	archivoChats.open(nombre + "_chats.txt");

	if (archivoChats.is_open()) {
		archivoChats >> numChats;
		inicializarListaChat(listaChats, redondear(numChats));
		
		for (int i = 0; i < numChats; i++) {
			cargarChat(archivoChats, nombre, chat);
			listaChats.elem[listaChats.cont] = chat;
			listaChats.cont++;
		}
		
		cargado = true;
		archivoChats.close();
	}

	return cargado;
}

void guardarListaChats(const tListaChats &listaChats, ofstream &archivo) {

	archivo << listaChats.cont << endl; 
	
	for (int i = 0; i < listaChats.cont; i++)
		guardarChat(archivo, listaChats.elem[i]);

	//archivo << "XXX";
}

bool anadirChatSinMensaje(tChat chat, tListaChats &listaChats) {
	bool ok = false;
	int pos = 0;

	if (listaChats.cont < MaxChat) {
		listaChats.elem[listaChats.cont] = chat; // Se añade el chat al emisor
		listaChats.cont++; 

		ok = true;
	}

	return ok;
}

void anadirChat(tChat chat, tListaChats &listaChats, string texto) {
	int nuevaCapacidad;
	tMensaje mensajeAux;

	// Compruebo si la capacidad del cont es la misma que la capacidad vieja
	if (listaChats.cont == listaChats.max) {
		nuevaCapacidad = (((listaChats.max * 3) / 2) + 1); // Si la lista esta llena ampliamos el array dinámico
		nuevaDimensionChat(listaChats, nuevaCapacidad);
	}

	mensajeAux = crearMensaje(chat.usuario, chat.hablaCon, texto);
	chat.listaMensajes.cont++;
	chat.listaMensajes.elem[0] = mensajeAux;

	listaChats.elem[listaChats.cont] = chat; // Se añade el chat al emisor
	listaChats.cont++; 
}

bool eliminarChat(tListaChats &listaChats, int pos) {

	if ((pos < 0) || (pos >= listaChats.cont))
		return false; 

	else {
		for (int i = pos + 1; i < listaChats.cont; i++)
			listaChats.elem[i - 1] = listaChats.elem[i]; // Se elimina el chat

		listaChats.cont--; 
		return true;
	}
}

void moverChat(tListaChats &listaChats, int pos) {
	tChat tmp = listaChats.elem[pos];

	for (int i = pos; i < listaChats.cont - 1; i++)
		listaChats.elem[i] = listaChats.elem[i + 1];

	listaChats.elem[listaChats.cont - 1] = tmp;
}

void ordenarPorNombre(tListaChats &listaChats) {
	bool inter = true;
	int i = 0;

	while ((i < listaChats.cont - 1) && inter) {
		inter = false;
		
		for (int j = listaChats.cont - 1; j > i; j--)
			if (listaChats.elem[j].hablaCon < listaChats.elem[j - 1].hablaCon) {
				tChat tmp;
				tmp = listaChats.elem[j];
				listaChats.elem[j] = listaChats.elem[j - 1];
				listaChats.elem[j - 1] = tmp;
				inter = true;
			}

		if (inter) i++;
	}
}

void ordenarPorFecha(tListaChats &listaChats) {
	tListaMensajes listaMensajes;
	bool inter = true;
	int i = 0;

	while ((i < listaChats.cont - 1) && inter) {
		inter = false;
		
		for (int j = listaChats.cont - 1; j > i; j--)
			if (listaChats.elem[j].listaMensajes.elem[listaChats.elem[j].listaMensajes.cont-1].fecha <
				listaChats.elem[j - 1].listaMensajes.elem[listaChats.elem[j].listaMensajes.cont-1].fecha) {
					tChat tmp;
					tmp = listaChats.elem[j];
					listaChats.elem[j] = listaChats.elem[j - 1];
					listaChats.elem[j - 1] = tmp;
					inter = true;
			}

			if (inter) i++;
	}
}

void mostrarListaChats (const tListaChats &listaChats) {
	// Muestra el último mensaje de cada chat
	
	for (int i = 0; i < listaChats.cont; i++) {
		cout << i << ": " << listaChats.elem[i].hablaCon << endl;
		mostrarMensaje(listaChats.elem[i].listaMensajes.elem[listaChats.elem[i].listaMensajes.cont - 1]);
	}
}

void nuevaDimensionChat(tListaChats &listaChats, int nuevaCapacidad) {
	tPuntChat puntChatAux; // Puntero auxiliar

	puntChatAux = new tChat[nuevaCapacidad];

	for (int i = 0; i < listaChats.cont; i++) {
		puntChatAux[i] = listaChats.elem[i]; 

	listaChats.max = nuevaCapacidad;
	
	delete []listaChats.elem; // Eliminación

	listaChats.elem = puntChatAux; // Le pasamos la dir. del puntero
}

void destruirListaChats(tListaChats &listaChats) {

	for (int i = 0; i < listaChats.cont; i++) 
		 destruirListaMensajes(listaChats.elem[i].listaMensajes);

	delete []listaChats.elem; // Se destruyen todos a la vez
	listaChats.cont = 0;
	listaChats.max = 0;
}