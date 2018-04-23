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
	// https://daynhauhoc.com/t/long-nhac-mp3-vao-ung-dung-console-c/34035
	//PlaySound("NguoiLaOi.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); //https://msdn.microsoft.com/en-us/library/windows/desktop/dd743680(v=vs.85).aspx
	Menu(menu);
	_getch();
}