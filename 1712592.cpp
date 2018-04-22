#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#pragma warning(disable:4996)

O buffer[30][30];

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
void drawBuffer(int dong, int cot, char kytu)
{
	buffer[dong][cot].kytu = kytu;
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
	//Toa do xe
	car.toado.x = (riasau+riatruoc)/2;
	car.toado.y = 28;
	car.score = 0;

	//Vat can
	/*	Hinh dang
						█ █
						███
						█ █
	*/
	for (i = 0; i < 10; i++)
	{
		vatcan[i].hinhdang.o[0][0] = 219; vatcan[i].hinhdang.o[0][2] = 219;
		vatcan[i].hinhdang.o[2][0] = 219; vatcan[i].hinhdang.o[2][2] = 219;
		vatcan[i].hinhdang.o[0][1] = ' '; vatcan[i].hinhdang.o[2][1] = ' ';
		vatcan[i].hinhdang.o[1][0] = 219; vatcan[i].hinhdang.o[1][2] = 219;
		vatcan[i].hinhdang.o[1][1] = 219;

		//Gan toa do vat can
		vatcan[i].toado.x = random(riatruoc,riasau);
		vatcan[i].toado.y = rand() % 4 - 6 * i;
		
		//random chieu vat can di chuyen
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
		coin[i].toado.x = random(riatruoc, riasau);
		coin[i].toado.y = rand() % Height;
	}

	//lam trang Buffer
	for (i = 0; i < 30; i++)
		for (k = 0; k < 30; k++)
			buffer[i][k].kytu = ' ';

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
void Create(CAR car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau,int sovatcan) // Ve xe vao duong dua
{
	int i, j, k;
	//ve xe vao duong dua
	for (i = -1; i < 2; i++)
		for (j = -1; j < 2; j++)
			drawBuffer(car.toado.y + i, car.toado.x + j, car.hinhdang.o[i + 1][j + 1]); //Ve xe vào buffer

	//ve tien
	for (k = 0; k < 10; k++)
		drawBuffer(coin[k].toado.y, coin[k].toado.x, '$'); // ve tien vao buffer

	//ve vat can vao duong dua
	for (k = 0; k < sovatcan; k++)
	{
		if (vatcan[k].toado.y > 0 && vatcan[k].toado.y < Height) //Nam ngoai man hinh thi ko dua vao
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					drawBuffer(vatcan[k].toado.y + i, vatcan[k].toado.x + j,vatcan[k].hinhdang.o[i + 1][j + 1]); //Ve vat can vao buffer
	}

	//ve lai lane
	Lane(riatruoc,riasau);

	//In buffer ra man hinh
	for(int i=0;i<Height;i++)
		for (int j = riatruoc; j < riasau; j++)
		{
			gotoxy(j, i);
			putchar(buffer[i][j].kytu);
			buffer[i][j].kytu = ' '; // in xoa xong huy ky tu
		}
}
void Nocursortype() // Xoa con tro chuot tren man hinh console: https://daynhauhoc.com/t/hoi-ve-con-tro-chuot-tren-man-hinh-console/34411/3
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void CarDiChuyen(CAR &car)
{
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khonog 
	{
		if ((GetAsyncKeyState(VK_LEFT)) && (car.toado.x > 2)) //Trai
			car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (car.toado.x < Width - 3)) //Phai
			car.toado.x++;
		if ((GetAsyncKeyState(VK_UP)) && (car.toado.y > 1)) //Len
			car.toado.y--;
		if ((GetAsyncKeyState(VK_DOWN)) && (car.toado.y < Height - 2)) //Xuong
			car.toado.y++;
	}
}
<<<<<<< HEAD

void VatCanDiChuyen(VATCAN vatcan[], int riatruoc, int riasau, int sovatcan)


=======
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
void VatCanDiChuyen(VATCAN vatcan[], int riatruoc, int riasau, int sovatcan)//add them di chuyen

