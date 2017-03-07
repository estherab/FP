// Esther Ávila Benito y Laura Pérez Jambrina

#include <iostream>
#include <string>
using namespace std;

#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

const int FICHAS = 4,
	      COLORES = 6,
	      INTENTOS = 20,
	      PUNT_SEMIACIERTOS = 1,
	      PUNT_ACIERTOS = 5,
	      PUNT_GANADA = 100,
	      X = 5, // Solo se pueden solicitar las pistas tras cada 5 intentos
	      Y = 2, // El máximo de pistas que puede dar son 2
	      MAX = 100; // Máximo de jugadores de la lista
const string ARCH_REGLAS = "ayuda.txt",
	         CENT = "XXX",
	         ARCH_USU = "usuarios.txt";

const bool REPETIR = false;

typedef enum {R, A, V, N, G, M, fallo} tColor;
typedef tColor tCodigo[FICHAS];

typedef struct {
	string nombre;
	int partidas,
		ganadas,
		puntos;
} tJugador;

typedef tJugador tJugadores[MAX];

typedef struct {
	tJugadores dato;
	int contador;
} tListaJug;

// PROTOTIPOS 
/*
Genera un código de colores aleatorio de tipo tColor y módulo de 1 a 6, omitiendo 
el valor fallo. El código lo almacena en un array (codigoMaquina) de tipo tColor.
*/
void codigoAleatorio(tCodigo codigoMaquina);
/*
Función que recibe un caracter y lo transforma en un tipo enumerado.
*/
tColor charToColor(char c);
/*
Función que recibe un color (tColor) y lo transforma en "char".
*/
char colorToChar (tColor color);
/*
Función que recibe un color (una letra) y muestra su nombre por pantalla.
*/
void colorToString(tColor color) ;
/*
Función que recibe el código del usuario y el código secreto de la máquina.
Devuelve los aciertos y semiaciertos (colores que también están en el 
código secreto, perro en otra posición) entre los dós códigos.
*/
void coloresCoincidentes(const tCodigo codigoMaquina, const tCodigo codigoUsuario, int &aciertos, int &semiAciertos);
/*
Función que recibe la entrada del usuario y devuelve un "bool" indicando si es 
un código válido o no. Se entiendo por código no válido aquel que tiene una 
letra que no pertenece al enumerado de colores  o con una longitud inferior a FICHAS.
*/
bool codigoValido(string entrada);
/*
Función que conduce una partida entera de MasterMind. Acaba cuando el usuario 
adivina el código o agota el máximo de intentos. Si el usuario introduce 0 se 
acaba la partida y si introduce "?" se le muestran las instrucciones por pantalla.
*/
void masterMind(tJugador &jugador);
/*
Muestra las intrucciones del archivo "ayuda.txt" por pantalla.
*/
void instrucciones();
/*
Función que indica si el archivo "ayuda.txt" se ha podido abrir.
*/
bool mostrar(ifstream &archivo);
/*
Función que calcula la puntuación de cada jugada dependiendo de 
los aciertos y semiaciertos (parámetros por valor).
*/
int calculaPuntuacion(int aciertos, int semiAciertos);
/*
Función que elige aleatoriamente una posición del código secreto 
y muestra el color de dicha poscición.
*/
void darPista(const tCodigo codigoMaquina);
/*
Función que muestra una pista si se cumplen los requisitos: 
no haber dado más de dos pistas y dar una pista cada 5 intentos.
*/
void pistaPermitida(int &intentosPista, int &pistas, tCodigo &codigoMaquina);
/*
Función que devuelve a "main" la opción elegida por el usuario.
*/
int menu(string nombre);
/*
Función que lee del archivo usuarios.txt, el cual contiene en cada línea el 
nombre de un jugador seguido del número de juegos de ese jugador, el número 
de veces que ha ganado y los puntos acumulados y muestra su contenido.
*/
void mostrarArchivo();
//void escribirTemporal();
/*
Función que pasa el contenido del archivo usuarios.txt a la lista de jugadores 
hasta que ésta se llene o hasta que lea el centinela del archivo.
*/
bool cargarLista(tListaJug &lista);
/*
Función que recorre toda la lista de jugadores y la vuelca en el archivo
usuarios.txt con los datos de las partidas actualizados.
*/
void guardar(const tListaJug lista);
/*
Función que busca en la lista el nombre de usuario insertado por teclado.
*/
bool buscarNombre(const tListaJug lista, string nombre, int &pos);
/*
Función que inserta un nuevo jugador en la lista, si el nombre introducido no se 
ha encontrado en ella.
*/
void insertarJugador(tListaJug &lista, string nombre);
/*
Función auxiliar que inicializa las estadísticas de las partidas de un nuevo jugador.
*/
tJugador nuevoJugador(string nombre);


