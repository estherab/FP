#include <iostream>
using namespace std;

#include <iomanip>

#include "Cliente.h"
#include "ListaChats.h"

tDatosCliente inicializarCliente(string cliente) {
	tDatosCliente datosCliente;

	datosCliente.usuario = cliente;
	datosCliente.listaChats.cont = 0;

	return datosCliente;
}

void mostrarMenu(tDatosCliente cliente) {

	mostrarCabecera(cliente.usuario);

	for (int i = 0; i < cliente.listaChats.cont; i++) {
		cout << i << ": " << cliente.listaChats.elem[i].hablaCon << endl ;
		mostrarMensaje(cliente.listaChats.elem[i].listaMensajes.elem[cliente.listaChats.elem[i].listaMensajes.cont-1]);
	}

	if (cliente.listaChats.cont == 0) {
		cout << "-------------------------------------------------------------------------------" << endl
			 << setw(50) << "No hay ningún chat" << endl
			 << "-------------------------------------------------------------------------------" << endl;
	}

	cout << "-------------------------------------------------------------------------------" << endl
		 << setw(37) << "Entrar al chat N: c N <intro>" << setw(40) << "Crear nuevo chat: n <intro>" << endl
		 << setw(37) << "Eliminar el chat N: e N <intro>" << setw(40) << "Ordenar chats por nombre: o n <intro>" << endl
		 << setw(37) << "Ordenar chats por fecha: o f <intro>" << setw(40) << "Salir: s <intro>" << endl
		 << "-------------------------------------------------------------------------------" << endl;
}





