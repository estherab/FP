// Esther Ávila Benito y Laura Pérez Jambrina

#include <iostream>
#include <string>
using namespace std;

#include <fstream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>

const int N = 8,
	      Colores = 4,
	      NumGrupo = 2, // Número desde el cual se pueden empezar hacer grupos
	      Intentos = 15, // Número máximo de intentos
	      MAX = 20, // Máximo de jugadores
	      PAUSA = 100; 
		  
const string ARCH_REGLAS = "ayuda.txt", // Archivo para las intrucciones 
	         CENT = "XXX",
	         ARCH_USU = "usuarios.txt"; // Archivo que guarda las puntuaciones de jugadores

typedef enum {azul, verde, rosa, amarillo, neutro} tFicha;

typedef tFicha tTablero[N][N];

typedef bool tIguales[N][N]; 

typedef enum {arriba, abajo, izquierda, derecha, error} tDireccion;

typedef enum { // Screen colors 
	black,         //   0 
	dark_blue,     //   1 
	dark_green,    //   2 
	dark_cyan,     //   3 
	dark_red,      //   4 
	dark_magenta,  //   5 
	dark_yellow,   //   6 
	light_gray,    //   7 
	dark_gray,     //   8 
	light_blue,    //   9 
	light_green,   //  10 
	light_cyan,    //  11 
	light_red,     //  12 
	light_magenta, //  13 
	light_yellow,  //  14 
	white          //  15 
} tColor;

typedef struct {
	tTablero tablero;
	int intentos;
	int puntos;
} tJuego;

typedef struct {
	string nombre;
	int partidas,
		puntos;
} tJugador;

typedef tJugador tJugadores[MAX];

typedef struct {
	tJugadores dato;
	int contador;
} tListaJug;


/*
Función que devuelve a "main" la opción elegida por el usuario.
*/
int menu(string nombre);
/*
Función que lleva a cabo un  procedimiento para el coloreado de determinadas casillas.
*/
void setColor(tColor color);
/*
Función que genera aleatoriamente los colores para cada casilla que forma el tablero. 
*/
void generarTablero(tTablero tablero);
/*
Función que te muestra el dibuxjo del tablero completo con sus colores, y sus líneas respectivas
con la dimensión constante de 8x8.
*/
void mostrarTablero(tJuego juego);
/*
Función que se encarga de dibujar la línea superior del tablero, ya que se dibuja diferente al resto de
la líneas que conforman el tablero.
*/
void dibujoLineaSuperior();
/*
Función que se encarga de dibujar las líneas intermedias del tablero, ya que se dibuja diferente
al resto de la líneas que conforman el tablero.
*/
void dibujoLineasIntermedias();
/*
Función que se encarga de dibujar la última línea del tablero, ya que se dibuja diferente al resto de
la líneas que conforman el tablero.
*/
void dibujoLineaInferior();
/*
Función que se encarga de dibujar los números relacionados con las filas y otros números relacionados 
con las columnas; para que así el jugador cuando realice una partida y tenga que insertar una coordenada
pueda poner la numeracíón correcta para la casilla que quiera mover.
*/
void dibujaNumTablero();
/*
Función que se encarga de borrar lo que se muestra por la consola y visualiza las jugadas y el borrado
y bajada de las fichas con una cierta velocidad.
*/
void dibujarTablero(tJuego juego);


/*
Función que tranforma el char introducido por el usuario ('a', 'b', 'i' y 'd') a un enumerado
arriba, abajo, izquierda o derecha. Para que así se pueda proceder al movimiento de las fichas.
*/
tDireccion charToDireccion(char dir);
/*
Función que comprube que el movimiento insertado por el usuario sea válido. No será válido
si se sale de los límites del tablero, si provoca movimientos inexistentes debido haber introducido
unas letras diferentes de 'a', 'b', 'i' y 'd'; o si el movimiento que va a relacizar no forma ningún
grupo a su alrededor.
*/
bool movimientoValido(tTablero tablero, tDireccion direccion, int fila, int columna);
/*
Función que realiza el intercambio de la fichas, a partir de la dirección insertada por el jugador.
*/
void intercambiarCasillas(tTablero tablero, int fila, int columna, tDireccion direccion);
/*
Función que realiza el desintercambio de las fichas, que se tendría que haber echo anteriormente.
Esta función solo se realiza si, se comprueba que no hay grupos.
*/
void desintercambiarCasillas(tTablero tablero, int fila, int columna, int direccion);


