#include <iostream>
#include <string>
using namespace std;

#include <fstream>
#include <iomanip>

#include "ListaUsuarios.h"
#include "DatosUsuario.h"
#include "Cliente.h"
#include "Chat.h"
#include "ListaChats.h"
#include "ListaMensajes.h"
#include "Mensaje.h"

typedef struct {
	tListaUsuarios listaUsuarios;
} tServidor;

void opNuevoChat(tDatosCliente &cliente, tServidor &servidor);
void opEliminarChat(tDatosCliente &cliente, int pos);
void opEntrarChat(tServidor &servidor, tDatosCliente &cliente, int pos);
void opOrdenarNombre(tDatosCliente &cliente);
void opOrdenarFecha(tDatosCliente &cliente);
void enviarMensaje(string texto, tServidor &servidor, tDatosCliente &cliente, tChat &chat);
void ejecutaCliente(tDatosCliente &cliente, tServidor &servidor, int pos);
void vaciarBuzon(tServidor &servidor, tDatosCliente &cliente, int pos);


int main() {
	tServidor servidor;
	tDatosCliente clienteActual;
	string usuarioLeido;
	ofstream salidaChats, salidaUsuarios;
	int pos;

	system("chcp 1252");

	if (!cargarListaUsuarios(servidor.listaUsuarios)) {
		cout << "ERROR: el fichero usuarios.txt no se encuentra o no es válido" << endl;
		system("pause");
	}

	else {
		cout << "Usuario (0 para salir): ";
		cin >> usuarioLeido;

		while (usuarioLeido != "0") { 
			if (buscarUsuario(servidor.listaUsuarios, usuarioLeido, pos)) {
				clienteActual.usuario = usuarioLeido;
				
				if (!cargarListaChats(clienteActual.listaChats, clienteActual.usuario)) 
					inicializarListaChat(clienteActual.listaChats);

				ejecutaCliente(clienteActual, servidor, pos);
			}

			else {
				cout << "Usuario no existente. Inténtelo de nuevo!" << endl;
				system("pause");
			}

			system("cls");
			cout << "Usuario (0 para salir): ";
			cin >> usuarioLeido;
		}
	}

	return 0;
}

void opNuevoChat(tDatosCliente &cliente, tServidor &servidor) {
	string nombre;
	tChat chat;
	int pos;

	string texto = "Nuevo chat iniciado por " + cliente.usuario;

	cout << "Id de usuario con quien quiere crear un nuevo chat: ";
	cin >> nombre;

	while (!buscarUsuario(servidor.listaUsuarios, nombre, pos)) {
		cout << "ERROR: usuario no existente!" << endl;
		system("pause");
		system("cls");
		cout << "Id de usuario con quien quiere crear un nuevo chat: ";
		cin >> nombre;
	}
	
	// Creo y añado el chat al cliente actual
	inicializarChat(chat, cliente.usuario, nombre);
	anadirChat(chat, cliente.listaChats, texto);

	// Creo y añado el mensaje al buzón del usuario
	tMensaje mensajeAux;
	mensajeAux = crearMensaje(chat.usuario, chat.hablaCon, texto);
	anadirMensajeBuzon(mensajeAux, chat.hablaCon, servidor.listaUsuarios);
}

void opEliminarChat(tDatosCliente &cliente, int pos) { 
	int posChats; // Posición del chat del receptor

	if (!eliminarChat(cliente.listaChats, pos))
		cout << "ERROR: índice de chat no válido!" << endl;

	else { 
		buscarChat(cliente.listaChats, cliente.listaChats.elem[pos].hablaCon, posChats); // Devuelve pos del chat receptor
		cout << "ERROR: No se ha eliminado el Chat de: " << cliente.listaChats.elem[pos].hablaCon << endl;
	}

	system("cls");
	mostrarMenu(cliente);
}

