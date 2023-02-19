#include <iostream>
#include <string>
#include <cstring> 
#include <stdio.h>
#include <Windows.h>
#include "Manager.h"
#include "Line.h"


using namespace std;
void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Manager m = Manager();
	hideCursor();
	m.startWorking();
	system("pause");
	return 0;
}