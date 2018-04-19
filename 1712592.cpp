#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#pragma warning(disable:4996)


void Input(PLAYER character, char filename[], int score)
{
	flushall();
	FILE *file = fopen(filename, "a");
	gotoxy(31,16);
	printf("Nhap ho va ten: "); 
	gets_s(character.Name);
	fprintf(file, "%s" "\n", character.Name);
	//fprintf(file, "\0");
	fprintf(file, "	%d\n", score);
	//fprintf(file, "\n");
	fclose(file);
	flushall();
	FlushConsoleInputBuffer;
}
void BXH() {
	char c;
	int length;
	system("cls");
	PLAYER list[1000];
	int i = 0;
	FILE *f = fopen("Player.txt", "r");
	while (!feof(f)) {
		fflush(stdin);
		fgets(list[i].Name, 30, f);
		if (!strcmp(list[i].Name, "\n"))					// 
			break;											//
		length = strlen(list[i].Name) - 1;					//
		if ((length > 0) && (list[i].Name[length] == '\n')) //
			list[i].Name[length] = '\0';					// https://stackoverflow.com/questions/25615916/removing-newline-from-fgets
		fscanf(f, "%d\n", &list[i].score);
		//fgetc(f);
		printf("%d. %s    %d\n", i + 1, list[i].Name, list[i].score);
		i++;
		fflush(stdin);
	}
	fclose(f);
	_getch();
}
void gotoxy(int x, int y) //Dua con tro toi mot vi tri tren man hinh console
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Shape(CAR &car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau) //Tao ra cac hinh dang cua cac vat tren man hinh
{
	int i, k;
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
	for (i = 0; i < 10; i++)
	{
		vatcan[i].hinhdang.o[0][0] = 'O'; vatcan[i].hinhdang.o[0][2] = 'O';
		vatcan[i].hinhdang.o[2][0] = 'O'; vatcan[i].hinhdang.o[2][2] = 'O';
		vatcan[i].hinhdang.o[0][1] = 'O'; vatcan[i].hinhdang.o[2][1] = 'O';
		vatcan[i].hinhdang.o[1][0] = 'O'; vatcan[i].hinhdang.o[1][2] = 'O';
		vatcan[i].hinhdang.o[1][1] = 'O';

		//Gan toa do vat can
		do
			vatcan[i].toado.x = rand() % (riasau - 3) + 1 + riatruoc;
		while((vatcan[i].toado.x >= riasau) || (vatcan[i].toado.x <= riatruoc));
		vatcan[i].toado.y = rand() % 4 - 6 * i;
		

		//Chon chieu vat can di chuyen
		k = rand() % 2;
		if (k == 0)
			vatcan[i].trangthai = LEFT;
		else
			vatcan[i].trangthai = RIGHT;

		//Bien
		vatcan[i].trai.x = vatcan[i].toado.x - 2;
		vatcan[i].phai.x = vatcan[i].toado.x + 2;
	}

	//Coin: $
	for (i = 0; i < 10; i++)
	{
		do
			coin[i].toado.x = rand() % (riasau - 1) + 1 + riatruoc;
		while ((coin[i].toado.x >= riasau) || (coin[i].toado.x <= riatruoc));
		coin[i].toado.y = rand() % Height;
	}
}
void Lane(int riatruoc, int riasau) //Ve lane
{
	/*
			|	|
			|	|
			.....
			|	|
	*/
	for (int i = 0; i < Height; i++)
	{
		gotoxy(riatruoc, i);
		putchar('|');
		gotoxy(riasau-1, i);
		putchar('|');
	}
}
void Create(CAR car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau,int sovatcan) // Ve xe vao duong dua
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
	for (k = 0; k < sovatcan; k++)
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
	Lane(riatruoc,riasau);
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


