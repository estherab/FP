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

typedef tChat *tPuntChat;

/*
Inicializa un chat que se acaba de crear. Recibe los datos del chat para inicializar 
la estructura y pone el contador de los mensajes a 0 (como el chat se acaba de crear,
aún no hay mensajes)
*/
void inicializarChat(tChat &chat, string id, string nombre);
/*
Carga un chat en el cliente registrado desde su archivo de chats (nombreUsuario_chats.txt). 
Devuelve una estructura de tipo tChat para introducirla en la lista de chats del usuario
*/
void cargarChat(ifstream &archivo, string usuario, tChat &chat);
/*
Guarda un chat del usuario en su archivo de chats (nombreUsuario_chats.txt)
*/
void guardarChat(ofstream &archivo, tChat chat);
/*
Función que muestra por pantalla el nombre de usuario del que posteriormente se van 
a mostrar todos sus chats.
*/
void mostrarCabecera(string usuario);
/*
Función que muestra por pantalla un chat con todos sus mensajes compuestos por 
el texto, la fecha y quien ha emitido el mensaje.
*/
void mostrarChat(tChat chat);

#endif


