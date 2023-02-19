#include "Manager.h";

using namespace std;

Manager::Manager() {
	conSize = s.getConsoleSize();
}


	void Manager::enteringParam(string text, int& val) {
		cout << text << endl;
		cin >> val;
		if (val < 1 || val > 30)
			throw "Error";
	}
	void Manager::enteringParam(string text, char& val) {
		cout << text << endl;
		cin >> val;
		if (val != 'Y' && val != 'y' && val != 'N' && val != 'n')
			throw "Error";
	}
	void Manager::enteringParamExp(string text, int& val) {
		cout << text << endl;
		cin >> val;
		if (val < 1 || val > 10) {
			throw "Error";
		}
	}
	void Manager::comparisonRad(int maxRadius, int minRadius) {
		if (maxRadius < minRadius) {
			throw "Error";
		}
	}
	void Manager::enteringParamExpProb(string text, int& val) {
		cout << text << endl;
		cin >> val;
		if (val < 1 || val > 1000) {
			throw "Error";
		}
	}
	void Manager::startWorking() {
		bool flag = false;
		while (!flag) {
			flag = printParam();
		}
		linesOutput();
	}
	bool Manager::printParam() {

		s.setColor(0, 2);
		for (int i = 0; i < conSize.width; i++) {
			cout << "-";
		}
		cout << endl;
		s.gotoXY((conSize.width - 6) / 2, 1);
		cout << "Matrix" << endl;
		for (int i = 0; i < conSize.width; i++) {
			cout << "-";
		}

		try {
			enteringParam("������� ������� ��������� ����� (�� 1 �� 30)", frequencyLines);
			enteringParam("������� �������� ����� (�� 1 �� 30)", speedLine);
			enteringParam("������� ����� ����� (�� 1 �� 30)", lengthLine);
			enteringParam("����� ��������� ���/���� (Y/N)", epilepsyMode);
			enteringParamExpProb("����������� ������ (�� 1 �� 1000)", probabilityExplosion);
			enteringParamExp("����������� ������ ������", minRadius);
			enteringParamExp("������������ ������ ������", maxRadius);
			comparisonRad(maxRadius, minRadius);
			system("cls");
			return true;

		}
		catch (...) {
			cout << "������ ����� ����������" << endl;
			system("pause");
			system("cls");
			return false;
		}
	}
	
	void Manager::linesOutput() {
		Figure* expl = 0;
		int checkingPoint = clock() + 1000;
		bool stop = 0;

		while (true) {
			if (clock() >= checkingPoint) {
				for (int i = 0; i < frequencyLines; i++) {
					Figure* f = new Line(lengthLine, speedLine, epilepsyMode, probabilityExplosion, maxRadius, minRadius);
					Varr.pushBack(f);
				}
				checkingPoint += 1000;
			}

			for (int i = 0; i < Varr.sizeVector(); i++) {
				if (Varr[i]->getNextStepTime() <= clock()) {
					expl = Varr[i]->draw();
					stop = Varr[i]->isForDelition();
					if (expl != NULL) {
						Varr.pushBack(expl);
					}
					if (stop) {
						Varr.erase(i + Varr.begin());
					}
				}
			}
		}
	}