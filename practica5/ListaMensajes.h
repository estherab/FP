#ifndef ListaMensajes_h
#define ListaMensajes_h

#include "Mensaje.h"

const int MAX_MEN = 10; // M�ximo de mensajes

typedef struct {
	tMensajePtn elem;
	int cont; // Capacidad que lees
	int max; // Capacidad actual
} tListaMensajes;

/*
Funci�n que inicializa el contador a cero, incializa una cantidad m�xima de mensajes y se crean todos los 
mensajes a la vez
*/
void inicializarListaMensajes(tListaMensajes &listaMensajes, int tam_inicial);
/*
Funci�n que carga la lista de Mensajes, leyendo el mensaje completo y cargandolo en la lista de mensajes.
*/
void cargarListaMensajes(tListaMensajes &listaMensajes, ifstream &archivo);
/*
Funci�n que muestra por pantalla la lista de mensajes.
*/
void mostrarListaMensajes(const tListaMensajes &listaMensajes);
/*
Funci�n que se le pasa un archivo de escritura abierto, en el cual escribe el n�mero de mensajes que tiene
y llama a otra funci�n para que guarde uno a uno los mensajes existentes que tiene el cliente.
*/
void guardarListaMensajes(const tListaMensajes &listaMensajes, ofstream &archivo);
/*
Funci�n que inserta al final de lista de mensajes, un mensaje e incrementa el contador de la lista.
*/
void anadirMensajeFinal(tListaMensajes &listaMensajes, tMensaje mensaje);
/*
Funci�n que llama a otra funci�n para mostrar el �ltimo mensaje existente en la lista de mensajes del cliente.
*/
void consultarUltimoMensaje(const tListaMensajes &listaMensajes);
/*
Funci�n que al cargarse las listas desde el fichero, crear el array con una capacidad suficiente como para guardar
todos los elementos redondeando a la siguiente decena.
*/
int redondear(int contador);
/*
Funci�n que copia lo que hab�a en el antiguo array al nuevo, redimensionandolo
*/
void nuevaDimension(tListaMensajes &listaMensajes, int newCapacidad);
/*
Funci�n que destruye todos los datos al final de programa
*/
void destruirListaMensajes(tListaMensajes &listaMensajes);

#endif