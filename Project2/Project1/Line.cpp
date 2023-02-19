#include "Line.h"
#include "Manager.h"

using namespace std;


	Line::Line(int length, int speed, char epilepsy, int probability, int maxRad, int minRad) {
		conSize = s.getConsoleSize();
		N = rand() % 2;
		Line::s = Symbol();
		Line::s1 = Symbol();
		Line::s2 = Symbol();
		color = rand() % 14 + 1;
		nextStepTime = clock() + rand() % 1000;
		Y = rand() % (conSize.height - 1) + 1;
		lengthLine = length;
		epilepsyMode = epilepsy;
		probabilityExplosion = probability;
		maxRadius = maxRad;
		minRadius = minRad;
		speedLine = speed;
	}

	bool Line::checkDeletion(int length, int X, int width) {
		return (length == 0 || X - length > width - 1);
	}

	bool Line::isForDeletion() {
		return isDeleting;
	}


	void Line::gotoXY(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hStdOut, coord);
	}


	void Line::currentColor(char epilepsyMode) {

		if (epilepsyMode == 'N' || epilepsyMode == 'n') {
			s.setColor(0, 2);
		}
		else {
			s.setColor(0, color);
		}

	}

	bool Line::bottomBorder(int Y, int height) {
		return Y + 1 < height;
	}
	bool Line::topBorder(int Y) {
		return Y - 1 >= 0;
	}
	bool Line::lengthCheck(int X, int width) {
		return X < width - 1 && X >= 0;
	}

	bool Line::calculationProbability(int probabilityExplosion) {
		if (rand() % 1000 + 1 <= probabilityExplosion) {
			return true;
		}
		else {
			return false;
		}
	}

	void Line::mashing() {
		if ((N + lengthLine) % 2 == 0) { //checking for erasure of a single or double character
			if (lengthCheck(X - lengthLine, conSize.width)) { //checking the last double character for a vertical limit
				if (bottomBorder(Y, conSize.height)) { //checking for going beyond the right border
					gotoXY(X - lengthLine, Y + 1);
					printf("%c", ' ');
				}
				if (topBorder(Y)) { //checking for going beyond the left border
					gotoXY(X - lengthLine, Y - 1);
					printf("%c", ' ');
				}
			}
		}
		else {
			if (lengthCheck(X - lengthLine, conSize.width)) { //checking the last single character for a vertical limit
				gotoXY(X - lengthLine, Y);
				printf("%c", ' ');
			}
		}
	}

	Figure* Line::draw() {
		

		if (checkDeletion(lengthLine, X, conSize.width)) {
			isDeleting = TRUE;
			return NULL;
		}

		if (N % 2 == 0) { //checking for the first output of a single or double character

			if (lengthCheck(X, conSize.width)) { //checking a double character for a vertical limit
				saveSymbol1 = s1.print();
				saveSymbol2 = s2.print();
				s.setColor(0, 15);
				if (bottomBorder(Y, conSize.height)) { //checking for going beyond the right border
					gotoXY(X, Y + 1);
					printf("%c", saveSymbol1);
				}
				if (topBorder(Y)) { //checking for going beyond the left border
					gotoXY(X, Y - 1);
					printf("%c", saveSymbol2);
				}
			}

			if (lengthCheck(X - 1, conSize.width)) { //checking the previous single character for a vertical limit
				//changing the color of a single character
				gotoXY(X - 1, Y);
				currentColor(epilepsyMode);
				printf("%c", saveSymbol);
			}
		}
		else {
			saveSymbol = s.print();
			if (lengthCheck(X, conSize.width)) { //checking a single character for a vertical limit
				gotoXY(X, Y);
				s.setColor(0, 15);
				printf("%c", saveSymbol);
			}
			if (lengthCheck(X - 1, conSize.width)) { //checking the previous double character for a vertical limit
				currentColor(epilepsyMode);
				if (bottomBorder(Y, conSize.height)) { //checking for going beyond the right border
					gotoXY(X - 1, Y + 1);
					printf("%c", saveSymbol1);
				}
				if (topBorder(Y)) { //checking for going beyond the left border
					gotoXY(X - 1, Y - 1);
					printf("%c", saveSymbol2);
				}
			}


		}
		
		mashing();
		X++;
		N++;
		nextStepTime += 1000 / speedLine;

		if ((calculationProbability(probabilityExplosion) == true) && (X < conSize.width - 1)) {
			Figure* e = new Explosion(maxRadius, minRadius, X, Y);
			mashing();
			lengthLine = lengthLine - 1;
			return e;
		}

		return NULL;
	}
