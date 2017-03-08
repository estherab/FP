#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include "DatosUsuario.h"

const int MAXUSUARIOS = 50; 
const string USUARIOS = "usuarios.txt";

typedef tDatosUsuPtr tArrayUsu[MAXUSUARIOS];

typedef struct {
	tArrayUsu datos;
	int cont;
} tListaUsuarios;

/*
Funci�n que inicializa la lista de usuarios, poniendo el contador de dicha lista a cero.
*/
void inicializarListaUsuarios(tListaUsuarios &listaUsu);
/*
Funci�n que abre un archivo de lectura para leer los usuarios y irlos cargando en una lista de usuarios.
Devuelve un tipo bool que te dice si se han cargado o no correctamente los usuarios
*/
bool cargarListaUsuarios(tListaUsuarios &listaUsu);
/*
Funci�n que sirve para mostrar por pantalla la lista de la lista de usuarios, la cual llama a otra funci�n para
para ir mostrandolos uno a uno por pantalla.
*/
void mostrarListaUsuarios(const tListaUsuarios &listaUsu);
/*
Funci�n que busca un usuario en la lista de usuarios y devuelve dos cosas:
- Pos: si se ha encontrado devolvera el n�mero de la posici�n en la que el usuario se encuentra en la lista
		si no se ha encontrado devolvera un -1.
-El �xito o no de b�squeda
*/
bool buscarUsuario(const tListaUsuarios &listaUsu, string buscado, int &pos);
/*
Funci�n que escribe en un archivo de escritura que se le pasa el usuario correspondiente y se escribe al 
final, (despu�s de haber escrito todos los usuarios) el centinela, en este caso: "XXX".
*/
void guardarListaUsuarios(const tListaUsuarios &listaUsu, ofstream &archivo);
/*
Funci�n que a�ade un mensaje al buz�n que tiene el usuario.
*/
void anadirMensajeBuzon(tMensaje mensaje, string nombre ,tListaUsuarios &usuario);
/*
Funci�n que destruye todos los datos al final de programa
*/
void destruirListaUsu(tListaUsuarios &listaUsuarios);

#endif