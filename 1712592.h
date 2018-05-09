#include <stdio.h>

#define Height 30 // Chiều cao đường đua
#define Width 30 // Chiều rộng đường đua
#define MAXMENU 5 //Danh sach max cua Menu
#define MAXVATCAN 10 
#define MAXCOIN 10
#define MAXBULLET 6 
#define TOPPLAYER 10 // 10 người chơi cao điểm nhất

//Màu
#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


enum TRANGTHAI  { UP,DOWN,LEFT,RIGHT}; // Liệt kê trạng thái gồm có các thành phần UP, DOWN, LEFT, RIGHT

struct PLAYER // Thông tin người chơi: họ tên, điểm ghi được
{
	char Name[30] = {'a'};
	int score;
};
struct TOADO // tọa độ của 1 điểm
{
	int x, y; //x: hoanh do, y: tung do
};
struct SHAPE // hình mảng của các vật
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
	TOADO toado, bientrai, bienphai;
	TRANGTHAI trangthai;
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
struct O
{
	char kytu;
	int mau;
};
//File, sắp xếp
void Input(int score);
void sortBXH(PLAYER arr[], int n);
void BXH();
void readRacingCar();
//Các hàm tham khảo
void gotoxy(int x, int y);
void drawBuffer(int dong, int cot, char kytu, int mau = 7);
void Nocursortype();
void textColor(int color);
// các hàm tính toán
inline int Random(int a, int b);
inline int Distance(int x, int y);
//Hàm trong game
void Shape(THINGS &thing);
void Lane(int riatruoc, int riasau);
void Create(THINGS thing);
void CarDiChuyen(CAR &car);
void moveVatCan(THINGS &thing);
void VatCanDiChuyen(THINGS &thing);
void CoinDiChuyen(THINGS &thing);
void ControlBullet(THINGS &thing);
void bulletvatcan(THINGS &thing);
void Control(THINGS &thing);
int Score(THINGS &thing);
void Ai(THINGS &thing);
bool GameOver(THINGS thing);
void playGame();
void controlTwoCar(THINGS &thing1, THINGS &thing2);
void control2Player(THINGS &thing1, THINGS &thing2);
void playTwoCar();
//Menu
void Rule();
int VietMenu(char *menu[]);
void Menu(char *menu[]);





