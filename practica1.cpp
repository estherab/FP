// Esther �vila Benito y Laura P�rez Jambrina

#include <iostream>
#include <string>
using namespace std;

#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

const int INTENTOS = 3;
const int LONGITUD = 4;
const int INTERVALO = 3;
const string ARCH_REGLAS = "versionCB.txt";
const string ARCH_VARIABLES = "configCB.txt";

/*
Funci�n que muestra el men� y devuelve la opci�n elegida por el usuario
*/
int menu();
/*
Devuelve un entero con la clave aleatoria generada por el ordenador.
La clave consta de LONGITUD d�gitos que est�n entre 1 e INTERVALO.
*/
int claveAleatoria(int longitud, int intervalo);
/*
Funci�n que devuelve una variable booleanoa indicando si la clave introducida por el usuario 
cumple las condiciones de longitud e intervalo.
*/
bool codigoValido(int clave, int intervalo, int longitud);
/*
Funci�n que compara la clave generada por el ordenador y la introducida por el usuario (par�metros) y devuelve el n�mero
de d�gitos coincidentes entre ellas. La comparaci�n finalizar� en cuanto se encuentre el primer d�gito que no coincida.
*/
int numeroBips(int claveMaquina, int clave);
/*
Funci�n que se emplea para invertir ambas claves con el fin de facilitar la comparaci�n.
Como salida obtenemos la clave introducida, pero invertida.
*/
int invertir(int clave);
/*
Funci�n principal que controla todo el desarrollo del juego. Desde ella invocamos a todas las funciones necesarias
para la manipulaci�n de las contrase�as.
Como salida, devuelve el n�mero de intentos empleados para adivinar la clave (nunca mayor que INTENTOS).
*/
void codeBreaker(int maxIntentos, int longitud, int intervalo);
/*
Funci�n que pide al usuario el nuevo n�mero de intentos y lo modifica en la variable maxIntentos.
*/
int pedirIntentos();
/*
Funci�n que pide al usuario la nueva longitud del d�gito y la modifica en la variable longitud.
*/
int pedirLongitud();
/*
Funci�n que pide al usuario el nuevo intervalo de d�gitos y lo modifica en la variable intervalo.
*/
int pedirIntervalo();
/*
Funci�n que muestra por consola el contenido del archivo "versionCB.txt"
*/
void instrucciones();
/*
Funci�n que devuelve una variable booleana indicando si se ha encontrado el archivo "versionCB.txt"
*/
bool mostrar(ifstream &archivo);
/*
Funci�n que lee las variables maxIntentos, longitud e intervalo del archivo "versionCB.txt" y 
se las comunica a codeBreaker() para la ejecuci�n del juego.
*/
void leerVariables(int &maxIntentos, int &longitud, int &intervalo);
/*
Funci�n que hace que al final del programa se guarde en el archivo los valores 
de las variables en el orden indicado.
*/
void guardarVariables (int maxIntentos, int longitud, int intervalo);
/*
Funci�n en la que el ordenador crea su propio c�digo para poder jugar contra el mismo.
*/
void rompedorAutomatico(int maxIntentos, int longitud, int intervalo);
/*
Funci�n para emitir un sonido similar a "BIP!" a trav�s de la funci�n "Beep()"  
contenida en la biblioteca Windows.h
*/
void bip();
/*
Funci�n para emitir un sonido similar a "BOP!" a trav�s de la funci�n "Beep()"  
contenida en la biblioteca Windows.h
*/
void bop();

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main() {
	int maxIntentos = INTENTOS, longitud = LONGITUD, intervalo = INTERVALO, opcion;

	system("chcp 1252");
	srand(time(NULL)); // Semilla

	leerVariables(maxIntentos, longitud, intervalo); 
	// Lee las variables del archivo

	do {
		opcion = menu();

		switch (opcion) {
		case 1:
			codeBreaker(maxIntentos, longitud, intervalo);
			break;
		case 2:
			maxIntentos = pedirIntentos();
			break;
		case 3:
			longitud = pedirLongitud();
			break;
		case 4:
			intervalo = pedirIntervalo();
			break;
		case 5:
			instrucciones();
			break;
		case 6:
			rompedorAutomatico(maxIntentos, longitud, intervalo);
			break;
		}

		guardarVariables (maxIntentos, longitud, intervalo); 
		// Guarda las �ltimas variables utilizadas en el archivo

	} while (opcion != 0);

	return 0;
}

