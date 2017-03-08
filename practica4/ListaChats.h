#ifndef ListaChats_h
#define ListaChats_h

#include "Chat.h"

const int CHATS = 10;

typedef tChat tArrayChats[CHATS];

typedef struct {
	tArrayChats elem;
	int cont;
} tListaChats;

bool buscarChat(const tListaChats &listaChats, string nombre, int &posChats);
void inicializarListaChat(tListaChats &listaChats);
bool cargarListaChats(tListaChats &listaChats, string nombre);
void guardarListaChats(const tListaChats &listaChats, ofstream &archivo);
bool anadirChat(tChat chat, tListaChats &listaChat, string texto);
bool anadirChatSinMensaje(tChat chat, tListaChats &listaChats);
bool eliminarChat(tListaChats &listaChats, int pos);
void moverChat(tListaChats &listaChats, int pos);
void ordenarPorNombre(tListaChats &listaChats);
void ordenarPorFecha(tListaChats &listaChats);
void mostrarListaChats (const tListaChats &listaChats);

#endif