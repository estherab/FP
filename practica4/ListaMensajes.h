#ifndef ListaMensajes_h
#define ListaMensajes_h

#include "Mensaje.h"

const int MaxMen = 10; 

typedef struct {
	tMensajePtn elem;
	int cont;
} tListaMensajes;

void inicializarListaMensajes(tListaMensajes &listaMensajes);
void cargarListaMensajes(tListaMensajes &listaMensajes, ifstream &archivo);
void mostrarListaMensajes(const tListaMensajes &listaMensajes);
void guardarListaMensajes(const tListaMensajes &listaMensajes, ofstream &archivo);
void anadirMensajeFinal(tListaMensajes &listaMensajes, tMensaje mensaje);
void consultarUltimoMensaje(const tListaMensajes &listaMensajes);

#endif