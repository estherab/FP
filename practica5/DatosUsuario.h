#ifndef DatosUsuario_h
#define DatosUsuario_h

#include "ListaMensajes.h"

typedef struct {
	string nombre;
	tListaMensajes buzon;
} tDatosUsuario;

typedef tDatosUsuario *tDatosUsuPtr;

/*
Funcion que llama a inicializar la lista de mensajes, para inicializar a lista de mensajes de un usuario.
*/
void inicializarUsuarios(tDatosUsuario &usuario);
/*
Función a la que se le pasa un archivo de lectura en el cual lee el nombre del usuario y comprueba que no sea el 
centinela y llama a otra función para que lea su lista de mensajes.
Devuelve si un bool, para saber si se ha cargado bien o no.
*/
bool cargarUsuario(tDatosUsuario &usuario, ifstream &archivo);
/*
Función que sirve para mostrar por pantalla, el nombre de el usuario, y a su vez esta función llama a otra función
para que muestre su lista de mensajes.
*/
void mostrarUsuario(const tDatosUsuario &usuario);
/*
Función a la que se le pasa un archivo de escritura para que escriba en el, el nombre del usuario, y se llama a otra funcíón
para que escriba la lista de mensajes de ese cliente.
*/
void guardarUsuario(const tDatosUsuario &usuario, ofstream &archivo);

#endif