/*
Función que comprueba de izquierda a derecha si hay grupos (en este caso en horizontal).
En el caso de encontrarse grupos pondra el array de boolenaos a true. Para que en una 
fución posterios esas casillas no aparezcan coloreada y se han pintadas en negro.
*/
void estabilizarTableroColumnas(tJuego &juego, tIguales &iguales);
/*
Función que comprueba de arriba a abajo si hay grupos (en este caso verticales).
En el caso de encontrarse grupos pondra el array de boolenaos a true. Para que en una 
fución posterios esas casillas no aparezcan coloreada y se han pintadas en negro.
*/
void estabilizarTableroFilas(tJuego &juego, tIguales &iguales);
/*
Fución que llama a : estabilizarTableroColumnas y estabilizarTableroFilas para así posteriormente
recorrer el array de booleanos para poner las casillas donde hay true en un color neutro 
(en este caso el color black). 
*/
bool estabilizarTableroCompleto(tJuego &juego);


/*
Función que a partir de la derecha de una coordenada comprueba si hay grupo.
Y devuelve el número de fichas que coinciden con las de la ficha inicial.
*/
int buscarDerecha(const tTablero tablero, int fila, int columna);
/*
Función que a partir de la izquierda de una coordenada comprueba si hay grupo.
Y devuelve el número de fichas que coinciden con las de la ficha inicial.
*/
int buscarIzquierda(const tTablero tablero, int fila, int columna);
/*
Función que a partir de arriba de una coordenada comprueba si hay grupo.
Y devuelve el número de fichas que coinciden con las de la ficha inicial.
*/
int buscarArriba(const tTablero tablero, int fila, int columna);
/*
Función que a partir de la abajo de una coordenada comprueba si hay grupo.
Y devuelve el número de fichas que coinciden con las de la ficha inicial.
*/
int buscarAbajo(const tTablero tablero, int fila, int columna);
/*
Función que llama a las funciones de: buscarDerecha, buscarIzquierda, buscarArriba y buscarAbajo
para comprobar si alguna ha devuelto algún coincidente superior a 2, que es a partir del cual
se pueden hacer grupos. En caso de si haber aunque sea solo un grupo de devolverá un true, 
para que así se pueda estabilizar el tablero al completo y sino un false, para poder 
desintercambiar el movimiento.
*/
bool hayGrupos(const tTablero tablero, int fila, int columna);
/*
Función que sirve para comprobar la otra casilla con la cual se ha intercambiado.
Y devuelve su respectiva coordenada, para así comprobar en ella si hay grupo
*/
void casillaSiguiente(int &fila, int &columna, tDireccion direccion);


/*
Función que va produciendo la bajada del fichas, debido a que habido grupos en el tablero
y aporceder a generar en las nueva casillas superiores colores de fichas aleatorios.
*/
void bajarFichas(tTablero tablero);
/*
Función que se encarga de proceder a la suma de los puntos de las respectivas jugadas
y de la estabilización del tablero.
La puntuación en cada jugada será la suma de los puntos de cada grupo de fichas conseguido,
directa o indirectamente: 3 puntos si se han alineado 3 fichas, 8 puntos si se han alineado 4
y 15 puntos para grupos de 5 o más fichas alineadas. 
*/
void sumarPuntos(int coincidentes, int &puntos);


