#pragma once
#ifndef LINE_HPP
#define LINE_HPP

#include "Symbol.h"
#include <iostream>
#include <string>
#include <cstring> 
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;
struct cs
{
	int width;
	int height;

};

class Line : public Symbol {
	struct cs conSize;

	int Y = 0;
	int N;
	int X = 0;
	int nextStepTime = 0;

	char saveSymbol;
	char saveSymbol1;
	char saveSymbol2;
	int colorChangeCounter = 0;
	int color;

public:
	struct cs getConsoleSize();
	Line();
	
	int getHeight() const { return conSize.height; }
	int getWidth() const { return conSize.width; }
	int getNextStepTime() const { return nextStepTime; }

	void setNextStepTime(int);
	void setY(int);

	void gotoXY(int x, int y);

	void currentColor(char epilepsyMode);

	Symbol s;
	Symbol s1;
	Symbol s2;

	bool bottomBorder(int Y, int height);
	bool topBorder(int Y);
	bool lengthCheck(int X, int width);

	int moveLine(int lengthLine, char epilepsyMode);

};


#endif