// Esther Ávila Benito y Laura Pérez Jambrina

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
Función que muestra el menú y devuelve la opción elegida por el usuario
*/
int menu();
/*
Devuelve un entero con la clave aleatoria generada por el ordenador.
La clave consta de LONGITUD dígitos que están entre 1 e INTERVALO.
*/
int claveAleatoria(int longitud, int intervalo);
/*
Función que devuelve una variable booleanoa indicando si la clave introducida por el usuario 
cumple las condiciones de longitud e intervalo.
*/
bool codigoValido(int clave, int intervalo, int longitud);
/*
Función que compara la clave generada por el ordenador y la introducida por el usuario (parámetros) y devuelve el número
de dígitos coincidentes entre ellas. La comparación finalizará en cuanto se encuentre el primer dígito que no coincida.
*/
int numeroBips(int claveMaquina, int clave);
/*
Función que se emplea para invertir ambas claves con el fin de facilitar la comparación.
Como salida obtenemos la clave introducida, pero invertida.
*/
int invertir(int clave);
/*
Función principal que controla todo el desarrollo del juego. Desde ella invocamos a todas las funciones necesarias
para la manipulación de las contraseñas.
Como salida, devuelve el número de intentos empleados para adivinar la clave (nunca mayor que INTENTOS).
*/
void codeBreaker(int maxIntentos, int longitud, int intervalo);
/*
Función que pide al usuario el nuevo número de intentos y lo modifica en la variable maxIntentos.
*/
int pedirIntentos();
/*
Función que pide al usuario la nueva longitud del dígito y la modifica en la variable longitud.
*/
int pedirLongitud();
/*
Función que pide al usuario el nuevo intervalo de dígitos y lo modifica en la variable intervalo.
*/
int pedirIntervalo();
/*
Función que muestra por consola el contenido del archivo "versionCB.txt"
*/
void instrucciones();
/*
Función que devuelve una variable booleana indicando si se ha encontrado el archivo "versionCB.txt"
*/
bool mostrar(ifstream &archivo);
/*
Función que lee las variables maxIntentos, longitud e intervalo del archivo "versionCB.txt" y 
se las comunica a codeBreaker() para la ejecución del juego.
*/
void leerVariables(int &maxIntentos, int &longitud, int &intervalo);
/*
Función que hace que al final del programa se guarde en el archivo los valores 
de las variables en el orden indicado.
*/
void guardarVariables (int maxIntentos, int longitud, int intervalo);
/*
Función en la que el ordenador crea su propio código para poder jugar contra el mismo.
*/
void rompedorAutomatico(int maxIntentos, int longitud, int intervalo);
/*
Función para emitir un sonido similar a "BIP!" a través de la función "Beep()"  
contenida en la biblioteca Windows.h
*/
void bip();
/*
Función para emitir un sonido similar a "BOP!" a través de la función "Beep()"  
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
		// Guarda las últimas variables utilizadas en el archivo

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
			<< "2 - Cambiar el número máximo de intentos" << endl
			<< "3 - Cambiar la longitud de los códigos" << endl
			<< "4 - Cambiar el intervalo de dígitos" << endl
			<< "5 - Acerca de CodeBreaker" << endl
			<< "6 - Rompedor automático" << endl
			<< "0 - Salir" << endl
			<< "Opción: ";
		cin.sync();
		cin >> opcion;
		cout << endl;

		if ((opcion < 0) && (opcion > 6))
			cout << "Opción incorrecta. Inténtalo de nuevo!" << endl;
	} while ((opcion < 0) && (opcion > 6)); // Mientras que la opción sea incorrecta, la sigue pidiendo

	return opcion;
}

int claveAleatoria(int longitud, int intervalo) {
	int claveMaquina = 0;

	for (int i = 0; i < longitud; i++) // Genera tantos dígitos aleatorios como longitud tiene la clave
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
		// Cuando encuentra el primer dígito no coincidente termina la comparación
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
			cout << endl << "ENHORABUENA. HAS ADIVINADO EL CÓDIGO!" << endl;

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
		cout << "Has agotado el número máximo de intentos. Lo siento, has perdido!" << endl; 

	else
		cout << "Has utilizado " << intentos << " intento(s)."<< endl;
}

int pedirIntentos() {
	int maxIntentos;

	do {
		cout << "Introduce el nuevo máximo de intentos: ";
		cin >> maxIntentos;
	} while (maxIntentos <= 0);
	
	cout << "Máximo de intentos modificado!" << endl;

	return maxIntentos;
}

int pedirLongitud() {
	int longitud;

	do {
		cout << "Introduce la nueva longitud de clave: ";
		cin >> longitud;
	} while (longitud <= 0);
	cout << "Longitud de código modificada!" << endl;

	return longitud;
}

int pedirIntervalo() {
	int intervalo;

	do {
		cout << "Introduce el nuevo dígito máximo: ";
		cin >> intervalo;
	} while ((intervalo <= 0) || (intervalo > 9));
	cout << "Intervalo de dígitos modificado!" << endl;

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
		// Se inicializa la nueva contraseña con tantos 1 como longitud tenga la claveMaquina
		clave2 = clave2 * 10 + primerDigito;

	archivo << "Introduce un código (0 para abandonar): " << clave2 << endl;

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
			// Cada dígito analizado que no coincide con el dígito de la 
			// claveMaquina se incrementa una unidad 
			clave2 = clave2 + pow(10, coincidentes);
			archivo << "Introduce un código (0 para abandonar): " << invertir(clave2) << endl;
		}
	} while ((intentos < maxIntentos) && coincidentes < longitud); 
	// Hasta que no acierte la contraseña o consuma todos los intentos

	if ((intentos == maxIntentos) && (coincidentes != longitud)) {
		cout << "No se ha encontrado la clave!" << endl;
		archivo << "Has agotado el número máximo de intentos. Lo siento, has perdido!" << endl; 
	}

	else {
		cout << "Clave encontrada!" << endl;
		archivo << endl << "ENHORABUENA. HAS ADIVINADO EL CÓDIGO!" << endl
			    << "Has utilizado " << intentos << " intento(s)."<< endl;
	}
	
	cout << "Puedes ver el resultado en al archivo (" << nombreArch << ")!" << endl << endl;
}

void bip() {
	// Los argumentos corresponen a la frecuencia y duración del sonido (en ms)
	Beep(880, 250); 
}

void bop() {

	Beep(440, 250);
}