/*
Función que conduce la jugada y que te permite introducir las coordenadas.
*/
void colorCrush(tJugador &jugador);
/*
Función en la cual, si se siguen encontrando grupos, hay que seguir bajando las fichas. Y seguir procediendo
a la busqueda de mas grupos hasta que no se encuentren más.
*/
void evaluarJugada(tJuego &juego);


/*
Función que lee del archivo usuarios.txt, el cual contiene en cada línea el 
nombre de un jugador seguido del número de juegos de ese jugador, el número 
de veces que ha ganado y los puntos acumulados y muestra su contenido.
*/
void mostrarArchivo();
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
/*
Función que indica si el archivo "ayuda.txt" se ha podido abrir.
*/
bool mostrarInstrucciones(ifstream &archivo);
/*
Muestra las intrucciones del archivo "ayuda.txt" por pantalla.
*/
void instrucciones();



int main() {
	srand(unsigned(time(NULL))); // Semilla

	int opcion, posJugActual = 0;
	string nombre;
	tListaJug lista;

	cargarLista(lista);

	cout << "Bienvenido a Color Crush! Por favor, introduce tu nombre: ";
	cin >> nombre;

	if (!buscarNombre(lista, nombre, posJugActual)) 
		insertarJugador(lista, nombre); // Si el nombre no esta en la lista, lo inserta

	do {
		opcion = menu(nombre);

		switch (opcion) {
		case 1:
			colorCrush(lista.dato[posJugActual]);
			guardar(lista);
			break;
		case 2:
			mostrarArchivo();
			break;
		case 3:
			instrucciones();
			break;
		}
	} while (opcion != 0);

	return 0;
}

int menu(string nombre) {
	int opcion;

	do {
		cout << endl << "Hola " << nombre << "! Elige una opcion..." << endl
			 << "1 - Jugar" << endl
			 << "2 - Puntuaciones" << endl
			 << "3 - Intrucciones del Juego" << endl
			 << "0 - Salir" << endl 
			 << "Opcion: ";
		cin >> opcion;

		if ((opcion < 0) || opcion > 3) 
			cout << "La opcion no es valida, intentelo de nuevo." << endl << endl;

	} while ((opcion < 0) || (opcion > 3)); 

	return opcion;
}

void setColor(tColor color) { 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(handle, color); 
}

void generarTablero(tTablero tablero) {

	for (int fila = 0; fila < N; fila++) 
		for (int col = 0; col < N; col++) 
			tablero[fila][col] = tFicha(rand() % Colores);
}

void mostrarTablero(tJuego juego) {

	cout << setw(18) << "Intentos: " << juego.intentos << setw(10) << "Puntos: " << juego.puntos << endl;

	for (int fila = N - 1; fila >= 0; fila--) {
		if (fila == N - 1) 
			dibujoLineaSuperior();

		for (int col = 0; col < N; col++) {
			if (col == 0) {
				setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
				cout << fila + 1 << setw(2) << char (179); // Muestra el número de la fila y dibuja: " ¦ "
			}

			if (juego.tablero[fila][col] == azul) 
				setColor(light_blue);

			else if (juego.tablero[fila][col] == verde) 
				setColor(light_green);

			else if (juego.tablero[fila][col] == rosa) 
				setColor(light_magenta);

			else if (juego.tablero[fila][col] == amarillo) 
				setColor(light_yellow);

			else if (juego.tablero[fila][col] == neutro) 
				setColor(black);

			cout << char (219) << char (219) << char (219); // Dibuja: " ¦¦¦ " 
			setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
			cout << char (179); // Dibuja: " ¦ "
		}

		cout << endl;
		if (fila != 0)
			dibujoLineasIntermedias();
	}
	dibujoLineaInferior();
	dibujaNumTablero ();

	cout << endl << endl;
}

void dibujoLineaSuperior() {

	setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
	cout << setw(3) << char(218); // Dibuja: " ┌ " 

	for (int i = 1; i <= N-1; i++) { 
		setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
		cout << char (196) << char (196) << char (196) << char (194); // Dibuja: " ───┬ "

		if (i == N-1) 
			cout << char (196) << char (196)  << char (196) << char (191) << endl; // Dibuja: " ───┐ "
	}
}

