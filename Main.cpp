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
	char *menu[] = { "Play game","Rule","Exit" };
	srand((unsigned)time(NULL));

	//Menu(menu, car, vatcan, coin, character);
	
	PLAYER player;
	char c;
	FILE *f = fopen("Player.txt", "w");
	for (int i = 0; i < 3; i++) {
		printf("Nhap ten: "); 
		scanf("%[^\n]s %c", player.Name, &c);
		printf("Nhap diem: ");
		scanf("%d", &player.score);
		scanf("%c", &c);
		fflush(stdin);
		//fwrite(&player, sizeof(PLAYER), 1, f);
		fprintf(f, "%s%d\n", player.Name, player.score);
	}
	fclose(f);
	//PLAYER player;
	PLAYER list[100];
	int a;
	FILE *fp = fopen("Player.txt", "r");
	if (fp != NULL) {
		fseek(f, 0, SEEK_END);
		a = ftell(fp) / sizeof(PLAYER);
		for (int i = 0; i < a; i++) {
			fscanf(fp, "%s	%d\n", player.Name, player.score);
			list[i] = player;
			printf("%d. %s   %d\n", i + 1, list[i].Name, list[i].score);
		}
	}
	fclose(fp);
	//Thiet lap thong so ve xe
	_getch();
}