int menu() {
	int opcion;

	do {
		cout << endl 
			<< "\t*************************" << endl
			<< "\t*      CODEBREAKER      *"  << endl
			<< "\t*************************" << endl
			<< endl << "1 - Jugar" << endl
			<< "2 - Cambiar el n�mero m�ximo de intentos" << endl
			<< "3 - Cambiar la longitud de los c�digos" << endl
			<< "4 - Cambiar el intervalo de d�gitos" << endl
			<< "5 - Acerca de CodeBreaker" << endl
			<< "6 - Rompedor autom�tico" << endl
			<< "0 - Salir" << endl
			<< "Opci�n: ";
		cin.sync();
		cin >> opcion;
		cout << endl;

		if ((opcion < 0) && (opcion > 6))
			cout << "Opci�n incorrecta. Int�ntalo de nuevo!" << endl;
	} while ((opcion < 0) && (opcion > 6)); // Mientras que la opci�n sea incorrecta, la sigue pidiendo

	return opcion;
}

int claveAleatoria(int longitud, int intervalo) {
	int claveMaquina = 0;

	for (int i = 0; i < longitud; i++) // Genera tantos d�gitos aleatorios como longitud tiene la clave
		claveMaquina = claveMaquina * 10 + (int (rand() % intervalo) + 1);

	return claveMaquina;
}

bool codigoValido(int clave, int intervalo, int longitud) {
	bool intervaloOK = true;
	int digitos = 0, aux;

	while (clave > 0 && intervaloOK) {
		aux = clave % 10;
		clave = clave / 10;
		intervaloOK = ((aux >= 1) && (aux <= intervalo));
		digitos++;
	}

	return ((digitos == longitud) && (intervaloOK));
}

int numeroBips(int claveMaquina, int clave) {
	int coincidentes = 0, nuevaMaquina, nuevaUsuario;

	nuevaMaquina = claveMaquina % 10;
	claveMaquina = claveMaquina / 10;

	nuevaUsuario = clave % 10;
	clave = clave / 10;

	while ((nuevaMaquina == nuevaUsuario) && (nuevaMaquina > 0) && (nuevaUsuario > 0)) { 
		// Cuando encuentra el primer d�gito no coincidente termina la comparaci�n
		coincidentes++;

		nuevaMaquina = claveMaquina % 10;
		claveMaquina = claveMaquina / 10;

		nuevaUsuario = clave % 10;
		clave = clave / 10;
	}

	return coincidentes;
}

int invertir(int clave) {
	int nuevaClave = 0;

	while (clave > 0) {
		nuevaClave = nuevaClave * 10 + (clave % 10);
		clave = clave / 10;
	}

	return nuevaClave;
}

void codeBreaker(int maxIntentos, int longitud, int intervalo) {
	int intentos = 0, clave, claveMaquina, claveComputadora, claveUsuario, coincidentes = 0;
	bool codigoOK = false;

	cout << "Codebreaker... " << maxIntentos << " intentos, longitud " << longitud << " - 1..." << intervalo << endl
	     << endl << "Introduce una clave (0 para terminar): ";
	cin >> clave;

	codigoOK = codigoValido(clave, intervalo, longitud);

	while ((!codigoOK) && (clave != 0)) { // Si la clave introducida no es correcta, la vuelve a pedir
		cout << endl << "Introduce una clave (0 para terminar): ";
		cin >> clave;
		codigoOK = codigoValido(clave, intervalo, longitud);
	}

	claveMaquina = claveAleatoria(longitud, intervalo);

	while ((clave != 0) && (intentos < maxIntentos) && (coincidentes != longitud)) {
		claveUsuario = invertir(clave);
		claveComputadora = invertir(claveMaquina);

		coincidentes = numeroBips(claveComputadora, claveUsuario);

		for (int i = 0; i < coincidentes; i++) {
			bip();
			cout << "bip ";
		}

		if (coincidentes < longitud) {
			bop();
			cout << "bop -- Acceso Denegado" << endl;
		}

		else
			cout << "-- Autorizado!" << endl;

		intentos++;

		if (coincidentes == longitud) 
			cout << endl << "ENHORABUENA. HAS ADIVINADO EL C�DIGO!" << endl;

		else if ((coincidentes < longitud) && (intentos < maxIntentos)) {
			cout << endl << "Introduce una clave (0 para terminar): ";
			cin >> clave;
			codigoOK = codigoValido(clave, intervalo, longitud);

			while ((!codigoOK) && (clave != 0)) { // Se vuelve a tener en cuenta que la clave introducida cumple los requisitos
				cout << endl << "Introduce una clave (0 para terminar): ";
				cin >> clave;
				codigoOK = codigoValido(clave, intervalo, longitud);
			}
		}
	}

	if ((intentos == maxIntentos) && (coincidentes != longitud))
		cout << "Has agotado el n�mero m�ximo de intentos. Lo siento, has perdido!" << endl; 

	else
		cout << "Has utilizado " << intentos << " intento(s)."<< endl;
}

