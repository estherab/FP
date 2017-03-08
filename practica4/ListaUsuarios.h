#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include "DatosUsuario.h"

const int USU = 10; // Máximo de usuarios
const string USUARIOS = "usuarios.txt";

typedef tDatosUsuario tArrayUsu[USU];

typedef struct {
	tArrayUsu datos;
	int cont;
} tListaUsuarios;

void inicializarListaUsuarios(tListaUsuarios &listaUsu);
bool cargarListaUsuarios(tListaUsuarios &listaUsu);
void mostrarListaUsuarios(const tListaUsuarios &listaUsu);
bool buscarUsuario(const tListaUsuarios &listaUsu, string buscado, int &pos);
void guardarListaUsuarios(const tListaUsuarios &listaUsu, ofstream &archivo);
void anadirMensajeBuzon(tMensaje mensaje, string nombre ,tListaUsuarios &usuario);

#endif