void dibujoLineasIntermedias() {

	for (int i = 0; i < N; i++) {
		if (i == 0) {
			setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
			cout << setw (3) << char (195) << char (196) << char (196) << char (196) << char (197); // Dibuja: " +---+" 
		}

		else if ((i > 0) && (i < (N -1))) 
			cout << char (196) << char (196) << char (196) << char (197); // Dibuja: " ---+";

		else if (i == (N-1)) 
			cout << char (196)  << char (196) << char (196) <<  char (180) << endl; // Dibuja: " ---¦"
	}
}

void dibujoLineaInferior() {

	cout << setw(3) << char (192); // Dibuja: " + " 

	for (int i = 1; i < N; i++) {

		setColor(white); // COLOR DE LAS LÍNEAS DEL TABLERO
		cout  << char (196) << char (196) << char (196) << char (193); // Dibuja: " ---- "

		if (i == (N-1)) 
			cout << char (196) << char (196)  << char (196) << char (217) << endl; // Dibuja: " ---+ "
	}
}

void dibujaNumTablero() {

	cout << setw(5) << "1";
	for (int j = 1; j < N; j++)
		cout << setw(4) << j + 1;
}

void dibujarTablero(tJuego juego) {

	system("cls"); // Sirve para limpiar la pantalla
	mostrarTablero(juego); 
	Sleep(PAUSA);
}

tDireccion charToDireccion(char dir) {
	tDireccion direccion;

	switch (dir) {
		case 'a': direccion = arriba; break;
		case 'b': direccion = abajo; break;
		case 'i': direccion = izquierda; break;
		case 'd': direccion = derecha; break;
		default: direccion = error; break;
	}

	return direccion;
}

bool movimientoValido(tTablero tablero, tDireccion direccion, int fila, int columna) {
	bool movValido = true;

	if (fila == -1)
		return true;

	if (direccion == error) {
		cout << "Direccion no valida! Intentalo de nuevo..." << endl;
		movValido = false;
	}

	else if ((columna < 0) || (columna > N - 1) || (fila < 0) || (fila > N - 1)) {
		cout << "Casilla no valida! Intentalo de nuevo..." << endl;
		movValido = false;
	}

	else if ((columna == 0 && direccion == izquierda) || (columna == N - 1 && direccion == derecha) ||
		(fila == 0 && direccion == abajo) || (fila == N - 1 && direccion == arriba)) {
			movValido = false;
			cout << "Se sale del tablero! Intentalo de nuevo..." << endl;
	}

	else {
		intercambiarCasillas(tablero, fila, columna, direccion);
		if (!hayGrupos(tablero, fila, columna)) {
			casillaSiguiente(fila, columna, direccion);
			if (!hayGrupos(tablero, fila, columna)) {
				cout << "Movimiento no valido! Intentalo de nuevo..." << endl;
				movValido = false;
				desintercambiarCasillas(tablero, fila, columna, direccion); // Si no hay grupos en el intercambio, lo deshago
			}
		}
	}


	return movValido;
}

void intercambiarCasillas(tTablero tablero, int fila, int columna, tDireccion direccion) {
	tFicha tmp;

	tmp = tablero[fila][columna]; // En tmp pongo la casilla actual

	switch (direccion) {
		case arriba: tablero[fila][columna] = tablero[fila + 1][columna];
			tablero[fila + 1][columna] = tmp;	
			break;

		case abajo: tablero[fila][columna] = tablero[fila - 1][columna]; 
			tablero[fila - 1][columna] = tmp;
			break;

		case izquierda: tablero[fila][columna] = tablero[fila][columna - 1];
			tablero[fila][columna - 1] = tmp;
			break;
			
		case derecha: tablero[fila][columna] = tablero[fila][columna + 1];
			tablero[fila][columna + 1] = tmp;
			break;
	}
}