//-----------------------------------------------------
//-----------------------------------------------------

int main() {
	system ("chcp 1252");
	srand(unsigned(time(NULL))); // Semilla

	int opcion, posJugActual = 0;
	string nombre;
	tListaJug lista;

	cargarLista(lista);

	cout << "Bienvenido a Mastermind! Por favor, introduce tu nombre: ";
	cin >> nombre;

	if (!buscarNombre(lista, nombre, posJugActual)) 
		insertarJugador(lista, nombre);

	do {
		opcion = menu(nombre);
		
		switch (opcion) {
		case 1:
			masterMind(lista.dato[posJugActual]);
			guardar(lista);
			break;
		case 2:
			mostrarArchivo();
			break;
		}
	} while (opcion != 0);

	return 0;
}

void codigoAleatorio(tCodigo codigoMaquina) {

	int pos = 4;
	bool encontrado = false;

	if (REPETIR) {
		for (int i = 0; i < FICHAS; i++) 
			codigoMaquina[i] = tColor (rand() % COLORES);
	}

	else { // Sin repetición
		for (int j = 0; j < FICHAS; j++) {
			codigoMaquina[j] = tColor (rand() % COLORES);
			int i = 0;
			while (i < j) {
				if (codigoMaquina[j] == codigoMaquina[i]) { // Si el color generado es igual a alguno ya presente, lo vuelve a generar
					codigoMaquina[j] = tColor (rand() % COLORES);
					i = 0; // Probar con los anteriores
				}
				else
					i++;
			}
		}
	}
}

tColor charToColor(char c) {
	tColor color;

	c = tolower(c); // También lee mayúsculas

	if (c == 'r') color = R;
	else if (c == 'a') color = A;
	else if (c == 'v') color = V;
	else if (c == 'n') color = N;
	else if (c == 'g') color = G;
	else if (c == 'm') color = M;
	else if (c != '0') color = fallo; // Para letras que no se corresponden con ningún color

	return color;
}

char colorToChar(tColor color) {
	char c = ' ';

	if (color == R) c = 'R';
	else if (color == A) c = 'A';
	else if (color == V) c = 'V';
	else if (color == N) c = 'N';
	else if (color == G) c = 'G';
	else if (color == M) c = 'M';

	return c;
}

void colorToString(tColor color) {

	switch (color) {
		case 'R': cout << "rojo";
		case 'A': cout << "azul";
		case 'V': cout << "verde";
		case 'N': cout << "negro";
		case 'G': cout << "granate";
		case 'M': cout << "marrón";
	}
	cout << endl;
}

void coloresCoincidentes(const tCodigo codigoMaquina, const tCodigo codigoUsuario, int &aciertos, int &semiAciertos) {
	typedef bool tSemiAciertos[FICHAS]; // Arrays para los colores que coinciden en distinta posición
	tSemiAciertos maquina, usuario;
	int k = 0;
	bool encontrado = false;

	for (int i = 0; i < FICHAS; i++) { // Aciertos
		if (codigoMaquina[i] == codigoUsuario[i]) {
			maquina[i] = true;
			usuario[i] = true;
			aciertos++;
		}

		else {
			maquina[i] = false;
			usuario[i] = false;
		}
	}

	for (int j = 0; j < FICHAS; j++) { // Semiaciertos
		if (!usuario[j]) {

			encontrado = false;
			k = 0;
			while ((k < FICHAS) && (!encontrado)) {
				if ((codigoUsuario[j] == codigoMaquina[k]) && (!maquina[k])) { 
					// Compara con un color del código secreto que no sea ya un acierto
					semiAciertos++;
					encontrado = true;
					maquina[k] = true; 
					usuario[j] = true;
					k = 0;
				}
				else 
					k++;
			}
		}
	}

	cout << endl << "Aciertos: " << aciertos << "       Semiaciertos: " << semiAciertos;
}

