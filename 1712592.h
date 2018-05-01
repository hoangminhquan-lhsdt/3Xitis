#include <stdio.h>

#define Height 30
#define Width 30
#define MAXMENU 5 //Danh sach max cua Menu

enum TRANGTHAI  { UP,DOWN,LEFT,RIGHT}; 
struct PLAYER
{
	char Name[30] = {'a'};
	int score;
};
struct TOADO
{
	int x, y; //x: hoanh do, y: tung do
};
struct SHAPE
{
	char o[3][3];
};
struct CAR
{
	SHAPE hinhdang;
	TOADO toado;
	int score;
};
struct VATCAN
{
	SHAPE hinhdang;
	TOADO toado, trai, phai;
	TRANGTHAI trangthai;
	int sovatcan;
};
struct COIN
{
	TOADO toado;
};
struct BULLET
{
	char bullet;
	TOADO toado;
	TRANGTHAI trangthai;
};
struct THINGS
{
	BULLET bullet[10];
	CAR car;
	VATCAN vatcan[10];
	COIN coin[10];
	int sovatcan, riatruoc, riasau,sodan;
};
struct CHUCHAY
{
	char str[8] = { "Playing" };
	TOADO toaodo;
	TRANGTHAI trangthai;
};
struct O
{
	char kytu;
};
void ControlBullet(THINGS &thing);//
void bulletvatcan(THINGS &thing);//
void BXH();
void Input(int score);
void gotoxy(int x, int y);
void Shape(THINGS &thing);
void Lane(int riatruoc, int riasau);
void Create(THINGS thing);
void moveVatCan(THINGS &thing);
void VatCanDiChuyen(THINGS &thing);
void CoinDiChuyen(THINGS &thing);
void CarDiChuyen(CAR &car);
void Control(THINGS &thing);
bool GameOver(THINGS thing);
int Score(THINGS &thing);
int Distance(int x, int y);
void Ai(THINGS &thing);
void playGame();
void controlTwoCar(THINGS &thing1, THINGS &thing2);
void control2Player(THINGS &thing1, THINGS &thing2);
void playTwoCar();
void Rule();
void Menu(char *menu[]);
void drawBuffer(int dong, int cot, char kytu);
void Nocursortype();
inline int random(int a, int b);