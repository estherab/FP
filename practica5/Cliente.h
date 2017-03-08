#ifndef Cliente_h
#define Cliente_h

#include "ListaChats.h"

typedef struct {
	string usuario;
	tListaChats listaChats;
} tDatosCliente;

/*
Funci�n que inicializa un nuevo cliente cuando todav�a no tiene ning�n chat.
*/
tDatosCliente inicializarCliente(const tListaUsuarios &listaUsu, string cliente);
/*
Muestra el men� de un cliente compuesto por la cabecera, la lista de chats en caso de que los haya
y todas las opciones que puede realizar.
*/
void mostrarMenu(tDatosCliente cliente);

#endif