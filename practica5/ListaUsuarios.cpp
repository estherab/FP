#include <iostream>
#include <string>
using namespace std;

#include <iomanip> 
#include <fstream>

#include "ListaUsuarios.h"

void inicializarListaUsuarios(tListaUsuarios &listaUsu) {
	listaUsu.cont = 0; 
}

bool cargarListaUsuarios(tListaUsuarios &listaUsu) {
	ifstream archivo; // Archivo de lectura
	tDatosUsuario datosUsu;
	bool exito = false;
	
	inicializarListaUsuarios(listaUsu);
	archivo.open(USUARIOS);

	if (archivo.is_open()) {
		while ((listaUsu.cont < MAXUSUARIOS) && (cargarUsuario(datosUsu, archivo))) {
			listaUsu.datos[listaUsu.cont] = new tDatosUsuario(datosUsu); // Meto el auxiliar que he leido en la lista
			listaUsu.cont++;
		}

		exito = true;
	}
	archivo.close();

	return exito;
}

void mostrarListaUsuarios(const tListaUsuarios &listaUsu) {

	for (int i = 0; i < listaUsu.cont; i++) 
		if (listaUsu.datos[i]->buzon.cont)
			mostrarUsuario(*listaUsu.datos[i]);
}

bool buscarUsuario(const tListaUsuarios &listaUsu, string buscado, int &pos) {
	int ini = 0, fin = listaUsu.cont, mitad;
	bool encontrado = false;
	pos = 0; 

	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (buscado < listaUsu.datos[mitad]->nombre)
			fin = mitad - 1;
		else if (listaUsu.datos[mitad]->nombre < buscado)
			ini = mitad + 1;
		else
			encontrado = true;
	}

	if (encontrado)
		pos = mitad;
	else
		pos = -1; // Si no se ha encontrado devuelve -1

	return encontrado;
}

void guardarListaUsuarios(const tListaUsuarios &listaUsu, ofstream &archivo) {

	for (int i = 0; i < listaUsu.cont; i++) 
		guardarUsuario(*listaUsu.datos[i], archivo); // Escribe un usuario

	archivo << "XXX"; 
}

void anadirMensajeBuzon(tMensaje mensaje, string nombre ,tListaUsuarios &usuario) {
	int pos;

	buscarUsuario(usuario, nombre, pos);

	anadirMensajeFinal(usuario.datos[pos]->buzon, mensaje);
}

void destruirListaUsu(tListaUsuarios &listaUsuarios) {
	
	for (int i = 0; i < listaUsuarios.cont; i++)  {
		destruirListaMensajes(listaUsuarios.datos[i]->buzon);
		delete listaUsuarios.datos[i]; // Devolvemos la memoria al montón
	}
}