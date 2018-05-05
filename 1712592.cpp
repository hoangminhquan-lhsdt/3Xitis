#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <mmsystem.h>
#pragma warning(disable:4996)

O buffer[30][30]; // khai báo để sử dụng toàn bài

//File
void Input(int score)
{
	system("cls");
	FILE *f = fopen("Player.txt", "a");
	PLAYER player;
	char c;
	gotoxy(0, 14);
	printf("Diem: %d\n",score);
	gotoxy(0, 15);
	printf("Nhap ten: ");
	scanf(" %[^\n]s &c", player.Name, &c);
	fprintf(f, "%s\n", player.Name);
	fprintf(f, "	%d\n", score);
	fclose(f);
	c = getch();
}
void sortBXH(PLAYER arr[], int n) {
	//Sắp xếp điểm
	PLAYER temp;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (arr[i].score > arr[j].score) {
				strcpy(temp.Name,arr[i].Name);
				temp.score = arr[i].score;
				strcpy(arr[i].Name, arr[j].Name);
				arr[i].score = arr[j].score;
				strcpy(arr[j].Name, temp.Name);
				arr[j].score = temp.score;
			}
	//In những người có điểm cao nhất
	int length;
	gotoxy(47,8);
	printf("HIGHEST SCORE\n");
	for (int i = 0; i < TOPPLAYER; i++) {
		if (!strcmp(arr[i].Name, "\n"))						// 
			break;											//
		length = strlen(arr[i].Name) - 1;					//
		if ((length > 0) && (arr[i].Name[length] == '\n'))	//
			arr[i].Name[length] = '\0';	// https://stackoverflow.com/questions/25615916/removing-newline-from-fgets
		gotoxy(42, 10+i);
		printf("%d.", i+1);
		gotoxy(45, 10+i);
		printf("%s", arr[i].Name);
		gotoxy(65, 10+i);
		printf("%d.\n", arr[i].score);
	}
}
void BXH() {
	//char c;
	int length;
	system("cls");
	PLAYER list[1000];
	int i = 0;
	FILE *f = fopen("Player.txt", "r");
	while (!feof(f)) {
		fgets(list[i].Name, 30, f);
		fscanf(f, "%d\n", &list[i].score);
		i++;
	}
	fclose(f);
	sortBXH(list, i);
	_getch();
}
//Các hàm tham khảo
void gotoxy(int x, int y) //Đưa con trỏ tới vị trí (x,y) trên màn hình console: https://daynhauhoc.com/t/xin-giai-thich-ve-ham-gotoxy/13723
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void drawBuffer(int dong, int cot, char kytu) // Giam giat cho man hinh console, link: https://www.youtube.com/watch?v=hsvzJlxG2LY
{
	buffer[dong][cot].kytu = kytu;
}
void Nocursortype() // Xóa con trỏ chuột trên màn hình console: https://daynhauhoc.com/t/hoi-ve-con-tro-chuot-tren-man-hinh-console/34411/3
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//Các hàm tính toán
inline int Random(int a, int b) // random trong đoạn [a,b]
{
	return rand() % (b - a - 1) + a;
}
inline int Distance(int x, int y) //Khoảng cách giữa các vật theo phương Ox hoặc Oy
{
	return abs(x - y);
}
//Các hàm trong game
void Shape(THINGS &thing) //Tạo hình dạng các vật: xe, vật cản, tiền, đạn.