void opEntrarChat(tServidor &servidor, tDatosCliente &cliente, int pos) {
	string texto;

	if ((cliente.listaChats.cont == 0) || (pos >= cliente.listaChats.cont)) {
		cout << "ERROR: Índice de chat no válido!" << endl;
		system("pause");
	}

	else {
		cout << "-------------------------------------------------------------------------------" << endl
			 << setw(40) <<  "CHAT CON " << cliente.listaChats.elem[pos].hablaCon << endl
			 << "-------------------------------------------------------------------------------" << endl;
		mostrarChat(cliente.listaChats.elem[pos]);

		cout << "Escribe aquí ($salir$ para salir): ";
		cin.sync();
		getline(cin, texto);

		while (texto != "$salir$") {
			enviarMensaje(texto, servidor, cliente, cliente.listaChats.elem[pos]);
			system("cls");
			mostrarChat(cliente.listaChats.elem[pos]);

			cout << "Escribe aquí ($salir$ para salir): ";
			getline(cin, texto);
		}
	}
}

void opOrdenarNombre(tDatosCliente &cliente) {
	ordenarPorNombre(cliente.listaChats);
}

void opOrdenarFecha(tDatosCliente &cliente) {
	ordenarPorFecha(cliente.listaChats);
}

void enviarMensaje(string texto, tServidor &servidor, tDatosCliente &cliente, tChat &chat) {
	tMensaje mensaje;
	int pos;

	mensaje = crearMensaje(cliente.usuario, chat.hablaCon, texto); 

	buscarUsuario(servidor.listaUsuarios, chat.hablaCon, pos); 
	// Se añade el mensaje al buzón del receptor
	anadirMensajeFinal(servidor.listaUsuarios.datos[pos].buzon, mensaje);
	pos = 0;

	//Se añade mensaje al cliente
	buscarChat(cliente.listaChats, chat.hablaCon, pos);
	anadirMensajeFinal(cliente.listaChats.elem[pos].listaMensajes, mensaje);
}

void ejecutaCliente(tDatosCliente &cliente, tServidor &servidor, int pos) {
	int num;
	string opcion, aux;
	ofstream salidaChats, salidaUsuarios;

	vaciarBuzon(servidor, cliente, pos);
	mostrarMenu(cliente);

	cin >> opcion;

	while (opcion != "s") {
		if (opcion == "c") {
			cin >> num;
			system("cls");
			opEntrarChat(servidor, cliente, num);
		}

		else if (opcion == "n") 
			opNuevoChat(cliente, servidor);

		else if (opcion == "e") {
			cin >> num;
			opEliminarChat(cliente, num);
		}

		else if (opcion == "o") {
			cin >> aux;
			if (aux == "n")
				opOrdenarNombre(cliente);

			else if (aux == "f")
				opOrdenarFecha(cliente);

			else {
				cout << "Opción no válida! Inténtelo de nuevo" << endl;
				system("pause");
			}
		}

		else {
			cout << "Opción no válida. Inténtelo de nuevo!" << endl;
			system("pause");
		}
		system("cls");
		mostrarMenu(cliente);
		cin >> opcion;
	}

	salidaChats.open(cliente.usuario + "_chats.txt");
	guardarListaChats(cliente.listaChats, salidaChats);
	salidaChats.close();

	salidaUsuarios.open(USUARIOS);
	guardarListaUsuarios(servidor.listaUsuarios, salidaUsuarios);
	salidaUsuarios.close();
}

void vaciarBuzon(tServidor &servidor, tDatosCliente &cliente, int pos) {
	int posChat;

	// Recorro el buzón del cliente y añado los chats del buzón a la lista del cliente
	for (int i = 0; i < servidor.listaUsuarios.datos[pos].buzon.cont; i++) {
		// Si el chat ya está, añado el mensaje al final
		if (buscarChat(cliente.listaChats, servidor.listaUsuarios.datos[pos].buzon.elem[i].emisor, posChat)) {
			cliente.listaChats.elem[posChat].listaMensajes.elem[cliente.listaChats.elem[posChat].listaMensajes.cont++] = 
			servidor.listaUsuarios.datos[pos].buzon.elem[i];
		} 
		
		else { // Si el chat no existe, lo creo
			tChat chat;
			chat.usuario = cliente.usuario;
			chat.hablaCon = servidor.listaUsuarios.datos[pos].buzon.elem[i].emisor;

			inicializarListaMensajes(chat.listaMensajes);

			chat.listaMensajes.elem[chat.listaMensajes.cont++] = servidor.listaUsuarios.datos[pos].buzon.elem[i];

			anadirChatSinMensaje(chat, cliente.listaChats);
		}
	}
	// Borro el buzón
	servidor.listaUsuarios.datos[pos].buzon.cont = 0;
}