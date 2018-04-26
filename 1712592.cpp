﻿#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <mmsystem.h>
#pragma warning(disable:4996)
O buffer[30][30];
void Input(int score)
{
	system("cls");
	FILE *f = fopen("Player.txt", "a");
	PLAYER player;
	char c;
	gotoxy(0, 15);
	printf("Nhap ten:  ");
	scanf(" %[^\n]s &c", player.Name, &c);
	fprintf(f, "%s\n", player.Name);
	fprintf(f, "	%d\n", score);
	fclose(f);
	c = getch();
}
void BXH() {
	//char c;
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

void drawBuffer(int dong, int cot, char kytu)
{
	buffer[dong][cot].kytu = kytu;
}
void Shape(THINGS &thing) //Tao ra cac hinh dang cua cac vat tren man hinh

{
	int i, k;
	// Xe
	/*	Hinh dang
						O-O
						|M|
						O-O
	*/
	thing.car.hinhdang.o[0][0] = 'O'; thing.car.hinhdang.o[0][2] = 'O'; //Banh truoc
	thing.car.hinhdang.o[2][0] = 'O'; thing.car.hinhdang.o[2][2] = 'O'; //Banh sau
	thing.car.hinhdang.o[0][1] = '-'; thing.car.hinhdang.o[2][1] = '-'; // Than truoc, than sau
	thing.car.hinhdang.o[1][0] = '|'; thing.car.hinhdang.o[1][2] = '|';
	thing.car.hinhdang.o[1][1] = 'M';
	//Toa do xe
	thing.car.toado.x = (thing.riasau+ thing.riatruoc)/2;
	thing.car.toado.y = 28;
	thing.car.score = 0;

	//Vat can
	/*	Hinh dang
						█ █
						███
						█ █
	*/
	for (i = 0; i < 10; i++)
	{
		thing.vatcan[i].hinhdang.o[0][0] = 219; thing.vatcan[i].hinhdang.o[0][2] = 219;
		thing.vatcan[i].hinhdang.o[2][0] = 219; thing.vatcan[i].hinhdang.o[2][2] = 219;
		thing.vatcan[i].hinhdang.o[0][1] = ' '; thing.vatcan[i].hinhdang.o[2][1] = ' ';
		thing.vatcan[i].hinhdang.o[1][0] = 219; thing.vatcan[i].hinhdang.o[1][2] = 219;
		thing.vatcan[i].hinhdang.o[1][1] = 219;

		//Gan toa do vat can
		thing.vatcan[i].toado.x = random(thing.riatruoc, thing.riasau);
		thing.vatcan[i].toado.y = rand() % 4 - 6 * i;
		
		//random chieu vat can di chuyen
		k = rand() % 2;
		if (k == 0)
			thing.vatcan[i].trangthai = LEFT;
		else
			thing.vatcan[i].trangthai = RIGHT;

		//Bien
		thing.vatcan[i].trai.x = thing.vatcan[i].toado.x - 1;
		thing.vatcan[i].phai.x = thing.vatcan[i].toado.x + 1;
	}

	//Coin: $
	for (i = 0; i < 10; i++)
	{
		thing.coin[i].toado.x = random(thing.riatruoc, thing.riasau);
		thing.coin[i].toado.y = rand() % Height;
	}

	//lam trang Buffer
	//for (i = 0; i < 30; i++)
		//for (k = 0; k < 30; k++)
			//buffer[i][k].kytu = ' ';

	//tao hinh cho dan
	for(i=0;i<10;i++)
		thing.bullet[i].bullet = 'l';
}
inline int random(int a, int b)
{
	return rand() % (b - a - 1) + a;
}
void Lane(int riatruoc, int riasau) //Ve lane
{
	/*
			|	|
			|	|
	*/
	for (int i = 0; i < Height; i++)
	{
		drawBuffer(i, riatruoc, '|');
		drawBuffer(i, riasau - 1, '|');
	}
}
void Create(THINGS thing) // Ve xe vao duong dua
{
	int i, j, k;
	//ve xe vao duong dua
	for (i = -1; i < 2; i++)
		for (j = -1; j < 2; j++)
			drawBuffer(thing.car.toado.y + i, thing.car.toado.x + j, thing.car.hinhdang.o[i + 1][j + 1]); //Ve xe vào buffer

	//ve tien
	for (k = 0; k < 10; k++)
		drawBuffer(thing.coin[k].toado.y, thing.coin[k].toado.x, '$'); // ve tien vao buffer

	//ve vat can vao duong dua
	for (k = 0; k < thing.sovatcan; k++)
	{
		if (thing.vatcan[k].toado.y > 0 && thing.vatcan[k].toado.y < Height) //Nam ngoai man hinh thi ko dua vao
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					drawBuffer(thing.vatcan[k].toado.y + i, thing.vatcan[k].toado.x + j, thing.vatcan[k].hinhdang.o[i + 1][j + 1]); //Ve vat can vao buffer
	}

	//ve lai lane
	Lane(thing.riatruoc, thing.riasau);

	//In buffer ra man hinh
	for(int i=0;i<Height;i++)
		for (int j = thing.riatruoc; j < thing.riasau; j++)
		{
			gotoxy(j, i);
			putchar(buffer[i][j].kytu);
			buffer[i][j].kytu = ' '; // in xoa xong huy ky tu
		}
	//create bullet
	DrawBullet(thing);
}
void Nocursortype() // Xoa con tro chuot tren man hinh console: https://daynhauhoc.com/t/hoi-ve-con-tro-chuot-tren-man-hinh-console/34411/3
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void CarDiChuyen(THINGS &thing)
{
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khong 
	{
		if ((GetAsyncKeyState(VK_LEFT)) && (thing.car.toado.x > 2)) //Trai
			thing.car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (thing.car.toado.x < Width - 3)) //Phai
			thing.car.toado.x++;
		if ((GetAsyncKeyState(VK_UP)) && (thing.car.toado.y > 1)) //Len
			thing.car.toado.y--;
		if ((GetAsyncKeyState(VK_DOWN)) && (thing.car.toado.y < Height - 2)) //Xuong
			thing.car.toado.y++;
	}
}
void createbullet2(THINGS &thing)
{
	int i;
	for (i = 0; i < 10; i+=2)
	{
		thing.bullet[i].toado.x = thing.car.toado.x-1;
		thing.bullet[i].toado.y = thing.car.toado.y-2;
		thing.bullet[i + 1].toado.x = thing.car.toado.x + 1;
		thing.bullet[i + 1].toado.y = thing.car.toado.y - 2;
	}
}
void ControlBullet(THINGS &thing)
{
		if (GetAsyncKeyState(VK_SPACE) && thing.sodan<10)//create bullet
		{
			thing.bullet[thing.sodan].toado.x = thing.car.toado.x - 1;
			thing.bullet[thing.sodan].toado.y = thing.car.toado.y - 2;
			thing.bullet[thing.sodan + 1].toado.x = thing.car.toado.x + 1;
			thing.bullet[thing.sodan + 1].toado.y = thing.car.toado.y - 2;
			thing.sodan+=2;
		}
}
void BulletMove(THINGS &thing)
{
	int j;
	for (j = 0; j < thing.sodan; j++)
	{
		if(thing.bullet[j].toado.y>=0)
		thing.bullet[j].toado.y -= 2;
		//thing.bullet[j + 1].toado.y -= 2;
	}
}
void DrawBullet(THINGS &thing)
{
	int i;
	for (i = 0; i < thing.sodan; i++)
	{
		drawBuffer(thing.bullet[i].toado.y, thing.bullet[i].toado.x, thing.bullet[i].bullet = 'l');
		//drawBuffer(thing.bullet[i +1].toado.y, thing.bullet[i +1].toado.x, thing.bullet[i +1].bullet = 'l');
	}
}