void desintercambiarCasillas(tTablero tablero, int fila, int columna, int direccion) {
	tFicha tmp;

	tmp = tablero[fila][columna];

	switch (direccion) {
	case arriba:
		tablero[fila][columna] = tablero[fila - 1][columna]; 
		tablero[fila - 1][columna] = tmp; 
		break;
		
	case abajo:
		tablero[fila][columna] = tablero[fila + 1][columna]; 
		tablero[fila + 1][columna] = tmp; 
		break;
		
	case izquierda:
		tablero[fila][columna] = tablero[fila][columna + 1];
		tablero[fila][columna + 1] = tmp; 
		break;
		
	case derecha:
		tablero[fila][columna] = tablero[fila][columna - 1];
		tablero[fila][columna - 1] = tmp; 
		break;
	}
}

void estabilizarTableroColumnas(tJuego &juego, tIguales &iguales) {
	bool encontrado;
	int pos, coincidentes, cont;

	for (int fila = N-1; fila >= 0; fila--) {
		for (int columna = 0; columna < N; columna++) {
			pos = columna + 1; // 'pos' sirve para poder comparar con la ficha de la dirección siguiente
			coincidentes = 0;
			cont = 0;
			encontrado = true;

			while ((pos < N) && encontrado) { // Comparo hasta que las dos fichas sean diferentes
				if (juego.tablero[fila][columna] == juego.tablero[fila][pos]) {
					pos++;
					coincidentes++;
				}
				else
					encontrado = false;
			}
			if (coincidentes >= NumGrupo) {
				sumarPuntos(coincidentes, juego.puntos);
				for (int i = columna; cont <= coincidentes; i++) {
					iguales[fila][i] = true; // Si hay grupo, las casillas pertenecientes a ese grupo las pongo a true
					cont++; // Incrementamos el contador para poderlos comparar con el número de coincidentes
				}
				columna += coincidentes;
			}
		}
	}
}

void estabilizarTableroFilas(tJuego &juego, tIguales &iguales) {
	bool encontrado;
	int pos, coincidentes, cont;

	for (int columna = 0; columna < N; columna++) {
		for (int fila = N-1; fila >= 0; fila--) {
			pos = fila - 1; // 'pos' sirve para poder comparar con la ficha de la dirección siguiente
			coincidentes = 0;
			cont = 0;
			encontrado = true;

			while ((pos >= 0) && encontrado) {
				if (juego.tablero[fila][columna] == juego.tablero[pos][columna]) {
					pos--;
					coincidentes++;
				}
				else
					encontrado = false;
			}
			if (coincidentes >= NumGrupo) {
				sumarPuntos(coincidentes, juego.puntos);
				for (int i = fila; cont <= coincidentes; i--) {
					iguales[i][columna] = true;
					cont++; // Incremento el contador para poderlo comparar con el número de coincidentes
				}
				fila = fila - coincidentes; 
			}
		}
	}
}

bool estabilizarTableroCompleto(tJuego &juego) {
	tIguales iguales = {false}; // Inicializo array de booleanos a false
	bool acabado = false;

	estabilizarTableroColumnas(juego, iguales); // Compruebo si hay grupos de izquierda a derecha en el tablero
	estabilizarTableroFilas(juego, iguales); // Compruebo si hay grupos de arriba a abajo en el tablero
	acabado = true;

	for (int columna = 0; columna < N; columna++) {
		for (int fila = N-1; fila >= 0; fila--) {
			if (iguales[fila][columna] == true) {
				acabado = false;
				juego.tablero[fila][columna] = neutro; // Las casillas de un grupo las pongo en "neutro" para pintarlas de negro
			}
		}
	}

	return acabado;
}

int buscarDerecha(const tTablero tablero, int fila, int columna) {
	int	pos = columna + 1, cont = 0, coincidentes = 0; 
	bool encontrado = true;

	while ((pos < N) && encontrado) {
		if (tablero[fila][columna] == tablero[fila][pos]) {
			pos++; // Se incrementa la posición para poder ir comparando
			coincidentes++; // Se incrementa el contador de fichas coincidentes
		}

		else 
			encontrado = false;
	}

	if (coincidentes >= NumGrupo) {
		for (int j = columna; cont <= coincidentes; j++) 
			cont++;
	}

	return coincidentes; // Devuelve el número de coincidentes encontrado, para saber si hay grupo
}

