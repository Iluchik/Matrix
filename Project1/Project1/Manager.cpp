#include "Manager.h";

using namespace std;

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
	void Manager::startWorking() {
		bool flag = false;
		while (!flag) {
			flag = printParam();
		}
		linesOutput();
	}
	bool Manager::printParam() {

		setColor(0, 2);
		for (int i = 0; i < getWidth(); i++) {
			cout << "-";
		}
		cout << endl;
		gotoXY((getWidth() - 6) / 2, 1);
		cout << "Matrix" << endl;
		for (int i = 0; i < getWidth(); i++) {
			cout << "-";
		}

		try {
			enteringParam("������� ������� ��������� ����� (�� 1 �� 30)", frequencyLines);
			enteringParam("������� �������� ����� (�� 1 �� 30)", speedLine);
			enteringParam("������� ����� ����� (�� 1 �� 30)", lengthLine);
			enteringParam("����� ��������� ���/���� (Y/N)", epilepsyMode);
			system("cls");
			return true;

		}
		catch (...) {
			cout << "������ ����� ����������" << endl;
			system("pause");
			system("cls");
			return false;
		}

		int X;
		int Y;

	}


	vector<int> Manager::randomTime() {
		int timePoint = 0;
		int offset = 0;
		vector <int> arrayPoints;
		vector <int> spawnPoints;
		int segment;
		spawnPoints.clear();
		
		for (int i = 0; i < frequencyLines - 1; i++) {
			timePoint = rand() % 1000;
			arrayPoints.push_back(timePoint);
		}

		sort(arrayPoints.begin(), arrayPoints.end());
		arrayPoints.insert(arrayPoints.begin(), 0);
		arrayPoints.push_back(1000);

		for (int i = 0; i < frequencyLines; i++) {
			offset = arrayPoints[i];
			if (i < frequencyLines) {
				segment = arrayPoints[i + 1] - arrayPoints[i];
				spawnPoints.push_back(rand() % (segment + 1) + offset);
			}
			
		}
		return spawnPoints;
	}

	void Manager::linesOutput() {
		vector <Line*> arr;
		vector <int> timeOffset;
		int stop = 0;
		int newTime = 0;
		oneSecondTime = clock() + 1000;
		while (true) {
			if (clock() >= oneSecondTime) {
				timeOffset = randomTime();
				for (int i = 0; i < frequencyLines; i++) {
					Line* l = new Line();
					arr.push_back(l);
					l->setNextStepTime(clock() + timeOffset[i]);
					l->setY(rand() % (getHeight() - 1) + 1);
				}
				Sleep(10);
				oneSecondTime += 1000;
			}

			for (int i = 0; i < arr.size(); i++) {

				stop = 0;
				if (arr[i]->getNextStepTime() <= clock()) {
					stop = arr[i]->moveLine(lengthLine, epilepsyMode);
					newTime = arr[i]->getNextStepTime() + 1000 / speedLine;
					arr[i]->setNextStepTime(newTime);
					if (stop == 1) {
						arr.erase(i + arr.begin());
					}
				}
			}
		}
	}