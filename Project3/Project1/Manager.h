#pragma once

#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "Vector.h"
#include <vector>
#include <ctime>
#include <algorithm> 
#include "Explosion.h"
#include "Line.h"

using namespace std;
class Manager {
	struct cs conSize;
	int frequencyLines = 0;
	int speedLine = 0;
	int lengthLine = 0;
	char epilepsyMode = ' ';
	int maxRadius = 0;
	int minRadius = 0;
	int probabilityExplosion = 0;
	Symbol s = Symbol();
public:
	Vector <Figure*> Varr;
	Manager();
	bool printParam();
	
	void enteringParam(string text, int& val);
	void enteringParam(string text, char& val);
	void enteringParamExp(string text, int& val);
	void enteringParamExpProb(string text, int& val);
	void comparisonRad(int maxRadius, int minRadius);
	void startWorking();
	void linesOutput();

	
};

#endif