bool codigoValido(string entrada) {
	tColor color;
	bool codigoOK = true;
	unsigned int i = 0;

	if (entrada.length() < FICHAS)  // Comprueba tamaño de la cadena
		codigoOK = false;

	else { 
		while ((i < FICHAS) && (codigoOK)) { 
			// Si la cadena tiene al menos 4 caracteres comprueba que cada uno de ellos no sea fallo
			color = charToColor(entrada[i]);

			if (color == fallo)
				codigoOK = false;

			else 
				i++;
		}
	}

	if (!codigoOK) 
		cout << "Código no válido. Letras de color válidas: R A V N G M. Inténtalo de nuevo!" << endl;

	return codigoOK;
}

void masterMind(tJugador &jugador) {
	tCodigo codigoUsuario, codigoMaquina;
	tColor color;
	string entrada = "";
	int intentos = 0, aciertos = 0, semiAciertos = 0, puntosAcumulados = 0, 
		puntosActuales = 0, intentosPista = 0, pistas = 0;
	bool codigoOK = false;

	codigoAleatorio(codigoMaquina);

	while ((intentos < INTENTOS) && (aciertos < FICHAS) && entrada != "0") {
		aciertos = 0; // Se incicializan para que no sume los aciertos con los de la jugada anterior
		semiAciertos = 0;
		cout << endl << "Mastermind! Códigos de "<< FICHAS << " colores (RAVNGM), "<< INTENTOS << " intentos, sin repetición."
			 << endl << "Código (? para ayuda, 0 para cancelar): ";
		cin >> entrada;

		if (entrada == "?") 
			instrucciones();

		else if (entrada == "!") 
			pistaPermitida(intentosPista, pistas, codigoMaquina);

		else if (entrada != "0") {
			codigoOK = codigoValido(entrada);

			if (codigoOK) {
				cout << setw(3) << intentos + 1 << ": ";
				for (int i = 0; i < FICHAS; i++) {
					color = charToColor(entrada[i]);
					codigoUsuario[i] = color;
					cout << " " << colorToChar(codigoUsuario[i]);
				}
				coloresCoincidentes(codigoUsuario, codigoMaquina, aciertos, semiAciertos); 
				puntosActuales = calculaPuntuacion(aciertos, semiAciertos);
				puntosAcumulados += puntosActuales;
				jugador.puntos += puntosAcumulados; 
				cout << setw(20) << puntosAcumulados << " puntos." << endl;
				intentos++;
				intentosPista++;
			}
		}
	}

	jugador.partidas++;

	if ((intentos == INTENTOS) && (aciertos < FICHAS)) 
		cout << "Lo siento, has agotado el número máximo de intentos" << endl;

	else if (aciertos == FICHAS) {
		jugador.puntos = puntosAcumulados; // Puntos totales del jugador en la partida
		cout << "FELICIDADES! Lo has conseguido en " << intentos << " intentos." << endl;
		jugador.ganadas++; 
	}
	else if (entrada == "0")
		cout << "Juego cancelado!" << endl;
	cout << endl;
}

void instrucciones() {
	ifstream archivo;
	string lectura;

	if (mostrar(archivo)) { // Si el archivo se ha abierto...
		getline (archivo, lectura); // Lee una línea entera
		while (lectura != CENT) {
			if (!archivo.fail()) 
				cout << lectura << endl;
			getline (archivo, lectura);
		}
		cout << endl;

		archivo.close(); 
	}
}

bool mostrar(ifstream &archivo) {
	bool aperturaOK = false;

	archivo.open(ARCH_REGLAS); 

	aperturaOK = archivo.is_open();

	if (!aperturaOK)
		cout << "ERROR en la apertura del archivo " << ARCH_REGLAS << "!" << endl;

	return aperturaOK;
}

int calculaPuntuacion(int aciertos, int semiAciertos) {
	int puntuacion = 0;

	puntuacion = semiAciertos * PUNT_SEMIACIERTOS + aciertos * PUNT_ACIERTOS;

	if (aciertos == FICHAS) 
		puntuacion = puntuacion + PUNT_GANADA;

	return puntuacion;
}

