#include <iostream>
#include <string>
using namespace std;

#include <fstream>

#include "Cliente.h"
#include "ListaChats.h"

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

void inicializarListaChat(tListaChats &listaChats) {
	listaChats.cont = 0;
}

bool cargarListaChats(tListaChats &listaChats, string nombre) {
	tChat chat;
	ifstream archivoChats;
	bool cargado = false;

	archivoChats.open(nombre + "_chats.txt");

	if (archivoChats.is_open()) {
		while ((listaChats.cont < MaxChat) && (cargarChat(archivoChats, nombre, chat))) {
			listaChats.elem[listaChats.cont] = chat;
			listaChats.cont++;
		}
		cargado = true;
		archivoChats.close();
	}

	return cargado;
}

void guardarListaChats(const tListaChats &listaChats, ofstream &archivo) {

	for (int i = 0; i < listaChats.cont; i++)
		guardarChat(archivo, listaChats.elem[i]);

	archivo << "XXX";
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

bool anadirChat(tChat chat, tListaChats &listaChats, string texto) {
	bool ok = false;
	tMensaje mensajeAux;

	if (listaChats.cont < MaxChat) {
		mensajeAux = crearMensaje(chat.usuario, chat.hablaCon, texto);

		chat.listaMensajes.cont++;
		chat.listaMensajes.elem[0] = mensajeAux; // Mensaje de inicio al principio

		listaChats.elem[listaChats.cont] = chat; // Se añade el chat al emisor
		listaChats.cont++; 

		ok = true;
	}

	return ok;
}

bool eliminarChat(tListaChats &listaChats, int pos) {

	if ((pos < 0) || (pos >= listaChats.cont))
		return false; // Si pos no válida

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
