#include <stdio.h>

#define Height 30
#define Width 30
#define MAXMENU 4 //Danh sach max cua Menu
//test
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
void BXH();
void Input(PLAYER player, char filename[], int score);
void gotoxy(int x, int y);
void Shape(CAR &car, VATCAN vatcan[], COIN coin[]);
void Lane(); 
void Create(CAR car, VATCAN vatcan[], COIN coin[]);
void VatCanDiChuyen(VATCAN vatcan[]);
void CoinDiChuyen(COIN coin[]);
void CarDiChuyen(CAR &car);
void Control(CAR &car, VATCAN vatcan[], COIN coin[]);
bool GameOver(CAR car, VATCAN vatcan[]);
int Score(CAR &car, COIN coin[]);
int Distance(int x, int y);
void Input(PLAYER character, char filename[], int score);
void Ai(CAR &car, VATCAN vatcan[], COIN coin[]);
void playGame(CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file);
void Rule();
void Menu(char *menu[], CAR &car, VATCAN vatcan[], COIN coin[], PLAYER &character, FILE *file);
void runWord();