int buscarIzquierda(const tTablero tablero, int fila, int columna) {
	int	pos = columna - 1, cont = 0, coincidentes = 0;  
	bool encontrado = true;

	while ((pos >= 0) && encontrado) {
		if (tablero[fila][columna] == tablero[fila][pos]) {
			pos--; // Se decrementa la posición para poder ir comparando
			coincidentes++; // Se incrementa el contador de fichas coincidentes
		}

		else 
			encontrado = false;
	}

	if (coincidentes >= NumGrupo) {
		for (int j = columna; cont <= coincidentes; j--) 
			cont++;
	}

	return coincidentes; // Devuelve el número de coincidentes encontrado, para saber si hay grupo
}

int buscarArriba(const tTablero tablero, int fila, int columna) {
	int	pos = fila + 1, cont = 0, coincidentes = 0; 
	bool encontrado = true;

	while ((pos < N ) && encontrado) {
		if (tablero[fila][columna] == tablero[pos][columna]) {
			pos++; // Se incrementa la posición para poder ir comparando
			coincidentes++; // Se incrementa el contador de fichas coincidentes
		}

		else 
			encontrado = false;

	}
	if (coincidentes >= NumGrupo) {
		for (int j = fila; cont <= coincidentes; j++) 
			cont++;
	}

	return coincidentes; // Devuelve el número de coincidentes encontrado, para saber si hay grupo
}

int buscarAbajo(const tTablero tablero, int fila, int columna) {
	int	pos = fila - 1, cont = 0, coincidentes = 0;  
	bool encontrado = true;

	while ((pos >= 0) && encontrado) {
		if (tablero[fila][columna] == tablero[pos][columna]) {
			pos--; // Se decrementa la posición para poder ir comparando
			coincidentes++; // Se incrementa el contador de fichas coincidentes
		}

		else 
			encontrado = false;

	}
	if (coincidentes >= NumGrupo) {
		for (int j = fila; cont <= coincidentes; j--) 
			cont++;
	}

	return coincidentes; // Devuelve el número de coincidentes encontrado, para saber si hay grupo
}

bool hayGrupos(const tTablero tablero, int fila, int columna) {
	int coincidentesD, coincidentesI;
	int coincidentesA, coincidentesB; 
	bool hayGrupo = false;

	coincidentesD =	buscarDerecha(tablero, fila, columna);
	coincidentesI = buscarIzquierda(tablero, fila, columna);
	coincidentesA = buscarArriba(tablero, fila, columna);
	coincidentesB = buscarAbajo(tablero, fila, columna);

	// Caso: 2 o más coincidentes apartir de la ficha 
	if ((coincidentesD >= 2) || (coincidentesI >= 2) || (coincidentesA >= 2) || (coincidentesB >= 2)) 
		hayGrupo = true;

	// Caso: un coincidente a derecha y otro coincidente a izquierda a partir de la ficha 
	else if ((coincidentesD == 1) && (coincidentesI == 1))
		hayGrupo = true;

	// Caso: un coincidente arriba y otro hacia abajo a partir de la ficha
	else if ((coincidentesA == 1) && (coincidentesB == 1))  
		hayGrupo = true;

	// Caso: ningún grupo
	else
		hayGrupo = false;

	return hayGrupo;
}

void casillaSiguiente(int &fila, int &columna, tDireccion direccion) {

	switch(direccion) {
		case arriba: fila++; break;
		case abajo: fila--; break;
		case izquierda: columna--; break;
		case derecha: columna++; break;
	}
}

