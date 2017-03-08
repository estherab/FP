#ifndef ListaChats_h
#define ListaChats_h

#include "Chat.h"

const int CHATS = 10;

typedef struct {
	tPuntChat elem;
	int cont; // Capacidad leida
	int max; // Capacidad m�xima actual
} tListaChats;

/*
Funci�n que inicializa el contador a cero, incializa una cantidad m�xima de chats y se crean todos los 
chats a la vez
*/
void inicializarListaChat(tListaChats &listaChats, int tam_inicial);
/*
Funci�n que busca un chat en la lista. Recibe como argumento el nombre del chat a buscar 
(el nombre del chat es el usuario con el que se est� hablando). Devuelve una variable booleana
indicando si ha habido �xito en la b�squeda.
*/
bool buscarChat(const tListaChats &listaChats, string nombre, int &posChats);
/*
Lee la informaci�n del archivo nombreUsuario_chats.txt y la vuelca en la lista de chats.
*/
bool cargarListaChats(tListaChats &listaChats, string nombre);
/*
Funci�n que guarda todos los chats de un usuario en su archivo correspondiente cuando se cierra sesi�n.
Se guardan los chat que ya ha leido el usuario.
*/
void guardarListaChats(const tListaChats &listaChats, ofstream &archivo);
/*
Funci�n que a�ade un nuevo chat cuando el usuario elige la opci�n del men� "nuevo chat".
A�ade al chat el mensaje inicial de "Nuevo chat iniciado por..."
*/
void anadirChat(tChat chat, tListaChats &listaChats, string texto);
/*
Funci�n correspondiente a la opci�n del men� "eliminar chat". Se le proporciona el �ndice del
chat que debe eliminar y devuelve una variable booleana indicando si se ha eliminado. Tambi�n devuelve la 
lista de chats modificada (un chat menos).
*/
bool anadirChatSinMensaje(tChat chat, tListaChats &listaChats);
/*
Funci�n correspondiente a la opci�n del men� "eliminar chat". Se le proporciona el �ndice del
chat que debe eliminar y devuelve una variable booleana indicando si se ha eliminado. Tambi�n devuelve la 
lista de chats modificada (un chat menos).
*/
bool eliminarChat(tListaChats &listaChats, int pos);
/*
Funci�n encargada de mover un chat de posici�n en la lista. Se utiliza cuando se abre un chat para escribir en �l
porque ahora ese chat debe aparecer el �ltimo en la lista al ser el �ltimo en ser modificado.
*/
void moverChat(tListaChats &listaChats, int pos);
/*
Funci�n que ordena una lista de chats por su nombre (persona con quien se est� hablando).
*/
void ordenarPorNombre(tListaChats &listaChats);
/*
Funci�n que ordena una lista de chats en funci�n de la fecha del �ltimo mensaje de cada chat.
*/
void ordenarPorFecha(tListaChats &listaChats);
/*
Funci�n que muestra por pantalla el �ltimo mensaje de cada chat.
*/
void mostrarListaChats (const tListaChats &listaChats);
/*
Funci�n que copia lo que hab�a en el antiguo array al nuevo, redimensionandolo
*/
void nuevaDimensionChat(tListaChats &listaChats, int newCapacidad);
/*
Funci�n que destruye todos los datos al final de programa
*/
void destruirListaChats(tListaChats &listaChats);

#endif