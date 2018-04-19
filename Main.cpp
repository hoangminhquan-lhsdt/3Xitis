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
	VATCAN vatcan[10], vatcan2[10];
	COIN coin[10], coin2[10];
	PLAYER character;
	CHUCHAY cc;
	int sovatcan = 5;
	char *menu[] = { "Play game","2 Player","Rule","BXH","Exit" };
	srand((unsigned)time(NULL));
	//FILE *file = fopen("Player.txt", "a+");
	Menu(menu);
	//Thiet lap thong so ve xe
	_getch();
}