{
	int i, k;
	// Xe
	/*	Hình dạng
						O-O
						|M|
						O-O
	*/
	thing.car.hinhdang.o[0][0] = 'O'; thing.car.hinhdang.o[0][2] = 'O'; //Bánh trước
	thing.car.hinhdang.o[2][0] = 'O'; thing.car.hinhdang.o[2][2] = 'O'; //Bánh sau
	thing.car.hinhdang.o[0][1] = '-'; thing.car.hinhdang.o[2][1] = '-'; // Thân trước và thân sau
	thing.car.hinhdang.o[1][0] = '|'; thing.car.hinhdang.o[1][2] = '|'; // Thân bên hông trái và phải
	thing.car.hinhdang.o[1][1] = 'M'; //Trung tâm xe
	//Tọa độ xe và điểm người chơi
	thing.car.toado.x = (thing.riasau+ thing.riatruoc)/2; // Cho xe ở giữa đường đua
	thing.car.toado.y = 28; // xe nằm ở cuối đường đua
	thing.car.score = 0; // Điểm

	//Vật cản
	/*	Hình dạng
						█ █
						███
						█ █
	*/
	for (i = 0; i < MAXVATCAN; i++) // MAXVATCAN == 10
	{
		thing.vatcan[i].hinhdang.o[0][0] = 219; thing.vatcan[i].hinhdang.o[0][2] = 219;
		thing.vatcan[i].hinhdang.o[2][0] = 219; thing.vatcan[i].hinhdang.o[2][2] = 219;
		thing.vatcan[i].hinhdang.o[0][1] = ' '; thing.vatcan[i].hinhdang.o[2][1] = ' ';
		thing.vatcan[i].hinhdang.o[1][0] = 219; thing.vatcan[i].hinhdang.o[1][2] = 219;
		thing.vatcan[i].hinhdang.o[1][1] = 219;

		//Gán tọa độ vật cản
		thing.vatcan[i].toado.x = Random(thing.riatruoc, thing.riasau); //Chú thích ở hàm random
		thing.vatcan[i].toado.y = rand() % 4 - 6 * i; // Làm các vật cản không bị dính vào nhau qua việc -6*i
		
		//random chiều vật cản sẽ đi: trái hoặc phải
		k = rand() % 2;
		if (k == 0)
			thing.vatcan[i].trangthai = LEFT;
		else
			thing.vatcan[i].trangthai = RIGHT;

		//Biên của vật cản: tới đó vật cản sẽ đổi chiều chuyển động
		thing.vatcan[i].bientrai.x = thing.vatcan[i].toado.x - 1;
		thing.vatcan[i].bienphai.x = thing.vatcan[i].toado.x + 1;
	}

	//Coin: $
	for (i = 0; i < MAXCOIN; i++)
	{
		thing.coin[i].toado.x = Random(thing.riatruoc, thing.riasau); // chú thích ở hàm random
		thing.coin[i].toado.y = rand() % Height; // cho tiền xuất hiện toàn màn hình
	}

	//Bullet: l
	for (i = 0; i < MAXBULLET; i++)
		thing.bullet[i].bullet = 'l';
}
void Lane(int riatruoc, int riasau) //Tạo đường đua (lane)
{
	/* Hình dạng lane
			|	|
			|	|
	*/
	// vẽ lane vào buffer
	for (int i = 0; i < Height; i++)
	{
		drawBuffer(i, riatruoc, '|');
		drawBuffer(i, riasau - 1, '|');
	}
}
void Create(THINGS thing) // Vẽ các vật: xe, vật cản, tiền, đạn.
{
	int i, j, k;
	//Vẽ xe vào buffer
	for (i = -1; i < 2; i++)
		for (j = -1; j < 2; j++)
			drawBuffer(thing.car.toado.y + i, thing.car.toado.x + j, thing.car.hinhdang.o[i + 1][j + 1]); //Ve xe vào buffer

	//Vẽ tiền vào buffer
	for (k = 0; k < MAXCOIN; k++)
		drawBuffer(thing.coin[k].toado.y, thing.coin[k].toado.x, '$'); // ve tien vao buffer

	//Vẽ vật cản vào buffer
	for (k = 0; k < thing.sovatcan; k++)
	{
		if (thing.vatcan[k].toado.y > 0 && thing.vatcan[k].toado.y < Height) //Nam ngoai man hinh thi ko dua vao
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					drawBuffer(thing.vatcan[k].toado.y + i, thing.vatcan[k].toado.x + j, thing.vatcan[k].hinhdang.o[i + 1][j + 1]); //Ve vat can vao buffer
	}

	//Vẽ đạn vào buffer
	for (i = 0; i < thing.sodan; i++)
	{
		drawBuffer(thing.bullet[i].toado.y, thing.bullet[i].toado.x, thing.bullet[i].bullet);
	}

	//Vẽ lại lane vào buffer
	Lane(thing.riatruoc, thing.riasau);

	//In buffer ra màn hình
	for(i=0;i<Height;i++)
		for (j = thing.riatruoc; j < thing.riasau; j++)
		{
			gotoxy(j, i);
			putchar(buffer[i][j].kytu);
			buffer[i][j].kytu = ' '; // sau khi in xong, trả về ký tự ' ' tại vị trí vừa in (xóa dấu tích)
		}
	
}
void CarDiChuyen(CAR &car) // Điều khiển xe
{
	if (_kbhit()) //Kiểm tra có phím nào được nhấn không
	{
		if ((GetAsyncKeyState(VK_LEFT)) && (car.toado.x > 2)) // Trái
			car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (car.toado.x < Width - 3)) //Phải
			car.toado.x++;
		if ((GetAsyncKeyState(VK_UP)) && (car.toado.y > 1)) //Lên 
			car.toado.y--;
		if ((GetAsyncKeyState(VK_DOWN)) && (car.toado.y < Height - 2)) //Xuống
			car.toado.y++;
	}
}
void moveVatCan(THINGS &thing) // Vật cản đứng yên
{
	for (int i = 0; i < thing.sovatcan; i++)
	{
		thing.vatcan[i].toado.y++; // vật cản đi xuống
		if (thing.vatcan[i].toado.y > Height) //Vật cản ra khỏi đường đua, tạo vật cản mới
		{
			thing.car.score++; // tăng điểm cho người chơi
							   //Tạo vật cản mới
			thing.vatcan[i].toado.x = Random(thing.riatruoc, thing.riasau);
			thing.vatcan[i].toado.y = rand() % 2;
		}
	}
}
void VatCanDiChuyen(THINGS &thing)// Vật cản di chuyển
{
	for (int i = 0; i < thing.sovatcan; i++)
	{
		//ĐỔI HƯỚNG DI CHUYỂN CỦA VẬT CẢN
		//Đụng biên đường đua
		if (thing.vatcan[i].toado.x == thing.riatruoc + 2)
			thing.vatcan[i].trangthai = RIGHT;
		if (thing.vatcan[i].toado.x == thing.riasau - 3)
			thing.vatcan[i].trangthai = LEFT;
		//Đụng biên trái và phải của vật cản
		if (thing.vatcan[i].toado.x == thing.vatcan[i].bientrai.x)
			thing.vatcan[i].trangthai = RIGHT;
		if (thing.vatcan[i].toado.x == thing.vatcan[i].bienphai.x)
			thing.vatcan[i].trangthai = LEFT;

		//DI CHUYỂN SANG TRÁI HOẶC PHẢI
		if (thing.vatcan[i].trangthai == LEFT)
			thing.vatcan[i].toado.x--;
		if (thing.vatcan[i].trangthai == RIGHT)
			thing.vatcan[i].toado.x++;

		//ĐI XUỐNG
		thing.vatcan[i].toado.y++;
		if (thing.vatcan[i].toado.y > Height) //Vat can ra khoi man hinh, tao vat can moi
		{
			thing.car.score++;
			thing.vatcan[i].toado.x = Random(thing.riatruoc, thing.riasau); // chú thích ở hàm random
			thing.vatcan[i].toado.y = rand() % 4;
		}

	}

}
void CoinDiChuyen(THINGS &thing) // coin di chuyển
{
	for (int i = 0; i < MAXCOIN; i++)
	{
		thing.coin[i].toado.y++;
		if (thing.coin[i].toado.y > Height) //Coin ra khỏi màn hình, tọa coin mới
		{
			thing.coin[i].toado.x = Random(thing.riatruoc, thing.riasau); // chú thích ở hàm random
			thing.coin[i].toado.y = rand() % 4;
		}
	}
}
void ControlBullet(THINGS &thing) // Điều khiển đạn
{
	if (GetAsyncKeyState(VK_SPACE) && thing.sodan < MAXBULLET)// tạo đạn
	{
		//Gán tọa độ vị trí xuất phát của đạn (2 viên): xuất phát ở 2 bánh trước
		//Viên 1
		thing.bullet[thing.sodan].toado.x = thing.car.toado.x - 1; 
		thing.bullet[thing.sodan].toado.y = thing.car.toado.y - 2;
		//Viên 2			
		thing.bullet[thing.sodan + 1].toado.x = thing.car.toado.x + 1;
		thing.bullet[thing.sodan + 1].toado.y = thing.car.toado.y - 2;
		thing.sodan+=2; // tăng số đạn
	}
	for (int j = 0; j < thing.sodan; j++)
	{
		if (thing.bullet[j].toado.y >= 0 ) // Kiểm tra đạn còn trong khu vực di chuyển không
			thing.bullet[j].toado.y -= 2; 
	}
	if (thing.bullet[0].toado.y <= 0 && thing.bullet[2].toado.y <= 0 && thing.bullet[4].toado.y <= 0 ) // chưa cmt
		if (thing.sodan >= 5)
			thing.sodan = 0;
}
void bulletvatcan(THINGS &thing) // Đạn, vật cản ,và tiền
{
	int i, j, k;
	for (i = 0; i < thing.sodan; i++)
	{
		//Đạn trúng tiền: ăn tiền, tạo tiền mới
		for (j = 0; j < MAXCOIN; j++)
			if (Distance(thing.bullet[i].toado.x, thing.coin[j].toado.x) == 0 && Distance(thing.bullet[i].toado.y, thing.coin[j].toado.y) == 0)
			{
				//Tạo tiền mới
				thing.coin[j].toado.x = Random(thing.riatruoc, thing.riasau); // chú thích ở hàm random
				thing.coin[j].toado.y = rand() % 4;
				// tăng điểm cho người chơi
				thing.car.score++; 
			}
		//Đạn trúng vật cản: đầy lùi vật cản về sau
		for (k = 0; k < thing.sovatcan; k++)
			if (Distance(thing.bullet[i].toado.x, thing.vatcan[k].toado.x) < 2 && Distance(thing.bullet[i].toado.y, thing.vatcan[k].toado.y) < 2)
				thing.vatcan[k].toado.y -= 2; // lùi 6 bước
	}
}
void Control(THINGS &thing) // Điều khiển
{
	//Xe
	CarDiChuyen(thing.car);

	//Đạn
	ControlBullet(thing);
	bulletvatcan(thing);

	//Coin
	CoinDiChuyen(thing);

	//Vật cản và vật cản di chuyển
	if (thing.car.score < 30)
		moveVatCan(thing);
	else VatCanDiChuyen(thing);
}
int Score(THINGS &thing) // Điểm
{
	for (int i = 0; i < MAXCOIN; i++)
	{
		if (Distance(thing.car.toado.x, thing.coin[i].toado.x) < 2 && Distance(thing.car.toado.y, thing.coin[i].toado.y) < 2)
		{
			thing.coin[i].toado.x = Random(thing.riatruoc, thing.riasau); // chú thích ở hàm random
			thing.coin[i].toado.y = rand() % 4;
			thing.car.score++; // tăng điểm
		}
	}
	return thing.car.score;
}
void Ai(THINGS &thing) // chua tinh truong hop car.toado.x == 2 vay no sang left 1 cai thi dung cmn
{
	//Chi an coin[0] thoi
	if (thing.car.toado.x < thing.coin[0].toado.x)
		thing.car.toado.x++;
	if (thing.car.toado.x > thing.coin[0].toado.x)
		thing.car.toado.x--;
	for (int i = 0; i < thing.sovatcan; i++)
	{
		if (thing.vatcan[i].toado.x + 1 == thing.car.toado.x - 1)
		{
			thing.car.toado.x++;
			//return;
		}
		if (thing.vatcan[i].toado.x - 1 == thing.car.toado.x + 1)
		{
			thing.car.toado.x--;
			//return;
		}
		if (thing.car.toado.x == thing.vatcan[i].toado.x - 1)
		{
			thing.car.toado.x = thing.car.toado.x--;
			//return;
		}
		if (thing.car.toado.x == thing.vatcan[i].toado.x + 1)
		{
			thing.car.toado.x = thing.car.toado.x++;
			//return;
		}
		if (thing.car.toado.x == thing.vatcan[i].toado.x)
		{
			thing.car.toado.x = thing.car.toado.x++;
			//return;
		}
	}
}
bool GameOver(THINGS thing) // Đụng vật cản
{
	for (int i = 0; i < thing.sovatcan; i++)
		if ((Distance(thing.car.toado.x, thing.vatcan[i].toado.x) < 3) && (Distance(thing.car.toado.y, thing.vatcan[i].toado.y) < 3)) 
			return true;
	return false;
}
void playGame() // Dành cho 1 người chơi (Solo)
{
	//CB cac thu can thiet
	THINGS thing;
	thing.riatruoc = 0, thing.riasau = Width, thing.sovatcan = 5, thing.sodan = 0;
	int score, time, temp = -1;
	system("cls");
	Shape(thing);
	Lane(thing.riatruoc, thing.riasau);
	Create(thing);

	//Bat dau game
	while (1)
	{
		//Các vật di chuyển: xe, vật cản, tiền, đạn.
		Control(thing); 

		//Vẽ các vật ra màn hình
		Create(thing); 

		//Làm xe di chuyển mượt hơn
		CarDiChuyen(thing.car);
		Create(thing); // vẽ lại

		//Tính điểm và ghi điểm ra màn hình
		score = Score(thing); //Điểm
		gotoxy(31, 15);
		printf("Score: %d", score); //Viết điểm
		if ((score % 20 == 0)&& temp!=score && score >1 && score <101) //Tăng dần các vật cản
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
		else Sleep(2);  // Tối đa nhịp game là: 2 ms
	}
	
}
void controlTwoCar(THINGS &thing1, THINGS &thing2)// Điều khiển 2 xe
{
	if (_kbhit()) //kiem tra xem co phim nao dc nhan khonog 
	{
		// Xe 1
		if ((GetAsyncKeyState(VK_LEFT)) && (thing1.car.toado.x > thing1.riatruoc + 2)) //Trái
			thing1.car.toado.x--;
		if ((GetAsyncKeyState(VK_RIGHT)) && (thing1.car.toado.x < thing1.riasau - 3)) //Phải
			thing1.car.toado.x++;
		if ((GetAsyncKeyState(VK_UP)) && (thing1.car.toado.y > 1)) //Lên
			thing1.car.toado.y--;
		if ((GetAsyncKeyState(VK_DOWN)) && (thing1.car.toado.y < Height - 2)) //Xuống
			thing1.car.toado.y++;
		//Xe 2: bằng các phím: 2,4,6,8: tương đương Xuống, trái, phải, lên
		if ((GetAsyncKeyState(VK_NUMPAD4)) && (thing2.car.toado.x > thing2.riatruoc + 2))//Trái
			thing2.car.toado.x--;
		if ((GetAsyncKeyState(VK_NUMPAD6)) && (thing2.car.toado.x < thing2.riasau - 3)) //Phải
			thing2.car.toado.x++;
		if ((GetAsyncKeyState(VK_NUMPAD8)) && (thing2.car.toado.y > 1)) //Lên
			thing2.car.toado.y--;
		if ((GetAsyncKeyState(VK_NUMPAD2)) && (thing2.car.toado.y < Height - 2)) //Xuống
			thing2.car.toado.y++;
	}
}
void control2Player(THINGS &thing1, THINGS &thing2) // Điều khiển các vật
{
	// Xe
	controlTwoCar(thing1, thing2);

	//Coin
	CoinDiChuyen(thing1);
	CoinDiChuyen(thing2);

	//Vật cản
	if (thing1.car.score < 30)
		moveVatCan(thing1);
	else VatCanDiChuyen(thing1);

	if (thing2.car.score < 30)
		moveVatCan(thing2);
	else VatCanDiChuyen(thing2);
}
void playTwoCar()//Hàm dưới cho 2 người chơi: Mục đích : ăn nhiều điểm hơn đối phương trong cùng 1 khoảng thời gian. Không bắn được
{
	//Thiet lap cac thong so khac
	THINGS thing1, thing2;
	//Thing1: người chơi 1
	thing1.sovatcan = 5;
	thing1.riatruoc = 0;
	thing1.riasau = Width;
	//Thing2: người chơi 2
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

	//Bắt đầu game
	while (1)
	{
		//Control: Làm các vật di chuyển
		control2Player(thing1, thing2);

		//Vẽ các vật ra màn hình
		Create(thing1); //Player 1
		Create(thing2);//Player 2

		//Làm mượt
		controlTwoCar(thing1,thing2);
		Create(thing1); //Player 1
		Create(thing2);//Player 2

		//Điểm
		score1 = Score(thing1);
		score2 = Score(thing2);//Diem
		if ((score1 % 20 == 0) && temp1 != score1 && score1 >1 && score1 <101) //Tăng vật cản
		{
			temp1 = score1;
			thing1.sovatcan++;
		}
		if ((score2 % 20 == 0) && temp2 != score2 && score2 >1 && score2 <101) //Tăng vật cản
		{
			temp2 = score2;
			thing2.sovatcan++;
		}
		//Ghi điểm
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
//Menu
void Rule() // Luật chơi
{
	gotoxy(40, 7);
	printf("Dieu khien xe tranh vat can\n");
	gotoxy(40, 9);
	printf("Nhan phim RIGHT de qua phai\n");
	gotoxy(40, 11);
	printf("Nhan phin LEFT de qua trai");
	gotoxy(40, 13);
	printf("Nhan phim UP de di len\n");
	gotoxy(40, 15);
	printf("Nhan phim DOWN de di xong\n");
	gotoxy(40, 17);
	printf("Nhan SPACE de ban\n");
}
int VietMenu(char *menu[]) // Viết menu
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
		if (GetAsyncKeyState(VK_RETURN)) return vitri;// Nhớ vị trí
		Sleep(100);
	}

}
void Menu(char *menu[]) // Menu
{
	int breaker = 1;
	int vitri;
	while (breaker) {
		vitri = VietMenu(menu); // nhớ chọn mục nào
		switch (vitri) {
		case 0:
		{
			playGame();
			break;
		}
		case 1:
		{
			playTwoCar();
			break;
		}
		case 2:
		{
			system("cls");
			Rule();
			system("pause");
			break;
		}
		case 3: //BXH
		{
			system("cls");
			BXH();
			system("pause");
			break;
		}
		case 4: breaker = 0; return;
		}
		vitri = VietMenu(menu); // nhớ chọn mục nào, không bị trường hợp auto vào khi thoat ra 
		Sleep(500);
	}
}




