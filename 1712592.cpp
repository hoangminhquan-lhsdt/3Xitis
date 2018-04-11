#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#pragma warning(disable:4996)
void Input(PLAYER player, char filename[], int score)
{
	FILE *file = fopen(filename, "ab");
	printf("Nhap ten: "); gets_s(player.Name);
	fwrite(&player, sizeof(PLAYER), 1, file);
	fclose(file);
}
void BXH(char filename[]) {
	//PLAYER bxh[10];
	PLAYER player;
	PLAYER list[100];
	int a;
	FILE *f = fopen("Player.txt", "r");
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		a = ftell(f) / sizeof(PLAYER);
		for (int i = 0; i < a; i++) {
			fscanf(f, "%s	%d\n", player.Name, player.score);
			list[i] = player;
			printf("%d. %s   %d\n", i+1, list[i].Name, list[i].score);
		}
	}
	fclose(f);
}
void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Shape(CAR &car, VATCAN vatcan[], COIN coin[])
{
	int i;
	// Xe
	/*	Hinh dang
							O-O
							|M|
							O-O
	*/
	car.hinhdang.o[0][0] = 'O'; car.hinhdang.o[0][2] = 'O'; //Banh truoc
	car.hinhdang.o[2][0] = 'O'; car.hinhdang.o[2][2] = 'O'; //Banh sau
	car.hinhdang.o[0][1] = '-'; car.hinhdang.o[2][1] = '-'; // Than truoc, than sau
	car.hinhdang.o[1][0] = '|'; car.hinhdang.o[1][2] = '|';
	car.hinhdang.o[1][1] = 'M';

	//Vat can
	/*	Hinh dang
							OOO
							OOO
							OOO
	*/
	for (i = 0; i < 5; i++)
	{
		vatcan[i].hinhdang.o[0][0] = 'O'; vatcan[i].hinhdang.o[0][2] = 'O';
		vatcan[i].hinhdang.o[2][0] = 'O'; vatcan[i].hinhdang.o[2][2] = 'O';
		vatcan[i].hinhdang.o[0][1] = 'O'; vatcan[i].hinhdang.o[2][1] = 'O';
		vatcan[i].hinhdang.o[1][0] = 'O'; vatcan[i].hinhdang.o[1][2] = 'O';
		vatcan[i].hinhdang.o[1][1] = 'O';
		vatcan[i].toado.x = rand() % (Width - 3) + 1;
		vatcan[i].toado.y = rand() % 4 - 6*i;
	}
	//Coin
	for (i = 0; i < 10; i++)
	{
		coin[i].toado.x = rand() % (Width - 1) + 1;
		coin[i].toado.y = rand() % Height;
	}
}
void Lane()
{
	for (int i = 0; i < Height; i++)
	{
		gotoxy(0, i);
		putchar('|');
		gotoxy(Width - 1, i);
		putchar('|');
	}
}
void Create(CAR car, VATCAN vatcan[], COIN coin[])
{
	int i, j, k;
	//Dua xe vao duong dua
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			gotoxy(car.toado.x+j, car.toado.y+i);
			putchar(car.hinhdang.o[i + 1][j + 1]);
		}
	}

	//Dua vat can vao duong dua
	for (k = 0; k < 5; k++)
	{
		if (vatcan[k].toado.y > 0 && vatcan[k].toado.y < Height)
		{
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j < 2; j++)
				{
					gotoxy(vatcan[k].toado.x + j, vatcan[k].toado.y + i);
					putchar(vatcan[k].hinhdang.o[i + 1][j + 1]);
				}
			}
		}
	}

	//Tao tien
	for (k = 0; k < 10; k++)
	{
		gotoxy(coin[k].toado.x, coin[k].toado.y);
		putchar('$');
	}

	//Tao lai lane
	Lane();
}
void CarDiChuyen(CAR &car)
{
	if (_kbhit())
	{
		if ((GetAsyncKeyState(VK_LEFT)) && (car.toado.x > 2))
			car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (car.toado.x < Width - 3))
			car.toado.x++;
	}
}
void VatCanDiChuyen(VATCAN vatcan[])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		vatcan[i].toado.y++;
		if (vatcan[i].toado.y > Height)
		{
			vatcan[i].toado.x = rand() % (Width - 3) + 1;
			vatcan[i].toado.y = rand() % 4;
		}
	}
}
void CoinDiChuyen(COIN coin[])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		coin[i].toado.y++;
		if (coin[i].toado.y > Height)
		{
			coin[i].toado.x = rand() % (Width - 3) + 1;
			coin[i].toado.y = rand() % 4;
		}
	}
}
void Control(CAR &car, VATCAN vatcan[], COIN coin[])
{
	int dem = 0;
	//Xe di chuyuen
	CarDiChuyen(car);

	//Vat can di chuyen
	VatCanDiChuyen(vatcan);

	// coin roi
	CoinDiChuyen(coin);
}
int Distance(int x, int y)
{
	return abs(x - y);
}
int Score(CAR &car, COIN coin[])
{
	for (int i = 0; i < 10; i++)
	{
		if (Distance(car.toado.x, coin[i].toado.x) < 2 && Distance(car.toado.y, coin[i].toado.y) < 2)
		{
			coin[i].toado.x = rand() % (Width - 3) + 1;
			coin[i].toado.y = rand() % 4;
			return car.score++;
		}
	}
	return car.score;
		
}
void Ai(CAR &car, VATCAN vatcan[], COIN coin[]) // chua tinh truong hop car.toado.x == 2 vay no sang left 1 cai thi dung cmn
{
	for (int i = 0; i < 10; i++)
	{
		if (car.toado.x <= coin[i].toado.x)
			//while (car.toado.x - 1 != coin.toado.x)
			car.toado.x++;
		if (car.toado.x >= coin[i].toado.x)
			//while (car.toado.x + 1 != coin.toado.x)
			car.toado.x--;
	}
	for (int i = 0; i < 5; i++)
	{
		if (vatcan[i].toado.x + 1 == car.toado.x - 1)
			car.toado.x++;
		if (vatcan[i].toado.x - 1 == car.toado.x + 1)
			car.toado.x--;
		if (car.toado.x == vatcan[i].toado.x - 1)
			car.toado.x = car.toado.x - 2;
		if (car.toado.x == vatcan[i].toado.x + 1)
			car.toado.x = car.toado.x + 2;
		if (car.toado.x == vatcan[i].toado.x)
			car.toado.x = car.toado.x + 3;
	}
}
bool GameOver(CAR car, VATCAN vatcan[])
{
	for (int i = 0; i < 5; i++)
	{
		if ((Distance(car.toado.x, vatcan[i].toado.x) < 3) && (Distance(car.toado.y, vatcan[i].toado.y) < 3)) return true;
	}
	return false;
}
void playGame(CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character)
{
	car.toado.x = 20;
	car.toado.y = 28;
	car.score = 0;
	int score;

	Shape(car, vatcan, coin);
	Lane();
	Create(car, vatcan, coin);

	while (1)
	{
		system("cls");

		Create(car, vatcan, coin);

		Control(car, vatcan, coin);
		//Ai(car, vatcan, coin);
		score = Score(car, coin);
		gotoxy(31, 15);
		printf("Score: %d", score);

		if (GameOver(car, vatcan))
		{
			gotoxy(31, 16);
			Input(character, "Player.txt", score);
			_getch();
			return;
		}

		Sleep(100 - score);
	}
}
void runWord()
{
	for (int i = 0; i < Height; i++)
	{
		gotoxy(40, i);
		printf("Ban Dang Dua Xe");
	}

}
void Rule()
{
	printf("Dung phim -> hay <- de dy chuyen\n");
	printf("Ne cac vat can va lay $ de tang diem so\n");
	printf("Nhan enter de play game\n");
}
void Menu(char *menu[], CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character)
{
	BXH("Player.txt");
	/*int vitri = 0;
	while (1)
	{
		system("cls");
		if (_kbhit)
		{
			if (GetAsyncKeyState(VK_UP))
			{
				if (vitri == 0)
					vitri = 2;
				else vitri--;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (vitri == 2)
					vitri = 0;
				else vitri++;
			}
		}

		// Viet menu
		for (int i = 0; i < 3; i++)
		{
			gotoxy(40, 15+i);
			if (vitri == i)
				printf(">>%s<<\n", menu[i]);
			else printf("--%s--\n", menu[i]);
		}

		// Vao menu
		if (_kbhit())
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				switch (vitri)
				{
				case 0: 
				{
					playGame(car, vatcan, coin, character);
					break;
				}
				case 1: 
				{
					system("cls");
					Rule();
					system("pause"); 
					while (1)
					{
						if (_kbhit())
						{
							if (GetAsyncKeyState(VK_RETURN))
							{
								Menu(menu, car, vatcan, coin, character);
							}
						}
					}
				}
				case 2: break;
				}
				break;
			}
		}
		Sleep(50);
	}*/
}


