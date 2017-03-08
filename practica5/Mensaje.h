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

/*
Funcion que recibe un archivo abierto para su correspondiente lectura y lee un mensaje, que consta de emisor, fecha y texto.
Devuelve dicho mensaje leido en el archivo.
*/
tMensaje leerMensaje(ifstream &archivo);
/*
Función que muestra un mensaje por pantalla, mostrando: emisor, fecha y texto.
*/
void mostrarMensaje(tMensaje mensaje);
/*
Función que sirve para mostrar la fehca en formato Año/Mes/Día, Hora/Minutos/Segundos
*/
void mostrarFecha(const tFecha &fecha);
/*
Fucnión que crea un mensaje, incluyendo en el emisor, receptor, texto y fecha (a la que ha sido enviada).
Devuelve el respectivo mensaje
*/
tMensaje crearMensaje(string cliente, string hablaCon, string texto);
/*
Función a la cual se le pasa un archivo de escritura abierto, para que escriba en el un respectivo mensaje
que consta de su emisor, fecha y texto.
*/
void guardarMensaje(ofstream &archivo, tMensaje mensaje);

#endif
