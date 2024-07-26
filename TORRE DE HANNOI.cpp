#include <iostream>
#include <conio.h>
#include <dos.h> 
#include <windows.h>
#include <time.h>

#define WIN_WIDTH 70 
#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5

using namespace std; 

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int torres[3][DISKS];
int torreTop[3] = {DISKS-1, -1, -1};

int intentos = 0; 
int puntuacion = 0; 

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void actualizarPuntuacion() {
	gotoxy(WIN_WIDTH + 7, 5);
	cout << "Intentos: " << intentos << endl;
}

void instrucciones() {
	system("cls");
	cout << "Instrucciones";
	cout << "\n----------------";
	cout << "\n Mové los discos de la Torre 1 a la Torre 3.";
	cout << "\n No podés poner un disco grande sobre uno pequeño.";
	cout << "\n Las torres están numeradas como 1, 2 y 3.";
	cout << "\n\nPresioná cualquier tecla para volver al menú";
	getch();
}

void dibujarDisco(int torre, int numDisco, int y) {
	int x;
	if (torre == 1) x = T1POS;
	else if (torre == 2) x = T2POS;
	else if (torre == 3) x = T3POS;
	
	x -= numDisco;
	
	for (int j = 0; j < ((numDisco) * 2) - 1; j++) {
		gotoxy(x, y);
		cout << "±";
		x++;
	}
}

void dibujarTorre(int torre) {
	int x;
	int y = 9;
	
	gotoxy(10, 10); cout << "==========";
	gotoxy(25, 10); cout << "==========";
	gotoxy(40, 10); cout << "==========";
	
	gotoxy(15, 11); cout << "1";
	gotoxy(30, 11); cout << "2";
	gotoxy(45, 11); cout << "3";
	
	for (int i = 0; i < 5; i++) {
		dibujarDisco(torre, torres[torre - 1][i], y);
		y--;
	}
}

int estaVacia(int numTorre) {
	for (int i = 0; i < DISKS; i++)
		if (torres[numTorre][i] != 0)
			return 0;
	return 1;
}

int validarMovimiento(int de, int a) {
	if (!estaVacia(a)) {
		if (torres[de][torreTop[de]] < torres[a][torreTop[a]])
			return 1;
		else 
			return 0;
	}
	return 1;
}

int moverDisco(int de, int a) {
	if (estaVacia(de)) return 0; 
	if (validarMovimiento(de, a)) { 
		if (torres[de][torreTop[de]] != 0) {
			torreTop[a]++;
			torres[a][torreTop[a]] = torres[de][torreTop[de]];
			torres[de][torreTop[de]] = 0;
			torreTop[de]--;
			return 1;
		}
	}
	return 0;
}

int ganaste() { 
	for (int i = 0; i < DISKS; i++)
		if (torres[2][i] != DISKS - i)
			return 0;
	return 1;
}

void jugar() {
	int de, a;
	for (int i = 0; i < DISKS; i++)
		torres[0][i] = DISKS - i;
		for (int i = 0; i < DISKS; i++)
			torres[1][i] = 0;
			for (int i = 0; i < DISKS; i++)
				torres[2][i] = 0;
				
				do {
					system("cls"); 		  
					
					cout << "============================================================" << endl;
					cout << "                       TORRE DE HANOI                       " << endl;
					cout << "============================================================" << endl << endl;
					
					dibujarTorre(1);
					dibujarTorre(2);
					dibujarTorre(3);
					
					if (ganaste()) {
						system("cls");
						cout << "============================================================" << endl;
						cout << "                           ¡GANASTE!                          " << endl;
						cout << "============================================================" << endl;
						cout << endl << endl << endl;
						cout << "Presioná cualquier tecla para volver al menú...";
						getch();
						break;
					}
					
					gotoxy(10, 15);
					cout << "De (Valores: 1, 2, 3): ";
					cin >> de;
					gotoxy(10, 16);
					cout << "A (Valores: 1, 2, 3): ";
					cin >> a;
					
					if (a < 1 || a > 3) continue;
					if (de < 1 || de > 3) continue;
					if (de == a) continue;
					
					de--;
					a--;
					
					moverDisco(de, a);
					
					if (kbhit()) {
						char ch = getch();
						if (ch == 'a' || ch == 'A') { 
						}
						if (ch == 'd' || ch == 'D') { 
						} 
						if (ch == 27) {
							break;
						}
					} 
					
				} while (1);
}

int main() {
	setcursor(0, 0); 
	srand((unsigned)time(NULL)); 
	
	do {
		system("cls");
		gotoxy(10, 5); cout << " -------------------------- "; 
		gotoxy(10, 6); cout << " |     Torre de Hanoi     | "; 
		gotoxy(10, 7); cout << " --------------------------";
		gotoxy(10, 9); cout << "1. Iniciar Juego";
		gotoxy(10, 10); cout << "2. Instrucciones";	 
		gotoxy(10, 11); cout << "3. Salir";
		gotoxy(10, 13); cout << "Seleccionar opción: ";
		char op = getche();
		
		if (op == '1') jugar();
		else if (op == '2') instrucciones();
		else if (op == '3') exit(0);
		
	} while (1);
	
	return 0;
}
