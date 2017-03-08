#ifndef Mensaje_h
#define Mensaje_h

#include <string>
using namespace std;

#include <ctime>

typedef time_t tFecha; 

typedef struct {
	string emisor;
	string receptor;
	tFecha fecha;
	string texto;
} tMensaje;

typedef tMensaje *tMensajePtn;

tMensaje leerMensaje(ifstream &archivo);
void mostrarMensaje(tMensaje mensaje);
void mostrarFecha(const tFecha &fecha);
tMensaje crearMensaje(string cliente, string hablaCon, string texto);
void guardarMensaje(ofstream &archivo, tMensaje mensaje);

#endif
