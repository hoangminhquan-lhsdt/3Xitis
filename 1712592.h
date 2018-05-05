#include <stdio.h>

#define Height 30
#define Width 30
#define MAXMENU 5 //Danh sach max cua Menu
#define MAXVATCAN 10
#define MAXCOIN 10
#define MAXBULLET 6
#define TOPPLAYER 10

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
struct SHAPE // hình mạng của các vật
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
struct O
{
	char kytu;
};

//File, sắp xếp
void Input(int score);
void sortBXH(PLAYER arr[], int n);
void BXH();
//Các hàm tham khảo
void gotoxy(int x, int y);
void drawBuffer(int dong, int cot, char kytu);
void Nocursortype();
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





