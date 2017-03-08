#include <string>
#include <iostream>
using namespace std;

#include <fstream>
#include <iomanip>

#include "Chat.h"
#include "ListaUsuarios.h"

void inicializarChat(tChat &chat, string id, string nombre) {

	chat.usuario = id;
	chat.hablaCon = nombre;
	inicializarListaMensajes(chat.listaMensajes, MAX_MEN);
}

void cargarChat(ifstream &archivo, string usuario, tChat &chat) { 

	int numMensajes;
	chat.usuario = usuario;
	archivo >> chat.hablaCon;

	archivo >> numMensajes;
	inicializarListaMensajes(chat.listaMensajes, redondear(numMensajes));

	for (int i = 0; i < numMensajes; i++) {
		chat.listaMensajes.elem[i] = leerMensaje(archivo);
		chat.listaMensajes.cont++;
	}
} 

void guardarChat(ofstream &archivo, tChat chat) { 

	archivo << chat.hablaCon << endl;
	guardarListaMensajes(chat.listaMensajes, archivo);
}

void mostrarCabecera(string usuario) {

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << setw(50) << "CHATSAPP 1.0: Chats de " << usuario << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
}

void mostrarChat(tChat chat) {

	for (int i = 0; i < chat.listaMensajes.cont; i++) { 
		cout << i << ": " << chat.hablaCon << endl;
		mostrarMensaje(chat.listaMensajes.elem[i]);
		cout << "-------------------------------------------------------------------------------" << endl;
	}
}
