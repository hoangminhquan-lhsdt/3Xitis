#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "1712592.h"
#include <Windows.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4996)

void main()
{
	char *menu[] = { "Play game","2 Player","Rule","BXH","Exit" };
	srand((unsigned)time(NULL));
	Menu(menu);
	_getch();
}