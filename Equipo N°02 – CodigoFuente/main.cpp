/* Equipo N°02 – CodigoFuente.cpp
    Jesús Augusto Reyes Mechato	[2210838]  
    Alejandra, Veliz García		[2311640]  
    Jordán F. Rodríguez Sánchez	[2111666]  
    Nicholas, Yarrow Larrauri	[2312374] 
*/
#include<iostream>
#include <ctime>
#include <fstream>
#include <string>
#include<conio.h>
#include <cstdlib>
#include <cmath>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <cwchar>

/*This game can be played with any numbers of tokens and jugador s*/
using namespace std;
int posicion[4][4] = { {0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15} };//indexes of tokens on tablero
int punto_partida[4] = { 17,30,56,43 };//jugadorInicial point of each code
int destino[3] = { 22,32,27 };//array used in MakingPathToHome
bool agregarPuntajeDoble  = false;//checking of adding in score twice when token is killed
bool otroAgregarPuntajeDoble = false;//checking of adding in score twice when token is reached
bool salidaFicha = false;//for checking and taking the token out when the token is killed at jugadorInicial point
bool haGanado = false;//To check if any jugador  has won and then to break both loops in JuegoPrincipal
bool opcionReglas = false;//for appropriate Continue Option for Reglas Menu
char eleccionSalidaFicha;
struct LUDO {
	short int NumeroDeJugadores;//Number of jugador s playing the Game
	char ficha[4][4];//tokens names
	char nombre[4][20];//names of jugador 
	char  FichasDisponible[4][4];//tokens that are available to start game with
	char FichasAlcanzadas[4][4];//tokens that have reached home
	char tablero[88];//LUDO bord
	short int puntos[4][4];//puntos of tokens
	char fichasEnTablero[4][4];//tokens that are available on tablero
	char jugadorInicial;//To get the jugador  from which game should be started
	short int numeroDeFichas;//Number of Tokens Used in Playing Game
};
void MostrarTurno(int jugador , LUDO& l);// To display jugador 's turn
void PantallaInicial();//To Display jugadorInicial screen
void MostrarJuegosGuardados(LUDO& l);//to display all the saved games
void  PosicionCorrecta(int jugador , int index, int dice, LUDO& l);//to move the token to right path
int FichasFuera(int jugador , LUDO& l);//Numbers of Tokens on the tablero
void MostrarTablero(LUDO& l);//Displaying The tablero
void FichasAlcanzadas(int jugador , int index, LUDO& l);//Number of Tokens that have reached final position
void IniciarArreglo(LUDO& l);//initiating tablero and other members of LUDO Struct
void IngresarNombres(LUDO& l);//Input names accorfing to number of jugador 
void EliminarFicha(int jugadorindex, int jugador , int position, LUDO& l, int dice);//killing the token
bool FichasDisponible(int jugador , char choice, LUDO& l);//checking if the token available for taking out
void SacarFichasEnTablero(int jugador , LUDO& l);//taking the token out when die number is 6
void MoverFicha(int jugador , LUDO& l, int dice);//For moving the token
void JuegoPrincipal(LUDO& l);//from where the functions are called
void NuevoJuego();//for playing new game
void SavingGame(LUDO l);//for saving game on user choice
void GuardarJuego();//for opening the saved games
void Reglas();//for displaying Reglas of games
void AcercaDe();//AcercaDe the author of code
void Menu();//Menu for selecting out of various choices
void LimpiarYMostrar(int jugador , LUDO& l) {
	system("CLS");
	MostrarTurno(jugador , l);
	MostrarTablero(l);
}
//Main Function
int main() {

	srand((time(0)));
	ShowWindow(GetConsoleWindow(), 3);//opening console in full screen
	PantallaInicial();
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);//changing font size
	Menu();
	system("pause");
}
int FichasDisponible(int jugador , LUDO& l) {
	int contador = 0;
	for (int i = 0; i < l.numeroDeFichas; i++)
		if (l. FichasDisponible[jugador][i] != ' ')
			contador++;
	return contador;
}
int FichasFuera(int jugador , LUDO& l) {//to check if there are more than one token out on the tablero
	int contador = 0;
	for (int i = 0; i < l.numeroDeFichas; i++)
		if (l.fichasEnTablero[jugador][i] != ' ')
			contador++;
	return contador;
}
void MostrarTablero(LUDO& l) {
	cout << "\t\t\t _________________________________________________________________\n";
	cout << "\t\t\t|           |           |__" << l.tablero[27] << "__|__" << l.tablero[28] << "__|__" << l.tablero[29] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.tablero[0] << "     |     " << l.tablero[1] << "     |__" << l.tablero[26] << "__|__" << l.tablero[73] << "__|__" << l.tablero[30] << "__|     " << l.tablero[4] << "     |     " << l.tablero[5] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.tablero[25] << "__|__" << l.tablero[74] << "__|__" << l.tablero[31] << "__|___________|___________|\n";
	cout << "\t\t\t|           |           |__" << l.tablero[24] << "__|__" << l.tablero[75] << "__|__" << l.tablero[32] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.tablero[2] << "     |     " << l.tablero[3] << "     |__" << l.tablero[23] << "__|__" << l.tablero[76] << "__|__" << l.tablero[33] << "__|     " << l.tablero[6] << "     |     " << l.tablero[7] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.tablero[22] << "__|__" << l.tablero[77] << "__|__" << l.tablero[34] << "__|___________|___________|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.tablero[16] << " | " << l.tablero[17] << " | " << l.tablero[18] << " | " << l.tablero[19] << " | " << l.tablero[20] << " | " << l.tablero[21] << " |                 | " << l.tablero[35] << " | " << l.tablero[36] << " | " << l.tablero[37] << " | " << l.tablero[38] << " | " << l.tablero[39] << " | " << l.tablero[40] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|                 |___|___|___|___|___|___|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.tablero[67] << " | " << l.tablero[68] << " | " << l.tablero[69] << " | " << l.tablero[70] << " | " << l.tablero[71] << " | " << l.tablero[72] << " |     L U D O     | " << l.tablero[82] << " | " << l.tablero[81] << " | " << l.tablero[80] << " | " << l.tablero[79] << " | " << l.tablero[78] << " | " << l.tablero[41] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|                 |___|___|___|___|___|___|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.tablero[66] << " | " << l.tablero[65] << " | " << l.tablero[64] << " | " << l.tablero[63] << " | " << l.tablero[62] << " | " << l.tablero[61] << " |                 | " << l.tablero[47] << " | " << l.tablero[46] << " | " << l.tablero[45] << " | " << l.tablero[44] << " | " << l.tablero[43] << " | " << l.tablero[42] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|_________________|___|___|___|___|___|___|\n";
	cout << "\t\t\t|           |           |__" << l.tablero[60] << "__|__" << l.tablero[87] << "__|__" << l.tablero[48] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.tablero[8] << "     |     " << l.tablero[9] << "     |__" << l.tablero[59] << "__|__" << l.tablero[86] << "__|__" << l.tablero[49] << "__|     " << l.tablero[12] << "     |     " << l.tablero[13] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.tablero[58] << "__|__" << l.tablero[85] << "__|__" << l.tablero[50] << "__|___________|___________|\n";
	cout << "\t\t\t|           |           |__" << l.tablero[57] << "__|__" << l.tablero[84] << "__|__" << l.tablero[51] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.tablero[10] << "     |     " << l.tablero[11] << "     |__" << l.tablero[56] << "__|__" << l.tablero[83] << "__|__" << l.tablero[52] << "__|     " << l.tablero[14] << "     |     " << l.tablero[15] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.tablero[55] << "__|__" << l.tablero[54] << "__|__" << l.tablero[53] << "__|___________|___________|\n";
}
void IniciarArreglo(LUDO& l) {
	l.jugadorInicial = 0;
	for (int i = 0; i < 88; i++)
		l.tablero[i] = ' ';
	char token = 'a';
	for (int i = 0; i < l.NumeroDeJugadores; i++) {
		for (int j = 0; j < l.numeroDeFichas; j++) {
			l.fichasEnTablero[i][j] = ' ';
			l.FichasAlcanzadas[i][j] = ' ';
			l.puntos[i][j] = 0;
			l.tablero[i * 4 + j] = token;//initializing tablero's Element
			l.ficha[i][j] = token;//token's array filling
			l. FichasDisponible[i][j] = token++;//available Token's array initializing
		}
	}
}
void IngresarNombres(LUDO& l) {//inputing the names of jugador s
	for (int i = 0; i < l.NumeroDeJugadores; i++) {
		cout << "Ingrese nombre del jugador " << i + 1 << " : ";
		cin >> l.nombre[i];
	}
}
int ContadorAlcanzado(int jugador , LUDO& l) {
	int contador = 0;
	for (int i = 0; i < l.numeroDeFichas; i++)
		contador = l.FichasAlcanzadas[jugador ][i] != ' ' ? contador + 1 : contador;
	return contador;
}
void FichasAlcanzadas(int jugador , int index, LUDO& l) {
	short int previous = punto_partida[jugador ] + l.puntos[jugador ][index];
	if (jugador  != 0) {
		previous = previous > 67 ? previous %= 52 : previous;
		previous = l.puntos[jugador ][index] >= 51 ? l.puntos[jugador ][index] + destino[jugador  - 1] : previous;
	}
	l.FichasAlcanzadas[jugador][index] = l.ficha[jugador ][index];
	l.fichasEnTablero[jugador][index] = ' ';
	l. FichasDisponible[jugador][index] = ' ';
	l.tablero[previous] = ' ';
	if (ContadorAlcanzado(jugador , l) == l.numeroDeFichas) {
		system("CLS");
		cout << "\n\n\n\n\t\t\t";
		cout << l.nombre[jugador ] << "FELICIDADESSSS GANASTE!!!";
		haGanado = true;
		return;
	}
	short int dice = rand() % 6 + 1;
	LimpiarYMostrar(jugador , l);
	cout << "Bonus por alcanzar la ficha:: \n";
	cout << "Die Number : " << dice << endl;
	if (dice != 6 and !FichasFuera(jugador , l))
		return;
	else if (dice == 6 and !FichasFuera(jugador , l))
		SacarFichasEnTablero(jugador , l);
	else if (FichasFuera(jugador , l))
		MoverFicha(jugador , l, dice);
}
void EliminarFicha(int jugadorindex, int jugador , int position, LUDO& l, int dice) {
	short int fundice;
	if (l.tablero[position] != ' ') {
		int i, j, funjugador /*jugador  whose token is killed*/, index;
		for (i = 0; i < 4; i++)
			for (j = 0; j < l.numeroDeFichas; j++)
				if (l.ficha[i][j] == l.tablero[position]) {
					funjugador  = i;
					index = j;
					break;
				}
		if (position == punto_partida[funjugador ]) {
			cout << (funjugador  == jugador  ? "No puedes sacar la ficha cuando ya hay una ficha presente\n": "No puedes matar al jugador en su punto de partida\n");
			if (FichasFuera(jugador , l) >= 2) {
				cout << "Elige otra fichan\n"; MoverFicha(jugador , l, dice);
				agregarPuntajeDoble  = true;
			}
			else {
				agregarPuntajeDoble  = true; return;
			}
		}
		else if (funjugador  == jugador ) {
			cout << "No puedes comer a tu propio jugador \n";
			if (FichasFuera(jugador , l) >= 2) {
				cout << "Elige otra ficha\n"; MoverFicha(jugador , l, dice);
				agregarPuntajeDoble  = true;
			}
			else return;
		}
		else {
			l.tablero[posicion[funjugador ][index]] = l.tablero[position];
			l.tablero[position] = ' ';
			l. FichasDisponible[funjugador ][index] = l.ficha[funjugador ][index];//making it available
			l.fichasEnTablero[funjugador ][index] = ' ';
			l.puntos[funjugador ][index] = 0;
			if (position == punto_partida[jugador ]) {
				salidaFicha = true;
				SacarFichasEnTablero(jugador , l);
				agregarPuntajeDoble  = true;
			}
			fundice = rand() % 6 + 1;
			if (fundice != 6 and !FichasFuera(jugador , l))
				return;
			else if (fundice == 6 and !FichasFuera(jugador , l))
				SacarFichasEnTablero(jugador , l);
			else if (FichasFuera(jugador , l)) {
				 PosicionCorrecta(jugador , jugadorindex, dice, l);
				LimpiarYMostrar(jugador , l);
				cout << "Bonus por comer ficha\n";
				cout << "Die Number is " << fundice << endl;
				MoverFicha(jugador , l, fundice);
				agregarPuntajeDoble  = true;
			}
		}
	}
}
bool  FichasDisponible(int jugador , char choice, LUDO& l) {//checking wheather the selected token is present
	for (int i = 0; i < l.numeroDeFichas; i++)
		if (l. FichasDisponible[jugador ][i] == choice)
			return true;
	return false;
}
void SacarFichasEnTablero(int jugador , LUDO& l) {//taking the token out when, no any token is out on tablero
	if (ContadorAlcanzado(jugador , l) == 4 or FichasFuera(jugador , l) == l.numeroDeFichas) return;
	 short int index;
	if (!salidaFicha) {
		cout << "Elija la ficha que desea sacar : ";
		for (int i = 0; i < l.numeroDeFichas; i++) {
			if (l. FichasDisponible[jugador ][i] != ' ')
				cout << l. FichasDisponible[jugador ][i] << ' ';
		}cout << ": ";
		do {//making the right choice
			cin >> eleccionSalidaFicha;
			if ((! FichasDisponible(jugador , eleccionSalidaFicha, l)))
				cout << "Eleccion invalida! Elija ficha disponible : ";
		} while (! FichasDisponible(jugador , eleccionSalidaFicha, l));
		salidaFicha = true;
	}
		for (int i = 0; i < l.numeroDeFichas; i++)
			if (l.ficha[jugador ][i] == eleccionSalidaFicha)
				index = i;//the index where the choosen token is present
	short int start = punto_partida[jugador ];
	if (l.tablero[start] != ' ') {
		EliminarFicha(index, jugador , start, l, 6);
		agregarPuntajeDoble  = false;
		salidaFicha = false;
	}
	if (salidaFicha) {
		l.tablero[start] = l.tablero[posicion[jugador ][index]];//taking the token out
		l.tablero[posicion[jugador ][index]] = ' ';//replacing the token with space on the home
		l. FichasDisponible[jugador ][index] = ' ';//making it unavilaible for coming on to the tablero
		l.fichasEnTablero[jugador ][index] = eleccionSalidaFicha;
		salidaFicha = false;
		short int dice = rand() % 6 + 1;
		LimpiarYMostrar(jugador , l);
		cout << "Bonus al sacar una ficha\nDie Number : " << dice << endl;
		MoverFicha(jugador , l, dice);
	}
}
void MakingPathToHome(int jugador , int index, int dice, LUDO& l, int previous) {
	if (l.puntos[jugador ][index] >= 51)
		previous = l.puntos[jugador ][index] + destino[jugador  - 1];
	l.tablero[l.puntos[jugador ][index] + dice + destino[jugador  - 1]] = l.tablero[previous];
	l.tablero[previous] = ' ';
	l.puntos[jugador ][index] += dice;
}
void  PosicionCorrecta(int jugador , int index, int dice, LUDO& l) {
	short int position;
	short int start = punto_partida[jugador ];
	short int previous = start + l.puntos[jugador ][index];
	if (jugador  >= 1) {
		if (previous > 67)
			previous %= 52;
		if (previous >= 0 and previous <= 10)
			previous += 52;
		if (l.puntos[jugador ][index] + dice > 50) {
			MakingPathToHome(jugador , index, dice, l, previous);
			return;
		}
		if (previous == 67) {
			position = 15 + dice;
			EliminarFicha(index, jugador , position, l, dice);
			if (agregarPuntajeDoble  or otroAgregarPuntajeDoble) { agregarPuntajeDoble  = false; otroAgregarPuntajeDoble = false; return; }
			l.tablero[position] = l.tablero[previous];
		}
		else if ((start + l.puntos[jugador ][index] + dice > 67)) {
			position = (start + l.puntos[jugador ][index] + dice) % 52;
			if (position >= 0 and position <= 10)
				position += 52;
			EliminarFicha(index, jugador , position, l, dice);
			if (agregarPuntajeDoble  or otroAgregarPuntajeDoble) { agregarPuntajeDoble  = false; otroAgregarPuntajeDoble = false; return; }
			l.tablero[position] = l.tablero[previous];
		}
		else {
			position = start + l.puntos[jugador ][index] + dice;
			EliminarFicha(index, jugador , position, l, dice);
			if (agregarPuntajeDoble  or otroAgregarPuntajeDoble) { agregarPuntajeDoble  = false; otroAgregarPuntajeDoble = false; return; }
			l.tablero[position] = l.tablero[previous];
		}
		l.tablero[previous] = ' ';
	}
	else {
		position = start + l.puntos[jugador ][index] + dice;
		EliminarFicha(index, jugador , position, l, dice);
		if (agregarPuntajeDoble  or otroAgregarPuntajeDoble) { agregarPuntajeDoble  = false; otroAgregarPuntajeDoble = false; return; }
		l.tablero[position] = l.tablero[previous];
		l.tablero[previous] = ' ';
	}
	l.puntos[jugador ][index] += dice;
}