int pedirIntentos() {
	int maxIntentos;

	do {
		cout << "Introduce el nuevo m�ximo de intentos: ";
		cin >> maxIntentos;
	} while (maxIntentos <= 0);
	
	cout << "M�ximo de intentos modificado!" << endl;

	return maxIntentos;
}

int pedirLongitud() {
	int longitud;

	do {
		cout << "Introduce la nueva longitud de clave: ";
		cin >> longitud;
	} while (longitud <= 0);
	cout << "Longitud de c�digo modificada!" << endl;

	return longitud;
}

int pedirIntervalo() {
	int intervalo;

	do {
		cout << "Introduce el nuevo d�gito m�ximo: ";
		cin >> intervalo;
	} while ((intervalo <= 0) || (intervalo > 9));
	cout << "Intervalo de d�gitos modificado!" << endl;

	return intervalo;
}

void instrucciones() {
	ifstream archivo;
	string lectura;

	if (mostrar(archivo)) {
		while (!archivo.eof()) {
			getline (archivo, lectura);

			if (!archivo.fail()) 
				cout << lectura << endl;
		}
		cout << endl;

		archivo.close(); // Cierre del archivo "versionCB.txt"
	}
}

bool mostrar(ifstream &archivo) {
	bool aperturaOK = false;

	archivo.open(ARCH_REGLAS); // Apertura del archivo "versionCB.txt"

	aperturaOK = archivo.is_open();

	if (!aperturaOK)
		cout << "ERROR en la apertura del archivo " << ARCH_REGLAS << "!" << endl;

	return aperturaOK;
}

void leerVariables(int &maxIntentos, int &longitud, int &intervalo) {
	ifstream datos;

	datos.open(ARCH_VARIABLES);

	if (datos.is_open()) {
		datos >> maxIntentos >> longitud >> intervalo;
		datos.close();
	} 
}

void guardarVariables(int maxIntentos, int longitud, int intervalo) {
	ofstream guardarArchivo;

	guardarArchivo.open(ARCH_VARIABLES);

	guardarArchivo << maxIntentos << endl << longitud << endl << intervalo << endl;

	guardarArchivo.close();
}

void rompedorAutomatico(int maxIntentos, int longitud, int intervalo) {
	int intentos = 0, claveMaquina, clave2 = 0, coincidentes = 0, contCoincidentes = 0, primerDigito = 1;
	bool codigoOK = false;
	ofstream archivo;
	string nombreArch;

	cout << "Nombre del archivo: ";
	cin >> nombreArch;

	archivo.open(nombreArch);

	claveMaquina = claveAleatoria(longitud, intervalo);
	cout << claveMaquina << endl; 
	claveMaquina = invertir(claveMaquina);

	for (int i = 0; i < longitud; i++) 
		// Se inicializa la nueva contrase�a con tantos 1 como longitud tenga la claveMaquina
		clave2 = clave2 * 10 + primerDigito;

	archivo << "Introduce un c�digo (0 para abandonar): " << clave2 << endl;

	do {
		coincidentes = numeroBips(claveMaquina, clave2);  

		for (int i = 0; i < coincidentes; i++)
			archivo << "bip ";

		if (coincidentes < longitud)
			archivo << "bop -- Acceso Denegado" << endl;

		else
			archivo << "-- Autorizado!" << endl;

		intentos++;

		if ((coincidentes < longitud) && (intentos < maxIntentos)) {
			// Cada d�gito analizado que no coincide con el d�gito de la 
			// claveMaquina se incrementa una unidad 
			clave2 = clave2 + pow(10, coincidentes);
			archivo << "Introduce un c�digo (0 para abandonar): " << invertir(clave2) << endl;
		}
	} while ((intentos < maxIntentos) && coincidentes < longitud); 
	// Hasta que no acierte la contrase�a o consuma todos los intentos

	if ((intentos == maxIntentos) && (coincidentes != longitud)) {
		cout << "No se ha encontrado la clave!" << endl;
		archivo << "Has agotado el n�mero m�ximo de intentos. Lo siento, has perdido!" << endl; 
	}

	else {
		cout << "Clave encontrada!" << endl;
		archivo << endl << "ENHORABUENA. HAS ADIVINADO EL C�DIGO!" << endl
			    << "Has utilizado " << intentos << " intento(s)."<< endl;
	}
	
	cout << "Puedes ver el resultado en al archivo (" << nombreArch << ")!" << endl << endl;
}

void bip() {
	// Los argumentos corresponen a la frecuencia y duraci�n del sonido (en ms)
	Beep(880, 250); 
}

void bop() {

	Beep(440, 250);
}