>>>>>>> 68c2b8c809855084a4813b7a0430ec6d6a70836c
{
	int i;
	for (i = 0; i < sovatcan; i++)
	{
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
			vatcan[i].toado.x = random(riatruoc, riasau);
			vatcan[i].toado.y = rand() % 4;
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
			coin[i].toado.x = random(riatruoc, riasau);
			coin[i].toado.y = rand() % 4;
		}
	}
}
void Control(CAR &car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau, CHUCHAY &cc, int sovatcan)
{
	//Xe di chuyuen
	CarDiChuyen(car);

	//CoinDiChuyen(coin);
	CoinDiChuyen(coin, riatruoc, riasau);

	//Vat can di chuyen
	VatCanDiChuyen(vatcan, riatruoc, riasau, sovatcan);
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
			coin[i].toado.x = random(riatruoc, riasau);
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
bool GameOver(CAR car, VATCAN vatcan[], int sovatcan)
{
	for (int i = 0; i < sovatcan; i++)
	{
		if ((Distance(car.toado.x, vatcan[i].toado.x) < 3) && (Distance(car.toado.y, vatcan[i].toado.y) < 3)) return true;
	}
	return false;
}
void playGame()
{
	CAR car;
	VATCAN vatcan[10];
	COIN coin[10];
	PLAYER character;
	int riatruoc = 0, riasau = Width, sovatcan = 5, score, time, temp = -1;
	CHUCHAY cc;
	cc.toaodo.y = 0;
	system("cls");

	//CB cac thu can thiet
	Shape(car, vatcan, coin, riatruoc, riasau);
	Lane(riatruoc, riasau);
	Create(car, vatcan, coin, riatruoc, riasau,sovatcan);

	//Bat dau game
	while (1)
	{
		Create(car, vatcan, coin, riatruoc, riasau,sovatcan); //Dua xe,vc, coin vao man hinh

		Control(car, vatcan, coin, riatruoc, riasau,cc,sovatcan); //Lam cho cac vat di chuyen

		score = Score(car, coin, riatruoc, riasau); //Diem
		gotoxy(31, 15);
		printf("Score: %d", score); //Viet diem
		if ((score % 20 == 0)&& temp!=score && score >1 && score <101) //Tao ra them cac vat can
		{
			temp = score;
			sovatcan++;
		}
		if (GameOver(car, vatcan,sovatcan))
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
		Nocursortype();
		//Nhip game
		time = 150 - score;
		if (time>3)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(3);
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
void playTwoCar()
{
	CAR car1, car2;
	VATCAN vatcan1[10], vatcan2[10];
	COIN coin1[10], coin2[10];
	CHUCHAY cc;
	int sovatcan1= 5,sovatcan2 = 5;

	//Thiet lap cac thong so khac
	int score1, score2, time, riatruoc1 = 0, riasau1 = Width , riatruoc2 = 90, riasau2 = 120, temp1 =-1, temp2 = -1;
	cc.toaodo.y = 0;
	system("cls");
	//CB cac thu can thiet
	//PLayer 1
	Shape(car1, vatcan1, coin1, riatruoc1, riasau1);
	Lane(riatruoc1, riasau1);
	//Player 2
	Shape(car2, vatcan2, coin2, riatruoc2, riasau2);
	Lane(riatruoc2, riasau2);
	//Dua vao 
	Create(car1, vatcan1, coin1, riatruoc1, riasau1,sovatcan1);
	Create(car2, vatcan2, coin2, riatruoc2, riasau2,sovatcan2);

	//Bat dau game
	while (1)
	{
		//Xuat ra man hinh
		Create(car1, vatcan1, coin1, riatruoc1, riasau1,sovatcan1); //Dua xe,vc, coin vao man hinh
		Create(car2, vatcan2, coin2, riatruoc2, riasau2,sovatcan2);

		//Control
		controlTwoCar(car1, car2, riatruoc1, riasau1, riatruoc2, riasau2); //Lam cho cac vat di chuyen

		VatCanDiChuyen(vatcan1, riatruoc1, riasau1,sovatcan1);
		VatCanDiChuyen(vatcan2, riatruoc2, riasau2,sovatcan2);
		CoinDiChuyen(coin1, riatruoc1, riasau1);
		CoinDiChuyen(coin2, riatruoc2, riasau2);
		//Ai(car, vatcan, coin);
		score1 = Score(car1, coin1, riatruoc1, riasau1);
		score2 = Score(car2, coin2, riatruoc2, riasau2);//Diem
		if ((score1 % 20 == 0) && temp1 != score1 && score1 >1 && score1 <101) //Tao ra them cac vat can
		{
			temp1 = score1;
			sovatcan1++;
		}
		if ((score2 % 20 == 0) && temp2 != score2 && score2 >1 && score2 <101) //Tao ra them cac vat can
		{
			temp2 = score2;
			sovatcan2++;
		}
		gotoxy(31, 7);
		printf("Score 1: %d", score1); //Viet diem
		gotoxy(78, 7);
		printf("Score 2: %d", score2);

		/*if (GameOver(car1, vatcan1,sovatcan1) || GameOver(car2, vatcan2,sovatcan2))
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
		}*/
		Nocursortype();
		//Nhip game
		time = 100 - score1;

		if (time>3)
			Sleep(time); //Diem cang cao cang nhanh 
		else Sleep(time);
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