void moveVatCan(VATCAN vatcan[], int riatruoc, int riasau, int sovatcan)
{
	int i;
	for (i = 0; i < sovatcan; i++)
	{
		vatcan[i].toado.y++;
		if (vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			vatcan[i].toado.x = rand() % (Width - 3) + 1;
			vatcan[i].toado.y = rand() % 2;
		}
	}
}
/*void DiChuyenPhai(VATCAN vatcan, int riatruoc, int riasau)//ban thu nghiem chua chay duoc
=======
void DiChuyenPhai(VATCAN vatcan, int riatruoc, int riasau)//thu nghiem
>>>>>>> 573a36769a928466b17d9e0d501062ef0ab5b55a
{
	vatcan.toado.y++;
	vatcan.toado.x++;
	if (vatcan.toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
	{
		do
			vatcan.toado.x = rand() % (riasau - 3) + 1 + riatruoc;
		while ((vatcan.toado.x >= riasau) || (vatcan.toado.x <= riatruoc));
		vatcan.toado.y = rand() % 3;
	}
	if (vatcan.toado.x + 2 == riasau)
		return;

}
void DiChuyenTrai(VATCAN vatcan, int riatruoc, int riasau)//thu nghiem
{
	vatcan.toado.y++;
	vatcan.toado.x--;
	if (vatcan.toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
	{
		do
			vatcan.toado.x = rand() % (riasau - 3) + 1 + riatruoc;
		while ((vatcan.toado.x >= riasau) || (vatcan.toado.x <= riatruoc));
		vatcan.toado.y = rand() % 3;
	}
	if (vatcan.toado.x - 2 == riatruoc)
		return;
<<<<<<< HEAD
}//thu nghiem chua chay duoc*/

void VatCanDiChuyen(VATCAN vatcan[], int riatruoc, int riasau, int sovatcan)//add them di chuyen

{
	int i;
	for (i = 0; i < sovatcan; i++)
	{
		/*vatcan[i].toado.y++;
		vatcan[i].toado.x++;
		if (vatcan[i].toado.x+2 == riasau)
			while (vatcan[i].toado.x != riatruoc)
				vatcan[i].toado.x--;
		if (vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			do
				vatcan[i].toado.x = rand() % (riasau - 3) + 1 + riatruoc;
			while ((vatcan[i].toado.x >= riasau) || (vatcan[i].toado.x <= riatruoc));
			vatcan[i].toado.y = rand() % 3;
		}
		DiChuyenPhai(vatcan[i], riatruoc, riasau);*/

		//Doi huong
		if (vatcan[i].toado.x == riatruoc + 2)
			vatcan[i].trangthai = RIGHT;
		if (vatcan[i].toado.x == riasau - 3)
			vatcan[i].trangthai = LEFT;
		if (vatcan[i].toado.x == vatcan[i].trai.x)
			vatcan[i].trangthai = RIGHT;
		if (vatcan[i].toado.x == vatcan[i].phai.x)
			vatcan[i].trangthai = LEFT;

		//Sang trai phai
		if (vatcan[i].trangthai == LEFT)
			vatcan[i].toado.x--;
		if (vatcan[i].trangthai == RIGHT)
			vatcan[i].toado.x++;

		//Di xuong
		vatcan[i].toado.y++;
		if (vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			do
				vatcan[i].toado.x = rand() % (riasau - 3) + 1 + riatruoc;
			while ((vatcan[i].toado.x >= riasau) || (vatcan[i].toado.x <= riatruoc));
			vatcan[i].toado.y = rand() % 3;
		}
		
	}
	
}

