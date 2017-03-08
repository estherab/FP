#ifndef DatosUsuario_h
#define DatosUsuario_h

#include "ListaMensajes.h"

typedef struct {
	string nombre;
	tListaMensajes buzon;
} tDatosUsuario;

void inicializarUsuarios(tDatosUsuario &usuario);
bool cargarUsuario(tDatosUsuario &usuario, ifstream &archivo);
void mostrarUsuario(const tDatosUsuario &usuario);
void guardarUsuario(const tDatosUsuario &usuario, ofstream &archivo);

#endif