#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)

void main()
{
	CAR car,car2;
	VATCAN vatcan[5], vatcan2[5];
	COIN coin[10], coin2[10];
	PLAYER character;
	char *menu[] = { "Play game","2 Player","Rule","BXH","Exit" };
	srand((unsigned)time(NULL));
	FILE *file = fopen("Player.txt", "a+");
	Menu(menu, car, vatcan, coin, character, file, car2, vatcan2,coin2);
	fclose(file);
	//Thiet lap thong so ve xe
	_getch();
}