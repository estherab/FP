#ifndef Chat_h
#define Chat_h

#include "ListaMensajes.h"
#include "ListaUsuarios.h"

const int MaxChat = 10;

typedef struct {
	string usuario;
	string hablaCon;
	tListaMensajes listaMensajes;
} tChat;

void inicializarChat(tChat &chat, string id, string nombre);
bool cargarChat(ifstream &archivo, string usuario, tChat &chat);
void guardarChat(ofstream &archivo, tChat chat);
void mostrarCabecera(string usuario);
void mostrarChat(tChat chat);

#endif