void moveVatCan(THINGS &thing)

{
	int i;
	for (i = 0; i < thing.sovatcan; i++)
	{
		thing.vatcan[i].toado.y++;
		if (thing.vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			thing.vatcan[i].toado.x = rand() % (Width - 3) + 1;
			thing.vatcan[i].toado.y = rand() % 2;
		}
	}
}

void VatCanDiChuyen(THINGS &thing)//add them di chuyen

{
	int i;
	for (i = 0; i < thing.sovatcan; i++)
	{
		//Doi huong
		if (thing.vatcan[i].toado.x == thing.riatruoc + 2)
			thing.vatcan[i].trangthai = RIGHT;
		if (thing.vatcan[i].toado.x == thing.riasau - 3)
			thing.vatcan[i].trangthai = LEFT;
		if (thing.vatcan[i].toado.x == thing.vatcan[i].trai.x)
			thing.vatcan[i].trangthai = RIGHT;
		if (thing.vatcan[i].toado.x == thing.vatcan[i].phai.x)
			thing.vatcan[i].trangthai = LEFT;

		//Sang trai phai
		if (thing.vatcan[i].trangthai == LEFT)
			thing.vatcan[i].toado.x--;
		if (thing.vatcan[i].trangthai == RIGHT)
			thing.vatcan[i].toado.x++;

		//Di xuong
		thing.vatcan[i].toado.y++;
		if (thing.vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			thing.vatcan[i].toado.x = random(thing.riatruoc, thing.riasau);
			thing.vatcan[i].toado.y = rand() % 4;
		}
		
	}
	
}
void CoinDiChuyen(THINGS &thing)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		thing.coin[i].toado.y++;
		if (thing.coin[i].toado.y > Height) //Coin ra khoi man hinh, tao coin moi
		{
			thing.coin[i].toado.x = random(thing.riatruoc, thing.riasau);
			thing.coin[i].toado.y = rand() % 4;
		}
	}
}
void Control(THINGS &thing)
{
	
	//Xe di chuyuen
	CarDiChuyen(thing);
	//bullet move
	ControlBullet(thing);
	//createbullet2(thing);
	BulletMove(thing);

	//CoinDiChuyen(coin)
	CoinDiChuyen(thing);

	//Vat can di chuyen
	if (thing.car.score < 20)
		moveVatCan(thing);
	else VatCanDiChuyen(thing);
}
int Distance(int x, int y) //Khoang cach giua cac vat tinh tu tam vat
{
	return abs(x - y);
}
int Score(THINGS &thing)
{
	for (int i = 0; i < 10; i++)
	{
		if (Distance(thing.car.toado.x, thing.coin[i].toado.x) < 2 && Distance(thing.car.toado.y, thing.coin[i].toado.y) < 2)
		{
			thing.coin[i].toado.x = random(thing.riatruoc, thing.riasau);
			thing.coin[i].toado.y = rand() % 4;
			thing.car.score++;
		}
	}
	return thing.car.score;
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
bool GameOver(THINGS thing)
{
	for (int i = 0; i < thing.sovatcan; i++)
	{
		if ((Distance(thing.car.toado.x, thing.vatcan[i].toado.x) < 3) && (Distance(thing.car.toado.y, thing.vatcan[i].toado.y) < 3)) return true;
	}
	return false;
}
void playGame()
{
	THINGS thing;
	thing.riatruoc = 0, thing.riasau = Width, thing.sovatcan = 5, thing.sodan = 0;
	int score, time, temp = -1;
	system("cls");
	
	//CB cac thu can thiet
	Shape(thing);
	Lane(thing.riatruoc, thing.riasau);
	Create(thing);

	//Bat dau game
	while (1)
	{
		//Dieu khien xe
		Control(thing); 
		//vecac vat vao duong dua
		Create(thing); 
		//Lam xe di chuyen muot hon
		CarDiChuyen(thing);
		Create(thing);
		//Tinh diem va ghi trong man hinh
		score = Score(thing); //Diem
		gotoxy(31, 15);
		printf("Score: %d", score); //Viet diem
		if ((score % 20 == 0)&& temp!=score && score >1 && score <101) //Tao ra them cac vat can
		{
			temp = score;
			thing.sovatcan++;
		}
		//Game over
		if (GameOver(thing))
		{
			Input(score);
			return;
		}
		//Xoa con tro chuot tren man hinh
		Nocursortype();
		//Nhip game
		time = 100 - score;
		if (time>2)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(2); 
	}
}
void controlTwoCar(THINGS &thing1, THINGS &thing2)
{
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khonog 
	{
		// Xe 1
		if ((GetAsyncKeyState(VK_LEFT)) && (thing1.car.toado.x > thing1.riatruoc + 2)) //Trai
			thing1.car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (thing1.car.toado.x < thing1.riasau - 3)) //Phai
			thing1.car.toado.x++;
		if ((GetAsyncKeyState(VK_UP)) && (thing1.car.toado.y > 1)) //Len
			thing1.car.toado.y--;
		if ((GetAsyncKeyState(VK_DOWN)) && (thing1.car.toado.y < Height - 2)) //Xuong
			thing1.car.toado.y++;
		//Xe 2
		if ((GetAsyncKeyState(VK_NUMPAD4)) && (thing2.car.toado.x > thing2.riatruoc + 2))//Trai
			thing2.car.toado.x--;
		if ((GetAsyncKeyState(VK_NUMPAD6)) && (thing2.car.toado.x < thing2.riasau - 3)) //Phai
			thing2.car.toado.x++;
		if ((GetAsyncKeyState(VK_NUMPAD8)) && (thing2.car.toado.y > 1)) //  Len
			thing2.car.toado.y--;
		if ((GetAsyncKeyState(VK_NUMPAD2)) && (thing2.car.toado.y < Height - 2)) // Xuong
			thing2.car.toado.y++;
	}
}
void playTwoCar()
{
	//Thiet lap cac thong so khac
	THINGS thing1, thing2;
	//Thing1
	thing1.sovatcan = 5;
	thing1.riatruoc = 0;
	thing1.riasau = Width;
	//Thing2
	thing2.sovatcan = 5,
	thing2.riatruoc=90;
	thing2.riasau = 120;
	int score1, score2, time, temp1 =-1, temp2 = -1;
	system("cls");

	//CB cac thu can thiet
	//PLayer 1
	Shape(thing1);
	Lane(thing1.riatruoc, thing2.riasau);
	Create(thing1);

	//Player 2
	Shape(thing2);
	Lane(thing2.riatruoc, thing2.riasau);
	Create(thing2);

	//Bat dau game
	while (1)
	{
		//Control: Lam cho cac vat di chuyen
		controlTwoCar(thing1,thing2); 
		VatCanDiChuyen(thing1);
		VatCanDiChuyen(thing2);
		CoinDiChuyen(thing1);
		CoinDiChuyen(thing2);

		//ve ra man hinh
		Create(thing1); //Player 1
		Create(thing2);//Player 2

		//Lam muot
		controlTwoCar(thing1,thing2);
		Create(thing1); //Player 1
		Create(thing2);//Player 2

		//Ai(car, vatcan, coin);
		//Diem
		score1 = Score(thing1);
		score2 = Score(thing2);//Diem
		if ((score1 % 20 == 0) && temp1 != score1 && score1 >1 && score1 <101) //Tao ra them cac vat can
		{
			temp1 = score1;
			thing1.sovatcan++;
		}
		if ((score2 % 20 == 0) && temp2 != score2 && score2 >1 && score2 <101) //Tao ra them cac vat can
		{
			temp2 = score2;
			thing2.sovatcan++;
		}
		gotoxy(31, 7);
		printf("Score 1: %d", score1); 
		gotoxy(78, 7);
		printf("Score 2: %d", score2);
		//Gameover
		if (GameOver(thing1) || GameOver(thing2))
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
		//Xoa con tro chuot
		Nocursortype();
		//Nhip game
		time = 100 - score1;

		if (time>2)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(2);
	}
}
/*void runWord(CHUCHAY &cc)
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
}*/
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
void Menu(char *menu[])
{
	int breaker = 1;
	int vitri;
	while (breaker) {
		vitri = VietMenu(menu);
		switch (vitri) {
		case 0:
		{
			if (_kbhit())
				playGame();
			break;
		}
		case 1:
		{
			playTwoCar();
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
		Sleep(500);
	}
}




