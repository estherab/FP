#ifndef ListaMensajes_h
#define ListaMensajes_h

#include "Mensaje.h"

const int MAX_MEN = 10; // Máximo de mensajes

typedef struct {
	tMensajePtn elem;
	int cont; // Capacidad que lees
	int max; // Capacidad actual
} tListaMensajes;

/*
Función que inicializa el contador a cero, incializa una cantidad máxima de mensajes y se crean todos los 
mensajes a la vez
*/
void inicializarListaMensajes(tListaMensajes &listaMensajes, int tam_inicial);
/*
Función que carga la lista de Mensajes, leyendo el mensaje completo y cargandolo en la lista de mensajes.
*/
void cargarListaMensajes(tListaMensajes &listaMensajes, ifstream &archivo);
/*
Función que muestra por pantalla la lista de mensajes.
*/
void mostrarListaMensajes(const tListaMensajes &listaMensajes);
/*
Función que se le pasa un archivo de escritura abierto, en el cual escribe el número de mensajes que tiene
y llama a otra función para que guarde uno a uno los mensajes existentes que tiene el cliente.
*/
void guardarListaMensajes(const tListaMensajes &listaMensajes, ofstream &archivo);
/*
Función que inserta al final de lista de mensajes, un mensaje e incrementa el contador de la lista.
*/
void anadirMensajeFinal(tListaMensajes &listaMensajes, tMensaje mensaje);
/*
Función que llama a otra función para mostrar el último mensaje existente en la lista de mensajes del cliente.
*/
void consultarUltimoMensaje(const tListaMensajes &listaMensajes);
/*
Función que al cargarse las listas desde el fichero, crear el array con una capacidad suficiente como para guardar
todos los elementos redondeando a la siguiente decena.
*/
int redondear(int contador);
/*
Función que copia lo que había en el antiguo array al nuevo, redimensionandolo
*/
void nuevaDimension(tListaMensajes &listaMensajes, int newCapacidad);
/*
Función que destruye todos los datos al final de programa
*/
void destruirListaMensajes(tListaMensajes &listaMensajes);

#endif