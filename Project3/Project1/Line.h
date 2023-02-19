#pragma once
#ifndef LINE_HPP
#define LINE_HPP 

#include "Symbol.h"
#include "Figure.h"
#include "Manager.h"
#include <iostream>
#include <string>
#include <cstring> 
#include <stdio.h>
#include <Windows.h>
#include <cstdlib> 
#include <time.h>
using namespace std;


class Line : public Figure {
	struct cs conSize;
	int X = 0;
	int Y = 0;
	int N;
	int nextStepTime = 0;
	char saveSymbol = ' ';
	char saveSymbol1 = ' ';
	char saveSymbol2 = ' ';
	int color;
	int lengthLine = 0;
	///////////////////////////////////////
	char epilepsyMode = ' ';
	int probabilityExplosion = 0;
	int maxRadius = 0;
	int minRadius = 0;
	int speedLine = 0;
	bool isDeleting = false;
	///////////////////////////////////////
public:
	bool isForDelition();
	Line(int length, int speed, char epilepsy, int probability, int maxRad, int minRad);
	int getNextStepTime() const { return nextStepTime; }
	void mashing();
	void gotoXY(int x, int y);
	void currentColor(char epilepsyMode);

	Symbol s;
	Symbol s1;
	Symbol s2;

	bool bottomBorder(int X, int width);
	bool topBorder(int X);
	bool lengthCheck(int y, int height);
	bool calculationProbability(int probabilityExplosion);
	Figure* draw();

};


#endif
