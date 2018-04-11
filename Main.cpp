#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)

void main()
{
	CAR car;
	VATCAN vatcan[5];
	COIN coin[10];
	PLAYER character;
	char *menu[] = { "Play game","Rule","BXH","Exit" };
	srand((unsigned)time(NULL));
	FILE *file = fopen("Player.txt", "a+");
	Menu(menu, car, vatcan, coin, character, file);
	fclose(file);
	//Thiet lap thong so ve xe
	_getch();
}