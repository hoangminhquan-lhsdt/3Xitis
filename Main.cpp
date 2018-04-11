#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>


void main()
{
	CAR car;
	VATCAN vatcan[5];
	COIN coin[10];
	PLAYER character;
	char *menu[] = { "Play game","Rule","Exit" };
	srand((unsigned)time(NULL));

	Menu(menu, car, vatcan, coin, character);


	//Thiet lap thong so ve xe
	_getch();
}