void MoverFicha(int jugador , LUDO& l, int dice) {
	char choiceToken = 'u';
	bool move = true;
	if (dice == 6 and FichasDisponible(jugador , l)) {
		move = false;
		cout << "Quieres sacar otra ficha? \nPresione y para Si y n para NO";
		do {
			choiceToken = _getch();
			cout << endl;
			if (choiceToken != 'y' and choiceToken != 'n')
				cout << "Eleccion invalida! Elije y/n : ";
		} while (choiceToken != 'y' and choiceToken != 'n');
	}
	if (choiceToken == 'y')
		SacarFichasEnTablero(jugador , l);
	else if (choiceToken == 'n' or move) {
		char choice; short int index;
		cout << "Que ficha deseas mover: ";
		do {
			index = -1;
			cin >> choice;
			for (int i = 0; i < l.numeroDeFichas; i++)
				if (l.ficha[jugador ][i] == choice)
					index = i;//el índice donde está presente la ficha elegida
			if (index == -1 or l.fichasEnTablero[jugador ][index] != choice)
				cout << "La ficha no esta disponible! Ingrese correctamente: ";
		} while (index == -1 or l.fichasEnTablero[jugador ][index] != choice);
		//movimiento ficha
		if (l.puntos[jugador ][index] + dice == 56) {
			cout << "Ficha alcanzada :(" << endl;
			FichasAlcanzadas(jugador , index, l);
			return;
		}
		else if (l.puntos[jugador ][index] + dice > 55) {
			cout << "No puedes avanzar\n";
			if (FichasFuera(jugador , l) == 2 or FichasFuera(jugador , l) == 3) {
				cout << "Elige otra ficha\n"; MoverFicha(jugador , l, dice);
				otroAgregarPuntajeDoble = true;
			}
			else return;
		}
		 PosicionCorrecta(jugador , index, dice, l);
		if (dice == 6) {
			dice = rand() % 6 + 1;
			LimpiarYMostrar(jugador , l);
			cout << "Bonus por obtener un SEIS\n";
			cout << "Die Number : " << dice << endl;
			MoverFicha(jugador , l, dice);
		}
	}
}
void MostrarTurno(int jugador , LUDO& l) {
	string name = l.nombre[jugador ];
	short int length = name.length() + 11;
	cout << "\t\t\t\t\t\t ";
	for (int i = 0; i < length; i++)
	cout << '_'; cout << endl;
	cout << "\t\t\t\t\t\t|" << "Turno de "<<name<< "  |\n";
	cout << "\t\t\t\t\t\t|";
	for (int i = 0; i < length; i++)
		cout << '_'; cout << "|\n";
}
void JuegoPrincipal(LUDO& l) {
	char getch;
	int dice = 0;
	int i = l.jugadorInicial;
	while (true)
	{
		for (; i < l.NumeroDeJugadores; i++) {
			system("CLS");
			MostrarTurno(i, l);
			MostrarTablero(l);
			cout << "Presione cualquier tecla para tirar el dado o \'S\' para guardar el juego";
			getch = _getch();
			if (getch == 'S') {
				SavingGame(l);
				Menu();
			}
			dice = rand() % 6 + 1;
			cout << "\n" << "Die Number :" << dice << endl;
			if ((dice != 6 and !FichasFuera(i, l)))
				continue;
			if (dice == 6 and !FichasFuera(i, l))//taking the token out
				SacarFichasEnTablero(i, l);
			else if (FichasFuera(i, l))
				MoverFicha(i, l, dice);
			if (haGanado)
				break;
		}
		if (haGanado) {
			haGanado = false;
			break;
		}
		i = 0;
	}
	cout << "\n\n\nPresione cualquier tecla para regresar al Menu ";
	_getch();
	Menu();
}
void NuevoJuego() {
	LUDO l;
	system("CLS");
	cout << "Ingrese el numero de jugadores [2-4]: ";
	do {
		cin >> l.numeroDeFichas;
		if (l.numeroDeFichas <= 0 or l.numeroDeFichas > 4)
			cout << "Debe haber al menos 1 ficha para jugar ";
	} while (l.numeroDeFichas <= 0 or l.numeroDeFichas > 4);
	cout << "Enter Number of jugador s <2-4> : ";
	do {
		cin >> l.NumeroDeJugadores;
		if (l.NumeroDeJugadores <= 1 or l.NumeroDeJugadores > 4)
			cout << "Debe haber al menos 2 o 4 jugadores ";
	} while (l.NumeroDeJugadores<= 1 or l.NumeroDeJugadores > 4);
	IniciarArreglo(l);
	IngresarNombres(l);
	opcionReglas = true;
	Reglas();
	system("CLS");
	JuegoPrincipal(l);
}
void SavingGame(LUDO l) {
	ofstream save("SavedGames.ludo", ios::app | ios::binary);
	save.write((char*)& l, sizeof(l));
	save.close();
}
void MostrarJuegosGuardados(LUDO& l) {
	for (int i = 0; i < l.NumeroDeJugadores; i++) {
		cout << l.nombre[i];
		if (i < l.NumeroDeJugadores- 1) cout << " VS ";
	}
	cout << endl;
}
void GuardarJuego() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tSAVED GAMES\n";
	ifstream read("SavedGames.ludo", ios::binary);
	read.seekg(0, ios::end);
	short int i = 0;
	LUDO savedludo;
	short int filesize = read.tellg();
	short int numberofGames = filesize / sizeof(LUDO);
	read.seekg(0, ios::beg);
	if (read.fail() or filesize < sizeof(LUDO)) {
		cout << "\t\t0 Saved Games,Play New Games\n\n";
		cout << "\t\tPresione cualquier tecla para regresar al  MENU ";
		_getch();
		Menu();
	}
	else {
		while (true)
		{
			read.read((char*)& savedludo, sizeof(LUDO));
			if (read.eof()) break;
			cout << "\t\t" << i + 1 << ". ";
			MostrarJuegosGuardados(savedludo);
			i++;
		}
		short int choice;
		cout << "Enter Game Number to open Game : ";
		do {
			cin >> choice;
			if (choice <= 0 or choice > numberofGames)
				cout << "Elección invalida, Ingrese nuevamente: ";
		} while (choice <= 0 or choice > numberofGames);
		read.seekg(0, ios::beg);
		read.seekg(sizeof(LUDO) * (choice - 1), ios::beg);
		read.read((char*)& savedludo, sizeof(LUDO));
		JuegoPrincipal(savedludo);
	}
	read.close();
}
void Reglas() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tREGLAS\n";
	cout << "\t\t1. La ficha saldra solo cuando el numero del dado sea 6.\n";
	cout << "\t\t2. La ficha no puede sacarse cuando ya hay una ficha del mismo jugador.\n";
	cout << "\t\t3. Si la ficha de otro jugador esta presente en el punto de inicio \n\t\tdel otro jugador, y el jugador saca la ficha,"
	"\n\t\tentonces la ficha ya presente sera eliminado.\n";
	cout << "\t\t4. Si la ficha se mueve a una posicion donde ya hay una \n\t\tficha presente, la ficha ya presente sera eliminado.\n";
	cout << "\t\t5. Se te dara un turno de bonificacion si sacas la ficha, eliminas una ficha o \n\t\tsi tu ficha llega a casa.\n";
	cout << "\t\t6. No hay puntos de parada en este LUDO en comparación con el LUDO tradicional.\n";
	cout << "\t\t7. Tambien se te dara un turno de bonificacion al obtener un seis.\n\n\n";
	cout << (opcionReglas ? "Presiona cualquier tecla para continuar" : "Presiona cualquier tecla para volver al MENU");
	_getch();
	if (opcionReglas) {
		opcionReglas = false;
		return;
	}
	else
		Menu();
}
void AcercaDe() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tAcercaDe\n\n";
	cout << "\t\tEste juego es creado por Alejandra Veliz, Nicholas Yarrow, Jordan Rodriguez y Jesus Reyes. \n\n\n";
	cout << "\t\tPresione una tecla para volver al MENU ";
	_getch();
	Menu();
}
void Menu() {
	system("CLS");
	char choice;
	cout << "\n\n\n\n\n\t\tMAIN MENU\n";
	cout << "\t\t1. NUEVO JUEGO\n";
	cout << "\t\t2. PLAY SAVED GAMES\n";
	cout << "\t\t3. REGLAS\n";
	cout << "\t\t4. AcercaDe\n";
	cout << "\t\t5. SALIR\n\n";
	cout << "\t\tSeleccione una opcion [1-5]: ";
	do {
		choice = _getch();
		cout << endl;
		if (choice != '1' and choice != '2' and choice != '3' and choice != '4' and choice != '5')
			cout << "Seleccione una opcion valida [1-4] ";
	} while (choice != '1' and choice != '2' and choice != '3' and choice != '4' and choice != '5');
	if (choice == '1')
		NuevoJuego();
	else if (choice == '2')
		GuardarJuego();
	else if (choice == '3')
		Reglas();
	else if (choice == '4')
		AcercaDe();
	else if (choice == '5')
		exit(0);
}
void PantallaInicial() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t                        _________    _________\n";
	cout << "\t\t\t\t\t|          |        |  |         \\  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|________  |________|  |_________/  |_________|\n";
	Sleep(800);
}

