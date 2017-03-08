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
Función que inicializa la lista de usuarios, poniendo el contador de dicha lista a cero.
*/
void inicializarListaUsuarios(tListaUsuarios &listaUsu);
/*
Función que abre un archivo de lectura para leer los usuarios y irlos cargando en una lista de usuarios.
Devuelve un tipo bool que te dice si se han cargado o no correctamente los usuarios
*/
bool cargarListaUsuarios(tListaUsuarios &listaUsu);
/*
Función que sirve para mostrar por pantalla la lista de la lista de usuarios, la cual llama a otra función para
para ir mostrandolos uno a uno por pantalla.
*/
void mostrarListaUsuarios(const tListaUsuarios &listaUsu);
/*
Función que busca un usuario en la lista de usuarios y devuelve dos cosas:
- Pos: si se ha encontrado devolvera el número de la posición en la que el usuario se encuentra en la lista
		si no se ha encontrado devolvera un -1.
-El éxito o no de búsqueda
*/
bool buscarUsuario(const tListaUsuarios &listaUsu, string buscado, int &pos);
/*
Función que escribe en un archivo de escritura que se le pasa el usuario correspondiente y se escribe al 
final, (después de haber escrito todos los usuarios) el centinela, en este caso: "XXX".
*/
void guardarListaUsuarios(const tListaUsuarios &listaUsu, ofstream &archivo);
/*
Función que añade un mensaje al buzón que tiene el usuario.
*/
void anadirMensajeBuzon(tMensaje mensaje, string nombre ,tListaUsuarios &usuario);
/*
Función que destruye todos los datos al final de programa
*/
void destruirListaUsu(tListaUsuarios &listaUsuarios);

#endif