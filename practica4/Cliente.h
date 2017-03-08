#ifndef Cliente_h
#define Cliente_h

#include "ListaChats.h"

typedef struct {
	string usuario;
	tListaChats listaChats;
} tDatosCliente;

tDatosCliente inicializarCliente(const tListaUsuarios &listaUsu, string cliente);
void mostrarMenu(tDatosCliente cliente);

#endif