void darPista(const tCodigo codigoMaquina) {	

	srand(time(NULL)); // Se refrescan los valores aleatorios
	int i; // posición
	char  color;
	string c; 
	i = (rand() % FICHAS); // Para coger una posición aleatoriamente
	color = colorToChar(codigoMaquina[i]);

	if (color == 'R') c = "Rojo";
	else if (color == 'A') c = "Azul";
	else if (color == 'V') c = "Verde";
	else if (color == 'N') c = "Negro";
	else if (color == 'G') c = "Granate";
	else if (color == 'M') c = "Marrón";

	cout << endl << "El color de la posición " << i + 1 << " es: " << c << endl;
}


void pistaPermitida(int &intentosPista, int &pistas, tCodigo &codigoMaquina) {
	bool pistaOK = false;

	if ((pistas < Y) && (intentosPista >= X)) {
		darPista(codigoMaquina);
		pistas++;
		intentosPista = 0;
	}

	else if (pistas == Y) 
		cout << "Lo siento ya has agotado el máximo de pistas" << endl;

	else if ((intentosPista % 5 != 0) || (intentosPista == 0))
		cout << "Lo siento. Puedes conseguir una pista cada " << X << " intentos" << endl; 
}

int menu(string nombre) {
	int opcion;

	do {
		cout << "Hola " << nombre << "! Elige una opción..." << endl
			 << "1 - Jugar" << endl
			 << "2 - Puntuaciones" << endl
			 << "0 - Salir" << endl 
			 << "Opción: ";
		cin >> opcion;

		if ((opcion < 0) || opcion > 2) 
			cout << "La opción no es válida, intentelo de nuevo." << endl << endl;

	} while ((opcion < 0) || (opcion > 2)); 

	return opcion;
}

void mostrarArchivo() {
	ifstream archivo;
	string nombreUsu;
	int juegos, ganados, puntos;

	archivo.open(ARCH_USU);

	if (archivo.is_open()) { // Si el archivo está abierto
		cout << endl;
		cout <<  setw(10) << "Usuario" << setw(18) <<  "Juegos" << setw(18) << "Ganados" << setw(18) <<  "Puntos" << endl; 

		archivo >> nombreUsu >> juegos >> ganados >> puntos;

		while (nombreUsu != CENT) { 
			// Mientras el nombre sea distinto del centinela, muestro el contenido de usuarios.txt
			cout <<  setw(10) << nombreUsu << setw(18) << juegos << setw(18) << ganados << setw(18) << puntos << endl;
			archivo >> nombreUsu >> juegos >> ganados >> puntos;
		}
		cout << endl;

		archivo.close(); 
	}

	else
		cout << "ERROR: No se ha encontrado el archivo 'usuarios'txt" << endl;
}

bool cargarLista(tListaJug &lista) {
	tJugador jugador;
	ifstream archivo;
	lista.contador = 0;

	archivo.open(ARCH_USU);

	if (!archivo.is_open())
		return false;

	else {
		archivo >> jugador.nombre;
		while ((lista.contador < MAX) && (jugador.nombre != CENT)) {
			archivo >> jugador.partidas;
			archivo >> jugador.ganadas;
			archivo >> jugador.puntos;
			archivo.get();
			lista.dato[lista.contador] = jugador;
			lista.contador++;
			archivo >> jugador.nombre;
		}
		archivo.close();
		return true;
	}
}

void guardar(const tListaJug lista) {
	ofstream salida;

	salida.open(ARCH_USU);

	for (int i = 0; i < lista.contador; i++) {
		salida << lista.dato[i].nombre << " ";
		salida << lista.dato[i].partidas << " ";
		salida << lista.dato[i].ganadas << " ";
		salida << lista.dato[i].puntos << endl;
	}
	salida << CENT;
	salida.close();
}

bool buscarNombre(const tListaJug lista, string nombre, int &pos) {
	bool encontrado = false;

	while ((pos < lista.contador) && !encontrado) {
		if (lista.dato[pos].nombre == nombre)
			encontrado = true;
		else 
			pos++;
	}

	return encontrado;
}

void insertarJugador(tListaJug &lista, string nombre) {
	tJugador jugador;
	jugador = nuevoJugador(nombre);

	if (lista.contador < MAX) {
		lista.dato[lista.contador] = jugador;
		lista.contador++;
	}
}

tJugador nuevoJugador(string nombre) {
	tJugador jugador;

	jugador.nombre = nombre;
	jugador.partidas = 0;
	jugador.ganadas = 0;
	jugador.puntos = 0;

	return jugador;
}




