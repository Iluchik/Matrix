
#include "Line.h"

using namespace std;

	void Line::setNextStepTime(int time) {
		nextStepTime = time;
	}
	void Line::setY(int y) {
		Y = y;
	}

	struct cs Line::getConsoleSize()
	{
		struct cs tmp;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		tmp.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		tmp.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return tmp;
	}
	Line::Line() {
		conSize = getConsoleSize();
		N = rand() % 2;
		Line::s = Symbol();
		Line::s1 = Symbol();
		Line::s2 = Symbol();
		color = rand() % 14 + 1;
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
			setColor(0, 2);
		}
		else {
			setColor(0, color);
		}

	}

	bool Line::bottomBorder(int Y, int height){
		return Y + 1 < height;
	}
	bool Line::topBorder(int Y) {
		return Y - 1 >= 0;
	}
	bool Line::lengthCheck(int X, int width) {
		return X < width-1 && X >= 0;
	}

	int Line::moveLine(int lengthLine, char epilepsyMode) {

		if (colorChangeCounter > lengthLine) { 
			colorChangeCounter = 0;
			color = rand() % 14 + 1;
		}

		if (X - lengthLine > getWidth() - 1) {
			return 1;
		}

		if (N % 2 == 0) { //checking for the first output of a single or double character
			
			if (lengthCheck(X, conSize.width)) { //checking a double character for a vertical limit
				saveSymbol1 = s1.print();
				saveSymbol2 = s2.print();
				setColor(0, 15);
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
				setColor(0, 15);
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
		else  {
			if (lengthCheck(X - lengthLine, conSize.width)) { //checking the last single character for a vertical limit
				gotoXY(X - lengthLine, Y);
				printf("%c", ' ');
			}
		}
	
		X++;
		N++;

		return 0;
	}