#ifndef Cliente_h
#define Cliente_h

#include "ListaChats.h"

typedef struct {
	string usuario;
	tListaChats listaChats;
} tDatosCliente;

/*
Función que inicializa un nuevo cliente cuando todavía no tiene ningún chat.
*/
tDatosCliente inicializarCliente(const tListaUsuarios &listaUsu, string cliente);
/*
Muestra el menú de un cliente compuesto por la cabecera, la lista de chats en caso de que los haya
y todas las opciones que puede realizar.
*/
void mostrarMenu(tDatosCliente cliente);

#endif