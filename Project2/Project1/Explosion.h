#pragma once

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Figure.h"
#include "Symbol.h"
using namespace std;

class Explosion : public Figure {
	Symbol s;
	struct cs conSize;
public:
	bool isForDeletion();
	bool checkY(int Y, int dev, int height);
	bool checkLeftX(int X, int dev, int radius);
	bool checkRightX(int X, int dev, int radius, int width);
	bool checkTopY(int X, int radius);
	bool checkBottomY(int Y, int dev, int radius);
	void printOrMash(bool flag);
	void drawingDiamond(int radius, int X, int Y, bool flag);
	Explosion(int maxRadius, int minRadius, int x, int y);
	bool isDeleting = false;
	int X;
	int Y;
	int currentRadius;
	int explosionRadius = 0;
	int nextStepTimeExp = 0;
	int getNextStepTime() const { return nextStepTimeExp; }
	
	Figure* draw();

};

#endif