void bajarFichas(tTablero tablero) {
	bool quedanNegras = true;

	while (quedanNegras) {
		quedanNegras = false;
		
		for (int col = 0; col < N; col++) {
			for (int fila = 0; fila < N; fila++) {
				
				if (tablero[fila][col] == neutro) {
					quedanNegras = true;
					
					if (fila != N-1) {
						tablero[fila][col] = tablero[fila+1][col];
						tablero[fila+1][col] = neutro;
					}
					
					else // Genero nuevas fichas en las casilla que se han quedado vacias
						tablero[fila][col] = tFicha (rand() % Colores);
				}
			}
		}
	}
}

void sumarPuntos(int coincidentes, int &puntos) {

	switch(coincidentes) {
		case 2: puntos += 3; break;
		case 3: puntos += 8; break;
		case 4: puntos += 15; break;
	}
}

void colorCrush(tJugador &jugador) {
	tJuego juego;
	tDireccion direccion;
	int fila = 1, columna;
	char dir;
	bool movValido = false;
	juego.intentos = Intentos;
	juego.puntos = 0;

	generarTablero(juego.tablero);
	dibujarTablero(juego);

	while ((fila != -1) && (juego.intentos > 0)) {
		evaluarJugada(juego); // Estabiliza, baja las fichas y genera las nuevas

		if (juego.intentos > 0) {
			cout << endl << "Fila, columna y letra de direccion (A, B, I o D; 0 para cancelar): ";
			cin >> fila >> columna >> dir;
			fila--;
			columna--;
			if (fila != -1) {
				direccion = charToDireccion(dir);

				while (!movimientoValido(juego.tablero, direccion, fila, columna) && (fila != -1)) {
					cout << "Fila, columna y letra de direccion (A, B, I o D; 0 para cancelar): ";
					cin >> fila >> columna >> dir;
					fila--;
					columna--;
					if (fila != -1) 
						direccion = charToDireccion(dir);
				}
				juego.intentos--;
				dibujarTablero(juego);
			}
		}
	}

	if (juego.intentos == 0) {
		evaluarJugada(juego);
		cout << "Ya no te quedan mas intentos! Has conseguido un total de " << juego.puntos << " PUNTOS!" << endl;
		jugador.puntos += juego.puntos;
		jugador.partidas++;
	}
}

void evaluarJugada(tJuego &juego) {

	while (!estabilizarTableroCompleto(juego)) {
		dibujarTablero(juego);
		bajarFichas(juego.tablero);
		dibujarTablero(juego);
	}
}

void mostrarArchivo() {
	ifstream archivo;
	string nombreUsu;
	int juegos, ganados, puntos;

	archivo.open(ARCH_USU);

	if (archivo.is_open()) { // Si el archivo está abierto
		cout << endl;
		cout <<  setw(10) << "Usuario" << setw(18) <<  "Juegos" << setw(18) << setw(18) <<  "Puntos" << endl; 

		archivo >> nombreUsu >> juegos >> puntos;

		while (nombreUsu != CENT) { 
			// Mientras el nombre sea distinto del centinela, muestro el contenido de usuarios.txt
			cout <<  setw(10) << nombreUsu << setw(18) << juegos << setw(18) << puntos << endl;
			archivo >> nombreUsu >> juegos >> puntos;
		}
		cout << endl;

		archivo.close(); 
	}

	else
		cout << "ERROR: No se ha encontrado el archivo " << ARCH_USU << "!" << endl;
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
	jugador.partidas = 0; // Inicializo las estadísticas para el nuevo jugador
	jugador.puntos = 0;

	return jugador;
}

bool mostrarInstrucciones(ifstream &archivo) {
	bool aperturaOK = false;

	archivo.open(ARCH_REGLAS); 

	aperturaOK = archivo.is_open();

	if (!aperturaOK)
		cout << "ERROR en la apertura del archivo " << ARCH_REGLAS << "!" << endl;

	return aperturaOK;
}

void instrucciones() {
	ifstream archivo;
	string lectura;

	if (mostrarInstrucciones(archivo)) { // Si el archivo se ha abierto...
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