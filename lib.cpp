#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "lib.h"
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void tao(char *&a)
{
	a = new char[9];
	int i;
	for (i = 0; i < 9; i++)
	{
		*(a + i) = '0';
	}
	
}
void in(char *a,int x,int y)
{
	system("cls");
	int i;
	gotoxy(x, y);
	for (i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
		{
			y++;
			putchar('\n');
			gotoxy(x, y); 
		}
		putchar(*(a + i));
	}
	Sleep(100);
}
void dichuyen(int x, int y,char *a)
{
	int i=0, j=0;
	while (i != x)
	{
		in(a, i, j);
		i++;
		if(j!=y)j++;
		if (i == x)
			while (i != 0)
			{
				in(a, i, j);
				i--;
				if(j!=y)j++;
			}
	}
}
