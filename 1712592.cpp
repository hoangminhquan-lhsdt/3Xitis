#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#pragma disable(warning:4996)
void Input(PLAYER player, char filename[], int score)
{
	FILE *file = fopen(filename, "ab");
	printf("Nhap ten: "); gets_s(player.Name);
	fwrite(&player, sizeof(PLAYER), 1, file);
	fclose(file);
}
void BXH(char filename[]) {
	PLAYER player;
	FILE *f = fopen(filename, "rb");
	if (f != NULL) {
		fread(&player, sizeof(PLAYER), 1, f);
	}
	fclose(f);
}
void gotoxy(int x, int y) //Dua con tro toi mot vi tri tren man hinh console
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Shape(CAR &car, VATCAN vatcan[], COIN coin[]) //Tao ra cac hinh dang cua cac vat tren man hinh
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
		vatcan[i].toado.y = rand() % 4 - 6 * i;
	}
	//Coin
	for (i = 0; i < 10; i++)
	{
		coin[i].toado.x = rand() % (Width - 1) + 1;
		coin[i].toado.y = rand() % Height;
	}
}
void Lane() //Ve lane
{
	for (int i = 0; i < Height; i++)
	{
		gotoxy(0, i);
		putchar('|');
		gotoxy(Width - 1, i);
		putchar('|');
	}
}
void Create(CAR car, VATCAN vatcan[], COIN coin[]) // Ve xe vao duong dua
{
	int i, j, k;
	//Dua xe vao duong dua
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			gotoxy(car.toado.x + j, car.toado.y + i);
			putchar(car.hinhdang.o[i + 1][j + 1]);
		}
	}

	//Dua vat can vao duong dua
	for (k = 0; k < 5; k++)
	{
		if (vatcan[k].toado.y > 0 && vatcan[k].toado.y < Height) //Nam ngoai man hinh thi ko dua vao
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
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khonog 
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
		if (vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			vatcan[i].toado.x = rand() % (Width - 3) + 1;
			vatcan[i].toado.y = rand() % 2;
		}
	}
}
void CoinDiChuyen(COIN coin[])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		coin[i].toado.y++;
		if (coin[i].toado.y > Height) //Coin ra khoi man hinh, tao coin moi
		{
			coin[i].toado.x = rand() % (Width - 3) + 1;
			coin[i].toado.y = rand() % 2;
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
int Distance(int x, int y) //Khoang cach giua cac vat tinh tu tam vat
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
void playGame(CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file)
{
	car.toado.x = 20;
	car.toado.y = 28;
	car.score = 0;
	int score, time;

	//CB cac thu can thiet
	Shape(car, vatcan, coin);
	Lane();
	Create(car, vatcan, coin);

	//Bat dau game
	while (1)
	{
		system("cls"); //Xoa man hinh

		Create(car, vatcan, coin); //Dua xe,vc, coin vao man hinh

		Control(car, vatcan, coin); //Lam cho cac vat di chuyen
									//Ai(car, vatcan, coin);
		score = Score(car, coin); //Diem
		gotoxy(31, 15);
		printf("Socre: %d", score); //Viet diem

		if (GameOver(car, vatcan))
		{
			fprintf(file, "%d\n", score);
			fclose(file);
			return;
		}

		//Nhip game
		time = 100 - score;
		if (time>3)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(time);
	}
}

void Rule()
{
	gotoxy(30, 15);
	printf("Dung cac phim mui ten di chuyen va nhat tien");
	gotoxy(30, 16);
	printf("Dont be hitted");
}
void Menu(char *menu[], CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file)
{
	int vitri = 0;
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
			gotoxy(40, 15 + i);
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
					playGame(car, vatcan, coin, character, file);
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
								Menu(menu, car, vatcan, coin, character, file);
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
	}
}


