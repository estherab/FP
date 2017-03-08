#ifndef ListaChats_h
#define ListaChats_h

#include "Chat.h"

const int CHATS = 10;

typedef struct {
	tPuntChat elem;
	int cont; // Capacidad leida
	int max; // Capacidad máxima actual
} tListaChats;

/*
Función que inicializa el contador a cero, incializa una cantidad máxima de chats y se crean todos los 
chats a la vez
*/
void inicializarListaChat(tListaChats &listaChats, int tam_inicial);
/*
Función que busca un chat en la lista. Recibe como argumento el nombre del chat a buscar 
(el nombre del chat es el usuario con el que se está hablando). Devuelve una variable booleana
indicando si ha habido éxito en la búsqueda.
*/
bool buscarChat(const tListaChats &listaChats, string nombre, int &posChats);
/*
Lee la información del archivo nombreUsuario_chats.txt y la vuelca en la lista de chats.
*/
bool cargarListaChats(tListaChats &listaChats, string nombre);
/*
Función que guarda todos los chats de un usuario en su archivo correspondiente cuando se cierra sesión.
Se guardan los chat que ya ha leido el usuario.
*/
void guardarListaChats(const tListaChats &listaChats, ofstream &archivo);
/*
Función que añade un nuevo chat cuando el usuario elige la opción del menú "nuevo chat".
Añade al chat el mensaje inicial de "Nuevo chat iniciado por..."
*/
void anadirChat(tChat chat, tListaChats &listaChats, string texto);
/*
Función correspondiente a la opción del menú "eliminar chat". Se le proporciona el índice del
chat que debe eliminar y devuelve una variable booleana indicando si se ha eliminado. También devuelve la 
lista de chats modificada (un chat menos).
*/
bool anadirChatSinMensaje(tChat chat, tListaChats &listaChats);
/*
Función correspondiente a la opción del menú "eliminar chat". Se le proporciona el índice del
chat que debe eliminar y devuelve una variable booleana indicando si se ha eliminado. También devuelve la 
lista de chats modificada (un chat menos).
*/
bool eliminarChat(tListaChats &listaChats, int pos);
/*
Función encargada de mover un chat de posición en la lista. Se utiliza cuando se abre un chat para escribir en él
porque ahora ese chat debe aparecer el último en la lista al ser el último en ser modificado.
*/
void moverChat(tListaChats &listaChats, int pos);
/*
Función que ordena una lista de chats por su nombre (persona con quien se está hablando).
*/
void ordenarPorNombre(tListaChats &listaChats);
/*
Función que ordena una lista de chats en función de la fecha del último mensaje de cada chat.
*/
void ordenarPorFecha(tListaChats &listaChats);
/*
Función que muestra por pantalla el último mensaje de cada chat.
*/
void mostrarListaChats (const tListaChats &listaChats);
/*
Función que copia lo que había en el antiguo array al nuevo, redimensionandolo
*/
void nuevaDimensionChat(tListaChats &listaChats, int newCapacidad);
/*
Función que destruye todos los datos al final de programa
*/
void destruirListaChats(tListaChats &listaChats);

#endif