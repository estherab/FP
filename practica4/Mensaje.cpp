#include <string>
#include <iostream>
using namespace std;

#include <fstream>

#include "Mensaje.h"

tMensaje leerMensaje(ifstream &archivo) {
	tMensaje mensaje;

	// Lee del archivo el emisor, la fecha y el mensaje
	archivo >> mensaje.emisor;
	archivo >> mensaje.fecha;
	getline(archivo, mensaje.texto);

	return mensaje;
}

void mostrarMensaje(tMensaje mensaje) {

	// Muestra el mensaje, compuesto por: emisor, fecha y texto
	cout << mensaje.emisor;
	cout << " ";
	mostrarFecha(mensaje.fecha);
	cout << " ";
	cout << mensaje.texto << endl;
}

void mostrarFecha(const tFecha &fecha) {
	tm ltm;

	localtime_s(&ltm, &fecha);
	cout << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	cout << ", "<< ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec;
} 

tMensaje crearMensaje(string cliente, string hablaCon, string texto) {
	tMensaje mensaje;

	mensaje.emisor = cliente;
	mensaje.receptor = hablaCon;
	mensaje.texto = texto;
	mensaje.fecha = time(0);

	return mensaje;
}

void guardarMensaje(ofstream &archivo, tMensaje mensaje) {

	// Guarda en un archivo el mensaje, compuesto por: emisor, fecha y texto.
	archivo << mensaje.emisor << " ";
	archivo << mensaje.fecha ;
	archivo << mensaje.texto << endl;
}