void CoinDiChuyen(COIN coin[], int riatruoc, int riasau)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		coin[i].toado.y++;
		if (coin[i].toado.y > Height) //Coin ra khoi man hinh, tao coin moi
		{
			do
				coin[i].toado.x = rand() % (riasau - 1) + 1 + riatruoc;
			while ((coin[i].toado.x >= riasau) || (coin[i].toado.x <= riatruoc));
			coin[i].toado.y = rand() % 4;
		}
	}
}
void Control(CAR &car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau, CHUCHAY &cc, int sovatcan)
{
	int dem = 0;
	//Xe di chuyuen
	CarDiChuyen(car);

	//Vat can di chuyen
	//moveVatCan(vatcan, riatruoc, riasau, sovatcan);
	VatCanDiChuyen(vatcan, riatruoc, riasau, sovatcan);

	//CoinDiChuyen(coin);

	CoinDiChuyen(coin, riatruoc, riasau);

	//chu chay
	runWord(cc);

}
int Distance(int x, int y) //Khoang cach giua cac vat tinh tu tam vat
{
	return abs(x - y);
}
int Score(CAR &car, COIN coin[], int riatruoc, int riasau)
{
	for (int i = 0; i < 10; i++)
	{
		if (Distance(car.toado.x, coin[i].toado.x) < 2 && Distance(car.toado.y, coin[i].toado.y) < 2)
		{
			do
				coin[i].toado.x = rand() % (riasau - 1) + 1 + riatruoc;
			while ((coin[i].toado.x >= riasau) || (coin[i].toado.x <= riatruoc));
			coin[i].toado.y = rand() % 4;
			car.score++;
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
void playGame(CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, int riatruoc, int riasau, CHUCHAY &cc, int &sovatcan)
{
	car.toado.x = 20;
	car.toado.y = 28;
	car.score = 0;
	int score, time, temp = -1;
	cc.toaodo.y = 0;
	//CB cac thu can thiet
	Shape(car, vatcan, coin, riatruoc, riasau);
	Lane(riatruoc, riasau);
	Create(car, vatcan, coin, riatruoc, riasau,sovatcan);

	//Bat dau game
	while (1)
	{
		system("cls"); //Xoa man hinh

		Create(car, vatcan, coin, riatruoc, riasau,sovatcan); //Dua xe,vc, coin vao man hinh

		Control(car, vatcan, coin, riatruoc, riasau,cc,sovatcan); //Lam cho cac vat di chuyen
									//Ai(car, vatcan, coin);
		score = Score(car, coin, riatruoc, riasau); //Diem
		gotoxy(31, 15);
		printf("Score: %d", score); //Viet diem
		if ((score %20 == 0)&& temp!=score && score >1 && score <101) //Tao ra them cac vat can
		{
			temp = score;
			sovatcan++;
		}
		if (GameOver(car, vatcan))
		{
			//FlushConsoleInputBuffer;
			//fflush(stdin);
			//fprintf(file, "%d\n", score);
			flushall();
			gotoxy(31, 16);
			Input(character, "Player.txt", score);
			_getch();
			return;
		}

		//Nhip game
		time = 100 - score;
		if (time>3)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(time);
	}
}
void controlTwoCar(CAR &car, CAR &car2, int riatruoc1, int riasau1, int riatruoc2, int riasau2)
{
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khonog 
	{

		if ((GetAsyncKeyState(VK_NUMPAD4)) && (car2.toado.x > riatruoc2 + 2))
			car2.toado.x--;
		if ((GetAsyncKeyState(VK_NUMPAD6)) && (car2.toado.x < riasau2 - 3))
			car2.toado.x++;
		if ((GetAsyncKeyState(VK_LEFT)) && (car.toado.x > riatruoc1 + 2))
			car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (car.toado.x < riasau1 - 3))
			car.toado.x++;
	}
}
void playTwoCar(CAR &car1, VATCAN vatcan1[], COIN coin1[], CAR &car2, VATCAN vatcan2[], COIN coin2[], CHUCHAY &cc, int sovatcan)
{
	car1.toado.x = 15;
	car1.toado.y = 28;
	car2.toado.x = 100;
	car2.toado.y = 28;

	car1.score = 0;
	car2.score = 0;
	int score1, score2, time;
	int riatruoc1 = 0;
	int riasau1 = Width;
	int riatruoc2 = 90;
	int riasau2 = 120;
	cc.toaodo.y = 0;
	//CB cac thu can thiet
	//PLayer 1
	Shape(car1, vatcan1, coin1, riatruoc1, riasau1);
	Lane(riatruoc1, riasau1);
	//Player 2
	Shape(car2, vatcan2, coin2, riatruoc2, riasau2);
	Lane(riatruoc2, riasau2);
	//Dua vao 
	Create(car1, vatcan1, coin1, riatruoc1, riasau1,sovatcan);
	Create(car2, vatcan2, coin2, riatruoc2, riasau2,sovatcan);

	//Bat dau game
	while (1)
	{
		system("cls"); //Xoa man hinh
					   //Xuat ra man hinh
		Create(car1, vatcan1, coin1, riatruoc1, riasau1,sovatcan); //Dua xe,vc, coin vao man hinh
		Create(car2, vatcan2, coin2, riatruoc2, riasau2,sovatcan);

		//Control
		controlTwoCar(car1, car2, riatruoc1, riasau1, riatruoc2, riasau2); //Lam cho cac vat di chuyen

		VatCanDiChuyen(vatcan1, riatruoc1, riasau1,sovatcan);
		VatCanDiChuyen(vatcan2, riatruoc2, riasau2,sovatcan);
		CoinDiChuyen(coin1, riatruoc1, riasau1);
		CoinDiChuyen(coin2, riatruoc2, riasau2);
		runWord(cc);
		//Ai(car, vatcan, coin);
		score1 = Score(car1, coin1, riatruoc1, riasau1);
		score2 = Score(car2, coin2, riatruoc2, riasau2);//Diem
		gotoxy(31, 7);
		printf("Score 1: %d", score1); //Viet diem
		gotoxy(80, 7);
		printf("Score 2: %d", score2);

		if (GameOver(car1, vatcan1) || GameOver(car2, vatcan2))
		{
			system("cls");
			if (score2 > score1)
			{
				gotoxy(30, 15);
				printf("Nguoi choi 2 thang\n");
				system("pause");
				return;
			}
			else if (score1 > score2)
			{
				gotoxy(30, 15);
				printf("Nguoi choi 1 thang\n");
				system("pause");
				return;
			}
			else
			{
				gotoxy(30, 15);
				printf("Hoa\n");
				system("pause");
				return;
			}
		}

		//Nhip game
		time = 100 - score1;

		if (time>3)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(time);
	}
}
void runWord(CHUCHAY &cc)
{
	
	//Di xuong di len
	if(cc.trangthai==DOWN)
		cc.toaodo.y++;
	if (cc.trangthai == UP)
		cc.toaodo.y--;

	//Doi chieu chuyen dong
	if (cc.toaodo.y == Height)
		cc.trangthai = UP;
	if (cc.toaodo.y == 0)
		cc.trangthai = DOWN;

	gotoxy(55, cc.toaodo.y);
	printf("%s", cc.str);
}
void Rule()
{
	gotoxy(30, 15);
	printf("Dung cac phim mui ten di chuyen va nhat tien.");
	gotoxy(30, 16);
	printf("Dont hit the obstacles.");
	gotoxy(30, 17);
}
int VietMenu(char *menu[]) {
	int vitri = 0;
	while (1)
	{
		system("cls");
		if (_kbhit)
		{
			if (GetAsyncKeyState(VK_UP))
			{
				if (vitri == 0)
					vitri = MAXMENU - 1;
				else vitri--;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (vitri == MAXMENU - 1)
					vitri = 0;
				else vitri++;
			}
		}
		for (int i = 0; i < MAXMENU; i++)
		{
			gotoxy(40, 15 + i);
			if (vitri == i)
				printf(">>%s<<\n", menu[i]);
			else printf("--%s--\n", menu[i]);
		}
		if (GetAsyncKeyState(VK_RETURN)) return vitri;
	}

}
void Menu(char *menu[], CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, CAR &car2, VATCAN vatcan2[], COIN coin2[], CHUCHAY &cc, int sovatcan)
{
	int breaker = 1;
	int vitri;
	while (breaker) {
		vitri = VietMenu(menu);
		switch (vitri) {
		case 0:
		{
			if (_kbhit())
				playGame(car, vatcan, coin, character, 0, Width, cc, sovatcan);
			break;
		}
		case 1:
		{
			playTwoCar(car, vatcan, coin, car2, vatcan2, coin2, cc, sovatcan);
			continue;
		}
		case 2:
		{
			system("cls");
			Rule();
			system("pause");
			if (_kbhit())
			{
				continue;
			}
		}
		case 3: //BXH
		{
			system("cls");
			BXH();
			system("pause");
			if (_kbhit())
			{
				continue;
			}
		}
		case 4: breaker = 0; break;
		}
	}

	/*int vitri = 0;
	while (1)
	{
		system("cls");
		if (_kbhit)
		{
			if (GetAsyncKeyState(VK_UP))
			{
				if (vitri == 0)
					vitri = MAXMENU-1;
				else vitri--;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (vitri == MAXMENU-1)
					vitri = 0;
				else vitri++;
			}
		}

		// Viet menu
		for (int i = 0; i < MAXMENU; i++)
		{
			gotoxy(40, 15 + i);
			if (vitri == i)
				printf(">>%s<<\n", menu[i]);
			else printf("--%s--\n", menu[i]);
		}*/

		// Vao menu
	/*while (1) {
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (vitri)
			{
			case 0:
			{
				if (_kbhit())
					playGame(car, vatcan, coin, character, file, 0, Width, cc, sovatcan);
				break;
			}
			case 1:
			{
				playTwoCar(car, vatcan, coin, car2, vatcan2, coin2, cc, sovatcan);
				break;
			}
			case 2:
			{
				system("cls");
				Rule();
				system("pause");
				if (_kbhit())
				{
					Menu(menu, car, vatcan, coin, character, file, car2, vatcan2, coin2, cc, sovatcan);
				}
				break;
			}
			case 3: //BXH
			{
				system("cls");
				BXH(file);
				system("pause");
				if (_kbhit())
				{
					Menu(menu, car, vatcan, coin, character, file, car2, vatcan2, coin2, cc, sovatcan);
				}
				break;
			}

			case 4: return;
			}

		}
	}*/
		//Sleep(50);
}




