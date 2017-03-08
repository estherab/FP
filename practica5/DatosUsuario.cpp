#include <iostream>
#include <string>
using namespace std;

#include <iomanip> 
#include <fstream>

#include "DatosUsuario.h"

void inicializarUsuarios(tDatosUsuario &usuario) {
	inicializarListaMensajes(usuario.buzon, MAX_MEN); 
}

bool cargarUsuario(tDatosUsuario &usuario, ifstream &archivo) {
	bool exito = false;

	inicializarUsuarios(usuario);
	archivo >> usuario.nombre;
	
	if (usuario.nombre != "XXX") {
		cargarListaMensajes(usuario.buzon, archivo);
		exito = true;
	}

	return exito;
}

void mostrarUsuario(const tDatosUsuario &usuario) {

	cout << usuario.nombre << endl;
	mostrarListaMensajes(usuario.buzon);
	cout << endl;
}

void guardarUsuario(const tDatosUsuario &usuario, ofstream &archivo) {

	archivo << usuario.nombre << endl;
	
	if (usuario.buzon.cont == 0)
		archivo << '0' << endl ;
	
	else 
		guardarListaMensajes(usuario.buzon, archivo);
}
