#include <stdio.h>

#define Height 30
#define Width 30
#define MAXMENU 5 //Danh sach max cua Menu

enum TRANGTHAI  { UP,DOWN};

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
	TOADO toado;
};
struct COIN
{
	TOADO toado;
};
struct CHUCHAY
{
	char str[8] = { "Playing" };
	TOADO toaodo;
	TRANGTHAI trangthai;
};
void BXH(FILE *f);
void Input(PLAYER player, char filename[], int score);
void gotoxy(int x, int y);
void Shape(CAR &car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau);
void Lane(int riatruoc, int riasau);
void Create(CAR car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau, int sovatcan);
void VatCanDiChuyen(VATCAN vatcan[], int riatruoc, int riasau, int sovatcan);
void CoinDiChuyen(COIN coin[], int riatruoc, int riasau);
void CarDiChuyen(CAR &car);
void Control(CAR &car, VATCAN vatcan[], COIN coin[], int riatruoc, int riasau, CHUCHAY &cc, int sovatcan);
bool GameOver(CAR car, VATCAN vatcan[]);
int Score(CAR &car, COIN coin[], int riatruoc, int riasau);
int Distance(int x, int y);
void Input(PLAYER character, char filename[], int score);
void Ai(CAR &car, VATCAN vatcan[], COIN coin[]);
void playGame(CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file, int riatruoc, int riasau, CHUCHAY &cc, int &sovatcan);
void controlTwoCar(CAR &car, CAR &car2, int riatruoc1, int riasau1, int riatruoc2, int riasau2);
void playTwoCar(CAR &car1, VATCAN vatcan1[], COIN coin1[], CAR &car2, VATCAN vatcan2[], COIN coin2[], CHUCHAY &cc, int sovatcan);
void Rule();
void Menu(char *menu[], CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file, CAR &car2, VATCAN vatcan2[], COIN coin2[], CHUCHAY &cc, int sovatcan);
void runWord(CHUCHAY &cc);
